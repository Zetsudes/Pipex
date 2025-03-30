

#ifndef PIPEX_H
# define PIPEX_H

# include "../greg_lib/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>

/************ ERROR HANDLING ************/
void    error_exit(const char *msg, int exit_code);
void    handle_error(int argc, char **argv);

#endif