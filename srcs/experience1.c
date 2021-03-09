/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experience1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:41:14 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/03/09 12:25:36 by magostin         ###   ########.fr       */
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
	pid = fork();
	//processus fils
	if (!pid)
	{
		//lancer la fonction des builtins
		dprintf(data->db.term2, "start printf\n");
		printf("BLABLA :)");
		dprintf(data->db.term2, "stop printf\n");
		close(fds[0]);
		close(fds[1]);
		dprintf(data->db.term2, "%d and %d closed\n", fds[0], fds[1]);
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
			dprintf(data->db.term1, "s = |%s|\n", string);
		}
		dprintf(data->db.term2, "\nrecupere de la pipe : !%s!\n", string);
	}
	dprintf(data->db.term2, "fin du processus %d\n", pid);
}