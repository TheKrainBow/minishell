/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:31:43 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/22 07:14:36 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_check_path(t_cmd *cmd)
{
	char	*new;
	int		k;
	int		i;

	i = 0;
	k = 5;
	new = NULL;
	if (ft_strncmp(cmd->name, "/bin/", 5) == 0)
		return (cmd->name);
	if (ft_strncmp(cmd->name, "./", 2) == 0)
		return (cmd->name);
	new = malloc(sizeof(char) * ft_strlen(cmd->name) + 6);
	new[0] = '/';
	new[1] = 'b';
	new[2] = 'i';
	new[3] = 'n';
	new[4] = '/';
	while (cmd->name[i])
		new[k++] = cmd->name[i++];
	new[k] = '\0';
	return (new);
}

int	ft_execve(t_cmd *cmd)
{
	int		status;
	int		pid;
	char	*tmp_name;

	status = 0;
	tmp_name = name_check_path(cmd);
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
