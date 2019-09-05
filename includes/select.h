/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:39:42 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/04 19:36:18 by dromansk         ###   ########.fr       */
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
# define UP 4283163
# define DOWN 4348699
# define RIGHT 4414235
# define LEFT 4479771
# define DEL 2117294875L
# define BS 127
# define SPACE ' '
# define ESC 27
# define ENTER 10

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
