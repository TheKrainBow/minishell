/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:13:30 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 17:57:50 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_toggle_quote(char c, t_data *data)
{
	if (data->quote == 0)
		data->quote = c;
	else if (data->quote == c)
		data->quote = 0;
}

void		lex_line(char *line, t_data *data)
{
	int		i;
	int		j;
	t_list	*words;

	i = 0;
	j = 0;
	data->quote = 0;
	words = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			ft_toggle_quote(line[i], data);
		else if ((line[i] == ' ') && !data->quote)
		{
			if (i != j)
				ft_lstadd_back(&words, ft_lstnew((void *)ft_strndup(line, j, i - j)));
			while (line[i + 1] && line[i + 1] == ' ' && !data->quote)
				i++;
			j = i + 1;
		}
		if ((line[i] == ';') && !data->quote)
		{
			if (i != j)
				ft_lstadd_back(&words, ft_lstnew((void *)ft_strndup(line, j, i - j)));
			ft_lstadd_back(&words, ft_lstnew((void *)ft_strdup(";")));
			j = i + 1;
		}
		i++;
	}
	if (line[j])
		ft_lstadd_back(&words, ft_lstnew((void *)ft_strndup(line, j, i - j)));
	data->lexed_line = words;
}