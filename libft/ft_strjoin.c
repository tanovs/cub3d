/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:07:24 by atable            #+#    #+#             */
/*   Updated: 2020/05/22 16:41:22 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (!(result = (char*)malloc((s1_len + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	i = 0;
	while (s2[i] != '\0')
	{
		result[i + s1_len] = s2[i];
		i++;
	}
	result[i + s1_len] = '\0';
	return (result);
}
