#include <stdio.h>
#include <string.h>

#include <cairo.h>
#include <cairo-svg.h> 
#include <cairo-pdf.h> 

#include "definitions.h"
#include "color_tools.h"


/* draws a single site with cairo 
   drawing context (cr) as a square
   given its position, size, color index and value
 */
void draw_site(cairo_t *cr, double x, double y, double size, int c, int site)
{
    /* hex color value for the full site */
    /* if c is less than COLOR_PAD then it is 
       valid RGB value 
       otherwise pick hex value 
       from lookup table using c as index shifted 
       by COLOR_PAD */
    int color = (c < COLOR_PAD) ? c : colormap[c - COLOR_PAD];
    rgb b_cl = hex_to_rgb(SITE_BLOCK_COLOR);
    rgb o_cl = hex_to_rgb(SITE_OPEN_COLOR);    
    rgb f_cl = hex_to_rgb(color);
    
    if (site == SITE_BLOCK)
        cairo_set_source_rgb(cr, b_cl.r, b_cl.g, b_cl.b);
    else if (site == SITE_OPEN)
        cairo_set_source_rgb(cr, o_cl.r, o_cl.g, o_cl.b);
    else if (site == SITE_FULL)
        cairo_set_source_rgb(cr, f_cl.r, f_cl.g, f_cl.b);
    
    cairo_rectangle(cr, x, y, size, size);
    cairo_fill_preserve(cr);
                 
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
}


/* Takes a filename of the output file, a grid structure
   and maximum image size (width or height)
   Writes the grid image to the file
 */
int create_image(const char *filename, int filenum, int total_images, grid *gd, double max_size, int cl)
{
    int i, j; 
    
    /* grid structure aspect ratio */
    double aspect = (double)gd->width / (double)gd->height;
    /* image parameters */
    double img_width  = (aspect > 1) ? max_size : max_size * aspect;
    double img_height = (aspect < 1) ? max_size : max_size / aspect;
    
    double site_size  = img_width/gd->width;
    double line_width = site_size/50.0;
    
    /* include border to the image size */
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
        
    // basename = strtok(filename, ".");
    // sprintf("%s_%%0%dd.%s", basename, total_images, ext)
    
  	if (strcmp(ext, "svg") == 0)
  	    surface = cairo_svg_surface_create(filename, img_width, img_height);
  	else if (strcmp(ext, "pdf") == 0)
        surface = cairo_pdf_surface_create(filename, img_width, img_height);
  	else if (strcmp(ext, "png") == 0)
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, img_width, img_height);
    else
    {
        printf("Unsupported output image format: '%s'\n", ext);
        return 2;
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


