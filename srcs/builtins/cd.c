/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 14:27:08 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		n_args;

	n_args = ft_tablen(cmd->args);
	if (n_args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		cmd->data->last_error = 1;
		return ;
	}
	if (n_args == 1)
		path = get_var_from_env(cmd->data->env, "HOME=");
	else
		path = cmd->args[1];
	cmd->data->last_error = chdir(path);
}
