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
    double prob;
    double size;
    int recursive;
    char filename[STR_BUF_SIZE];
} args;


typedef enum
{
  COLOR_ROYAL_BLUE=1,
} color;


/* from utils.c */
void free_grid(grid *gd);
grid* allocate_grid(int width, int height);
void write_grid(const char *filename, grid *gd);

/* from percolation.c */
int run_percolation(grid *gd, double prob, int recursive_flag);

/* from drawing.c */
int create_image(const char *filename, grid *gd, double max_size);

/* from parse_options.c */
void parse_options(int argc, char **argv, args *arg);


#endif /* __DEFINITIONS_H__ */


