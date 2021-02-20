/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_to_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:02:29 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 23:00:20 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_is_builtins(char *arg)
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

void		ft_node(t_data *data)
{
	t_list	*tmp;
	int		redirect;
	static void		(*functions[8])(t_cmd *cmd, t_data *data) =
	{
		ft_cmd,
		echo,
		cd,
		pwd,
		ft_export_env,
		ft_unset_env,
		ft_print_env,
		ft_exit
	};
	t_cmd	cmd;

	tmp = data->parsed_line;
	while (tmp)
	{
		cmd.args = ft_lst_to_tab(tmp->content);
		if (!cmd.args || !cmd.args[0])
		{
			ft_free_tab(cmd.args);
			return ;
		}
		redirect = ft_is_builtins(cmd.args[0]);
		functions[redirect](&cmd, data);
		dprintf(data->db.term2, "%d\n", redirect);
		tmp = tmp->next;
		ft_free_tab(cmd.args);
	}
}