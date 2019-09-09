/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:39:42 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/05 21:41:19 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H
# include "libft.h"
# include "termcap.h"
# include "sel_structs.h"
# include "signal.h"
# include "sys/ioctl.h"
# define ULINE "\e[4m"
# define REV "\e[7m"
# define REV_ULINE "\e[4;7m"
# define NORM "\e[m"
# define UP "\e[A" 
# define DOWN "\e[B"
# define RIGHT "\e[C"
# define LEFT "\e[D"
# define DEL "\e[3~"
# define BS "\127" //also ascii value 8 apparently
# define SPACE " "
# define ESC "\e"
# define ENTER "\10"

t_sel_list		*make_list(int ac, char **av);
t_select		*make_select(t_sel_list *options);
t_select		*store_sel(t_select *sel);
void			free_sel(t_select *sel);
void			sel_signals(void);
void			screen_save_clear(int mode);

void			print_selected(t_select *sel);
void			ft_do_cap(char *cap);
void			print_opts(t_select *sel);
void			columnize_opts(t_select *sel);
void			add_colour(char *colour, t_sel_list *opts);
void			del_item(t_select *sel);
void			select_item(t_select *sel);
void			move_hor(t_select *sel, t_sel_list *opt);
void			move_ver(t_select *sel, int up);
int				selchar(int c);

#endif
