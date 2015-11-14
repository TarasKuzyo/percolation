#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"


int main(int argc, char **argv)
{
    srand(time(NULL));
    clock_t beg, end;

    cmd_args args;
    parse_options(argc, argv, &args);
    
    grid *gd = allocate_grid(args.width, args.height);
    
    beg = clock();
    run_percolation(gd, args.prob, args.recursive);
    end = clock();
    
    if (args.img_output)
        create_image(args.filename, gd, args.size, args.color);
    
    printf("Finished in %g sec\n", (double)(end - beg) / CLOCKS_PER_SEC);

    free_grid(gd);
    
    return 0;
}
