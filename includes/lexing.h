/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 03:08:55 by magostin          #+#    #+#             */
/*   Updated: 2021/04/23 14:15:30 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

void		lex_line(char *line, t_data *data);
void		pars_line(t_data *data);
void		ft_print_pars_line(t_data *data);
char		separator(char *str);
char		**ft_lst_to_tab_minishell(t_list *lst);
int			ft_lstsize_minishell(t_list *lst);
void		ft_destroy_pars_line(t_data *data);
void		pars_redirection_cmd(t_cmd *cmd);
void		apply_pipeline(t_data *data);
void		change_env_str(char **str, t_data *data);
void		apply_env(t_data *data, t_list *line);
void		pars_line_v2(t_data *data);

void		ft_close_fd(t_lst_fd *fd);
void		ft_destroy_pars_line(t_data *data);
void		ft_print_args(t_cmd *cmd, t_data *data);
void		ft_print_pars_line(t_data *data);
t_list		*create_cmd(t_list *lst, int piped);
void		execute_line(char *line, t_data *data);

#endif
