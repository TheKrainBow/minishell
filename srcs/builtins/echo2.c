/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:08:56 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/06/25 14:25:12 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_option(char *word)
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

int	print_esc(char *word, int *i)
{
	if (word[*i + 1])
	{
		ft_putchar(word[*i + 1]);
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
	name = malloc(sizeof(char) * size);
	if (!(name))
		return (NULL);
	ft_strlcpy(name, word + save, size);
	return (name);
}

int	print_var(char *word, int *i, t_data *data)
{
	char	*name;
	int		number;
	char	*content;

	if (word[*i + 1] && word[*i + 1] == '?')
	{
		ft_putnbr(data->wexitstatus);
		(*i) += 2;
		return (1);
	}
	name = get_name(word, i);
	if (!(name))
		return (0);
	number = ft_find_in_env(name, data);
	free(name);
	if (number < 0)
		return (0);
	content = ft_strchr(data->temp_environ[number], '=') + 1;
	ft_putstr(content++);
	return (ft_strlen(content));
}
