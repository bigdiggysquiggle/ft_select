/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/03 20:47:48 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

t_select	*sel;

void			ft_do_cap(char *cap)
{
	char	*s;

	s = tgetstr(cap);
	tputs(s, 1);
}

void			noncanon(sel)
{
	tcgettattr(0, sel->termios);
	tcsettatr(0, ICANON, sel->termios);
}

void			handle_input(t_select *sel, char c)
{
	if (c == SPACE)
		select_item(sel);
	if (c == LEFT)
		move_hor(sel, sel->options->prev);
	if (c == RIGHT)
		move_hor(sel, sel->options->next);
	if (c == UP)
		move_ver(sel, 1);
	if (c == DOWN)
		move_ver(sel, 0);
}

static t_select	ft_select(t_select *sel)
{
//	char	buf[45067];
	char	c[1];
	

	noncanon(sel);
//	tgetent(buf, getenv("TERM"));
//	ft_do_cap("cl");
	sel_signals();
	print_opts(sel);
	while (!sel->status)
	{
		read(1, c, 1);
		handle_input(sel, *c);
	}
//	tputs(buf);
}

int				main(int ac, char **av)
{
	t_sel_list	*list;
	termios_o	og;

	if (!isatty(0))
		ft_printf("Error: Not a tty\n");
	else if (tcgettatr(0, &og))
		ft_printf("Error: Couldn't get terminal attributes\n");
	else if ((list = make_list(ac, av)) && (sel = make_select(list)))
	{
		store_sel(sel);
		ft_do_cap("smcup");//might be wrong termcap
		sel = ft_select(sel);
	}
	else
	{
		ft_printf("Error: Failed to generate selection list\n");
		return (1);
	}
	tcsetattr(1, TCSANOW, &og);
	ft_do_cap("rmcup");//might be wrong termcap
	print_sel(sel);
	return (0);
}
