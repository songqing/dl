#%matplotlib inline
import os
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
PRETRAINED = '/home/songqing/dl/caffe/examples/mnist/zsqequal_lenet_iter_10000.caffemodel'
def classifynum(iternum):
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
	if(os.path.isfile(IMAGE_FILE) == False):
		return
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
	#print 'prediction shape:', prediction[0].shape
#plt.plot(prediction[0])
	#print 'predicted class:', prediction[0].argmax()
	#print 'predicted class:', prediction[0][nummax]
	#print 'predicted class:', prediction[0]
	if(prediction[0][nummax]<0.978):
		prediction[0][nummax]=0
	elif((len(finallist)==0)):
		finallist.append(nummax)
		ratelist.append(prediction[0][nummax])
		poslist.append(iternum)
	elif(iternum - poslist[-1]<=5 and prediction[0][nummax] > ratelist[-1]):
		if(len(finallist)>1):
			if(iternum-poslist[-2] < 14):
				if(nummax==1):
					if(prediction[0][nummax] > 0.999):
						finallist[-1]=nummax
						ratelist[-1]=prediction[0][nummax]
						poslist[-1]=iternum
				else:
					finallist[-1]=nummax
					ratelist[-1]=prediction[0][nummax]
					poslist[-1]=iternum
		else:
			finallist[-1]=nummax
			ratelist[-1]=prediction[0][nummax]
			poslist[-1]=iternum
	elif((iternum-poslist[-1])>4 and len(finallist) < 11):
		if(nummax==1):
			if(prediction[0][nummax] > 0.999):
				finallist.append(nummax)
				ratelist.append(prediction[0][nummax])
				poslist.append(iternum)
		else:
			finallist.append(nummax)
			ratelist.append(prediction[0][nummax])
			poslist.append(iternum)
	outfile.write(str(nummax)+' '+str(prediction[0][nummax])+'\n')

#%timeit net.predict([input_image])

# Resize the image to the standard (256, 256) and oversample net input sized crops.
	input_oversampled = caffe.io.oversample([caffe.io.resize_image(input_image, net.image_dims)], net.crop_dims)
# 'data' is the input blob name in the model definition, so we preprocess for that input.
	caffe_input = np.asarray([net.preprocess('data', in_) for in_ in input_oversampled])
# forward() takes keyword args for the input blobs with preprocessed input arrays.
#%timeit net.forward(data=caffe_input)
if __name__ == '__main__':
	piccount=0
	finallist=[]
	poslist=[]
	ratelist=[]
	outfile=open('smallpic.txt','w')
	for i in range(1,130):
		classifynum(i)
	outfile.close()
	print finallist
	print ratelist
	print poslist

