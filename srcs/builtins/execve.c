/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:31:43 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/24 23:57:32 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_from_env(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	path = ft_split(env[i] + 5, ':');
	return (path);
}

char	*get_path(t_cmd *cmd)
{
	int		i;
	char	*dest;
	char	**path;
	char	*tmp;

	i = 0;
	path = get_path_from_env(cmd->data->env);
	tmp = ft_strjoin("/", cmd->name);
	while (path && path[i])
	{
		dest = ft_strjoin(path[i], tmp);
		if (access(dest, F_OK | X_OK) == 0)
		{
			free(tmp);
			ft_free_tab(path);
			return (dest);
		}
		free(dest);
		i++;
	}
	ft_free_tab(path);
	free(tmp);
	return (NULL);
}

int	ft_execve(t_cmd *cmd)
{
	int		status;
	int		pid;
	char	*tmp_name;

	status = 0;
	tmp_name = get_path(cmd);
	pid = fork();
	if (pid == 0)
	{
		if (execve(tmp_name, cmd->args, cmd->data->env) == -1)
		{
			if (tmp_name != cmd->name)
				free(tmp_name);
			return (0);
		}
	}
	else
	{
		if (tmp_name != cmd->name)
			free(tmp_name);
		wait(&status);
	}
	return (1);
}
