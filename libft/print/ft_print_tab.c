/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:04:56 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 23:56:27 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_tab(char **strs)
{
	ft_print_tab_fd(strs, 1);
}

void		ft_print_tab_fd(char **strs, int fd)
{
	int			i;

	i = -1;
	while (strs && strs[++i])
	{
		ft_putstr_fd(strs[i], fd);
		ft_putchar_fd('\n', fd);
	}
}