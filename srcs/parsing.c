/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 03:05:16 by magostin          #+#    #+#             */
/*   Updated: 2021/01/12 03:59:23 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str);

int			commas(char *str)
{
	while (str && *str)
	{
		if (*str == ';')
			return (1);
		str++;
	}
	return (0);
}

int			multiple_commands(char *str)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 0;
	while (str && str[i])
	{
		if (str[i] == ';')
		{
			str[i] = 0;
			pars_line(str + j);
			j = i + 1;
			ret = 1;
		}
		i++;
	}
	if (str[i] == 0 && j != i)
	{
		str[i] = 0;
		pars_line(str + j);
		j = i + 1;
		ret = 1;
	}
	return (ret);
}

void		pars_line(char *str)
{
	if (commas(str) && multiple_commands(str))
		return ;
	printf("%s\n", str);
}