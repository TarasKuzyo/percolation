#ifndef __COLOR_TOOLS_H__
#define __COLOR_TOOLS_H__

#define NUM_COLORS 6
#define COLOR_PAD (0xffffff + 1)


typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;        
} int_rgb;


typedef struct {
    float r;
    float g;
    float b;        
} float_rgb;


float colormap[NUM_COLORS][3][3];

float_rgb hex_to_float_rgb(int hex_val);
int str_to_hex(char *color, int *hex);


#endif /* __COLOR_TOOLS_H__ */


