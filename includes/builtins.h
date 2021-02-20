/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:01:52 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 22:46:02 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_print_env(t_cmd *cmd, t_data *data);
void	ft_export_env(t_cmd *cmd, t_data *data);
int		ft_env_size(void);
void	ft_malloc_env(void);
void	ft_free_env(void);
int		ft_find_in_env(char *name);
void	ft_unset_env(t_cmd *cmd, t_data *data);
void	ft_update_path(t_data *data);

void	ft_execve(t_cmd *cmd, t_data *data);
void	ft_cmd(t_cmd *cmd, t_data *data);

void	pwd(t_cmd *cmd, t_data *data);
void	cd(t_cmd *cmd, t_data *data);
void	echo(t_cmd *cmd, t_data *data);
void	ft_exit(t_cmd *cmd, t_data *data);
int		print_esc(char *word, int *i);
char	*get_name(char *word, int *i);
int		print_var(char *word, int *i, t_data *data);

void	ft_node(t_data *data);
void	ft_free_list(t_list *big_node);

#endif