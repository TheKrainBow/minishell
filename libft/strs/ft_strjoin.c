/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 03:11:06 by magostin          #+#    #+#             */
/*   Updated: 2021/02/22 20:12:41 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	int		j;
	char	*dest;

	size = 0;
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_strlen(s2);
	if (!(dest = malloc((size + 1) * sizeof(char))))
		return (0);
	i = -1;
	if (s1)
		while (s1[++i])
			dest[i] = s1[i];
	else
		i = 0;
	j = -1;
	if (s2)
		while (s2[++j])
			dest[i + j] = s2[j];
	dest[i + j] = 0;
	return (dest);
}
