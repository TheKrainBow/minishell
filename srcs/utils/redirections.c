/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:41:59 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 04:44:04 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_options(t_token token)
{
	if (token == OUT_APPEND)
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (token == OUT_TRUNCATE)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	if (token == IN)
		return (O_RDONLY);
	return (0);
}

void	handle_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	content->fd = open(content->str, open_options(content->token), 0777);
	if (content->fd < 0)
	{
		dprintf(2, "minishell: no such file or directory: %s\n", content->str);
		return ;
	}
	dup2(content->fd, content->token != IN);
}

void	close_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	close(content->fd);
}
