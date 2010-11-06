#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"

/**
 *  @attention  Beware of MAX_CMD_LENGTH limit!
 */ 
struct t_cmd commands[NO_OF_COMMANDS] = {
        { "help", func_help },
        { "quit", func_quit },
};      

int cmd_cmp( const void *e1, const void *e2 ) {
    struct t_cmd * p_cmd_1 = (struct t_cmd *) e1;
    struct t_cmd * p_cmd_2 = (struct t_cmd *) e2;
        
    return strncmp( p_cmd_1->cmd, p_cmd_2->cmd, MAX_CMD_LENGTH );
}

char func_help(
        const unsigned char argc,
        const char *        argv[] )
{  
    (void) printf( "Usage: cmd <arg1> <arg2> <arg3> ...\n" );
    (void) printf( "\n" );
    (void) printf( "Commands:\n" );
    (void) printf( "    help    print this help message\n" );
    (void) printf( "    quit    quit application\n" );
        
    return EXIT_SUCCESS;
}

char func_quit(
        const unsigned char argc,
        const char *        argv[] )
{
    (void) printf( "Exiting ...\n" );
    exit( EXIT_SUCCESS );
}
