/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:37:35 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	join(t_gnl *save, char *b)
{
	char	*ret;
	size_t	b_len;
	size_t	i;

	if (!b)
		return ;
	b_len = ft_strlen(b);
	if (!(ret = malloc(save->offset + b_len + 1)))
		return ;
	i = 0;
	while (i < save->offset)
	{
		ret[i] = save->buf[i];
		i++;
	}
	while (i < save->offset + b_len)
	{
		ret[i] = b[i - save->offset];
		i++;
	}
	ret[i] = 0;
	free(save->buf);
	save->buf = ret;
}

char	*get_line(t_gnl *save)
{
	char	*ret;
	size_t	i;

	if (!(ret = malloc(save->offset + 1)))
		return (0);
	i = 0;
	while (i < save->offset)
	{
		ret[i] = save->buf[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	get_saved(t_gnl *save)
{
	char	*ret;
	size_t	i;

	i = save->offset;
	while (save->buf && save->buf[i])
		i++;
	if (save->offset == i)
	{
		free(save->buf);
		save->buf = 0;
		save->offset = 0;
		return ;
	}
	if (!(ret = malloc(i - save->offset + 1)))
		return ;
	save->offset++;
	i = 0;
	while (save->buf[save->offset])
		ret[i++] = save->buf[save->offset++];
	ret[i] = 0;
	free(save->buf);
	save->buf = ret;
	save->offset = 0;
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	save;
	char			*buf;
	int				r;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line || !(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	r = 1;
	while (no_endl(&save) && (r = read(fd, buf, BUFFER_SIZE)))
	{
		if (r < 0)
		{
			free(buf);
			return (-1);
		}
		buf[r] = 0;
		join(&save, buf);
	}
	free(buf);
	*line = get_line(&save);
	get_saved(&save);
	if (r == 0)
		return (0);
	return (1);
}
