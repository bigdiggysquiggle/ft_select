/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:54:24 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/23 13:19:21 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	win_resize(int sig)
{
	t_select	*sel;

	if (sig == SIGWINCH)
	{
		ft_do_cap("cl");
		sel = store_sel(NULL);
		print_opts(sel);
	}
}

void	sel_int(int sig)
{
	t_select *sel;

	if (sig)
	{
		sel = store_sel(0);
		tcsetattr(sel->termfd, TCSANOW, sel->old);
		screen_save_clear(1, sel);
		free_sel(sel);
		exit(1);
	}
}

/*
**	signal(SIGKILL, sel_kill);
**	signal(SIGQUIT, sel_quit);
**	signal(SIGSTOP, sel_stop);
**	signal(SIGCONT, sel_cont);
*/

void	sel_signals(void)
{
	signal(SIGWINCH, win_resize);
	signal(SIGINT, sel_int);
}
