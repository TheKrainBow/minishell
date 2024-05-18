/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:08:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 03:53:48 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd(t_data *data, t_list *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->args = ft_lsttotab_if(tokens, &is_arg, &lst_conv);
	cmd->name = cmd->args[0];
	cmd->data = data;
	ft_lstadd_back(&data->cmds, ft_lstnew(cmd));
}
/* Handle redirections here */

int	parse_input(t_data *data, char *input)
{
	t_list	*tokens;
	t_list	**splitted_tokens;
	int		i;

	tokens = input_lexer(input);
	if (check_tokens(&tokens) == 0)
		return (0);
	splitted_tokens = ft_lstsplit(tokens, &is_pipe, &free_lexer);
	i = 0;
	while (splitted_tokens[i])
	{
		create_cmd(data, splitted_tokens[i]);
		ft_lstclear(&splitted_tokens[i], &free_lexer);
		i++;
	}
	free(splitted_tokens);
	return (1);
}
