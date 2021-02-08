/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/02/08 18:45:00 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	/*char				*line;
	int					ret;*/

	data.dict_size = 6;
	data.lex_dict = dict;
	ft_malloc_env();
	ft_export_env("toto", "5");
	ft_export_env("tata", "5");
	ft_print_env();
	ft_unset_env("toto");
	ft_print_env();
	/*
	ret = 1;
	line = NULL;
	while (ret)
	{
		ft_putstr_fd("Minishell >: ", 1);
		ret = get_next_line(0, &line);
		lex_line(&data, line);
		free(line);
	}*/
	ft_free_env();
	exit (1);
}