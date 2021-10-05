/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:46 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:22:27 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd, t_data *data)
{
	char	*path;

	(void)cmd;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return ;
	ft_putendl(path);
	free(path);
	data->wexitstatus = 0;
}
