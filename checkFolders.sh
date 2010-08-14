#!/bin/bash
FOLDERS="/usr/class/cs143 /usr/class/cs143/sub*/pp2/mfranci1-2 /usr/class/cs143/sub*/pp3/mfranci1-4 /usr/class/cs143/sub* /usr/class/cs143/sub*/pp2 /usr/class/cs143/sub*/pp3 /usr/class/cs143/sub*/pp4 /usr/class/cs143/sub*/pp3check /usr/class/cs143/WWW /usr/class/cs143/WWW/handouts /usr/class/cs143/WWW/grades /usr/class/cs143/assi* /usr/class/cs106b/WWW/handouts /afs/ir.stanford.edu/users/m/f/mfranci1/public"
EMAIL='3104833831@txt.att.net'
WORKIN='/tmp/mfranci1-script'
CURRENTDIR=`pwd`
BODY=''
NL=`echo -e "\n"`


if [ ! -d $WORKIN ]
then
    mkdir $WORKIN
fi
cd $WORKIN



for (( ;; ))
do
echo "checking folders at `date`"
BODY=''
for FOLDER in $FOLDERS
do
    FILE=`echo $FOLDER | awk '{gsub(/\//, ".", $0); gsub(/\*/, "", $0); print "list" $0}'`
    ls -1 "$FOLDER" >& test.out
    OUTPUT=`diff -wN $FILE test.out`
    if [ -n "$OUTPUT" ]
    then
	BODY="$BODY $NL
$FOLDER $OUTPUT"
	rm -f "$FILE"
	mv test.out "$FILE"
    else
	rm -f test.out
    fi
done

if [ -n "$BODY" ]
then
    echo "$BODY"
    echo "$BODY" | mail -s "Files Change" $EMAIL
fi

chmod 666 *
touch *

sleep 300

done
