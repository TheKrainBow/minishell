/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:46 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/16 00:05:20 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	char	*path;

	path = NULL;
	if ((path = getcwd(NULL, 0)) == NULL)
		return (-1);
	printf("%s\n", path);
	free(path);
	return (0);
}
