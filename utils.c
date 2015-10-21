#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

/* frees memory for a 2D matrix with number of rows
   given by height
 */
void free_matrix(int **matrix, int height) 
{
	int i;

	for (i = 0; i < height; ++i)
		free(matrix[i]);

	free(matrix);
}


/* allocates a 2D width x height matrix
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
	    /* alocate memory for rows of data */
		if (( matrix[i] = malloc(width * sizeof(int)) ) == NULL)
		{
		    /* free already allocated part of matrix */
			free_matrix(matrix, i); 
			return NULL;
		}
	}
    
    return matrix;
}



/*  Frees memory allocated for the grid    
 */
void free_grid(grid *gd)
{
    free_matrix(gd->cells, gd->height);
    free(gd);
}


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


void write_grid(const char *filename, grid *gd)
{
    FILE *fp;
    
    int i, j;
    
    if ((fp = fopen(filename, "w")) == NULL) 
	{
        printf("Cannot open file '%s' to write\n", filename);
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


