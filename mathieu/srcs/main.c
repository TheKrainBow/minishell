/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 22:01:07 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	data.path = NULL;
	ft_malloc_env();
	ft_update_path(&data);
	t_cmd		cmd;

	cmd.args = ft_split("ls", ' ');
	ft_cmd(&cmd, &data);
	ft_free_split(cmd.args);
	ret = 1;
	line = NULL;
	while (ret)
	{
		ft_putstr_fd("Minishell >: ", 1);
		ret = get_next_line(0, &line);
		lex_line(&data, line);
		free(line);
	}
	ft_free_env();
	exit (1);
}