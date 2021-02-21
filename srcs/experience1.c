/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experience1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:41:14 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/21 22:58:51 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirector(int fd_default_output, t_red *outs)
{
	int		fds[2];
	pid_t	pid;
	char	buf[2];
	int		ret;
	int		ret_child;
	char	*string;

	pipe(fds);
	buf[1] = '\0';
	ret = 1;
	(void)outs;
	string = NULL;
	pid = fork();
	//processus pere
	if (pid)
	{
		while (ret > 0)
		{
			ret = read(fds[0], buf, 1);
			printf("\nbuf = %s", buf);
			string = ft_strjoin(string, buf);
			printf("\nstring = %s", string);
		}
		waitpid(pid, &ret_child, 0);
		close(fds[0]);
		printf("\nrecupere de la pipe : !%s!\n", string);
	}
	//processus fils
	else
	{
		//lancer la fonction des builtins
		dup2(fds[1], fd_default_output);
		printf("BLABLA\n");
		close(fds[1]);
		exit(1);
		printf("0");
	}
	printf("fin du processus %d\n", pid);
}