/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:52:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/21 01:28:15 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(void *ptr)
{
	t_lexer	*lexer;

	lexer = ptr;
	free(lexer->str);
	free(lexer);
}

void	free_cmd(void *ptr)
{
	t_cmd	*cmd;
	int		i;

	cmd = ptr;
	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	if (cmd->out)
		ft_lstclear(&cmd->out, &free_lexer);
	free(cmd->args);
	free(cmd);
}

t_data	*init_data(char **environ)
{
	t_data	*dest;

	dest = ft_calloc(1, sizeof(t_data));
	dest->env = ft_tabcpy(environ);
	dest->std_in = dup(STDIN_FILENO);
	dest->std_out = dup(STDOUT_FILENO);
	return (dest);
}

void	free_data(t_data *data)
{
	ft_free_tab(data->env);
	free(data);
}
