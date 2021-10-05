/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:44:44 by magostin          #+#    #+#             */
/*   Updated: 2021/07/02 17:25:24 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redir(t_cmd *cmd, int *i, char type)
{
	char		**args_temp;

	args_temp = cmd->args;
	cmd->args = ft_strs_rmi(cmd->args, ft_tablen(cmd->args), *i);
	ft_free_tab(args_temp);
	if (type == '>')
		redirect_out(cmd, cmd->args[*i], 0);
	else if (type == '<')
		redirect_in(cmd, cmd->args[*i]);
	else
		redirect_out(cmd, cmd->args[*i], 1);
	args_temp = cmd->args;
	cmd->args = ft_strs_rmi(cmd->args, ft_tablen(cmd->args), *i);
	ft_free_tab(args_temp);
	(*i)--;
}

void	pars_redirection_cmd(t_cmd *cmd)
{
	int			i;

	i = -1;
	while (cmd && cmd->args && cmd->args[++i])
	{
		if (ft_strcmp(cmd->args[i], ">") == 0)
			apply_redir(cmd, &i, '>');
		else if (ft_strcmp(cmd->args[i], ">>") == 0)
			apply_redir(cmd, &i, '+');
		else if (ft_strcmp(cmd->args[i], "<") == 0)
			apply_redir(cmd, &i, '<');
	}
}

void	pars_redirection(t_data *data)
{
	t_list		*temp;
	t_cmd		*cmd;

	temp = data->parsed_line;
	while (temp)
	{
		cmd = (t_cmd *)temp->content;
		pars_redirection_cmd(cmd);
		temp = temp->next;
	}
}

void	pars_line_v2(t_data *data)
{
	t_list		*lexed_line;
	t_list		*i;

	data->parsed_line = NULL;
	lexed_line = data->lexed_line;
	if (!(lexed_line))
		return ;
	i = data->lexed_line;
	while (i)
	{
		if (ft_strcmp(";", (char *)i->content) == 0)
		{
			ft_lstadd_back(&data->parsed_line, create_cmd(lexed_line, 0));
			lexed_line = i->next;
		}
		else if (ft_strcmp("|", (char *)i->content) == 0)
		{
			ft_lstadd_back(&data->parsed_line, create_cmd(lexed_line, 1));
			lexed_line = i->next;
		}
		i = i->next;
	}
	if (lexed_line)
		ft_lstadd_back(&data->parsed_line, create_cmd(lexed_line, 0));
	apply_pipeline(data);
}
