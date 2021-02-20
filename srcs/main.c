/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 22:39:42 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(void)
{
	t_data				data;
	char				*line;
	int					ret;

	data.db.term1 = open("/dev/pts/1", O_RDWR);
	data.db.term2 = open("/dev/pts/2", O_RDWR);
	data.path = NULL;
	ft_malloc_env();
	ret = 1;
	line = NULL;
	while (ret)
	{
		ft_putstr_fd("Minishell >: ", 1);
		ret = get_next_line(0, &line);
		lex_line(line, &data);
		ft_putstr_fd("\033c\033[3J\033[0;33mLexed line:\033[0m\n", data.db.term2);
		ft_lstprint_fd(data.lexed_line, data.db.term2);
		pars_line(&data);
		ft_print_pars_line(&data);
		free(line);
		ft_node(&data);
		ft_free_list(data.parsed_line);
	}
	ft_free_env();
	exit (1);
}