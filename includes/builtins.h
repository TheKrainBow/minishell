/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:01:52 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 22:22:21 by magostin         ###   ########.fr       */
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

int		cd(/*t_data *data,*/char *arg);
int		echo(t_cmd *cmd, t_data *data);
int		pwd(void);

#endif