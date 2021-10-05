/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:43:38 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 14:17:55 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_in(t_cmd *cmd, char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 1)
	{
		ft_putstr("Minishell: ");
		ft_putstr(file_name);
		ft_putstr(": Aucun fichier ou dossier de ce type\n");
		return (fd);
	}
	ft_append_lst(&cmd->fd_in, fd);
	return (dup2(fd, 0));
}
