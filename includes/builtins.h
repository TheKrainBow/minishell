/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:01:52 by magostin          #+#    #+#             */
/*   Updated: 2021/02/16 14:11:32 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_print_env(void);
int		ft_export_env(t_cmd *cmd, t_data *data);
int		ft_env_size(void);
void	ft_malloc_env(void);
void	ft_free_env(void);
int		ft_find_in_env(char *name);
int		ft_unset_env(t_cmd *cmd, t_data *data);
void	ft_update_path(t_data *data);

void	ft_execve(t_cmd *cmd, t_data *data);
void	ft_cmd(t_cmd *cmd, t_data *data);

void	pwd(t_data *data);
void	cd(char *arg, t_data *data);
void	echo(t_cmd *cmd, t_data *data);
int		print_esc(char *word, int *i);
char	*get_name(char *word, int *i);
int		print_var(char *word, int *i, t_data *data);

#endif