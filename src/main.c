#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"

int main( int argc, char * argv[] ) {
    unsigned char   _argc = 0, i;
    char *          _argv[( INPUT_LINE_LENGTH + 1 ) / 2] = { 0 };
    char *          cmd_string;
    struct t_cmd    cmd_to_check = { "", NULL };
    char            input_buffer[INPUT_LINE_LENGTH];
    char            input_buffer_cpy[INPUT_LINE_LENGTH];
    size_t          input_string_length;
    char            last_return_value = EXIT_SUCCESS;
    struct t_cmd *  p_found_cmd;

    qsort( commands, NO_OF_COMMANDS, sizeof(struct t_cmd), cmd_cmp ); 

    while( 1 ) {

        /*  Print prompt and read one line with length INPUT_LINE_LENGTH
         *  from STDIN. Handle trailing newline character for later
         *  processing of command input line.   */
        if ( last_return_value ) {
            (void) printf( "%d uC> ", last_return_value );
        } else {
            (void) printf( "uC> " );
        }
        if ( ! fgets( input_buffer, INPUT_LINE_LENGTH, stdin ) ) {
            (void) fprintf( stderr, "Error reading from STDIN!\n" );
            break;
        }
        input_string_length = strlen(input_buffer);
        if ( input_buffer[input_string_length-1] != 0x0A ) {
            (void) printf( "\n" );
        } else {
            input_buffer[input_string_length-1] = ' ';
        }

        /*  Count words on command line and safe into _argc */
        strncpy( input_buffer_cpy, input_buffer, INPUT_LINE_LENGTH );
        cmd_string = strtok( input_buffer_cpy, " \t" );
        while ( cmd_string != NULL ) {
            _argc++;
            cmd_string = strtok( NULL, " \t" );
        }

        /*  Parse for command and assemble _argv[]  */
        strncpy( input_buffer_cpy, input_buffer, INPUT_LINE_LENGTH );
        cmd_string = strtok( input_buffer_cpy, " \t" );
        strncpy( cmd_to_check.cmd, cmd_string, MAX_CMD_LENGTH );
        i = 0;
        do {
            _argv[i++]  = cmd_string;
            cmd_string  = strtok( NULL, " \t" );
        } while ( cmd_string != NULL );
                
        /*  Search command in command list and execute! */
        p_found_cmd = (struct t_cmd *) bsearch( &cmd_to_check, commands,
                NO_OF_COMMANDS, sizeof(struct t_cmd), cmd_cmp );
        if ( p_found_cmd == NULL ) {
            (void) fprintf( stderr, "Command not found!\n" );
        } else {
            last_return_value = p_found_cmd->func( _argc, (const char **) _argv );
        }

    }

    return EXIT_SUCCESS;
}
