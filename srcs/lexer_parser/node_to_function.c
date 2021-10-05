/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_to_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:02:29 by magostin          #+#    #+#             */
/*   Updated: 2021/10/05 15:25:12 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtins(char *arg)
{
	if (!(ft_strcmp(arg, "echo")))
		return (1);
	if (!(ft_strcmp(arg, "cd")))
		return (2);
	if (!(ft_strcmp(arg, "pwd")))
		return (3);
	if (!(ft_strcmp(arg, "export")))
		return (4);
	if (!(ft_strcmp(arg, "unset")))
		return (5);
	if (!(ft_strcmp(arg, "env")))
		return (6);
	if (!(ft_strcmp(arg, "exit")))
		return (7);
	return (0);
}

void	ft_node_cmd(t_cmd *cmd, t_data *data)
{
	int				redirect;
	static void		(*functions[8])(t_cmd *cmd, t_data *data) =
	{ft_cmd, ft_echo, ft_cd, ft_pwd, ft_export_env, ft_unset_env,
	ft_print_env, ft_exit};

	data->wexitstatus = 0;
	redirect = ft_is_builtins(cmd->args[0]);
	functions[redirect](cmd, data);
}

void	ft_node(t_data *data)
{
	t_list			*temp;
	int				redirect;
	t_cmd			*cmd;
	static void		(*functions[8])(t_cmd *cmd, t_data *data) =
	{ft_cmd, ft_echo, ft_cd, ft_pwd, ft_export_env, ft_unset_env,
	ft_print_env, ft_exit};

	temp = data->parsed_line;
	while (temp)
	{
		cmd = (t_cmd *)temp->content;
		redirect = ft_is_builtins(cmd->args[0]);
		functions[redirect](cmd, data);
		temp = temp->next;
	}
}
