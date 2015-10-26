#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "definitions.h"
#include "color_tools.h"


void parse_options(int argc, char **argv, args *arg)
{
    static char *usage = "NAME                                                 \n"
                         "       percolation - 2D site percolation             \n"  
                         "                                                     \n"
                         "SYNOPSIS                                             \n"
                         "       percolation [OPTION]...                       \n"
                         "                                                     \n"
                         "DESCRIPTION                                          \n"
                         "       -w, --width                                   \n"
                         "           grid width                                \n"
                         "                                                     \n"
                         "       -h, --height                                  \n"
                         "           grid height                               \n"
                         "                                                     \n"
                         "       -p, --probability                             \n"
                         "           site vacancy probability                  \n"
                         "                                                     \n"
                         "       -o, --output                                  \n"
                         "           output image file (either png or svg)     \n"
                         "                                                     \n"
                         "       -s, --size                                    \n"
                         "           maximum image size                        \n"
                         "                                                     \n"
                         "       -c, --color                                   \n"
                         "           color for the full sites in form '#rrggbb'\n"
                         "           or as a lookup table index                \n"                         
                         "                                                     \n"
                         "       -l, --list-colors                             \n"
                         "           dispalys a list of predefined colors and  \n"
                         "           their indexes (an argument for -c option) \n"
                         "                                                     \n"
                         "       -r, --recursive                               \n"
                         "           enable recursive flow propagation         \n"
                         "                                                     \n"  
                         "       -O, --no-output                               \n" 
                         "           disable image output                      \n" 
                         "                                                     \n"                        
                         "       --help                                        \n"
                         "           display this help and exit                \n" 
                         "                                                     \n"
                         "AUTHOR                                               \n"  
                         "       Written by Taras Kuzyo                        \n"                         
                         "                                                     \n";

    
    static const struct option long_opts[] = {
                        { "width",       required_argument, NULL, 'w' }, 
                        { "height",      required_argument, NULL, 'h' },    
                        { "probability", required_argument, NULL, 'p' },
                        { "output",      required_argument, NULL, 'o' },       
                        { "size",        required_argument, NULL, 's' },
                        { "color",       required_argument, NULL, 'c' },
                        { "list-colors", no_argument,       NULL, 'l' },
                        { "recursive",   no_argument,       NULL, 'r' },
                        { "no-output",   no_argument,       NULL, 'O' },
                        { "help",        no_argument,       NULL,  0  },
                        {  NULL,         no_argument,       NULL,  0  }  };
            
    char *options = "w:h:p:p:o:s:c:lrO";

    int opt = 0;
    int long_index = 0;
    
    /* minimal values for some arguments */
    const int min_width = 2, min_height = 2, min_size = 64;
    /* flags indicating option invocation */
    int width_flag = 0, height_flag = 0, prob_flag = 0;
    
    /* default values for the arguments */
    int recursive_flag = 0;
    int img_output = 1;
    int width = 0, height = 0;
    double prob = 0.0, size = 800.0;    
    char filename[STR_BUF_SIZE] = "";
    int color = 0;
    
    
    /* print usage if no args */
    if (argc == 1)
    {
        printf("%s", usage);
        exit(0);
    }
    
    /* process options */
    while ((opt = getopt_long(argc, argv, options, long_opts, &long_index)) != -1)
    {
        switch (opt)
        {
            case 'w':
                width_flag = 1;
                width = atoi(optarg);
                break;
                
            case 'h':
                height_flag = 1;
                height = atoi(optarg);
                break;
                
            case 'p':
                prob_flag = 1;
                prob = atof(optarg);
                break;
            
            case 's':
                /* image maximum size 
                   (either width of height) in px */
                size = atof(optarg);
                break;
                
            case 'o':
                /* set custum output filename */
                strcpy(filename, optarg);
                break;
                
            case 'c':
                /* try converting from hex representation
                   use simple integer conversion if failed */
                if ( ! str_to_hex(optarg, &color) )
                    color = COLOR_PAD + atoi(optarg);
                break;
                
            case 'l':
                /* list colors indexes available */
                colormap_show();
                exit(0);
                break;
                
            case 'r':
                recursive_flag = 1;
                break;
                
            case 'O':
                img_output = 0;
                break;
                
            case 0:
                printf("%s", usage);
                exit(0);
                break;
                        
            case '?':
                exit(1);
                break;
                
            default:
                printf("%s: unknown option '%s'\n", argv[0], optarg);
                exit(1);
                break;
        }
    }
    /* check if required arguments were passed */
    if (!width_flag)
    {
        printf("%s: missing '-w' option\n", argv[0]);
        exit(1);
    }
    if (!height_flag)
    {
        printf("%s: missing '-h' option\n", argv[0]);
        exit(1);
    }
    if (!prob_flag)
    {
        printf("%s: missing '-p' option\n", argv[0]);
        exit(1);
    }
    /* check probability range */
    if (prob < 0.0 || prob > 1.0)
    {
        printf("%s: invalid probability value: %g\n", argv[0], prob);
        exit(1);
    }
    /* check if color index is valid */
    if (color < 0 || color - COLOR_PAD >= NUM_COLORS)
    {
        printf("%s: unknown color code: %x\n", argv[0], (int)(color));
        exit(1);
    }
    
    size   = (size   < min_size  ) ? min_size   : size;
    width  = (width  < min_width ) ? min_width  : width;
    height = (height < min_height) ? min_height : height;
    
    /* set default image filename */
    if (strlen(filename) == 0)
        snprintf(filename, STR_BUF_SIZE, "output_%d_%d_%g.png", width, height, prob);
        
    arg->width      = width;
    arg->height     = height;
    arg->prob       = prob;
    arg->size       = size;
    arg->color      = color;
    arg->img_output = img_output;
    arg->recursive  = recursive_flag;
    strcpy(arg->filename, filename);
}


