/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:14:49 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 14:19:44 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_append_lst_pid(t_lst_pid **lst, pid_t pid)
{
	t_lst_pid	*new;

	new = malloc(sizeof(t_lst_pid));
	if (!(new))
		return ;
	new->pid = pid;
	new->next = NULL;
	new->prev = NULL;
	ft_lstadd_front((t_list **)(lst), (t_list *)new);
}

void	ft_append_lst(t_lst_fd **lst, int fd)
{
	t_lst_fd	*new;

	new = malloc(sizeof(t_lst_fd));
	if (!(new))
		return ;
	new->fd = fd;
	new->next = NULL;
	new->prev = NULL;
	ft_lstadd_back((t_list **)(lst), (t_list *)new);
}

int	redirect_out(t_cmd *cmd, char *file_name, int append)
{
	int		fd;
	int		flags;

	flags = O_CREAT | O_RDWR;
	if (append)
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	fd = open(file_name, flags,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (!(fd))
		return (0);
	ft_append_lst(&cmd->fd_out, fd);
	return (dup2(fd, 1));
}
