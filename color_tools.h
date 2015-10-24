#ifndef __COLOR_TOOLS_H__
#define __COLOR_TOOLS_H__


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


float colormap[4][3][3];

float_rgb hex_to_float_rgb(int hex_val);


#endif /* __COLOR_TOOLS_H__ */


