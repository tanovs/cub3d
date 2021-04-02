/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 09:56:31 by atable             #+#    #+#             */
/*   Updated: 2020/09/14 10:40:56 by atable            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	data_from_file(t_list **list, t_data *data)
{
	int		res;
	t_list	*tmp;
	t_list	*buf;

	tmp  = *list;
	while (tmp)
	{
		if ((res = moove_to_struct(data, tmp->content)) == -1)
			return (free_func(data, &tmp));
		if (res == 2)
		{
			if (!(data->map = moove_map_to_struct(tmp)))
				return (free_func(data, &tmp));				
			ft_lstclear(&tmp);
			break ;
		}
		buf = tmp->next;
		ft_lstdelone(tmp);
		tmp = buf;
	}
	*list = NULL;
	return (0);
}

static int	read_from_file(int fd, t_data *data)
{
	char	*line;
	int		tmp;
	t_list	*list;

	line = NULL;
	list = NULL;
	while ((tmp = get_next_line(fd, &line)) == 1)
	{
		ft_lstadd_back(&list, ft_lstnew(line));
		if (!list)
		{
			ft_lstclear(&list);
			ft_putstr("Error\nMemory error\n");
			return (-1);
		}
	}
	ft_lstadd_back(&list, ft_lstnew(line));
	if (!list)
	{
		ft_lstclear(&list);
		ft_putstr("Error\nMemory error\n");
		return (-1);
	}
	return (data_from_file(&list, data));
}

int			check_data_content(t_data *data)
{
	if (!data->east_path || !data->north_path || !data->south_path ||
		!data->west_path || !data->sprite_path || !data->map ||
		data->ceiling.blue == -1 || data->ceiling.green == -1 ||
		data->ceiling.red == -1 || data->floor.red == -1 ||
		data->floor.green == -1 || data->floor.blue == -1 ||
		data->resol.w == -1 || data->resol.h == -1)
	{
		ft_putstr("Error\nNot full file\n");
		free_struct(data);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	initial_data(&data);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr("Error\nOpen file Error\n");
		return(0);
	}
	data.save = 0;
	if ((argc == 3) && (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0))
		data.save = 1;
	if (read_from_file(fd, &data) == -1 || check_data_content(&data) == -1)
		return (0);
	if (make_wind(&data) == -1)
		ft_putstr("Error\nNot valid path\n");
	return (0);
}