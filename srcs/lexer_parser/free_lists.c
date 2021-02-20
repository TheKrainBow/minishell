/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:31:54 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/20 22:37:25 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_sublist(t_list *node)
{
	if (node->content)
		free(node->content);
	if (node->next)
		ft_free_sublist(node->next);
	free(node);
}

void	ft_free_list(t_list *big_node)
{
	if (big_node->content)
		ft_free_sublist(big_node->content);
	if (big_node->next)
		ft_free_list(big_node->next);
	free(big_node);
}
