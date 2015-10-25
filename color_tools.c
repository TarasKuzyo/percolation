#include <stdio.h>
#include "color_tools.h"


float colormap[NUM_COLORS][3][3] = {
    {{0.15, 0.15, 0.15}, 
     {0.90, 0.90, 0.90}, 
     {0.40, 0.40, 0.90}},
    
    {{0.15, 0.15, 0.15}, 
     {0.90, 0.90, 0.90}, 
     {0.45, 0.25, 0.30}},
     
    {{0.15, 0.15, 0.15}, 
     {0.90, 0.90, 0.90}, 
     {0.35, 0.65, 0.15}},
     
    {{0.15, 0.15, 0.15}, 
     {0.90, 0.90, 0.90}, 
     {0.45, 0.51, 0.18}},
};


rgb hex_to_rgb(int hex_val)
{
    rgb color;
    color.r = ((hex_val >> 16) & 0xff) / 255.0;
    color.g = ((hex_val >> 8 ) & 0xff) / 255.0;
    color.b = ((hex_val      ) & 0xff) / 255.0;

    return color;
}


int rgb_to_hex(rgb color)
{   
    return (( (int)(color.r * 255) & 0xff ) << 16) + 
           (( (int)(color.g * 255) & 0xff ) << 8 ) + 
            ( (int)(color.b * 255) & 0xff );
}

/* converts color string of form #rrggbb to 
   its hex value
 */
int str_to_hex(char *str, int *hex)
{
    return (str[0] == '#') ? sscanf(str + 1, "%x", hex) : 0;
}

