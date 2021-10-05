/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:54:09 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:17:14 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(t_lst_fd *fd)
{
	t_lst_fd	*temp;

	while (fd)
	{
		temp = fd->next;
		close(fd->fd);
		free(fd);
		fd = temp;
	}
	fd = NULL;
}

void	ft_destroy_pars_line(t_data *data)
{
	t_list		*temp;
	t_cmd		*cmd;
	int			ret;

	ft_lstlast(&data->parsed_line);
	while (data->parsed_line)
	{
		temp = data->parsed_line->prev;
		cmd = ((t_cmd *)data->parsed_line->content);
		waitpid(cmd->pid, &ret, 0);
		ft_close_fd(cmd->fd_in);
		ft_close_fd(cmd->fd_out);
		ft_free_tab(cmd->args);
		free(cmd);
		free(data->parsed_line);
		data->parsed_line = temp;
	}
}

t_list	*create_cmd(t_list *lst, int piped)
{
	t_cmd		*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (lst)
		cmd->args = ft_lst_to_tab_minishell(lst);
	else
		cmd->args = NULL;
	cmd->piped = piped;
	cmd->fd_out = NULL;
	cmd->fd_in = NULL;
	cmd->pid = 0;
	return (ft_lstnew((void *)(cmd)));
}
