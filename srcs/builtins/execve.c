/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:31:43 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 04:21:23 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_from_env(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	return (env[i]);
}

char	*get_path(t_cmd *cmd)
{
	int		i;
	char	*dest;
	char	**path;
	char	*tmp;

	if (ft_strchr(cmd->name, '/'))
		return (ft_strdup(cmd->name));
	i = 0;
	tmp = get_var_from_env(cmd->data->env, "PATH");
	if (!tmp)
		return (ft_strdup(cmd->name));
	path = ft_split(tmp + 5, ':');
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

void	ft_execve(t_cmd *cmd)
{
	int		ret;
	int		pid;
	char	*tmp_name;

	ret = 0;
	tmp_name = get_path(cmd);
	pid = fork();
	if (pid == 0)
	{
		ret = execve(tmp_name, cmd->args, cmd->data->env) * -127;
		if (tmp_name != cmd->name)
			free(tmp_name);
		free_data(cmd->data);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	free(tmp_name);
	if (WIFEXITED(ret))
		cmd->data->last_error = WEXITSTATUS(ret);
	else
		cmd->data->last_error = 0;
	if (cmd->data->last_error == 127)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->name, 2);
	}
	return ;
}
