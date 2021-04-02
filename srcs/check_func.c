/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:42:02 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 10:47:41 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(char *line)
{
	int i;

	i = 0;
	while (*line != ' ' && *line != '\0' && *line != '\n')
	{
		line++;
		i++;
	}
	if (*(line - 1) != 'm' || *(line - 2) != 'p' ||
		*(line - 3) != 'x' || *(line - 4) != '.')
		return (-1);
	if (*line != '\0')
	{
		line = skip_spaces(line);
		if (*line != '\0')
			return (-1);
	}
	return (i);
}

int	check_num_line(char *line, char sym)
{
	int	fl;

	fl = 0;
	while (ft_memchr("0123456789, \n", *line, 13))
	{
		if (ft_isalnum(*line) && ft_memchr(", \0\n", *(line + 1), 5))
			fl++;
		line++;
	}
	if (*line != '\0')
		return (-1);
	if (sym == 'R' && fl != 2)
		return (-1);
	if (sym == 'F' && fl != 3)
		return (-1);
	return (0);
}

int	check_vertical_wall(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (line[i] != '\0')
	{
		if (line[i] == '1')
		{
			j = i;
			while (line[j] != ' ' && line[j] != '\0')
				j++;
			if (line[j - 1] != '1' || (i == (j - 1) && line[i - 1] == '0'))
				return (-1);
			i = j;
		}
		else
			i++;
	}
	if (j == -1 && i != 0)
		return (j);
	if (i == 0)
		return (1);
	return (0);
}

int	check_map_content(char *line, int *fl)
{
	while (*line != '\0')
	{
		if (*line != '1' && *line != '0' && *line != ' ')
		{
			if (*line != '2')
			{
				if (!ft_memchr("NSWE", *line, 4))
					return (-1);
				if (*fl == 1)
					return (-1);
				*fl = 1;
			}
		}
		line++;
	}
	return (0);
}

int	check_first_last_line(char *line, char *tmp)
{
	if (*line == '\0')
		line = tmp;
	while (*line != '\0')
	{
		if (*line != ' ' && *line != '1')
			return (-1);
		line++;
	}
	return (0);
}
