#!/bin/bash

for j in {1..3}
do
	for i in {90..150}
	do
	        sleep 0.09
	        echo "$(cat dummy.rt | head -11)" > dummy.rt
	        echo "C  0,0,0  0,0,1  $i" >> dummy.rt
	        ../minirt dummy.rt&
	done

	sleep 1

	for i in {1..70}
	do 
	   kill -13 "$(pgrep minirt | tail -1)" 
	    sleep 0.09
	done
done