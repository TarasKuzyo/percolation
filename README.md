# Percolation
2D site percolation project.

[Percolation](https://en.wikipedia.org/wiki/Percolation_theory)

This program uses [Cairo graphics library](https://www.cairographics.org)
for generation .svg and .png output images.


### Command line options

       -w, --width                                   
           grid width                                
                                                     
       -h, --height                                  
           grid height                               
                                                     
       -p, --probability                             
           site vacancy probability                 
                                                     
       -o, --output                                  
           output image file (either .png or .svg format)     
                                                     
       -s, --size                                    
           maximum image size (useful for large grids)                      
                                                     
       -c, --color                                   
           color for the full sites in form '#rrggbb'
           or as a lookup table index                
                                                     
       -l, --list-colors                             
           dispalys a list of predefined colors and  
           their indexes (an argument for -c option) 
                                                     
       -r, --recursive                               
           enable recursive flow propagation 
           (might cause stack overflow on large grids)     
                                                     
       -O, --no-output                               
           disable image output                      
                                                     
       --help                                        
           display this help and exit                

### Compilation and usage

Provided cairo is installed the project can be compiled with make command
which creates percolation executtable


### Sample runs

./percolation -w 50 -h 50 -p 0.6 -o flow.svg

./percolation -w 50 -h 50 -p 0.5 --recursive

./percolation --width 2048 --height 2048 --probability 0.65 --size 800 --output flow_large.png

./percolation -w 400 -h 200 -p 0.45 -c 2

./percolation -w 400 -h 200 -p 0.45 -c #ff22ee


### Sample images

<a><img src="data/img_p40.png" align="left"  height="320" alt="p = 0.4" ></a>
<a><img src="data/img_p50.png" align="right" height="320" alt="p = 0.5" ></a>
<a><img src="data/img_p60.png" align="left"  height="320" alt="p = 0.6" ></a>
<a><img src="data/img_p70.png" align="right" height="320" alt="p = 0.7" ></a>


### TODO

* [x]     add colors to color map
* [x]     set color from command line
* [x]     parse color ~~both as enum and int~~ as hex
* [ ]     make README more complrehensive
* [ ]     add pdf output
