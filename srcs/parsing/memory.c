/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:52:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 02:53:05 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(void *ptr)
{
	t_lexer *lexer = ptr;
	free(lexer->str);
	free(lexer);
}

void	free_cmd(void *ptr)
{
	t_cmd *cmd = ptr;
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i++]);
	}
	free(cmd->args);
	free(cmd);
}
