/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_redirect_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 21:19:42 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 21:20:10 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(void)
{
	t_data				data;
	char				*line;
	int					ret;

	data.db.term1 = open("/dev/pts/1", O_RDWR);
	data.db.term2 = open("/dev/pts/2", O_RDWR);
	data.path = NULL;
	ft_malloc_env();

	t_cmd cmd;

	cmd.args = ft_split("cat" , 0);
	int fd = open("test.txt", O_RDWR);
	int fds[2];

	pipe(fds);
	dup2(fds[0], 0);

	pid_t pid = fork();
	if (!pid)
	{
		close(fds[0]);
		ret = 1;
		while (ret)
		{
			ret = get_next_line(fd, &line);
			ft_putstr_fd(line, fds[1]);
			free(line);
		}
		ft_cmd(&cmd, &data);
		exit(1);
	}
	close(fds[1]);
	exit(1);
}