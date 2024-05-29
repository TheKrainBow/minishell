/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giorgi <giorgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 03:03:14 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/30 00:02:56 by giorgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	//size_t	i;
	size_t	src_size;

	src_size = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len == 0 || start > src_size)
		return (ft_strdup(""));
	//i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s + start, len + 1);
	return (dest);
}
