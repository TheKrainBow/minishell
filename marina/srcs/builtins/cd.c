/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:23:43 by marina            #+#    #+#             */
/*   Updated: 2021/01/26 18:08:39 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*#include "../../includes/minishell.h"*/

char		**ft_split(char const *s, char c);
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

int	cd(/*t_data *data,*/char *arg)
{
	pwd();
	printf("%d\n",chdir(arg));
	pwd();
}

char	*quote_bin(char *path)
{
	int	i;
	int	sq;
	int	wq;
	char	*new;

	i = 0;
	sq = 0;
	wq = 0;
	while (path[i] && sq < 2 && wq < 2)
	{
		if (path[i] == '\'')
			sq++;
		if (path[i] == '"')
			wq++;
		i++;
	}
	if (sq < 2 && wq < 2)
		return (path);
	if (!(new = malloc(ft_strlen())))
}

int	main(void)
{
	char	*arg = "test/../..";
	char	**path;
	int		i;

	path = ft_split(arg, '/');
	i = 0;
	while (path[i])
	{
		path[i] = quote_bin(path[i]);
		cd(path[i]);
		free(path[i]);
		i++;
	}
	free(path);
	return (0);
}