#include <stdio.h>  // for snprintf
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "boost/algorithm/string.hpp"
#include "google/protobuf/text_format.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/net.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/io.hpp"
#include "caffe/vision_layers.hpp"

using namespace caffe;  // NOLINT(build/namespaces)

template<typename Dtype>
int feature_extraction_pipeline(int argc, char** argv);

int main(int argc, char** argv) {
  return feature_extraction_pipeline<float>(argc, argv);
//  return feature_extraction_pipeline<double>(argc, argv);
}

template<typename Dtype>
class writeDb
{
public:
	void open(string dbName)
	{
		db.open(dbName.c_str());
	}
	void write(const Dtype &data)
	{
		db<<data;
	}
	void write(const string &str)
	{
		db<<str;
	}
	virtual ~writeDb()
	{
		db.close();
	}
private:
	std::ofstream db;
};

template<typename Dtype>
int feature_extraction_pipeline(int argc, char** argv) {
  ::google::InitGoogleLogging(argv[0]);
  const int num_required_args = 6;
  if (argc < num_required_args) {
    LOG(ERROR)<<
    "This program takes in a trained network and an input data layer, and then"
    " extract features of the input data produced by the net.\n"
    "Usage: extract_features  pretrained_net_param"
    "  feature_extraction_proto_file  extract_feature_blob_name1[,name2,...]"
    "  save_feature_leveldb_name1[,name2,...]  img_path  [CPU/GPU]"
    "  [DEVICE_ID=0]\n"
    "Note: you can extract multiple features in one pass by specifying"
    " multiple feature blob names and leveldb names seperated by ','."
    " The names cannot contain white space characters and the number of blobs"
    " and leveldbs must be equal.";
    return 1;
  }
  int arg_pos = num_required_args;

  arg_pos = num_required_args;
  if (argc > arg_pos && strcmp(argv[arg_pos], "GPU") == 0) {
    LOG(ERROR)<< "Using GPU";
    uint device_id = 0;
    if (argc > arg_pos + 1) {
      device_id = atoi(argv[arg_pos + 1]);
      CHECK_GE(device_id, 0);
    }
    LOG(ERROR) << "Using Device_id=" << device_id;
    Caffe::SetDevice(device_id);
    Caffe::set_mode(Caffe::GPU);
  } else {
    LOG(ERROR) << "Using CPU";
    Caffe::set_mode(Caffe::CPU);
  }
  Caffe::set_phase(Caffe::TEST);

  arg_pos = 0;  // the name of the executable
  string pretrained_binary_proto(argv[++arg_pos]);//网络模型参数文件

  string feature_extraction_proto(argv[++arg_pos]);

  shared_ptr<Net<Dtype> > feature_extraction_net(
      new Net<Dtype>(feature_extraction_proto));

  feature_extraction_net->CopyTrainedLayersFrom(pretrained_binary_proto);//将网络参数load进内存


  string extract_feature_blob_names(argv[++arg_pos]);
  vector<string> blob_names;//要抽取特征的layer的名字，可以是多个
  boost::split(blob_names, extract_feature_blob_names, boost::is_any_of(","));

  string save_feature_leveldb_names(argv[++arg_pos]);
  vector<string> leveldb_names;// 这里我改写成一个levedb为一个文件，数据格式不使用真正的levedb，而是自定义
  boost::split(leveldb_names, save_feature_leveldb_names,
               boost::is_any_of(","));
  CHECK_EQ(blob_names.size(), leveldb_names.size()) <<
      " the number of blob names and leveldb names must be equal";
  size_t num_features = blob_names.size();

  for (size_t i = 0; i < num_features; i++) {
    CHECK(feature_extraction_net->has_blob(blob_names[i]))  //检测blob的名字在网络中是否存在
        << "Unknown feature blob name " << blob_names[i]
        << " in the network " << feature_extraction_proto;
  }


  vector<shared_ptr<writeDb<Dtype> > > feature_dbs;
  for (size_t i = 0; i < num_features; ++i) //打开db，准备写入数据
  {
    LOG(INFO)<< "Opening db " << leveldb_names[i];
    writeDb<Dtype>* db = new writeDb<Dtype>();
    db->open(leveldb_names[i]);
    feature_dbs.push_back(shared_ptr<writeDb<Dtype> >(db));
  }



  LOG(ERROR)<< "Extacting Features";

  const shared_ptr<Layer<Dtype> > layer = feature_extraction_net->layer_by_name("data");//获取第一层
  MyImageDataLayer<Dtype>* my_layer = (MyImageDataLayer<Dtype>*)layer.get();
  my_layer->setImgPath(argv[++arg_pos],1);//"/media/G/imageset/clothing/针织衫/针织衫_1.jpg"
  //设置图片路径

  vector<Blob<float>*> input_vec;
  vector<int> image_indices(num_features, 0);
  int num_mini_batches = 1;//atoi(argv[++arg_pos]);//共多少次迭代。  每次迭代的数量在prototxt用batchsize指定
  for (int batch_index = 0; batch_index < num_mini_batches; ++batch_index) //共num_mini_batches次迭代
  {
    feature_extraction_net->Forward(input_vec);//一次正向传播
    for (int i = 0; i < num_features; ++i) //多层特征
    {
      const shared_ptr<Blob<Dtype> > feature_blob = feature_extraction_net
          ->blob_by_name(blob_names[i]);
      int batch_size = feature_blob->num();
      int dim_features = feature_blob->count() / batch_size;

      Dtype* feature_blob_data;

      for (int n = 0; n < batch_size; ++n)
      {
        feature_blob_data = feature_blob->mutable_cpu_data() +
            feature_blob->offset(n);
        feature_dbs[i]->write("3 ");
        for (int d = 0; d < dim_features; ++d)
        {
          feature_dbs[i]->write((Dtype)(d+1));
          feature_dbs[i]->write(":");
          feature_dbs[i]->write(feature_blob_data[d]);
          feature_dbs[i]->write(" ");
        }
        feature_dbs[i]->write("\n");

      }  // for (int n = 0; n < batch_size; ++n)
    }  // for (int i = 0; i < num_features; ++i)
  }  // for (int batch_index = 0; batch_index < num_mini_batches; ++batch_index)


  LOG(ERROR)<< "Successfully extracted the features!";
  return 0;
}

