import sys
caffe_root = '/home/aclass/dl/caffe/caffe/'
sys.path.append(caffe_root+'python')
sys.path.append('/usr/lib/python2.7/dist-packages')
import caffe


model_file = caffe_root+'/models/bvlc_reference_caffenet/deploy.prototxt'
pretrained= '/home/aclass/dl/modles/bvlc_reference_caffenet.caffemodel'
image_file = '/home/aclass/dl/test/images/cat.jpg'
npload = caffe_root+ 'python/caffe/imagenet/ilsvrc_2012_mean.npy'

net = caffe.Classifier(model_file, pretrained,channel_swap=(2,1,0),raw_scale=255,image_dims=(256, 256))
net.set_phase_test()
net.set_mode_cpu()
input_image = caffe.io.load_image(image_file)
#<span style="color:#FF0000;">
prediction = net.predict([input_image])  # predict takes any number of images, and formats them for the Caffe net automatically
print 'prediction shape:', prediction[0].shape
print 'predicted class:', prediction[0].argmax()

prediction = net.predict([input_image], oversample=False)
print 'prediction shape:', prediction[0].shape
print 'predicted class:', prediction[0].argmax()
