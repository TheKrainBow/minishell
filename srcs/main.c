/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/01/22 11:09:14 by magostin         ###   ########.fr       */
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

int		check_line(char *line)
{
	while (line && *line)
	{
		if (*line == ';' && (line + 1) && *(line + 1) == ';')
			return (0);
		line++;
	}
	return (1);
}

int		main(void)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ft_putstr("\033[4m\033[36;1mMinishell \033[1;31m>:\033[0m ");
		ret = get_next_line(0, &line);
		printf("%s\n", line);
		free(line);
	}
	return (42);
}