/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/01/24 20:41:45 by magostin         ###   ########.fr       */
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
int		main(int ac, char **av)
{
	t_data		data;
	static t_gram		dict[4] = {
		{";", 1, CHAR_SEMI},
		{" ", 1, CHAR_WSPACE},
		{"\t", 1, CHAR_WSPACE}
	};

	(void)ac;
	data.lex_dict = dict;
	lex_line(&data, av[1]);
	return (42);
}