/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 10:06:15 by tanos             #+#    #+#             */
/*   Updated: 2020/10/06 23:28:11 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst);
void				ft_lstdelone(t_list *lst);
t_list				*ft_lstnew(char *content);
int					ft_lstsize(t_list *lst);
void				*ft_memchr(const void *array, int c, size_t n);
char				*ft_strdup(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strlcpy(char *dest, const char *source, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strnstr(const char *big, const char *little, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_putstr(char *s);
int					ft_isalnum(int c);
int					ft_strncmp(const char *str1, const char *str2, size_t n);

#endif