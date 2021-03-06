#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define SITE_BLOCK 0
#define SITE_OPEN  1
#define SITE_FULL  2

#define STR_BUF_SIZE 256


typedef struct
{
    int width;
    int height;
    int **cells;

} grid;


typedef struct
{
    int width;
    int height;
    int numrepeats;
    int recursive;
    int img_output;
    int color;
    double prob;
    double size;
    char filename[STR_BUF_SIZE];
} cmd_args;


/* from utils.c */
grid* allocate_grid(int width, int height);
void free_grid(grid *gd);
void write_grid(const char *filename, grid *gd);
int num_digits(int n);

/* from percolation.c */
int run_percolation(grid *gd, double prob, int recursive_flag);

/* from drawing.c */
int create_image(const char *filename, int filenum, int total_images, grid *gd, double max_size, int cl);

/* from parse_options.c */
void parse_options(int argc, char **argv, cmd_args *args);


#endif /* __DEFINITIONS_H__ */


