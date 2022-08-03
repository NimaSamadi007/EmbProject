#!/bin/bash

while [ 1 ]
do
	# get average load
	lavg=$(cat /proc/loadavg | awk '{print $1}')
	# publish data to broker
	mosquitto_pub -h localhost -t sensors/load -m "$lavg" -u load -P 12345678 -q 2
	sleep 1
done
