/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/29 21:26:51 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

t_select	*sel;

void			ft_do_cap(char *cap)
{
	char	buf[45067];
	char	*s;

	s = tgetstr(cap);
	tputs(s, 1);
}

void			noncanon(sel)
{
	tcgettattr(0, sel->termios);
	tcsettatr(0, ICANON, sel->termios);
}

static t_select	ft_select(t_select *sel)
{
	char	buf[45067];

	noncanon(sel);
	tgetent(buf, getenv("TERM"));
	ft_do_cap("cl");
	signal(SIGWINCH, win_resize);//can use global vars for this fuck yeah
	//find out other signals I need to check for
	while (!sel->status)
	{
		//
	}
	tputs(buf);
}

int				main(int ac, char **av)
{
	t_sel_list	*list;
	termios_o	og;

	if (!isatty(0))
		//error here
	if (tcgettatr(0, &og))
		//error here
	if ((list = make_list(ac, av)) && (sel = make_select(list)))
		sel = ft_select(sel);
	tcsetattr(1, TCSANOW, &og);
	print_sel(sel);
	return (0);
}
