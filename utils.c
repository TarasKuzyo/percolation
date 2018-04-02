#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"


static int** allocate_matrix(int width, int height);
static void   free_matrix(int **matrix, int height);


/* allocates a (width x height) matrix
   returns a pointer to a matrix on success
   or NULL pointer on memory allocation failure
 */
int** allocate_matrix(int width, int height)
{
    int **matrix = NULL;
	int i;

    /* allocate matrix rows pointers */
	if (( matrix = malloc(height * sizeof(int*)) ) == NULL)
        return NULL;
        
	for (i = 0; i < height; i++)
	{
	    /* alocate memory for rows data */
		if (( matrix[i] = malloc(width * sizeof(int)) ) == NULL)
		{
		    /* free the part of matrix which is already allocated */
			free_matrix(matrix, i); 
			return NULL;
		}
	}
    
    return matrix;
}


/* frees memory for a 2D matrix with the
   number of its rows given by height
 */
void free_matrix(int **matrix, int height) 
{
	int i;

	for (i = 0; i < height; ++i)
		free(matrix[i]);

	free(matrix);
}


/* allocates a new grid structure given 
   its dimensions (width and height)
   returns NULL if allocation failed 
 */
grid* allocate_grid(int width, int height)
{
    int **cells = allocate_matrix(width, height);
    if (cells == NULL)
        return NULL;
    
    grid *gd = malloc(sizeof(grid));
    if (gd == NULL)
    {
        free_matrix(cells, height);
        return NULL;
    }
    
    gd->width  = width;
    gd->height = height;
    gd->cells  = cells;

    return gd;
}


/*  frees memory allocated for the grid    
 */
void free_grid(grid *gd)
{
    free_matrix(gd->cells, gd->height);
    free(gd);
}


/* saves current grid structure as an ascii file
 */
void write_grid(const char *filename, grid *gd)
{
    FILE *fp;
    int i, j;
    
    if ((fp = fopen(filename, "w")) == NULL) 
	{
        printf("Cannot open file '%s' to write.\n", filename);
		return;
	}
    
    for (i = 0; i < gd->height; i++)
	{
	    for (j = 0; j < gd->width; j++)
            fprintf(fp, "%d", gd->cells[i][j]);

        fprintf(fp, "\n");
	}
    
    fclose(fp);
}


/* returns the number of digits in n
 */
int num_digits(int n) 
{
    int r = 1;
    while (n > 9) 
    {
        n /= 10;
        r++;
    }
    return r;
}


