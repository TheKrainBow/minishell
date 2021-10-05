/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:56:05 by magostin          #+#    #+#             */
/*   Updated: 2021/07/02 17:25:29 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "minishell.h"

void	reset_std(t_data *data)
{
	dup2(data->fd.stdin_save, 0);
	dup2(data->fd.stdout_save, 1);
}

void	pipe_next(t_cmd **cmd, t_cmd **prev_cmd, t_data *data)
{
	pipe((*cmd)->fds);
	dup2((*cmd)->fds[1], 1);
	close((*cmd)->fds[1]);
	if ((*prev_cmd) && (*prev_cmd)->piped)
	{
		dup2((*prev_cmd)->fds[0], 0);
		close((*prev_cmd)->fds[0]);
	}
	g_pid.pid = fork();
	if (!g_pid.pid)
	{
		pars_redirection_cmd((*cmd));
		ft_node_cmd((*cmd), data);
		ft_free_tab((*cmd)->args);
		ft_close_fd((*cmd)->fd_out);
		ft_close_fd((*cmd)->fd_in);
		reset_std(data);
		free((*cmd));
		exit(1);
	}
	else
		(*cmd)->pid = g_pid.pid;
	close(1);
	reset_std(data);
}

void	pipe_prev(t_cmd **cmd, t_cmd **prev_cmd, t_data *data)
{
	if ((*prev_cmd) && (*prev_cmd)->piped)
	{
		dup2((*prev_cmd)->fds[0], 0);
		close((*prev_cmd)->fds[0]);
	}
	pars_redirection_cmd((*cmd));
	ft_node_cmd((*cmd), data);
	reset_std(data);
}

void	apply_pipeline(t_data *data)
{
	t_list		*current;
	t_list		*next;
	t_cmd		*cmd;
	t_cmd		*prev_cmd;

	ft_free_list(data->lexed_line);
	current = data->parsed_line;
	prev_cmd = NULL;
	g_pid.pid = 0;
	while (current)
	{
		apply_env(data, current);
		next = current->next;
		cmd = (t_cmd *)current->content;
		if (cmd && cmd->piped)
			pipe_next(&cmd, &prev_cmd, data);
		else
			pipe_prev(&cmd, &prev_cmd, data);
		prev_cmd = cmd;
		current = next;
	}
}
