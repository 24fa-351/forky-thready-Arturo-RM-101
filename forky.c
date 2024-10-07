#include <stdio.h>
#include <stdlib.h>

#include "forky.h"

int main(int argc, char *argv[]) {
    // Gets the arguments onto the corresponding variables
    int Num_Things = atoi(argv[1]);
    int Pattern_Num = atoi(argv[2]);
    
    // Tests to see if arguments 2 is asking for pattern 1 or 2
    if (Pattern_Num == 1) {
        Fork_Pattern_One(Num_Things);
    } else if (Pattern_Num == 2) {
        Fork_Pattern_Two(Num_Things);
    } else {
        printf("Invalid step number\n");
    }

    return 0;
}