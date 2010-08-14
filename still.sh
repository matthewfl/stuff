#!/bin/bash

EMAIL='spam@matthewfl.com'

while [ true ]
do
	SUB="Still here "
	D=`date`
	SUB=`echo $SUB $D`
	echo $SUB
	date | mail -s "$SUB" "$EMAIL"
	sleep 21600
done
