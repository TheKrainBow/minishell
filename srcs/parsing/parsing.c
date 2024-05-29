/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:08:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:25:52 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_env_variable(char *str, t_data *data)
{
	int		i;
	char	*tmp;
	char	*dest;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	tmp = ft_substr(str, 1, i - 1);
	if (!tmp)
		return (NULL);
	dest = get_var_from_env(data->env, tmp);
	free(tmp);
	if (!dest)
		return (NULL);
	return (dest + i);
}

void	ft_str_replace(char **s1, int start, int len, char *s2)
{
	char	*tmp;

	tmp = ft_substr(*s1, 0, start);
	ft_strjoin_to(&tmp, s2);
	ft_strjoin_to(&tmp, *s1 + start + len);
	free(*s1);
	*s1 = tmp;
}

void	handle_var(t_lexer *token, t_data *data, int i)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	if (ft_strncmp(token->str + i, "$?", 2) == 0)
	{
		tmp = ft_itoa(data->last_error);
		ft_str_replace(&token->str, i, 2, tmp);
		free(tmp);
	}
	else
	{
		len = 1;
		while (token->str[i + len] && (ft_isalnum(token->str[i + len]) || token->str[i] == '_'))
			len++;
		ft_str_replace(&token->str, i, len, find_env_variable(token->str + i, data));
	}
}

void	expand_env(t_lexer *token, t_data *data)
{
	int		i;
	char	quote;

	if (token->token != T_NONE)
		return ;
	quote = 0;
	i = 0;
	while (token->str[i])
	{
		if (ft_isquote(token->str[i]))
			swap_quote(&quote, token->str[i]);
		else if (token->str[i] == '$' && quote != '\'')
		{
			handle_var(token, data, i);
			i--;
		}
		i++;
	}
}

void	remove_quotes(void *content)
{
	t_lexer	*token;
	int		i;
	char	quote;

	quote = 0;
	token = content;
	if (token->token != T_NONE)
		return ;
	i = 0;
	while (token->str[i])
	{
		if (ft_isquote(token->str[i]) && (!quote || quote == token->str[i]))
		{
			swap_quote(&quote, token->str[i]);
			ft_memmove(token->str + i, token->str + i + 1,
				ft_strlen(token->str + i + 1) + 1);
			continue ;
		}
		i++;
	}
}

void	test(t_data *data, t_list *tokens)
{
	while (tokens)
	{
		expand_env(tokens->content, data);
		tokens = tokens->next;
	}
}

void	create_cmd(t_data *data, t_list *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	test(data, tokens);
	ft_lstiter(tokens, &remove_quotes);
	cmd->args = ft_lsttotab_if(tokens, &is_arg, &lst_conv);
	ft_lstrm_if(&tokens, &is_arg, &free_lexer);
	cmd->out = tokens;
	cmd->name = cmd->args[0];
	cmd->data = data;
	ft_lstadd_back(&data->cmds, ft_lstnew(cmd));
}

int	parse_input(t_data *data, char *input)
{
	t_list	*tokens;
	t_list	**splitted_tokens;
	int		i;

	if (!input[0])
		return (1);
	tokens = input_lexer(input);
	if (check_tokens(&tokens) == 0)
		return (0);
	splitted_tokens = ft_lstsplit(tokens, &is_pipe, &free_lexer);
	i = 0;
	while (splitted_tokens[i])
	{
		create_cmd(data, splitted_tokens[i]);
		i++;
	}
	free(splitted_tokens);
	return (1);
}
