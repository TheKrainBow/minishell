/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:10:59 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 21:00:55 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mathieu/includes/minishell.h"

/*int		main(void)
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
}*/

int		echo(t_cmd *cmd, t_data *data);

int		main(void)
{
	t_data	data;
	t_cmd	cmd;
	char	*input;
	int		i;

	data.wexitstatus = 1234;
	ft_malloc_env();
	input = NULL;
	get_next_line(0, &input);
	cmd.args = ft_split(input, ' ');
	free(input);
	echo(&cmd, &data);
	i = 0;
	while (cmd.args[i])
	{
		free(cmd.args[i]);
		i++;
	}
	free(cmd.args);
	return (0);
}