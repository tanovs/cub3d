/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_to_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 10:27:37 by tanos             #+#    #+#             */
/*   Updated: 2020/10/09 10:48:10 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			moove_to_struct(t_data *data, char *line)
{
	line = skip_spaces(line);
	if (ft_strnstr(line, "NO", 2))
		return (make_path(line + 2, &data->north_path));       
	else if (ft_strnstr(line, "SO", 2))
		return (make_path(line + 2, &data->south_path));
	else if (ft_strnstr(line, "WE", 2))
		return (make_path(line + 2, &data->west_path));
	else if (ft_strnstr(line, "EA", 2))
		return (make_path(line + 2, &data->east_path));
	else if (ft_strnstr(line, "S ", 2))
		return (make_path(line + 2, &data->sprite_path));
	else if (*line == '1')
		return (2);      
	else if (ft_strnstr(line, "R ", 2))
		return (make_resolution(&data->resol, line + 1));
	else if (ft_strnstr(line, "F ", 2))
		return (make_ceil_floor_color(&data->floor, line + 1));
	else if (ft_strnstr(line, "C ", 2))
		return (make_ceil_floor_color(&data->ceiling, line + 1));
	else if (*line == '\0')
		return (0);      
	return (-1);
}

static int	check_horizont_walls1(char *prev, char *cur, char *next)
{
	int	i;
	int	size_prev;
	int	size_next;

	i = 0;
	size_prev = ft_strlen(prev);
	size_next = ft_strlen(next);
	while (cur[i] != '\0')
	{
		if (ft_memchr("NSWE02", cur[i], 6))
		{
			if (i > size_prev || i > size_next)
				return (-1);
			if (prev[i] == ' ' || next[i] == ' ')
				return (-1);
			if (prev[i] == '\0' || next[i] == '\0')
				return (-1);
			if (cur[i - 1] == ' ' || cur[i - 1] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	check_horizont_walls(t_list *list)
{
	char	*prev;
	char	*cur;
	char	*next;

	prev = list->content;
	list = list->next;
	cur = list->content;
	list = list->next;
	next = list->content;
	list = list->next;
	while (list)
	{
		if (check_horizont_walls1(prev, cur, next) == -1)
			return (-1);
		prev = cur;
		cur = next;
		next = list->content;
		list = list->next;
	}
	return (0);
}

int help_fun(int fl)
{
	if (fl == 0)
		return (-1);
	return (0);
}

static int	check_list(t_list *list, int *size)
{
	int		fl;
	int		i;
	int		res;
	char	*tmp;

	fl = 0;
	i = -1;
	while (list)
	{
		if (++i == 0 || i == (*size - 1))
			if (check_first_last_line(list->content, tmp) == -1)
				return (-1);
		if ((check_map_content(list->content, &fl) == -1) ||
			((res = check_vertical_wall(list->content)) == -1))
			return (-1);
		if (res == 1)
		{
			*size -= 1;
			i -= 1;
		}
		if (res == 0)
			tmp = list->content;
		list = list->next;
	}
	return (help_fun(fl));
}

char		**moove_map_to_struct(t_list *list)
{
	int		i;
	int		size;
	char	**array;

	size = ft_lstsize(list);
	if (check_list(list, &size) == -1 || check_horizont_walls(list) == -1)
		return (NULL);	
	i = 0;
	if (!(array = (char **)malloc(sizeof(char *) * (size + 1))))
		return (0);
	while (list && list->content[0] != '\0' && list->content[0] != '\n')
	{
		if (!(array[i] = ft_strdup(list->content)))
		{
			free_array(array);
			return (NULL);
		}
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}