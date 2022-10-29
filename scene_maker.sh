#!/bin/bash

## colors
white='255,255,255'
grey='128,128,128'
red='255,0,0'
green='0,255,0'
blue='0,0,255'
redish='255,128,128'
greenish='128,255,128'
blueish='128,128,255'
cyan='0,255,255'
magenta='255,0,255'
yellow='255,255,0'
cyanish='128,255,255'
magentaish='255,128,255'
yellowish='255,255,128'
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
matte='0.75 0.15 0.1'
polish='0.5 0.35 0.15'
shiny='0.35 0.2 0.45'
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
	echo `bc <<< "scale = 5; $2 / sqrt(($1 * $1) + 1)"` 
}

# cn_hyp(s, ht) print the hypothenus of a cone with slope 's' and height 'ht'
cn_hyp ()
{
	echo `bc <<< "scale = 5; $2 * sqrt(($1 * $1) + 1)"` 
}

## vectors
zero='0,0,0'
x='1,0,0'
y='0,1,0'
z='0,0,1'
negx='-1,0,0'
negy='0,-1,0'
negz='0,0,-1'

unit ()
{
	echo $(bc << COMPUTATION
scale = 5;
hyp = sqrt( $1 * $1 + $2 * $2 + $3 * $3 );
$1 / hyp;
$2 / hyp;
$3 / hyp;
COMPUTATION
	) | awk '{printf "%.5f,%.5f,%.5f", $1, $2, $3}'
}


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
replace_rt='./replace_rt.sh' # useful for debug

$new_rt mirror.rt << SCENE 
A	0.15	$white
C	6,-6,0	`unit -1 1 0`	70

L	1,-1,3	3		$white	

pl	-2,0,0  $x		$blue		$mirror 0
pl	0,2,0	$negy	$white		$shiny	1
sp	$zero	2		$raspberry 	$shiny 0
SCENE

$new_rt lampshade.rt << SCENE
A	0.3		$white
C	0,-10,0 `unit -1 4 -1` 	70
L	-1,0,-1	6	$yellowish
# adding this light allows the cone to not look flat
L	0,0,30  20  $blueish
cn  $zero `unit -1 -0.4 -1` 1 2 	$purple $shiny 0
pl  0,0,-3 $z 						$grey $polish 1
SCENE

bonus="0.5 0.2 0.3 0 xpm_height_maps/rough_stripes.xpm $pi"
$new_rt cn_sp_cy.rt << SCENE
A 0.15			$white
C 0,-10,0		0,1,0           70
L 0,0,3         2.5             $white
# test comment

cn	-2.5,0,0    0,0,-1   0.5 `cn_ht 0.5 $pi`   255,0,128 $bonus
sp	0,0,0           2              			   190,255,0 $bonus
cy	2.5,0,0  	 0,0,1  2   3    			   64,0,255 $bonus

SCENE

$new_rt spheres.rt << SCENE
A	0.10			$white
C	7.5,-4.5,0		`unit -1 1 0`	55
L	5,2,0		6	$yellowish
sp	0,3,0		2	$turquoise $matte
sp	-4.5,3,0	6	$orange	$polish
sp	0,4,1.5		1.6	$purple	$polish
SCENE

$new_rt bicolor.rt << SCENE
A	0.2			$white
C	0,-8,0		$y	55
L	-3.5,-1,0	8	$orange
L	3.5,-1,0	8	$turquoise
sp	-1.5,1,-1	2	0,50,255	$shiny
sp	1.5,1,-1	2	$white 		$matte 1
pl	0,4,0		$y	$grey		$shiny 0
pl	0,0,-2		$z	$white		$matte 1
SCENE


