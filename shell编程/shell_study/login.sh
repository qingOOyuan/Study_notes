#! /bin/sh 

echo "Enter password:"

COUNTER=0

read TRY

while [ "$TRY" != "000000" -a "$COUNTER" -lt 3 ]; do

       echo "Sorry, try again"

       COUNTER=$(($COUNTER+1))

       read TRY

done
