/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:15 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/13 22:39:45 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../mathieu/includes/minishell.h"

int		ft_find_in_env(char *name);

void	print_esc(char *word, int *i)
{
	if (word[*i + 1])
	{
		printf("%c", word[*i + 1]);
		*i += 2;
	}
}

char	*get_name(char *word, int *i)
{
	char	*name;
	int		size;

	size = 1;
	while (word[*i] && ft_isalnum(word[*i]))
	{
		size++;
		*i = *i + 1;
	}
	if (!(name = malloc(sizeof(char) * size )))
		return (NULL);
	ft_strlcpy(name, &word[*i], size);
	return (name);
}

void	print_var(char *word, int *i)
{
	char	*name;
	int		number;
	char	*content;

	if (!(name = get_name(word, i)))
		return ;
	number = ft_find_in_env(name);
	if (number < 0)
		return ;
	content = ft_strchr(__environ[number], '=');
	printf("%s", content++);
}

void	printing(char *word)
{
	int		strong;
	int		i;

	strong = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\\')
			print_esc(&word[i], &i);
		if (word[i] == '\'')
			strong = (strong + 1) % 2;
		if (!strong && word[i] == '$')
			print_var(&word[i], &i);
		if (!strong && word[i] == '"')
			i++;
		printf("%c", word[i]);
		i++;
	}
}

int		echo(t_cmd *cmd)
{
	int		i;

	i = 1;
	if (!ft_strncmp(cmd->args[1], "-n", 3))
		i++;
	while (cmd->args[i])
	{
		printing(cmd->args[i]);
		if (cmd->args[++i])
			printf(" ");
	}
	if (ft_strncmp(cmd->args[1], "-n", 3))
		printf("\n");
	return (0);
}