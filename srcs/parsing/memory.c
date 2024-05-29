/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:52:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 01:09:56 by maagosti         ###   ########.fr       */
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
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->env = ft_tabcpy(environ);
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	data->last_error = 0;
	return (data);
}

void	free_data(t_data *data)
{
	if (data->cmds)
		ft_lstclear(&data->cmds, &free_cmd);
	ft_free_tab(data->env);
	free(data);
}
