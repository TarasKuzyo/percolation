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
    
    int count = 0;
    
    beg = clock();
    for (int i = 0; i < args.numrepeats; i++)
    {
        count = count + run_percolation(gd, args.prob, args.recursive);
        if (args.img_output)
            create_image(args.filename, i, args.numrepeats, gd, args.size, args.color);
    }
    end = clock();
    
    printf("Finished in %g sec\n", (double)(end - beg) / CLOCKS_PER_SEC);
    printf("Percolation probability is: %g\n", count / (double)args.numrepeats);

    free_grid(gd);
    
    return 0;
}
