/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 19:02:33 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signum;

static void	move_to_dir(char **env, char *path)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	g_signum = -chdir(path);
	if (g_signum)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		return (free(oldpwd));
	}
	set_env_var(env, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	set_env_var(env, "PWD", newpwd);
	free(newpwd);
}

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
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		path = get_var_from_env(cmd->data->env, "OLDPWD") + 7;
		ft_printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	move_to_dir(cmd->data->env, path);
}
