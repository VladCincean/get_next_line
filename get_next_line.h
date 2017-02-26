/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcincean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:01:26 by vcincean          #+#    #+#             */
/*   Updated: 2017/02/14 15:17:37 by vcincean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFF_SIZE 32

typedef struct	s_file_pool
{
	int		fd;
	char	*text;
}				t_file_pool;

int				get_next_line(int const fd, char **line);

#endif
