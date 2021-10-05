/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:18:34 by magostin          #+#    #+#             */
/*   Updated: 2021/10/05 15:25:53 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_quotes(char *value, t_data *data)
{
	int		i;
	char	*temp;
	char	*new_value;
	char	old_quote;

	i = -1;
	data->quote = 0;
	new_value = NULL;
	while (value[++i])
	{
		old_quote = data->quote;
		if (value[i] == '\'' || value[i] == '\"')
			ft_toggle_quote(value[i], data);
		if (old_quote == data->quote)
		{
			temp = ft_strndup(value, i, 1);
			ft_strjoin_to(&new_value, temp);
			free(temp);
		}
	}
	return (new_value);
}

void	ft_print_sorted_env(t_data *data)
{
	char	**sorted_env;

	sorted_env = ft_sort_strs(data->temp_environ);
	ft_export_print(sorted_env);
	ft_free_tab(sorted_env);
}
