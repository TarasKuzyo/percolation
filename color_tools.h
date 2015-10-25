#ifndef __COLOR_TOOLS_H__
#define __COLOR_TOOLS_H__

/* size of the lookup table */
#define NUM_COLORS 8
/* color indexes of some predefined colors */
#define COLOR_PAD (0xffffff + 1)    


#define SITE_BLOCK_COLOR 0x262626
#define SITE_OPEN_COLOR  0xe6e6e6


typedef struct {
    float r;
    float g;
    float b;        
} rgb;


int colormap[NUM_COLORS];
void colormap_show();

rgb hex_to_rgb(int hex_val);
int str_to_hex(char *color, int *hex_val);


#endif /* __COLOR_TOOLS_H__ */


