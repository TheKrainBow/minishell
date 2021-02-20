/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:46 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/20 22:12:01 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_cmd *cmd, t_data *data)
{
	char	*path;

	(void)cmd;
	path = NULL;
	if ((path = getcwd(NULL, 0)) == NULL)
		return ;
	printf("%s\n", path);
	free(path);
	data->wexitstatus = 0;
}
