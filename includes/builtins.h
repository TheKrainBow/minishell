/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:01:52 by magostin          #+#    #+#             */
/*   Updated: 2021/10/05 15:26:54 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_print_env(t_cmd *cmd, t_data *data);
void	ft_export_env(t_cmd *cmd, t_data *data);
int		ft_env_size(char **env);
void	ft_malloc_env(t_data *data);
void	ft_free_env(t_data *data);
int		ft_find_in_env(char *name, t_data *data);
void	ft_unset_env(t_cmd *cmd, t_data *data);
void	ft_update_path(t_data *data);
void	ft_print_sorted_env(t_data *data);
void	ft_export_print(char **strs);

void	ft_execve(t_cmd *cmd, t_data *data);
void	ft_cmd(t_cmd *cmd, t_data *data);

void	ft_pwd(t_cmd *cmd, t_data *data);
void	ft_cd(t_cmd *cmd, t_data *data);
void	env_update(char *path, t_cmd *cmd, t_data *data);
void	ft_echo(t_cmd *cmd, t_data *data);
void	quote_bin(char **path, t_data *data);
void	ft_exit(t_cmd *cmd, t_data *data);
int		print_esc(char *word, int *i);
char	*get_name(char *word, int *i);
int		print_var(char *word, int *i, t_data *data);
void	ft_toggle_quote(char c, t_data *data);

void	ft_node_cmd(t_cmd *cmd, t_data *data);
void	ft_node(t_data *data);
void	ft_free_list(t_list *big_node);

void	remove_char(char **string, int *a, int *b);
int		env_check(char *del, t_data *data);
int		ft_option(char *word);
void	quote_bin2(char **path, int *strong, int *weak, int *i);
void	quote_bin(char **path, t_data *data);

void	reset_std(t_data *data);

char	*clear_quotes(char *value, t_data *data);
#endif
