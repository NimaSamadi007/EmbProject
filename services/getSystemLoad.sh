#!/bin/bash

while [ 1 ]
do
	# get average load
	lavg=$(cat /proc/loadavg | awk '{print $1}')
	# publish data to broker
	mosquitto_pub -h localhost -t sensors/load -m "$lavg" -u load -P 12345678 -q 2
	# you can comment out the following line to control 
	# duration of message pulishes
	# sleep 1
done
