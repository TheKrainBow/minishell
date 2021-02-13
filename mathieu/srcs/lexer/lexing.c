/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:12:47 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 20:38:57 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		find_char_in_dict(t_data *data, char c)
{
	int		i;

	i = -1;
	while (++i < data->dict_size)
	{
		if (c == data->lex_dict[i].c[0])
		{
			if ((data->lex_dict[i].c_type == CHAR_WQUOTE ||
			data->lex_dict[i].c_type == CHAR_SQUOTE) && !data->quote)
				data->quote = c;
			else if (c == data->quote)
			{
				data->quote = 0;
				return (-2);
			}
			return (i);
		}
	}
	return (-1);
}

char	*ft_strndup(const char *str, int start, int n)
{
	char		*dest;
	int			size;
	int			i;

	if (!str || start < 0 || n <= 0 || start > (int)ft_strlen(str))
		return (NULL);
	if ((int)ft_strlen(str) - start < n)
		size = ft_strlen(str) - start;
	else
		size = n;
	if (!(dest = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < size)
		dest[i] = str[start + i];
	dest[i] = 0;
	return (dest);
}

int		lex_line(t_data *data, char *line)
{
	t_lex		*splited_line;
	t_lex		*split_temp;
	char		*temp;
	int			i;
	int			j;
	int			ret;

	i = -1;
	j = 0;
	data->quote = 0;
	splited_line = NULL;
	data->ret_temp = -1;
	while (line && line[++i])
	{
		ret = find_char_in_dict(data, line[i]);
		if ((ret != data->ret_temp || ret != -1) && !data->quote && ret != -2)
		{
			if (data->lex_dict[data->ret_temp].c_type != CHAR_WSPACE)
			{
				temp = ft_strndup(line, j, i - j);
				if (temp)
					ft_lstadd_back_lexer(&splited_line, ft_lstnew_lexer(temp, (int)ft_strlen(temp), data->lex_dict[data->ret_temp].c_type));
				while (line[i] && (data->lex_dict[ret = find_char_in_dict(data, line[i])].c_type) == CHAR_WSPACE)
					i++;
				j = i;
			}
		}
		data->ret_temp = ret;
	}
	if (j < (int)ft_strlen(line))
	{
		temp = ft_strndup(line, j, i - j);
		ft_lstadd_back_lexer(&splited_line, ft_lstnew_lexer(temp, (int)ft_strlen(temp), data->lex_dict[data->ret_temp].c_type));
	}
	
	while (splited_line)
	{
		printf("%d %d |%s|\n", splited_line->content.s, splited_line->content.c_type, splited_line->content.c);
		split_temp = splited_line;
		splited_line = splited_line->next;
		free(split_temp->content.c);
		free(split_temp);
	}
	return (1);
}
