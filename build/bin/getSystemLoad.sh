#!/bin/bash

while [ 1 ]
do
	# get average load
	lavg=$(cat /proc/loadavg | awk '{print $1}')
	# publish data to broker
	sleep 1
done
