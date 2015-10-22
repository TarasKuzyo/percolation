#include <stdio.h>
#include <string.h>

#include <cairo.h>
#include <cairo-svg.h> 

#include "definitions.h"


static float colormap[4][3][3] = {
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


/* darws a single site with cairo 
   drawing context (cr) as a square
   given its position, size and value
 */
void draw_site(cairo_t *cr, double x, double y, double size, color cl, int site)
{
    /* color shortcut 
       (range is checked on input) */
    float (*c)[3][3] = &colormap[cl];
    
    if (site == SITE_BLOCK)
        cairo_set_source_rgb(cr, (*c)[0][0], (*c)[0][1], (*c)[0][2]);
    else if (site == SITE_OPEN)
        cairo_set_source_rgb(cr, (*c)[1][0], (*c)[1][1], (*c)[1][2]);
    else if (site == SITE_FULL)
        cairo_set_source_rgb(cr, (*c)[2][0], (*c)[2][1], (*c)[2][2]);
    
    cairo_rectangle(cr, x, y, size, size);
    cairo_fill_preserve(cr);
                 
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
}


/* Takes a filename of the output file, grid structure
   and maximum image size (width or height)
   Writes the grid image to the file
 */
int create_image(const char *filename, grid *gd, double max_size, color cl)
{
    int i, j; 
    
    /* grid structure aspect ratio */
    double aspect = (double)gd->width / (double)gd->height;
    /* image parameters */
    double img_width  = (aspect > 1) ? max_size : max_size * aspect;
    double img_height = (aspect < 1) ? max_size : max_size / aspect;
    
    double site_size  = img_width/gd->width;
    double line_width = site_size/50.0;
    
    /* include border to the image width */
    double border_width = max_size/50.0;
    img_width  = img_width  + 2 * border_width;
    img_height = img_height + 2 * border_width;
    
    cairo_surface_t *surface;
  	cairo_t *cr;
  	
  	/* extract an extension from filename */
  	char *ext = strrchr(filename, '.');
    if (!ext) /* no extension */
    {
        printf("File extension missing for the output image name: '%s'\n", filename);
        return 1;
    }
    else
        ext = ext + 1;
    
  	if (strcmp(ext, "svg") == 0)
  	    surface = cairo_svg_surface_create(filename, img_width, img_height);
  	else if (strcmp(ext, "png") == 0)
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, img_width, img_height);
    else
    {
        printf("Unsupported output image format: '%s'\n", ext);
        return 1;
    }
        
	cr = cairo_create(surface);

    /* set background */
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, img_width, img_height);
    cairo_fill(cr);
    
    /* line settings */
    cairo_set_line_width(cr, line_width);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);  
    
    /* draw grid sites */
    for (i = 0; i < gd->height; i++)
        for (j = 0; j < gd->width; j++)
            draw_site(cr, border_width + j * site_size,
                          border_width + i * site_size, 
                          site_size, cl, gd->cells[i][j]);          
    
    if (strcmp(ext, "png") == 0)
        cairo_surface_write_to_png(surface, filename);
    
    cairo_destroy(cr);
	cairo_surface_destroy(surface);
	
	return 0;
} 


