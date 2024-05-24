/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:57:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/23 21:28:45 by maagosti         ###   ########.fr       */
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

static void	remove_token(t_token token, t_list **node)
{
	if (token == PIPE)
	{
		*node = (*node)->next;
		return ;
	}
	*node = (*node)->next;
	get_lexer((*node)->content)->token = get_lexer((*node)->prev->content)
	->token;
	ft_lstrmone((*node)->prev, &free_lexer);
	*node = (*node)->next;
}

int	check_tokens(t_list **tokens)
{
	t_list	*prev;
	t_token	token;

	while (*tokens)
	{
		token = get_lexer((*tokens)->content)->token;
		if (token == T_NONE)
		{
			prev = (*tokens);
			(*tokens) = (*tokens)->next;
			continue ;
		}
		if (!(*tokens)->next || get_lexer((*tokens)->next->content)->token != T_NONE)
		{
			printf("minishell: parse error near `%s'\n",
				token_to_strs(get_lexer((*tokens)->content)->token));
			ft_lstclear(tokens, &free_lexer);
			return (0);
		}
		remove_token(token, tokens);
	}
	if (prev)
		*tokens = prev;
	ft_lstfirst(tokens);
	return (1);
}
