#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Illegal number of arguments provided"
	echo "Example of running script: ./runServer 0.0.0.0 1234"
else
	# path to the where server code and index.php exists
	cd /home/nima/Documents/e/embedded-sys/project/server/build/bin

	#run server
	./server $1 $2 . 10 block
fi

