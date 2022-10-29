#!/bin/bash
rt_dir="$1"
fn="${rt_dir}/$2"
if [ -f "$fn" ] 
then
	exit
else
	cat > $fn
fi
