#!/bin/bash

while [ 1 ]
do
	# record sound from microphone
	arecord -f S16_LE -d 1 ./audio.wav 1>/dev/null 2>&1
	# extract volume with sox
	sox -t .wav ./audio.wav -n stat 2> data.txt
	sound_lvl=$(grep "Maximum amplitude" data.txt | awk '{print $3}')
	if (( $(echo "$sound_lvl > 0.7" |bc -l) )); then
		echo "Threshold violated!, $sound_lvl"
		# insert data to database
		mysql -u test -p123456 -h "localhost" -D "sensors" -e "INSERT INTO sound (amplitude) VALUES ($sound_lvl)"
	else
		echo "Okay!, $sound_lvl"
	fi
done
