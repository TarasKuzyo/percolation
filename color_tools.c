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


int_rgb hex_to_int_rgb(int hex_val)
{
    int_rgb rgb_color;
    rgb_color.r = ((hex_val >> 16) & 0xff);
    rgb_color.g = ((hex_val >> 8 ) & 0xff);
    rgb_color.b = ((hex_val      ) & 0xff);

    return rgb_color;
}


int int_rgb_to_hex(int_rgb rgb)
{   
    return ((rgb.r & 0xff) << 16) + 
           ((rgb.g & 0xff) << 8 ) + 
            (rgb.b & 0xff);
}


float_rgb hex_to_float_rgb(int hex_val)
{
    float_rgb rgb_color;
    rgb_color.r = ((hex_val >> 16) & 0xff) / 255.0;
    rgb_color.g = ((hex_val >> 8 ) & 0xff) / 255.0;
    rgb_color.b = ((hex_val      ) & 0xff) / 255.0;

    return rgb_color;
}


int float_rgb_to_hex(int_rgb rgb)
{   
    return (( (int)(rgb.r * 255) & 0xff ) << 16) + 
           (( (int)(rgb.g * 255) & 0xff ) << 8 ) + 
            ( (int)(rgb.b * 255) & 0xff );
}

/* converts color string of form #rrggbb to 
   its hex value
 */
int str_to_hex(char *color, int *hex)
{
    return (color[0] == '#') ? sscanf(color + 1, "%x", hex) : 0;
}

