/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marina <marina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:23:43 by marina            #+#    #+#             */
/*   Updated: 2021/01/26 21:37:03 by marina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "../../includes/minishell.h"*/

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



char	*dequote(char *arg, int first, int second)
{
	char	*new;
	int		i;

	if (!(new = malloc(sizeof(char) * (strlen(arg) - 1))))
		return (NULL);
	i = 0;
	while (i < first)
	{
		new[i] = arg[i];
		i++;
	}
	while (i < second - 1)
	{
		new[i] = arg[i + 1];
		i++;
	}
	while (i < strlen(arg) - 1)
	{
		new[i] = arg[i + 2];
		i++;
	}
	new[i] = '\0';
	free (arg);
	return (new);
}

char	*quote_bin(char *arg)
{
	int		i;
	int		sq;
	int		wq;

	i = 0;
	sq = -1;
	wq = -1;
	while (arg[i] && ((arg[i] != '"' && arg[i] != '\'')
	|| (arg[i] == '"' && wq == -1) || (arg[i] == '\'' && sq == -1)))
	{
		if (arg[i] == '"')
			wq = i;
		if (arg[i] == '\'')
			sq = i;
		i++;
	}
	if ((arg[i] == '"' && wq != -1) || (arg[i] == '\'' && sq != -1))
	{
		if (arg[i] == '"')
			arg = dequote(arg, wq, i);
		else
			arg = dequote(arg, sq, i);
		arg = quote_bin(arg);
	}
	return (arg);
}

int	cd(/*t_data *data,*/char *arg)
{
	char	*path;

	pwd();
	path = quote_bin(arg);
	printf("res quote_bin = %s\n", path);
	printf("%d\n",chdir(path));
	pwd();
}

int	main(void)
{
	char	*arg = ".'./'l'exer'";
	char	*path;
	int		i;

	if (!(path = malloc(sizeof(char) * (strlen(arg) + 1))))
		return (-1);
	i = 0;
	while (arg[i])
	{
		path[i] = arg[i];
		i++;
	}
	path[i] = '\0';
	i = cd(path);
	return (0);
}