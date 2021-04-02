/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 23:58:22 by tanos             #+#    #+#             */
/*   Updated: 2020/10/08 23:52:26 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (0);
}

void	free_line(char **line)
{
	char	*tmp;

	tmp = *line;
	free(tmp);
	*line = NULL;
}

void	free_path(t_data *data)
{
	if (data->west_path != NULL)
		free_line(&data->west_path);
	if (data->sprite_path != NULL)
		free_line(&data->sprite_path);
	if (data->south_path != NULL)
		free_line(&data->south_path);
	if (data->north_path != NULL)
		free_line(&data->north_path);
	if (data->east_path != NULL)
		free_line(&data->east_path);
}

int		free_struct(t_data *data)
{
	free_path(data);
	if (data->map != NULL)
		free_array(data->map);
	return (0);
}

int		free_func(t_data *data, t_list **list)
{
	free_struct(data);
	ft_lstclear(list);
	ft_putstr("Error\nNot valid file\n");
	return (-1);
}