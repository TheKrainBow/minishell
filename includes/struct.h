/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:04:10 by magostin          #+#    #+#             */
/*   Updated: 2021/10/05 15:23:59 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"
# define SIZE_HISTORY 10
# define GPROMPT "\033[1;32m➜  \033[1;34mminishell\033[0m "
# define RPROMPT "\033[1;31m➜  \033[1;34mminishell\033[0m "

typedef struct s_lst_pid
{
	pid_t					pid;
	struct s_lst_pid		*next;
	struct s_lst_pid		*prev;
}							t_lst_pid;

typedef struct s_global
{
	pid_t					pid;
	int						exit_status;
	int						main;
}							t_global;

extern t_global			g_pid;

typedef struct s_lst_fd
{
	int						fd;
	struct s_lst_fd			*next;
	struct s_lst_fd			*prev;
}							t_lst_fd;

typedef struct s_cmd
{
	char					**args;
	t_lst_fd				*fd_out;
	t_lst_fd				*fd_in;
	pid_t					pid;
	int						piped;
	int						fds[2];
}							t_cmd;

typedef struct s_fd
{
	int						stdout_save;
	int						stdin_save;
	int						*fd_in;
	int						fd_in_size;
}							t_fd;

typedef struct s_caps
{
	char					*reset;
	char					*le;
	char					*nd;
	char					*dl;
	char					*sc;
	char					*rc;
	char					*ce;
}							t_caps;

typedef struct s_data
{
	t_fd					fd;
	t_lst_pid				*pid;
	t_caps					*caps;
	char					*history[SIZE_HISTORY];
	char					*save_cmd_history;
	char					*current_cmd;
	int						index_history;
	t_list					*lexed_line;
	t_list					*parsed_line;
	struct termios			save_old_term;
	char					quote;
	char					**path;
	char					**temp_environ;
	int						wexitstatus;
	int						wifexited;
	int						printed;
}							t_data;

#endif
