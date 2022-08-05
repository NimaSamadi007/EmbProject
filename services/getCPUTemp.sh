#!/bin/bash

while [ 1 ]
do
	cpu_temp=$(cat /sys/class/thermal/thermal_zone2/temp)
	cpu_temp=$(echo "scale=2; $cpu_temp / 1000" | bc -l)
	# publish CPU temp to broker
	mosquitto_pub -h localhost -t sensors/temp -m "$cpu_temp" -u temp -P 12345678 -q 2
	# you can comment out the following line to control 
	# duration of message pulishes
	# sleep 1
done

