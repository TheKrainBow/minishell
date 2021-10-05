/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:13:30 by magostin          #+#    #+#             */
/*   Updated: 2021/06/25 14:17:02 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_toggle_quote(char c, t_data *data)
{
	if (data->quote == 0)
		data->quote = c;
	else if (data->quote == c)
		data->quote = 0;
}

static void	init(int *i, int *j, t_data *data, t_list **words)
{
	*i = 0;
	*j = 0;
	data->quote = 0;
	*words = NULL;
}

void	lex_line2(int *i, int *j, t_list **words, char *line)
{
	if (*i != *j)
		ft_lstadd_back(words,
			ft_lstnew((void *)ft_strndup(line, *j, *i - *j)));
	if (line[*i] != '>')
		ft_lstadd_back(words, ft_lstnew((void *)ft_strndup(line, *i, 1)));
	else if (line[*i + 1] == '>')
		ft_lstadd_back(words, ft_lstnew((void *)ft_strndup(line, (*i)++, 2)));
	else
		ft_lstadd_back(words, ft_lstnew((void *)ft_strndup(line, *i, 1)));
	*j = *i + 1;
}

void	lex_line(char *line, t_data *data)
{
	int		i;
	int		j;
	t_list	*words;

	init(&i, &j, data, &words);
	while (line && line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			ft_toggle_quote(line[i], data);
		else if ((line[i] == ' ') && !data->quote)
		{
			if (i != j)
				ft_lstadd_back(&words,
					ft_lstnew((void *)ft_strndup(line, j, i - j)));
			while (line[i + 1] && line[i + 1] == ' ' && !data->quote)
				i++;
			j = i + 1;
		}
		if ((ft_strchr(";|<>", line[i])) && !data->quote)
			lex_line2(&i, &j, &words, line);
		i++;
	}
	if (line && line[j])
		ft_lstadd_back(&words, ft_lstnew((void *)ft_strndup(line, j, i - j)));
	data->lexed_line = words;
}
