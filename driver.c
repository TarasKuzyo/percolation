#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"


int main(int argc, char **argv)
{
    srand(time(NULL));
    
    args cmd_args;
    parse_options(argc, argv, &cmd_args);
    
    grid *gd = allocate_grid(cmd_args.width, cmd_args.height);
    run_percolation(gd, cmd_args.prob, cmd_args.recursive);

    create_image(cmd_args.filename, gd, cmd_args.size);
    //write_grid("out.txt", gd);

    free_grid(gd);
    
    return 0;
}
