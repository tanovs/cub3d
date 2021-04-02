/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:24:11 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 00:04:34 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	moove_img_to_bmp(int fd, t_bmp *bmp, t_vars *cub)
{
	int	i;
	int	j;
	int	*res;

	if (!(res = (int*)malloc(bmp->biwidth * bmp->biheight * sizeof(int))))
		return (-1);
	i = 0;
	j = 0;
	while (i < bmp->biheight)
	{
		while (j < bmp->biwidth)
		{
			res[i * bmp->biwidth + j] = *(int*)(cub->wind.adr +
				((bmp->biheight - i) * cub->wind.ll + j * (cub->wind.bpp / 8)));
			j++;
		}
		j = 0;
		i++;
	}
	write(fd, res, bmp->bisizeimage);
	free(res);
	return (0);
}

static int	write_bmp(t_bmp bmp, t_vars *cub)
{
	int	fd;

	if ((fd = open("cub3d.bmp", O_CREAT | O_WRONLY |
		O_TRUNC | O_APPEND, 0777)) < 0)
		return (-1);
	write(fd, &bmp.bftype, 2);
	write(fd, &bmp.bfsize, 4);
	write(fd, &bmp.bfreserved1, 2);
	write(fd, &bmp.bfreserved2, 2);
	write(fd, &bmp.bfoffbits, 4);
	write(fd, &bmp.bisize, 4);
	write(fd, &bmp.biwidth, 4);
	write(fd, &bmp.biheight, 4);
	write(fd, &bmp.biplanes, 2);
	write(fd, &bmp.bibitcount, 2);
	write(fd, &bmp.bicompression, 4);
	write(fd, &bmp.bisizeimage, 4);
	write(fd, &bmp.bixpelspermeter, 4);
	write(fd, &bmp.biypelspermeter, 4);
	write(fd, &bmp.biclrused, 4);
	write(fd, &bmp.biclrimportant, 4);
	moove_img_to_bmp(fd, &bmp, cub);
	close(fd);
	return (0);
}

static int initial_bmp(t_bmp *bmp, t_vars *cub)
{
	bmp->bftype[0] = 'B';
	bmp->bftype[1] = 'M';
	bmp->bfsize = 54 + 4 * (cub->wind.resol.h * cub->wind.resol.w);
	bmp->bfreserved1 = 0;
	bmp->bfreserved2 = 0;
	bmp->bfoffbits = 54;
	bmp->bisize = 40;
	bmp->biwidth = cub->wind.resol.w;
	bmp->biheight = cub->wind.resol.h;
	bmp->biplanes = 1;
	bmp->bibitcount = 32;
	bmp->bicompression = 0;
	bmp->bisizeimage = 4 * (cub->wind.resol.h * cub->wind.resol.w);
	bmp->bixpelspermeter = 0;
	bmp->biypelspermeter = 0;
	bmp->biclrused = 0;
	bmp->biclrimportant = 0;
	return (0);
}

int			make_bmp(t_vars *cub)
{
	t_bmp	bmp;

	initial_bmp(&bmp, cub);
	write_bmp(bmp, cub);
	del_win(cub);
	return (0);
}