/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:57:35 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 00:20:07 by maagosti         ###   ########.fr       */
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

static void	remove_token(t_token token, t_list **node)
{
	if (token == PIPE)
	{
		*node = (*node)->next;
		return ;
	}
	*node = (*node)->next;
	((t_lexer *)(*node)->content)->token = ((t_lexer *)(*node)->prev->content)
		->token;
	ft_lstrmone((*node)->prev, &free_lexer);
	*node = (*node)->next;
}

int	token_error(t_list **tokens)
{
	if (!(*tokens)->next)
	{
		ft_printf("minishell: syntax error near unexpected"
			" token `newline'\n");
		return (ft_lstclear(tokens, &free_lexer), 0);
	}
	if (((t_lexer *)(*tokens)->next->content)->token
		!= T_NONE)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			token_to_strs(((t_lexer *)(*tokens)->next->content)->token));
		return (ft_lstclear(tokens, &free_lexer), 0);
	}
	return (0);
}

int	check_tokens(t_list **tokens)
{
	t_list	*prev;
	t_token	token;

	while (*tokens)
	{
		token = ((t_lexer *)(*tokens)->content)->token;
		if (token == T_NONE)
		{
			prev = (*tokens);
			(*tokens) = (*tokens)->next;
			continue ;
		}
		if (!(*tokens)->next
			|| ((t_lexer *)(*tokens)->next->content)->token != T_NONE)
			return (token_error(tokens));
		remove_token(token, tokens);
	}
	*tokens = prev;
	ft_lstfirst(tokens);
	return (1);
}
