/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:41:09 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 14:53:47 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_func_cmd	get_cmd(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (&ft_echo);
	if (!ft_strcmp(name, "cd"))
		return (&ft_cd);
	if (!ft_strcmp(name, "pwd"))
		return (&ft_pwd);
	if (!ft_strcmp(name, "unset"))
		return (&ft_unset);
	if (!ft_strcmp(name, "env"))
		return (&ft_env);
	if (!ft_strcmp(name, "export"))
		return (&ft_export);
	if (!ft_strcmp(name, "exit"))
		return (&ft_exit);
	return (&ft_execve);
}

void	pipe_prev(t_list *node)
{
	t_cmd	*prev_cmd;
	t_cmd	*cmd;

	cmd = node->content;
	if (node->prev)
	{
		prev_cmd = node->prev->content;
		dup2(prev_cmd->pipe[0], STDIN_FILENO);
		close(prev_cmd->pipe[0]);
	}
	ft_lstiter(cmd->out, &handle_redirection);
	get_cmd(cmd->name)(cmd);
}

void	pipe_next(t_list *node)
{
	t_cmd	*cmd;

	cmd = node->content;
	pipe(cmd->pipe);
	dup2(cmd->pipe[1], STDOUT_FILENO);
	close(cmd->pipe[1]);
	if (node->prev)
	{
		dup2(((t_cmd *)node->prev->content)->pipe[0], STDIN_FILENO);
		close(((t_cmd *)node->prev->content)->pipe[0]);
	}
	cmd->pid = fork();
	if (!cmd->pid)
	{
		ft_lstiter(cmd->out, &handle_redirection);
		get_cmd(cmd->name)(cmd);
		close(cmd->pipe[0]);
		dup2(cmd->data->std_in, STDIN_FILENO);
		dup2(cmd->data->std_out, STDOUT_FILENO);
		free_data(cmd->data);
		exit(cmd->data->last_error);
	}
}
