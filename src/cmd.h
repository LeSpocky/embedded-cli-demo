#ifndef _CMD_H_
#define _CMD_H_

#define INPUT_LINE_LENGTH   20  /**< maximum length of command line including terminating zero                                          */
#define MAX_CMD_LENGTH      5   /**< maximum length of command string itself, including terminating zero                                */
#define NO_OF_COMMANDS      2   /**< number of commands, has to be changed whenever struct t_cmd commands[NO_OF_COMMANDS] is changed    */

/**
 *  Function pointer type for command evaluation.
 */
typedef char (*t_cmd_func)( const unsigned char argc, const char * argv[] );

/**
 *  Command evaluation structure containing the string of the command
 *  itself and a function pointer to the function to be executed.
 */
struct t_cmd {
    char        cmd[MAX_CMD_LENGTH];    /**< command string     */
    t_cmd_func  func;                   /**< function pointer   */
};

extern struct t_cmd commands[NO_OF_COMMANDS];

/**
 *  Compare function for qsort() and bsearch() comparing structures of
 *  type struct t_cmd.
 *
 *  @param[in]  e1  pointer to first struct
 *  @param[in]  e2  pointer to second struct
 *
 *  @return -1, 0 or 1 depending which is less, equal or greater.
 */
extern int cmd_cmp( const void *e1, const void *e2 );

/**
 *  Print help message, nothing more.
 *
 *  @param[in]  argc    number of arguments
 *  @param[in]  argv[]  list of null terminated argument strings
 *
 *  @return 0 in case of success, error value otherwise
 */
extern char func_help(
        const unsigned char argc,
        const char *        argv[]
);

extern char func_quit(
        const unsigned char argc,
        const char *        argv[]
);

#endif
