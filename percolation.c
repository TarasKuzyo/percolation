#include <stdlib.h>
#include "definitions.h"


/* generates a ramdom grid for given 
   site vacancy probability */
void create_grid(grid *gd, double prob)
{
    int i, j;
    
    for (i = 0; i < gd->height; i++)
        for (j = 0; j < gd->width; j++)
             gd->cells[i][j] = ( (double)rand() / (double)RAND_MAX < prob ) ? SITE_OPEN : SITE_BLOCK;
    
}


/* fills upper layer cells that are open 
 */
void start_flow(grid *gd)
{
    int j;
    
    for (j = 0; j < gd->width; j++)
        if (gd->cells[0][j] == SITE_OPEN)
            gd->cells[0][j] = SITE_FULL;

}


/* checks if the grid structure percolates
   i.e., if any bottom layer cell is full 
 */
int percolates(grid *gd)
{
    int j;
    
    /* check if at least one of bottom cells is full */
    for (j = 0; j < gd->width; j++)
        if (gd->cells[gd->height - 1][j] == SITE_FULL)
            return 1;
    
    return 0;
}


/* Takes a pointer to the grid and indexes of
   the full cell. Updates all open adjacent
   neighbors as being filled and calls itself
   for the updated neighbors recursively 
 */
void update_neighbors(grid *gd, int i, int j)
{
    if (i > 0 && gd->cells[i - 1][j] == SITE_OPEN)
    {
        gd->cells[i - 1][j] = SITE_FULL;
        update_neighbors(gd, i - 1, j);
    }
        
    if (j > 0 && gd->cells[i][j - 1] == SITE_OPEN)
    {
        gd->cells[i][j - 1] = SITE_FULL;
        update_neighbors(gd, i, j - 1);
    }

    if (i + 1 < gd->height && gd->cells[i + 1][j] == SITE_OPEN)
    {
        gd->cells[i + 1][j] = SITE_FULL;
        update_neighbors(gd, i + 1, j);
    }
    
    if (j + 1 < gd->width && gd->cells[i][j + 1] == SITE_OPEN)
    {
        gd->cells[i][j + 1] = SITE_FULL;
        update_neighbors(gd, i, j + 1);
    }
        
}

 
/* Fills the structure with the flow recursively
   (propagates the FULL site state to all open
   sites that are adjacent to the FULL cells)
 */
void flow_recursive(grid *gd)
{
    int i, j;
    
    for (i = 0; i < gd->height; i++)
        for (j = 0; j < gd->width; j++)
            if (gd->cells[i][j] == SITE_FULL)
                update_neighbors(gd, i, j);

}


/* Takes a pointer to the grid and indexes of
   the open cell. If any of neighboring cells
   is full then the target cell is also set to
   full and a value of 1 is returned.
   Otherwise 0 is returned.
 */
int check_neighbors(grid *gd, int i, int j)
{
    if (i > 0 && gd->cells[i - 1][j] == SITE_FULL)
    {
        gd->cells[i][j] = SITE_FULL;
        return 1;
    }
        
    if (j > 0 && gd->cells[i][j - 1] == SITE_FULL)
    {
        gd->cells[i][j] = SITE_FULL;
        return 1;
    }

    if (i + 1 < gd->height && gd->cells[i + 1][j] == SITE_FULL)
    {
        gd->cells[i][j] = SITE_FULL;
        return 1;
    }
    
    if (j + 1 < gd->width && gd->cells[i][j + 1] == SITE_FULL)
    {
        gd->cells[i][j] = SITE_FULL;
        return 1;
    }
    
    return 0;
}


/* Fills the structure with the flow in iterative way 
   (keep propagating the flow from top left to bottom right
   and from bottom right to to left until no cell was updated
   on the previous step)
 */
void flow_iterative(grid *gd)
{
    int i, j;
    int update_flag = 1;
    while (update_flag)
    {
        update_flag = 0;
        
        for (i = 0; i < gd->height; i++)
            for (j = 0; j < gd->width; j++)
                if (gd->cells[i][j] == SITE_OPEN)
                    update_flag += check_neighbors(gd, i, j);
                
        for (i = gd->height - 1; i >= 0; i--)
            for (j = gd->width - 1; j >= 0; j--)
                if (gd->cells[i][j] == SITE_OPEN)
                    update_flag += check_neighbors(gd, i, j);            
    
    }

}


/* generate random grid structure
   with given site vacancy probability
 */
int run_percolation(grid *gd, double prob, int recursive_flag)
{
    create_grid(gd, prob);
    start_flow(gd);
    
    if (recursive_flag)
        flow_recursive(gd);
    else
        flow_iterative(gd);
    
    return percolates(gd);
}


