#!/bin/bash

a=1

while [ ! -e "$f1" ]
do
	sleep 2
	DATE1=$(date "+%Y-%m-%d_%H:%M:%S")
	#fswebcam -r 352*288 --no-banner /home/pi/output/img_$DATE1.jpg
	fswebcam -r 1280*960 --no-banner /home/pi/output/img_$DATE1.jpg
	f1="/home/pi/output/img_$DATE1.jpg"
done

sleep 2
	

while [ ! -e "$f2" ]
do
	sleep 2
	DATE2=$(date "+%Y-%m-%d_%H:%M:%S")
	#fswebcam -r 352*288 --no-banner /home/pi/output/img_$DATE2.jpg
	fswebcam -r 1280*960 --no-banner /home/pi/output/img_$DATE2.jpg
	f2="/home/pi/output/img_$DATE2.jpg"
done
	
python /home/pi/test4.py $f1 $f2 $a > /home/pi/result
cat /home/pi/result
#cat /home/pi/result | mail -s "be careful!!!" pinghe.yeh@gmail.com
#cat /home/pi/result | mail -s "be careful!!!" cys10107@gmail.com
a=$a+1

while [ 1 ]
do
	f1=$f2
	f2=""
	while [ ! -e "$f2" ]
	do
		sleep 2
		DATE2=$(date "+%Y-%m-%d_%H:%M:%S")
		#fswebcam -r 352*288 --no-banner /home/pi/output/img_$DATE2.jpg
		fswebcam -r 1280*960 --no-banner /home/pi/output/img_$DATE2.jpg
		f2="/home/pi/output/img_$DATE2.jpg"
	done

	python /home/pi/test4.py $f1 $f2 $a > /home/pi/result
	cat /home/pi/result
	
	a=$a+1
	if [$a == 5]
	then
		a=1
	fi	
done


