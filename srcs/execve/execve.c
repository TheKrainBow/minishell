/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:36:14 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 23:05:59 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>
#include <sys/types.h>

void		ft_create_new_path(t_cmd *cmd, char *dir)
{
	char			*temp;

	if (dir[ft_strlen(dir) - 1] != '/')
	{
		temp = ft_strjoin(dir, "/");
		dir = temp;
	}
	temp = ft_strjoin(dir, cmd->args[0]);
	free(cmd->args[0]);
	cmd->args[0] = temp;
}

int			find_cmd_in_dir(t_cmd *cmd, char *dir)
{
	DIR				*directory;
	struct dirent	*dp;

	directory = opendir(dir);
	while ((dp = readdir(directory)) != NULL)
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
	}
	closedir(directory);
	return (0);
}

int			ft_find_in_path(t_cmd *cmd, t_data *data)
{
	int			i;

	i = 0;
	ft_update_path(data);
	while (data->path && data->path[i] && !find_cmd_in_dir(cmd, data->path[i]))
		i++;
	if (!data->path[i])
	{
		printf("Minishell: command not found: %s\n", cmd->args[0]);
		return (1);
	}
	return (0);
}

void		ft_cmd(t_cmd *cmd, t_data *data)
{
	if (!(ft_strchr(cmd->args[0], '/')))
		if (ft_find_in_path(cmd, data))
			return ;
	ft_execve(cmd, data);
}

void		ft_execve(t_cmd *cmd, t_data *data)
{
	pid_t	fork_return;
	int		ret;
	int		exec_ret;

	fork_return = fork();
	if (!fork_return)
	{
		exec_ret = execve(cmd->args[0], cmd->args, __environ) * -127;
		exit(exec_ret);
	}
	else
		waitpid(fork_return, &ret, 0);
	if (!(WIFEXITED(ret)))
		printf("execve crashed :(\n");
	data->wexitstatus = WEXITSTATUS(ret);
	data->wifexited = WIFEXITED(ret);
	if (data->wexitstatus == 127)
		printf("Minishell: no such file or directory: %s\n", cmd->args[0]);
}