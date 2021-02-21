/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:26 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/21 20:14:15 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_char(char *string, int *a, int *b)
{
	int		i;
	char	*new;

	if (!(new = malloc(sizeof(char) * (strlen(string) - 1))))
		return (NULL);
	i = 0;
	while (string && string[i] && i < *a)
	{
		new[i] = string[i];
		i++;
	}
	while (string && string[i] && i + 1 < *b)
	{
		new[i] = string[i + 1];
		i++;
	}
	while (string && string[i])
	{
		new[i] = string[i + 2];
		i++;
	}
	new[i] = '\0';
	*a = -1;
	*b -= 2;
	return (new);
}

char	*quote_bin(char *path)
{
	int		weak;
	int		strong;
	int		i;

	weak = -1;
	strong = -1;
	i = 0;
	while (path && path[i])
	{
		if (path[i] == '\'' && weak == -1)
		{
			if (strong >= 0)
				path = remove_char(path, &strong, &i);
			else
				strong = i;
		}
		else if (path[i] == '"' && strong == -1)
		{
			if (weak >= 0)
				path = remove_char(path, &weak, &i);
			else
				weak = i;
		}
		i++;
	}
	return (path);
}

char	*get_path_in_env(char *var)
{
	int		index;
	char	*path;

	path = NULL;
	index = ft_find_in_env(var);
	if (index >= 0)
		path = ft_strchr( __environ[index], '=') + 1;
	return (path);
}

void	env_update(char *path, t_data *data)
{
	
	char	*oldpath;
	t_cmd	env_update;
	
	oldpath = getcwd(NULL, 0);
	if (!(env_update.args = malloc(sizeof(char*) * 3)))
		return ;
	env_update.args[1] = ft_strjoin("OLDPWD=", oldpath);
	env_update.args[2] = NULL;
	ft_export_env(&env_update, data);
	free(oldpath);
	data->wexitstatus = chdir(path);
	//free(path);
	path = getcwd(NULL, 0);
	free(env_update.args[1]);
	env_update.args[1] = ft_strjoin("PWD=", path);
	//free (path);
	ft_export_env(&env_update, data);
	free(env_update.args[1]);
	free(env_update.args);
}

void	cd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (cmd->args[1] && ft_strcmp("~", cmd->args[1]))
	{
		path = quote_bin(cmd->args[1]);
		if (!ft_strcmp("-", path))
		{
			//free(path);
			path = get_path_in_env("OLDPWD");
		}
	}
	else
		path = get_path_in_env("HOME");
	env_update(path, data);
}
