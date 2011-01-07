#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"

int main( int argc, char * argv[] ) {
    unsigned char   _argc = 0, i;
    char *          _argv[( INPUT_LINE_LENGTH + 1 ) / 2] = { 0 };
    char *          cmd_string;
    struct t_cmd    cmd_to_check = { "", NULL };
    char            input_buffer[INPUT_LINE_LENGTH] = { 0 };
    char            input_buffer_cpy[INPUT_LINE_LENGTH] = { 0 };
    size_t          input_string_length;
    char            last_return_value = EXIT_SUCCESS;
    struct t_cmd *  p_found_cmd;

    /*  test    */
    /*
    printf( "Newline:         0x%02X\n", '\n' );
    printf( "Carriage Return: 0x%02X\n", '\r' );
    */
    /*  /test   */

    qsort( commands, NO_OF_COMMANDS, sizeof(struct t_cmd), cmd_cmp ); 

    (void) printf( "Sorted commands:" );
    for ( i = 0; i < NO_OF_COMMANDS; i++ ) {
        printf( " %s", commands[i].cmd );
    }
    (void) printf( "\n\n" );

    while( 1 ) {
        
        /*  (Re)initialize. */
        _argc = 0;
        memset( _argv, 0, ( INPUT_LINE_LENGTH + 1 ) / 2 );

        /*  Print prompt and read one line with length INPUT_LINE_LENGTH
         *  from STDIN. Handle trailing newline character for later
         *  processing of command input line.   */
        if ( last_return_value ) {
            (void) printf( "%d > ", last_return_value );
        } else {
            (void) printf( "> " );
        }
        if ( ! fgets( input_buffer, INPUT_LINE_LENGTH, stdin ) ) {
            (void) fprintf( stderr, "Error reading from STDIN!\n" );
            break;
        }

        /* (void) printf( "input_buffer: '%s'\n", input_buffer ); */
        input_string_length = strlen( input_buffer );
        if ( input_buffer[input_string_length-1] == '\n' ) {
            input_buffer[input_string_length-1] = ' ';
            /*
            fprintf( stderr, 
                    "Replaced trailing LF with whitespace ...\n" );
            */
        }

        /**
          * @todo   flush stdio input buffer to not get input more than
          *         our buffer size next time. issue warning if
          *         truncated.
          */

        /*
        for ( i = 0; i < INPUT_LINE_LENGTH; i++ ) {
            (void) printf( "%02X ", input_buffer[i] );        
        }
        (void) printf( "\n" );
        */

        /*  Count words on command line and safe into _argc */
        strncpy( input_buffer_cpy, input_buffer, INPUT_LINE_LENGTH );
        /*
        for ( i = 0; i < INPUT_LINE_LENGTH; i++ ) {
            (void) printf( "%02X ", input_buffer_cpy[i] );        
        }
        (void) printf( "\n" );
        return EXIT_SUCCESS;
        */
        cmd_string = strtok( input_buffer_cpy, " \t" );
        while ( cmd_string != NULL ) {
            _argc++;
            cmd_string = strtok( NULL, " \t" );
        }
        printf( "_argc: %d\n", _argc );

        /*  Parse for command and assemble _argv[]  */
        strncpy( input_buffer_cpy, input_buffer, INPUT_LINE_LENGTH );
        cmd_string = strtok( input_buffer_cpy, " \t" );
        strncpy( cmd_to_check.cmd, cmd_string, MAX_CMD_LENGTH );
        printf( "parsed command: '%s'\n", cmd_to_check.cmd );
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
