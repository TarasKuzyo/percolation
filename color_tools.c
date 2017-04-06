#include <stdio.h>
#include "color_tools.h"


/* lookup table for some of the predefined colors */
int colormap[NUM_COLORS] = {0xd53e4f, 0xf46d43, 0xfdae61, 
        0xfee08b, 0xe6f598, 0xabdda4, 0x66c2a5, 0x3288bd };


/* displays contents of the colormap array
   both as hex values and rgb colors 
 */
void colormap_show()
{
    int i, hex;
    int r, g, b;
    rgb  color;
    
    printf("List of the predefined colors:\n");
    printf("    Index       Hex         RGB Value\n");
    for (i = 0; i < NUM_COLORS; i++)
    {
        hex   = colormap[i];
        color = hex_to_rgb(hex);
        r = (int)(color.r * 255);
        g = (int)(color.g * 255);
        b = (int)(color.b * 255);
        printf("\t%d   #%x   (%3d, %3d, %3d)\n", i, hex, r, g, b);
    }        
}


/* converts hex value to rgb struct
 */
rgb hex_to_rgb(int hex_val)
{
    rgb color;
    color.r = ((hex_val >> 16) & 0xff) / 255.0;
    color.g = ((hex_val >> 8 ) & 0xff) / 255.0;
    color.b = ((hex_val      ) & 0xff) / 255.0;

    return color;
}


/* converts rgb struct to hex value 
 */
int rgb_to_hex(rgb color)
{   
    return (( (int)(color.r * 255) & 0xff ) << 16) + 
           (( (int)(color.g * 255) & 0xff ) << 8 ) + 
            ( (int)(color.b * 255) & 0xff );
}


/* converts color string of form "#rrggbb"
   to its hex value
   returns 1 on success and 0 on failure
 */
int str_to_hex(char *str, int *hex)
{
    return (str[0] == '#') ? sscanf(str + 1, "%x", hex) : 0;
}


