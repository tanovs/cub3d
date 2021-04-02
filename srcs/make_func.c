/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:43:52 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 00:05:07 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	make_path(char *line, char **field)
{
	int	res;

	line = skip_spaces(line);
	if ((res = check_line(line)) == -1)
		return (-1);
	*field = ft_substr(line, 0, res);
	return (0);
}

int	make_resolution(t_res *resol, char *line)
{
	line = skip_spaces(line);
	if (check_num_line(line, 'R') == -1)
		return (-1);
	resol->w = ft_atoi(line);
	line = skip_num(line);
	if (*line != ' ')
		return (-1);
	resol->h = ft_atoi(line);
	line = skip_num(line);
	line = skip_spaces(line);
	if (*line != '\0')
		return (-1);
	return (0);
}

int	make_ceil_floor_color(t_color *side, char *line)
{
	line = skip_spaces(line);
	if (check_num_line(line, 'F') == -1)
		return (-1);
	side->red = ft_atoi(line);
	line = skip_num(line);
	line = skip_spaces(line);
	if (*line != ',')
		return (-1);
	line++;
	side->green = ft_atoi(line);
	line = skip_num(line);
	line = skip_spaces(line);
	if (*line != ',')
		return (-1);
	line++;
	side->blue = ft_atoi(line);
	line = skip_num(line);
	line = skip_spaces(line);
	if (*line != '\0')
		return (-1);
	if (side->blue > 255 || side->green > 255 || side->red > 255)
		return (-1);
	return (0);
}