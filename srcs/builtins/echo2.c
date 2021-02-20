/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:08:56 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/02/16 14:10:49 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
