/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 22:49:14 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 00:11:20 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	side(char sym)
{
	if (sym == 'N')
		return (270);
	if (sym == 'W')
		return (180);                   
	if (sym == 'S')
		return (90);
	if (sym == 'E')
		return (0);
}

static int		make_position(t_vars *cub, int i, int j, char c)
{
	cub->pos.x = j;
	cub->pos.y = i;
	cub->pos.dir = side(c);
	return (0);
}

int				start_pos(t_vars *cub, char ***array)
{
	char	**arr;
	int		i;
	int		j;
	
	i = 0;
	arr = *array;
	cub->raws = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_memchr("NSWE", arr[i][j], 5))
			{
				make_position(cub, i, j, arr[i][j]);
				arr[i][j] = '0';
			}
			j++;
		}
		if (j > cub->raws)
			cub->raws = j;
		i++;
	}
	cub->lines = i;
	return (0);
}