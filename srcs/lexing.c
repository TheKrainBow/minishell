/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:12:47 by magostin          #+#    #+#             */
/*   Updated: 2021/01/22 12:08:05 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gram	find_char_in_dict(t_data *data, char c)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (c == data->lex_dict[i].c[0])
			return (data->lex_dict[i]);
	}
	return (data->lex_dict[0]);
}

int		lex_line(t_data *data, char *line)
{
	char		**splited_line;
	printf("%d\n", data->lex_dict[2].s);
	(void)splited_line;
	(void)line;
	return (1);
}
