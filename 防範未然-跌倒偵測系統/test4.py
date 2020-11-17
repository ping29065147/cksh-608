import cv2
import math
import sys
import numpy as np
#!/usr/bin/python

len = len(sys.argv)
print len
if len != 4:
    print "Uasge: program image_file1 image_file2 fileno"
    sys.exit()
else :
    f1 = sys.argv[1]
    f2 = sys.argv[2]
    f3 = sys.argv[3]

print f3

imgFirst = cv2.imread("/home/pi/s00.jpg",0)
imgtwo = cv2.imread("/home/pi/s31.jpg",1)

#imgFirst = cv2.resize(i1, None, fx=0.4, fy=0.4, interpolation=cv2.INTER_CUBIC)
#imgtwo = cv2.resize(i2, None, fx=0.4, fy=0.4, interpolation=cv2.INTER_CUBIC)
imgSecond = cv2.cvtColor(imgtwo, cv2.COLOR_BGR2GRAY)

result = cv2.absdiff(imgFirst,imgSecond)
cv2.imshow('a',result)

#et, result = cv2.threshold(result, 40, 255, cv2.THRESH_BINARY)
#cv2.imshow('b',result)

rows,cols = result.shape[:2]
kernel_5x5=np.ones((10,10),np.float32)/100.0
img2 = cv2.filter2D(result, -1, kernel_5x5)
#cv2.imshow('c',img2)
#blurred = cv2.GaussianBlur(result, (11,11),0)
#binaryIMG = cv2.Canny(blurred, 20, 160)
median = cv2.medianBlur(img2,5)

ret, result = cv2.threshold(median, 70, 255, cv2.THRESH_BINARY)
cv2.imshow('d',result)

matrix = np.ones((5,5),np.uint8)
eff = cv2.dilate(result, matrix, iterations = 7)
erosion=cv2.erode(eff, matrix, iterations = 5)

(cnts,_) = cv2.findContours(erosion.copy(),cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

clone = imgtwo.copy()

#cv2.drawContours(clone, cnts, -1, (0,255,0),3)

#aff = eff

spot = [[0 for i in range(4)] for j in range(10)]
idx = 0

for c in cnts:

	x, y, w, h = cv2.boundingRect(c)
	cv2.rectangle(clone, (x , y), (x + w, y + h), (0, 255, 0), 2)

	spot[idx][0] = x
	spot[idx][1] = y
	spot[idx][2] = w
	spot[idx][3] = h
	idx = idx + 1

	#cv2.drawcontours(imgtwo, contours)
	print "x = ",x
	print "y = ",y
	print "w = ",w
	print "h = ",h
	i = (h*1.0/w)
	#j = (w*1.0/h)
	print "h/w = ",i
	#print "j = ",j
	for times in range(0,3,1) :
		if i < 0.8 :
			print "be careful!"
		else :
			print "no"

#print "idx:", idx
filename = "foo.txt" + str(f3)
print filename
fo = open(filename, "w")

for i in range(idx) :
	for j in range(4) :
	   fo.write('{:03d} '.format(spot[i][j]))
	   print spot[i][j]
"""	   
	print "x", i, ":", spot[i][0]
	print "y", i, ":", spot[i][1]
	print "w", i, ":", spot[i][2]
	print "h", i, ":", spot[i][3]
"""

fo.close()
	
cv2.imshow('clone',clone)
#cv2.imshow('R',imgFirst)
cv2.waitKey(0)
cv2.waitKey(0)
cv2.waitKey(0)
#cv2.destroyAllWindows()


