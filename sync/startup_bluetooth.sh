#!/bin/bash

echo "welcome"

#sudo bluetoothctl

#set the bluetooth discoverable on and pairable on 
echo -e 'discoverable on\npairable on\nshow \nquit' | sudo bluetoothctl
