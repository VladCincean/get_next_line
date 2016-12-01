#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static ssize_t	read_more(int const fd, char **text)
{
	char		*buffer;
	ssize_t		size;

	if (fd < 0 || !text)
		return (STATUS_ERROR);
	buffer = ft_strnew(BUFF_SIZE + 1);
	size = read(fd, buffer, BUFF_SIZE);
	if (size == -1)
	{
		ft_strdel(&buffer);
		return (STATUS_ERROR);
	}
	buffer[size] = '\0';
	*text = ft_strjoin(*text, buffer);
	ft_strdel(&buffer);
	if (!(*text))
		return (STATUS_ERROR);
	return (size);

}

int				get_next_line(int const fd, char **line)
{
	static char	*text = NULL;
	ssize_t 	size;
	char		*ptr;

	if (!text)
		text = (char *)ft_memalloc(sizeof(char));
	if (!text || fd < 0 || !line)
		return (STATUS_ERROR);
	size = 1;
	while ((ptr = ft_strchr(text, 0x0a)) == NULL)
	{
		size = read_more(fd, &text);
		if (size == -1)
			return (STATUS_ERROR);
		if (size == 0)
			break ;
	}
	*line = ft_strsub(text, 0, ptr - text);
	text = ft_strsub(text, ptr - text + 1, ft_strlen(text));
	if (size == 0)
		return (STATUS_DONE);
	return (STATUS_SUCCESS);
}
