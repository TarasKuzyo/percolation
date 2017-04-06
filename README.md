# Percolation
The site percolation code on two dimensional grid


### Description

The code implements [site percolation problem](https://en.wikipedia.org/wiki/Percolation_theory) 
on 2D rectangular grid of cells (or "sites"). 

A site is "occupied" with probability `p` or "empty" with probability `1 - p` and 
those probabilities are assumed to be independent for all cells. The question of the problem is: 
for a given `p`, what is the probability that an open path exists between top and bottom?
According to the theory there exists a critical `p` below which the probability is always 0 
and above which the probability is always 1. For 2D site percolation the critical value of `p` is close to 0.6.

The program generates a grid of cells for the site vacancy probability `p` and creates a percolation flow
from top to bottom. The output can be visualized with grid image.
[Cairo graphics library](https://www.cairographics.org) is used for generation .svg and .png output images.


### Compilation and usage

Provided cairo is installed the project can be compiled with `makefile`
which creates the `percolation` executable.

The program takes 3 mandatory command line arguments:
* grid width
* grid height
* site vacancy probability (floating point value in 0..1 range). 

Optionally one can set the output file paraneters (name, type, maximum image size) and color scheme used.

By default the output is written to the .png image called `'output_ww_hh_pp.png'` with
the maximum size of 800px where `ww` and `hh` are grid width and height respectfully, 
and `pp` is site vacancy probability.


### Command line options

       -w, --width                                   
           grid width (mandatory)                              
                                                     
       -h, --height                                  
           grid height (mandatory)                             
                                                     
       -p, --probability                             
           site vacancy probability (mandatory)            
                                                     
       -o, --output                                  
           output image file (either .png or .svg format)     
                                                     
       -s, --size                                    
           maximum image size (useful for large grids)                      
                                                     
       -c, --color                                   
           color for the full sites in form '#rrggbb'
           or as a lookup table index                
                                                     
       -l, --list-colors                             
           dispalys a list of predefined colors and  
           their indices (an argument for -c option) 
                                                     
       -r, --recursive                               
           enable recursive flow propagation 
           (might cause stack overflow on large grids)     
                                                     
       -O, --no-output                               
           disable image output                      
                                                     
       --help                                        
           display this help and exit                


### Sample runs

./percolation -w 50 -h 50 -p 0.6 -o flow.svg

Create a 50x50 grid with site vacancy probability p = 0.6 and 
save the output image in flow.svg


./percolation -w 50 -h 50 -p 0.5 --recursive

Run recursive propagation on 50x50 grid with p = 0.5


./percolation --width 2048 --height 2048 --probability 0.65 --size 800 --output flow_large.png

Create 2048x2048 grid with p=0.65 and save the output to the image flow_large.png wit maximum size 800px


./percolation -w 400 -h 200 -p 0.45 -c 2

Run on 400x200 grid with p = 0.45 and fill percolated cells with custom from the colortable.


./percolation -w 400 -h 200 -p 0.45 -c #ff22ee

Run on 400x200 grid with p = 0.45 and fill percolated cells with custom hex color.


### TODO

* [x]     add colors to color map
* [x]     set color from command line
* [x]     parse color ~~both as enum and int~~ as hex
* [ ]     make README more complrehensive
* [ ]     add pdf output


### Sample images

<a><img src="data/img_p40.png" align="left"  height="320" alt="p = 0.4" ></a>
<a><img src="data/img_p50.png" align="right" height="320" alt="p = 0.5" ></a>
<a><img src="data/img_p60.png" align="left"  height="320" alt="p = 0.6" ></a>
<a><img src="data/img_p70.png" align="right" height="320" alt="p = 0.7" ></a>



