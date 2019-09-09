/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:54:24 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/08 17:48:35 by dromansk         ###   ########.fr       */
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
		while (sel->options->col != 0 && sel->options->row != 0)
			sel->options = sel->options->next;
		print_opts(sel);
	}
}

void	sel_quit(int sig)
{
	t_select *sel;

	if (sig)
	{
		sel = store_sel(0);
		sel->status = 1;
	}
}

void	sel_signals(void)
{
	signal(SIGWINCH, win_resize);
//	signal(SIGKILL, sel_kill);
	signal(SIGQUIT, sel_quit);
//	signal(SIGSTOP, sel_stop);
//	signal(SIGCONT, sel_cont);
}
