/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcincean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:01:20 by vcincean          #+#    #+#             */
/*   Updated: 2017/02/14 12:56:23 by vcincean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static size_t	read_more(int const fd, char **text)
{
	char	*buffer;
	char	*new_text;
	ssize_t	size;

	if (fd < 0 || NULL == text || !(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	size = read(fd, buffer, BUFF_SIZE);
	buffer[size] = 0x0;
	if (size > 0)
	{
		new_text = ft_strjoin(*text, buffer);
		ft_strdel(text);
		*text = new_text;
	}
	ft_strdel(&buffer);
	return (size);
}

static void		manage_pointers(char **line, char **text, char *ptr)
{
	char	*new_text;

	if (ptr == NULL)
	{
		*line = ft_strdup(*text);
		new_text = NULL;
	}
	else
	{
		*line = ft_strsub(*text, 0, ft_strlen(*text) - ft_strlen(ptr));
		new_text = ft_strdup(ptr + 1);
	}
	ft_strdel(text);
	*text = new_text;
}

int				get_next_line(int const fd, char **line)
{
	static char	*text = NULL;
	ssize_t		size;
	char		*ptr;

	if (fd < 0 || NULL == line || BUFF_SIZE < 1)
		return (-1);
	if (NULL == text)
		text = (char *)ft_memalloc(sizeof(char));
	if (NULL == text)
		return (-1);
	size = 1;
	while (size != 0 && (ptr = ft_strchr(text, 0x0a)) == NULL)
	{
		size = read_more(fd, &text);
		if (size == -1)
			return (-1);
	}
	manage_pointers(line, &text, ptr);
	return (!(size == 0 && ft_strlen(*line) == 0));
}
