#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Illegal number of arguments provided"
	echo "Example of running script: ./runServer 0.0.0.0 1234"
else
	# path to the where server code and index.php exists
	cd /home/nima/Documents/e/embedded-sys/project/server/build/bin

	# first run php server on port 1234 (make sure this port is available, otherwise must be changed)
	# php -S localhost:1234>/dev/null 2>&1 &

	# then run my server
	./server $1 $2 . 10 block
fi

