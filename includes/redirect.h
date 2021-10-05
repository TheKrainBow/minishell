/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:13:21 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/04/29 12:12:02 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H
# include "minishell.h"

void	redirector(int fd_default_output, t_data *data);
int		redirect_in(t_cmd *cmd, char *file_name);
int		redirect_out(t_cmd *cmd, char *file_name, int append);
void	ft_append_lst_pid(t_lst_pid **lst, pid_t pid);
void	ft_append_lst(t_lst_fd **lst, int fd);

#endif
