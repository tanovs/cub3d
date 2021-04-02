/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:52:46 by atable            #+#    #+#             */
/*   Updated: 2020/05/18 19:15:56 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dest, const char *source, size_t n)
{
	unsigned int	i;
	size_t			size;

	if (!dest && !source)
		return (0);
	i = 0;
	size = ft_strlen(source);
	if (n == 0)
		return (size);
	while (source[i] && (i < (n - 1)))
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (size);
}
