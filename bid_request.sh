#!/usr/bin/env sh

if [ $# -lt 4 ] ; then
    echo "$0 ENDPOINT_URL DATA_FILE JSON|PROTOBUF TRACE_FILE" 1>&2
    exit 1
fi

ENDPOINT=$1
DATA=$2
FORMAT=$3
TRACE=$4

if [ $FORMAT = "JSON" ] ; then
    cat $DATA | curl --verbose --trace-ascii ${TRACE} --trace-time --header "Content-Type: application/json" --header "Connection: keep-alive" --user-agent "FluctRTBbot/1.0(+http://fluct.jp)" --data @- $ENDPOINT
elif [ $FORMAT = "PROTOBUF" ] ; then
    cat $DATA | curl --verbose --trace-ascii ${TRACE} --trace-time --header "Content-Type: application/octet-stream" --header "Connection: keep-alive" --user-agent "FluctRTBbot/1.0(+http://fluct.jp)" --data-binary @- $ENDPOINT
else
    echo "Unknown format:" $FORMAT 1>&2
    exit 1
fi
