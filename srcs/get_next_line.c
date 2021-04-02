/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanos <tanos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:44:37 by atable            #+#    #+#             */
/*   Updated: 2020/09/05 10:44:26 by tanos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	new_keeper(char **keeper, char *str, int start)
{
	char	*tmp;

	tmp = *keeper;
	if (!(*keeper = ft_substr(str, start, ft_strlen(str) - start)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

int	follow_str(char *str, char *sym)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	*sym = str[i];
	return (i);
}

int	write_line(char *buf, char **line, char **keeper)
{
	char	*str;
	char	*tmp;
	char	sym;
	int		i;

	i = follow_str(buf, &sym);
	if (!(str = ft_substr(buf, 0, i)))
		return (-1);
	tmp = *line;
	if (!(*line = ft_strjoin(*line, str)))
	{
		free(tmp);
		free(str);
		return (-1);
	}
	free(tmp);
	free(str);
	if (buf[i] != '\0')
		if (new_keeper(keeper, buf, i + 1) == -1)
			return (-1);
	if (buf[i] == '\n')
		return (1);
	return (2);
}

int	rekeeper(char **keeper, char **line)
{
	char	*tmp;
	char	sym;

	tmp = *line;
	if (!(*line = ft_substr(*keeper, 0, follow_str(*keeper, &sym))))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	if (follow_str(*keeper, &sym) != (int)ft_strlen(*keeper))
	{
		if (new_keeper(keeper, *keeper, follow_str(*keeper, &sym) + 1) == -1)
			return (-1);
		if (sym == '\n')
			return (1);
	}
	else
	{
		free(*keeper);
		*keeper = NULL;
	}
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static char	*keeper;
	char		buf[11];
	int			res;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_strdup("");
	if (keeper)
	{
		res = rekeeper(&keeper, line);
		if (res != 2)
			return (res);
	}
	while ((res = read(fd, buf, 10)) > 0)
	{
		buf[res] = '\0';
		if ((res = write_line(buf, line, &keeper)) != 2 && res != 0)
			return (res);
		if (res == 0)
			break ;
	}
	if (res < 0)
		return (-1);
	free(keeper);
	return (0);
}
