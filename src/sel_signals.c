/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:54:24 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/31 15:58:47 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	win_resize(int sig)
{
	t_select	*sel;
	if (sig = SIGWINCH)
	{
		//window reprinting
		sel = store_sel(0);
		ft_select(0);
	}
}

void	sel_signals(void)
{
	signal(SIGWINCH, win_resize);
}
