/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:59:17 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 20:39:00 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_lstadd_back_lexer(t_lex **alst, t_lex *new)
{
	t_lex *maillon;

	if (!alst || !new)
		return ;
	maillon = *alst;
	if (!maillon)
	{
		*alst = new;
		return ;
	}
	while (maillon->next != NULL)
		maillon = maillon->next;
	maillon->next = new;
	new->next = NULL;
}

t_lex	*ft_lstnew_lexer(char *c, int s, int c_type)
{
	t_lex	*maillon;

	if (!(maillon = (t_lex *)malloc(sizeof(t_lex))))
		return (0);
	maillon->content.c = c;
	maillon->content.s = s;
	maillon->content.c_type = c_type;
	maillon->next = NULL;
	return (maillon);
}
