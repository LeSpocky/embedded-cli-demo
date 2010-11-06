#include <stdio.h>
#include <stdlib.h>
#include "cmd.h"

int main( int argc, char * argv[] ) {

    qsort( commands, NO_OF_COMMANDS, sizeof(struct t_cmd), cmd_cmp ); 

    while( 1 ) {

    }

    return EXIT_SUCCESS;
}
