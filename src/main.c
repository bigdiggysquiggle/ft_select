/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/05 14:58:18 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			ft_do_cap(char *cap)
{
	char	*s;

	s = tgetstr(cap, NULL);
	tputs(s, 1, selchar);
}

long			read_chars(void)
{
	long	msg;

	msg = 0;
	if (read(0, &msg, 8) < 0)
		return (0);
	return (msg);
}

void			handle_input(t_select *sel, long c)
{
	//if above changes, make this do numerical comparisons
	add_colour(sel->options->sel ? REV : NORM, sel->options);
	if (SPACE == c)
		select_item(sel);
	if (LEFT == c)
		move_hor(sel, sel->options->prev);
	if (RIGHT == c)
		move_hor(sel, sel->options->next);
	if (UP == c)
		move_ver(sel, 1);
	if (DOWN == c)
		move_ver(sel, 0);
	if (DEL == c || BS == c)
		del_item(sel);
	if (ESC == c)
		sel->status = 1;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}

static t_select	*ft_select(t_select *sel)
{
	long	c;

	sel->termios->c_iflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, sel->termios);
	sel_signals();
	print_opts(sel);
	while (!sel->status)
	{
		c = read_chars();
		handle_input(sel, c);
	}
	return (sel);
}

int				main(int ac, char **av)
{
	t_select		*sel;
	t_sel_list		*list;
	struct termios	og;

	sel = NULL;
	if (!isatty(0))
		ft_printf("Error: Not a tty\n");
	else if (tcgetattr(0, &og))
		ft_printf("Error: Couldn't get terminal attributes\n");
	else if ((list = make_list(ac, av)) && (sel = make_select(list)))
	{
		store_sel(sel);
		screen_save_clear(0);
		sel = ft_select(sel);
	}
	else
	{
		ft_printf("Error: Failed to generate selection list\n");
		return (1);
	}
	tcsetattr(1, TCSANOW, &og);
	screen_save_clear(1);
	print_selected(sel);
	return (0);
}
