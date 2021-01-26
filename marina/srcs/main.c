/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/01/26 16:52:09 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (str && *str)
	{
		ft_putchar(*str);
		str++;
	}
}

char	*ft_strndup(const char *str, int start, int n);
int		main(void)
{
	t_data				data;
	static t_gram		dict[6] = {
		{"\'", 1, CHAR_SQUOTE},
		{"\"", 1, CHAR_WQUOTE},
		{"|", 1, CHAR_PIPE},
		{";", 1, CHAR_SEMI},
		{" ", 1, CHAR_WSPACE},
		{"\t", 1, CHAR_WSPACE}
	};
	char				*line;
	int					ret;

	data.dict_size = 6;
	data.lex_dict = dict;
	ret = 1;
	line = NULL;
	while (ret)
	{
		ft_putstr("Minishell >: ");
		ret = get_next_line(0, &line);
		lex_line(&data, line);
		free(line);
	}
	return (1);
}