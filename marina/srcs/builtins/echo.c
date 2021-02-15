/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:10:15 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/15 20:59:57 by mdelwaul         ###   ########.fr       */
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

int		ft_option(char *word)
{
	int		i;

	if (!word || word[0] != '-')
		return (0);
	i = 1;
	while (word[i] && word[i] == 'n')
		i++;
	if (i > 1 && word[i] == '\0')
		return (1);
	return (0);
}

int		print_esc(char *word, int *i)
{
	if (word[*i + 1])
	{
		printf("%c", word[*i + 1]);
		*i += 2;
		return (1);
	}
	return (0);
}

char	*get_name(char *word, int *i)
{
	char	*name;
	int		size;
	int		save;

	size = 1;
	(*i)++;
	save = *i;
	while (word && word[*i] && ft_isalnum(word[*i]))
	{
		size++;
		(*i)++;
	}
	if (!(name = malloc(sizeof(char) * size)))
		return (NULL);
	ft_strlcpy(name, &word[save], size);
	return (name);
}

int		print_var(char *word, int *i, t_data *data)
{
	char	*name;
	int		number;
	char	*content;

	if (word[*i + 1] && word[*i + 1] == '?')
	{
		printf("%d", data->wexitstatus);
		(*i) += 2;
		return (1);
	}
	if (!(name = get_name(word, i)))
		return (0) ;
	number = ft_find_in_env(name);
	free(name);
	if (number < 0)
		return (0);
	content = ft_strchr(__environ[number], '=') + 1;
	printf("%s", content++);
	return(ft_strlen(content));
}

int		printing(char *word, t_data *data)
{
	int		strong;
	int		i;
	int		printed;

	strong = 0;
	printed = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\\')
			printed += print_esc(&word[i], &i);
		if (word[i] == '\'')
		{
			strong = (strong + 1) % 2;
			i++;
		}
		if (!strong && word[i] == '$')
			printed += print_var(&word[i], &i, data);
		if (!strong && word[i] == '"')
			i++;
		if (word[i])
		{
			printf("%c", word[i]);
			printed++;
			i++;
		}
	}
	return (printed);
}

int		echo(t_cmd *cmd, t_data *data)
{
	int		i;
	int		printed;
	int		n;

	n = 0;
	i = 1;
	while (ft_option(cmd->args[i]))
		i++;
	if (i != 1)
		n = 1;
	while (cmd->args[i])
	{
		printed = printing(cmd->args[i], data);
		if (cmd->args[++i] && printed)
			printf(" ");
	}
	if (!n)
		printf("\n");
	return (0);
}