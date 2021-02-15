/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:04:56 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 13:17:15 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_tab(char **strs)
{
	int			i;

	i = -1;
	while (strs && strs[++i])
	{
		ft_putstr_fd(strs[i], 1);
		ft_putchar_fd('\n', 1);
	}
}