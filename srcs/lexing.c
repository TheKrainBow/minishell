/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:12:47 by magostin          #+#    #+#             */
/*   Updated: 2021/01/24 19:42:24 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_char_in_dict(t_data *data, char c)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (c == data->lex_dict[i].c[0])
			return (i);
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
	t_list		**splited_line;
	t_list		*split_temp;
	char		*temp;
	int			i;
	int			word_start;
	int			j;
	int			ret;

	i = -1;
	word_start = 0;
	j = 0;
	splited_line = NULL;
	while (line && line[++i])
	{
		if ((ret = find_char_in_dict(data, line[i])) != -1)
		{
			temp = ft_strndup(line, j, i - j);
			printf("|%s| %d %d\n", temp, i, j);
			split_temp = ft_lstnew(temp);
			ft_lstadd_back(splited_line, ft_lstnew(temp));
			j = i;
		}
	}
	return (1);
}
