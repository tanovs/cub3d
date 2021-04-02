/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 09:57:01 by tanos             #+#    #+#             */
/*   Updated: 2020/10/09 10:47:34 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define M_PI 3.1415926535

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"

typedef struct		s_bmp
{
	char			bftype[2];
	int				bfsize;
	short			bfreserved1;
	short			bfreserved2;
	int				bfoffbits;
	int				bisize;
	int				biwidth;
	int				biheight;
	short			biplanes;
	short			bibitcount;
	int				bicompression;
	int				bisizeimage;
	int				bixpelspermeter;
	int				biypelspermeter;
	int				biclrused;
	int				biclrimportant;
}					t_bmp;

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_res
{
	int				w;
	int				h;
}					t_res;

typedef struct		s_pos
{
	float			x;
	float			y;
	float			dir;
}					t_pos;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct		s_data
{
	t_res			resol;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*sprite_path;
	t_color			floor;
	t_color			ceiling;
	char			**map;
	int				save;
}					t_data;

typedef struct		s_wind
{
	void			*img;
	char			*adr;
	int				bpp;
	int				ll;
	int				endian;
	t_res			resol;
}					t_wind;

typedef struct		s_spr
{
	int				x;
	int				y;
	float			dist;
}					t_spr;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_wind			wind;
	t_wind			north;
	t_wind			south;
	t_wind			east;
	t_wind			west;
	t_wind			sprite;
	t_spr			*spr;
	t_pos			pos;
	int				floor_color;
	int				ceil_color;
	char			**map;
	int				player_size;
	int				t_stepx;
	int				t_stepy;
	int				sprites;
	int				side;
	int				cub_side;
	int				lines;
	int				raws;
	int				n;
	int				save;
	float			*wall_dist;
	float			fov;
	float			fov_rad;
	float			dir_rad;
}					t_vars;

int					ft_atoi(const char *str);
int					ft_isalnum(int c);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst);
void				ft_lstdelone(t_list *lst);
t_list				*ft_lstnew(char *content);
int					ft_lstsize(t_list *lst);
void				*ft_memchr(const void *array, int c, size_t n);
void				ft_putstr(char *s);
char				*ft_strdup(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strlcpy(char *dest, const char *source, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					get_next_line(int fd, char **line);
int					free_struct(t_data *data);
int					free_array(char **array);
int					free_func(t_data *data, t_list **list);
char				*skip_num(char *line);
char				*skip_spaces(char *line);
int					moove_to_struct(t_data *data, char *line);
char				**moove_map_to_struct(t_list *list);
int					check_line(char *line);
int					check_num_line(char *line, char sym);
int					check_vertical_wall(char *line);
int					check_first_last_line(char *line, char *tmp);
int					check_map_content(char *line, int *fl);
int					make_path(char *line, char **field);
int					make_resolution(t_res *resol, char *line);
int					make_ceil_floor_color(t_color *side, char *line);
void				initial_data(t_data *data);
int					initial_cub(t_data *data, t_vars *cub);
int					make_wind(t_data *data);
int					start_pos(t_vars *cub, char ***array);
float				abs_angel(float angel);
void				my_mlx_pixel_put(t_wind *data, int x, int y, int color);
int					draw_ray(t_vars *cub, float ray_dir, int i, float *start);
float				*find_dist(t_vars *cub, float *hor, float *vert);
int					texture_color(t_vars *cub, int height, float *res, int i);
int					keyboard(int key, t_vars *cub);
int					draw_3d_map(t_vars *cub);
void				free_path(t_data *data);
int					del_win(t_vars *cub);
int					draw_sprite(t_vars *cub, float *start);
int					get_color(t_wind data, int x, int y);
int					make_bmp(t_vars *cub);
int					init_path_null(t_vars *cub);
int					get_color(t_wind data, int x, int y);
int					destr(t_vars *cub);

#endif