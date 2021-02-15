/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:44:44 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 22:53:47 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_print_pars_line(t_data *data)
{
	t_list		*temp;

	ft_putstr_fd("\033[0;33mParsed line:\033[0m\n", data->db.term2);
	temp = data->parsed_line;
	while (temp)
	{
		ft_putstr_fd("\033[0;33m-----------\033[0m\n", data->db.term2);
		ft_lstprint_fd((t_list *)temp->content, data->db.term2);
		temp = temp->next;
	}
}

t_list		*ft_malloc_cmd(t_list *args)
{
	t_list		*dest;
	t_cmd		cmd;

	if (!(dest = malloc(sizeof(t_list))))
		return (NULL);
	cmd.args = ft_lst_to_tab(args);
	dest->content = (void *)&cmd;
	dest->next = NULL;
	return (dest);
}

void		ft_create_cmd(t_data *data)
{
	t_list		*temp;

	temp = data->parsed_line;
}

void		pars_line(t_data *data)
{
	t_list		*temp;

	data->parsed_line = NULL;
	ft_lstadd_back(&data->parsed_line, ft_lstnew(data->lexed_line));
	temp = data->lexed_line;
	while (temp)
	{
		if (temp->next && !(ft_strcmp((char *)temp->next->content, ";")))
		{
			if (temp->next->next)
				ft_lstadd_back(&data->parsed_line, ft_lstnew(temp->next->next));
			free(temp->next->content);
			free(temp->next);
			temp->next = NULL;
			temp = ft_lstlast(data->parsed_line)->content;
		}
		else
			temp = temp->next;
	}
	data->lexed_line = NULL;
}