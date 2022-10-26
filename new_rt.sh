#!/bin/bash
rt_dir='rt_scenes'
fn="${rt_dir}/$1"
if [ -f "$fn" ] 
then
	exit
else
	cat > $fn
fi
