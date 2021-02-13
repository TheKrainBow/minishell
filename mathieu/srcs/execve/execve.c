/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:36:14 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 20:38:09 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>
#include <sys/types.h>

void		ft_find_in_path(t_cmd *cmd)
{
	DIR		*directory;

	directory = opendir(".");
}

void		ft_execve(t_cmd *cmd)
{
	pid_t	fork_return;
	int		ret;

	printf("%s\n", cmd->args[0]);
	fork_return = fork();
	if (!fork_return)
	{
		execve(cmd->args[0], cmd->args, __environ);
		exit(5);
	}
	else
		waitpid(fork_return, &ret, 0);
	if (WIFEXITED(ret))
		printf("%d %d\n", WEXITSTATUS(ret), WIFEXITED(ret));
	else
		printf("Fatal Error\n");
}