/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcincean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:01:20 by vcincean          #+#    #+#             */
/*   Updated: 2017/02/15 13:45:21 by vcincean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static size_t		read_more(int const fd, char **text)
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

static void			manage_pointers(char **line, char **text, char *ptr)
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

static t_file_pool	*get_existent_buffer(t_list **file_list, int fd)
{
	t_list	*temp;

	temp = *file_list;
	while (temp != NULL && ((t_file_pool *)(temp->content))->fd != fd)
		temp = temp->next;
	if (temp != NULL && ((t_file_pool *)(temp->content))->fd == fd)
	{
		if (((t_file_pool *)(temp->content))->text == NULL)
			((t_file_pool *)(temp->content))->text = (char *)ft_memalloc(1);
		if (((t_file_pool *)(temp->content))->text == NULL)
			return (NULL);
		return ((t_file_pool *)(temp->content));
	}
	return (NULL);
}

static t_file_pool	*get_buffer(t_list **file_list, int fd)
{
	t_file_pool	*temp;
	t_list		*new;

	temp = NULL;
	if (get_existent_buffer(file_list, fd) != NULL)
		return (get_existent_buffer(file_list, fd));
	if ((temp = (t_file_pool *)malloc(sizeof(t_file_pool))) == NULL)
		return (NULL);
	temp->fd = fd;
	if ((temp->text = (char *)ft_memalloc(sizeof(char))) == NULL)
	{
		free(temp);
		return (NULL);
	}
	if ((new = ft_lstnew(temp, sizeof(t_file_pool))) == NULL)
	{
		free(temp->text);
		free(temp);
		return (NULL);
	}
	ft_lstadd(file_list, new);
	free(temp);
	return ((t_file_pool *)((*file_list)->content));
}

int					get_next_line(int const fd, char **line)
{
	static t_list	*file_list = NULL;
	t_file_pool		*file;
	ssize_t			size;
	char			*ptr;

	if (fd < 0 || NULL == line || BUFF_SIZE < 1)
		return (-1);
	size = 1;
	if ((file = get_buffer(&file_list, fd)) == NULL)
		return (-1);
	while (size != 0 && (ptr = ft_strchr(file->text, 0x0a)) == NULL)
	{
		size = read_more(fd, &(file->text));
		if (size == -1)
			return (-1);
	}
	manage_pointers(line, &(file->text), ptr);
	return (!(size == 0 && ft_strlen(*line) == 0));
}
