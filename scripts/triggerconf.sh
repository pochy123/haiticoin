#!/bin/bash -ev

mkdir -p ~/.trigger
echo "rpcuser=username" >>~/.trigger/trigger.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.trigger/trigger.conf

