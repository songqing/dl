#%matplotlib inline
import matplotlib
import numpy as np
import matplotlib.pyplot as plt
#%matplotlib inline

# Make sure that caffe is on the python path:
caffe_root = '/home/songqing/dl/caffe/'  # this file is expected to be in {caffe_root}/examples
import sys
sys.path.insert(0, caffe_root + 'python')
sys.path.append('/usr/lib/python2.7/dist-packages')

import caffe

filename='0'
piccount=0
counttemp=0
# Set the right path to your model definition file, pretrained model weights,
# and the image you would like to classify.
MODEL_FILE = caffe_root+'examples/mnist/lenet.prototxt'
PRETRAINED = '/home/songqing/dl/caffe/examples/mnist/zsq1_lenet_iter_1000.caffemodel'
def classifynum():
	global piccount
	counttemp=piccount
	piccount=piccount+1
	filename='0'
	if counttemp< 10:
		filename=filename+'00'+str(counttemp)
	elif counttemp < 100:
		filename=filename+'0'+str(counttemp)
	else:
		filename=filename+str(counttemp)

	IMAGE_FILE = '/home/songqing/dl/dl/phone/phonenum_recognition/BMP7/testpic/pic'+filename+'.bmp'
#IMAGE_FILE = '/home/songqing/dl/dl/task/task1/imdata/3_0005.bmp'

	caffe.set_phase_test()
	caffe.set_mode_cpu()
	net = caffe.Classifier(MODEL_FILE, PRETRAINED)
#                       mean=np.load(caffe_root + 'python/caffe/imagenet/ilsvrc_2012_mean.npy'),
#							channel_swap=(2,1,0),
#                      raw_scale=28,
#                       image_dims=(28, 28))
	input_image = caffe.io.load_image(IMAGE_FILE,color=False)
#plt.imshow(input_image)
	prediction=net.predict([input_image],oversample=False)
	nummax=prediction[0].argmax()
	print 'prediction shape:', prediction[0].shape
#plt.plot(prediction[0])
	print 'predicted class:', prediction[0].argmax()
	print 'predicted class:', prediction[0][nummax]
	print 'predicted class:', prediction[0]
	outfile.write(str(nummax)+' '+str(prediction[0][nummax])+'\n')

#%timeit net.predict([input_image])

# Resize the image to the standard (256, 256) and oversample net input sized crops.
	input_oversampled = caffe.io.oversample([caffe.io.resize_image(input_image, net.image_dims)], net.crop_dims)
# 'data' is the input blob name in the model definition, so we preprocess for that input.
	caffe_input = np.asarray([net.preprocess('data', in_) for in_ in input_oversampled])
# forward() takes keyword args for the input blobs with preprocessed input arrays.
#%timeit net.forward(data=caffe_input)
# Full pipeline timing.
#%timeit net.predict([input_image])

# Forward pass timing.
#%timeit net.forward(data=caffe_input)
if __name__ == '__main__':
	piccount=0
	outfile=open('smallpic.txt','w')
	for i in range(1,118):
		classifynum()
	outfile.close()
