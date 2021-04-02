/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:29:17 by atable            #+#    #+#             */
/*   Updated: 2020/05/19 19:06:48 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (str1[0] == '\0' || str2[0] == '\0')
		return ((unsigned char)str1[0] - (unsigned char)str2[0]);
	while ((str1[i] && str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (str1[i] == '\0' || str2[i] == '\0')
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
