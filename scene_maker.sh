#!/bin/bash

## colors
white='255,255,255'
grey='128,128,128'
red='255,0,0'
green='0,255,0'
blue='0,0,255'
cyan='0,255,255'
magenta='255,0,255'
yellow='255,255,0'
turquoise='0,128,255'
jade='0,255,128'
purple='128,0,255'
khaki='128,255,0'
pink='255,0,128'
orange='255,128,0'
raspberry='255,0,64'

## materials
diff_only='1 0 0' # default
spec_only='0 1 0'
refl_only='0 0 1'
matte='0.7 0.2 0.1'
polish='0.5 0.35 0.15'
shiny='0.4 0.35 0.25'
mirror='0.1 0.05 0.85'

## math
pi='3.1416'

# circumf(d) prints the radius of a circle with diameter r
circumf () 
{
	echo `bc <<< "scale = 5; $1 * $pi"`
}

# diam(c) prints the diameter of a circle with circumference c 
diam ()
{
	echo `bc <<< "scale = 5; $1 / $pi"`
}

# cn_ht(s, hyp) print the height of a cone with slope 's' and hypothenus 'hyp'
cn_ht () 
{
	echo `bc <<< "scale = 5; sqrt(($2 * $2) - ($1 * $1))"` 
}

# cn_hyp(s, ht) print the hypothenus of a cone with slope 's' and height 'ht'
cn_hyp ()
{
	echo `bc <<< "scale = 5; sqrt(($2 * $2) + ($1 * $1))"` 
}

inv_sqrt ()
{
	echo `bc <<< "scale = 5; 1 / sqrt($1)"`
}

## vectors
zero='0,0,0'
x='1,0,0'
y='0,1,0'
z='0,0,1'
negx='-1,0,0'
negy='0,-1,0'
negz='0,0,-1'

## dirs
xpm_dir='xpm_height_maps'
rt_dir='rt_scenes'

## allowed lines
# arg within [] are optional
# ambient light:
#	A intensity color [noflare]
# camera:
#	C pos dir fov_deg
# light :
#	L pos intensity color
# shape :
# 	<shape_id> <shape_param> color [coefs checker bump_map map_height] 
# where <shape_id> <shape_param> can have the forms:
# sphere :
#	sp center diameter
# plane :
# 	pl point normal
# cylinder :
#	cy pos dir height diameter (where pos is the center of one face)
# cone:
#	cn vertex dir cone_height slope (where slope * point_height = radius for all
#	points)

## scenes
new_rt='./new_rt.sh'
$new_rt mirror.rt << HD 
A	0.2		$white
C	6,-6,0	-`inv_sqrt 2`,`inv_sqrt 2`,0	70
L	1,-1,3	0.75	$white	
pl	-2,0,0  $x		$blue		$mirror 0
pl	0,2,0	$negy	$white		$polish	1
sp	$zero	2		$raspberry 	$shiny 0
HD

