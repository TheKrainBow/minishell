/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:06:50 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 14:16:24 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_minishell(t_list *lst)
{
	int		size;

	size = 0;
	while (lst && separator((char *)lst->content) == 0)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	**ft_lst_to_tab_minishell(t_list *lst)
{
	char	**dest;
	int		i;

	dest = malloc(sizeof(char *) * (ft_lstsize_minishell(lst) + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (lst && separator((char *)lst->content) == 0)
	{
		dest[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
