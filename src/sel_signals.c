/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:54:24 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 22:17:51 by dromansk         ###   ########.fr       */
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
		signal(SIGWINCH, win_resize);
	}
}

void	sel_int(int sig)
{
	t_select	*sel;

	if (sig)
	{
		sel = store_sel(0);
		tcsetattr(sel->termfd, TCSANOW, sel->old);
		screen_save_clear(1, sel);
		free_sel(sel);
		exit(1);
	}
}

void	sel_stop(int sig)
{
	t_select	*sel;

	sel = store_sel(0);
	screen_save_clear(1, sel);
	if (sig == SIGTSTP)
	{
		signal(sig, SIG_DFL);
		ioctl(2, TIOCSTI, "\x1A");
	}
}

void	sel_cont(int sig)
{
	t_select	*sel;

	if (sig)
	{
		sel = store_sel(0);
		screen_save_clear(0, sel);
		signal(SIGCONT, sel_cont);
		print_opts(sel);
		signal(SIGTSTP, sel_stop);
		signal(SIGSTOP, sel_stop);
	}
}

void	sel_signals(void)
{
	signal(SIGWINCH, win_resize);
	signal(SIGINT, sel_int);
	signal(SIGCONT, sel_cont);
	signal(SIGSTOP, sel_int);
	signal(SIGKILL, sel_int);
	signal(SIGQUIT, sel_int);
	signal(SIGABRT, sel_int);
	signal(SIGTSTP, sel_stop);
}
