#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static ssize_t	read_more(int const fd, char **text)
{
	char		*buffer;
	char		*new_text;
	ssize_t		size;

	if (fd < 0 || !text)
		return (STATUS_ERROR);
	if (!(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (STATUS_ERROR);
	size = read(fd, buffer, BUFF_SIZE);
	if (size > 0)
	{
		buffer[size] = 0x0;
		new_text = ft_strjoin(*text, buffer);
		ft_strdel(text);
		*text = new_text;
	}
	ft_strdel(&buffer);
	return (size);
}

int				get_next_line(int const fd, char **line)
{
	static char	*text = NULL;
	char		*new_text;
	ssize_t 	size = 1;
	char		*ptr;

	if (!text)
		text = (char *)ft_memalloc(sizeof(char));
	if (!text || fd < 0 || !line)
		return (STATUS_ERROR);
	while ((ptr = ft_strchr(text, 0x0a)) == NULL)
	{
		size = read_more(fd, &text);
		if (size == -1)
			return (STATUS_ERROR);
		if (size == 0)
			break ;
	}
	*line = ft_strsub(text, 0, ft_strlen(text) - ft_strlen(ptr));
	if (ptr)
		new_text = ft_strdup(ptr + 1);
	ft_strdel(&text);
	text = new_text;
	if (size == 0)
		return (STATUS_DONE);
	return (STATUS_SUCCESS);
}
