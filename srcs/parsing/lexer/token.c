/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:57:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 02:59:45 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_to_strs(t_token token)
{
	if (token == PIPE)
		return ("|");
	if (token == OUT_TRUNCATE)
		return (">");
	if (token == OUT_APPEND)
		return (">>");
	if (token == IN)
		return ("<");
	if (token == HERE_DOC)
		return ("<<");
	if (token == WHITESPACE)
		return ("space");
	return ("arg");
}

t_token	get_token(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	if (!ft_strncmp(str, "<<", 2))
		return (HERE_DOC);
	if (!ft_strncmp(str, ">>", 2))
		return (OUT_APPEND);
	if (!ft_strncmp(str, ">", 1))
		return (OUT_TRUNCATE);
	if (!ft_strncmp(str, "<", 1))
		return (IN);
	if (ft_iswhitespace(*str))
		return (WHITESPACE);
	return (T_NONE);
}

static t_lexer	*get_lexer(void *ptr)
{
	return (ptr);
}

int	check_tokens(t_list **tokens)
{
	t_list	*node;
	t_token	token;

	node = *tokens;
	while (node)
	{
		token = get_lexer(node->content)->token;
		if (token == T_NONE || token == PIPE)
		{
			node = node->next;
			continue ;
		}
		if (!node->next || get_lexer(node->next->content)->token != T_NONE)
		{
			printf("minishell: parse error near `%s'\n", token_to_strs(get_lexer(node->content)->token));
			ft_lstclear(tokens, &free_lexer);
			return (0);
		}
		node = node->next;
		get_lexer(node->content)->token = get_lexer(node->prev->content)->token;
		ft_lstrmone(node->prev, &free_lexer);
		node = node->next;
	}
	return (1);
}
