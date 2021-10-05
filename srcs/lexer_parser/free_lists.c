/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:31:54 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/04/07 23:43:20 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_sublist(t_list *node)
{
	if (node && node->content)
		free(node->content);
	if (node && node->next)
		ft_free_sublist(node->next);
	free(node);
}

void	ft_free_list(t_list *big_node)
{
	if (big_node && big_node->content)
		free(big_node->content);
	if (big_node && big_node->next)
		ft_free_list(big_node->next);
	free(big_node);
}
