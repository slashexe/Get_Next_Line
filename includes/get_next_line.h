#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "get_next_line.h"


# define BUFF_SIZE 20
# define MALL(x) if (!x) return (-1);

int		get_next_line(const int fd, char **line);
#endif