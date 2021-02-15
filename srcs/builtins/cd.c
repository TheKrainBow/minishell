/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:26 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/15 22:18:48 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "../../includes/minishell.h"*/

char	*remove_char(char *string, int *a, int *b)
{
	int		i;
	char	*new;

	if (!(new = malloc(sizeof(char) * (strlen(string) - 1))))
		return (NULL);
	i = 0;
	while (string && string[i] && i < *a)
	{
		new[i] = string[i];
		i++;
	}
	while (string && string[i] && i + 1 < *b)
	{
		new[i] = string[i + 1];
		i++;
	}
	while (string && string[i])
	{
		new[i] = string[i + 2];
		i++;
	}
	new[i] = '\0';
	*a = -1;
	*b -= 2;
	return (new);
}

char	*quote_bin(char *path)
{
	int		weak;
	int		strong;
	int		i;

	weak = -1;
	strong = -1;
	i = 0;
	while (path && path[i])
	{
		if (path[i] == '\'' && weak == -1)
		{
			if (strong >= 0)
				path = remove_char(path, &strong, &i);
			else
				strong = i;
		}
		else if (path[i] == '"' && strong == -1)
		{
			if (weak >= 0)
				path = remove_char(path, &weak, &i);
			else
				weak = i;
		}
		i++;
	}
	return (path);
}

int	cd(/*t_data *data,*/char *arg)
{
	char	*path;

	path = quote_bin(arg);
	return (chdir(path));
}
