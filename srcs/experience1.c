/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experience1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:41:14 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/22 20:43:58 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirector(int fd_default_output, t_red *outs, t_data *data)
{
	int		fds[2];
	pid_t	pid;
	char	*buf;
	int		ret;
	int		ret_child;
	char	*string;

	pipe(fds);
	ret = 1;
	(void)outs;
	string = NULL;
	ret_child = dup2(fds[1], fd_default_output);
	//ret_child = dup2(fds[1], copy_fd);
	pid = fork();
	//processus fils
	if (!pid)
	{
		//lancer la fonction des builtins
		printf("BLABLA :)");
		close(fds[0]);
		close(fds[1]);
		dprintf(data->db.term2, "fd closed\n");
		exit(1);
	}
	//processus pere
	else
	{
		buf = malloc(sizeof(char) * 2);
		while (ret > 0)
		{
			ret = read(fds[0], buf, 1);
			buf[ret] = '\0';
			string = ft_strjoin(string, buf);
			dprintf(data->db.term2, "string = |%s|\n", string);
		}
		//close(fds[0]);
		close(ret_child);
		printf("\nrecupere de la pipe : !%s!\n", string);
	}
	printf("fin du processus %d\n", pid);
//		waitpid(pid, &ret_child, 0);

}