/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanos <tanos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:46:06 by atable            #+#    #+#             */
/*   Updated: 2020/09/05 11:33:50 by tanos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list *tmp;
	t_list *buff;

	if (!lst)
		return ;
	buff = *lst;
	while (buff)
	{
		tmp = buff->next;
		ft_lstdelone(buff);
		buff = tmp;
	}
	*lst = NULL;
}
