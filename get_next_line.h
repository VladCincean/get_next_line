#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"
# define BUFF_SIZE 32
# define STATUS_SUCCESS 1
# define STATUS_DONE 0
# define STATUS_ERROR -1

int	get_next_line(int const fd, char **line);

#endif
