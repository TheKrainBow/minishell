/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:51:06 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 02:51:51 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lst_conv(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (ft_strdup(lexer->str));
}

int	is_pipe(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (lexer->token == PIPE);
}

int	is_arg(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (lexer->token == T_NONE);
}
