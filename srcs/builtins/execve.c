/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:36:14 by magostin          #+#    #+#             */
/*   Updated: 2021/07/07 22:19:55 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/types.h>

void	ft_create_new_path(t_cmd *cmd, char *dir)
{
	char			*temp;
	char			*dest;

	if (dir && dir[0] && dir[ft_strlen(dir) - 1] != '/')
	{
		dest = ft_strjoin(dir, "/");
		temp = dest;
		dest = ft_strjoin(dest, cmd->args[0]);
		free(temp);
		free(cmd->args[0]);
		cmd->args[0] = dest;
	}
	else
	{
		dest = ft_strjoin(dir, cmd->args[0]);
		free(cmd->args[0]);
		cmd->args[0] = dest;
	}
}

int	find_cmd_in_dir(t_cmd *cmd, char *dir)
{
	DIR				*directory;
	struct dirent	*dp;

	directory = opendir(dir);
	if (!directory)
		return (0);
	dp = readdir(directory);
	while (directory && dp != NULL)
	{
		if (ft_strcmp(dp->d_name, ".") && ft_strcmp(dp->d_name, ".."))
		{
			if (!ft_strcmp(dp->d_name, cmd->args[0]))
			{
				ft_create_new_path(cmd, dir);
				closedir(directory);
				return (1);
			}
		}
		dp = readdir(directory);
	}
	closedir(directory);
	return (0);
}

int	ft_find_in_path(t_cmd *cmd, t_data *data)
{
	int			i;

	i = 0;
	while (data->path && data->path[i] && !find_cmd_in_dir(cmd, data->path[i]))
		i++;
	if (!data->path || !data->path[i])
	{
		reset_std(data);
		printf("Minishell: command not found: %s\n", cmd->args[0]);
		data->wexitstatus = 127;
		return (1);
	}
	return (0);
}

void	ft_cmd(t_cmd *cmd, t_data *data)
{
	if (!(ft_strchr(cmd->args[0], '/')))
		if (ft_find_in_path(cmd, data))
			return ;
	ft_execve(cmd, data);
}

void	ft_execve(t_cmd *cmd, t_data *data)
{
	pid_t	fork_return;
	int		ret;
	int		exec_ret;

	fork_return = fork();
	if (!fork_return)
	{
		exec_ret = execve(cmd->args[0], cmd->args, data->temp_environ) * -127;
		ft_free_tab(cmd->args);
		free(cmd);
		exit(exec_ret);
	}
	else
		waitpid(fork_return, &ret, 0);
	reset_std(data);
	data->wexitstatus = WEXITSTATUS(ret);
	data->wifexited = WIFEXITED(ret);
	if (data->wexitstatus == 127)
	{
		ft_putstr("Minishell: no such file or directory: ");
		ft_putendl(cmd->args[0]);
	}
}
