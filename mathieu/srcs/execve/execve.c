/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:36:14 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 21:44:53 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>
#include <sys/types.h>


int			find_cmd_in_dir(t_cmd *cmd, char *dir)
{
	DIR				*directory;
	struct dirent	*dp;
	char			*temp;

	directory = opendir(dir);
	while ((dp = readdir(directory)) != NULL)
	{
		if (!(!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, "..")))
		{
			if (!ft_strcmp(dp->d_name, cmd->args[0]))
			{
				temp = ft_strjoin(dir, cmd->args[0]);
				free(cmd->args[0]);
				cmd->args[0] = temp;
				closedir(directory);
				return (1);
			}
		}
	}
	closedir(directory);
	return (0);
}

void		ft_find_in_path(t_cmd *cmd)
{
	find_cmd_in_dir(cmd, "./");
	(void)cmd;
}

void		ft_cmd(t_cmd *cmd, t_data *data)
{
	if (!(ft_strchr(cmd->args[0], '/')))
		ft_find_in_path(cmd);
	ft_execve(cmd, data);
}

void		ft_execve(t_cmd *cmd, t_data *data)
{
	pid_t	fork_return;
	int		ret;

	printf("%s\n", cmd->args[0]);
	fork_return = fork();
	if (!fork_return)
	{
		exit(execve(cmd->args[0], cmd->args, __environ) * -127);
	}
	else
		waitpid(fork_return, &ret, 0);
	if (WIFEXITED(ret))
		printf("WEXITSTATUS=%d WIFEXITED=%d ret=%d\n", WEXITSTATUS(ret), WIFEXITED(ret), ret);
	else
		printf("Fatal Error\n");
	(void)data;
}