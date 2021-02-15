/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:51:14 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 17:45:51 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstprint_fd(t_list *lst, int fd)
{
	int		i;

	i = 0;
	while (lst)
	{
		/*ft_putchar_fd('|', fd);
		ft_putstr_fd((char *)lst->content, fd);
		ft_putstr_fd("|\n", fd);*/
		dprintf(fd, " %-4d\033[1;31m[\033[0m%s\033[1;31m]\033[0m\n", i, (char *)lst->content);
		lst = lst->next;
		i++;
	}
}

void		ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("|%s|\n", (char *)lst->content);
		lst = lst->next;
	}
}