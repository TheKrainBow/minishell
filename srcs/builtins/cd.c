/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 16:34:24 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signum;

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		n_args;

	n_args = ft_tablen(cmd->args);
	if (n_args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		g_signum = 1;
		return ;
	}
	if (n_args == 1)
		path = get_var_from_env(cmd->data->env, "HOME") + 5;
	else
		path = cmd->args[1];
	g_signum = chdir(path);
	path = getcwd(NULL, 0);
	if (!g_signum)
		set_env_var(cmd->data->env, "PWD", path);
	free(path);
}
