#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"


int main(int argc, char **argv)
{
    srand(time(NULL));
    clock_t beg, end;

    args cmd_args;
    parse_options(argc, argv, &cmd_args);
    
    grid *gd = allocate_grid(cmd_args.width, cmd_args.height);
    
    beg = clock();
    run_percolation(gd, cmd_args.prob, cmd_args.recursive);
    end = clock();
    
    create_image(cmd_args.filename, gd, cmd_args.size, cmd_args.color);
    
    printf("Finished in %g sec\n", (double)(end - beg) / CLOCKS_PER_SEC);

    free_grid(gd);
    
    return 0;
}
