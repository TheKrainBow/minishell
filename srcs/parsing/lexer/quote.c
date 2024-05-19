/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 03:01:15 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/19 21:54:00 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

void	swap_quote(char *quote, char c)
{
	if (!ft_isquote(c))
		return ;
	if (*quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

int	skip_quotes(char *input)
{
	char	quote;
	int		i;

	i = 0;
	quote = *input;
	input++;
	while (quote && input[i])
	{
		swap_quote(&quote, input[i]);
		i++;
	}
	return (i + 1);
}
