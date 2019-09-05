/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/04 18:28:37 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			ft_do_cap(char *cap)
{
	char	*s;

	s = tgetstr(cap, NULL);
	tputs(s, 1, selchar);
}

char			*read_chars(char *c)
{
	if (read(1, c, 1) > 0)
	{
		if (c[0] != ESC && c[0] != ' ')
			return ("");
		else if (read(1, c, 2) > 0)
			if (c[1] == '3' && read(1, c + 2, 1) > 0)
				c[3] = 0;
			else
				c[2] = 0;
		else
			return ("");
	}
	return (c);
}

void			handle_input(t_select *sel, char *c)
{
	add_colour(sel->options->sel ? REV : NORM, sel->options);
	if (ft_strequ(SPACE, c))
		select_item(sel);
	if (ft_strequ(LEFT, c))
		move_hor(sel, sel->options->prev);
	if (ft_strequ(RIGHT, c))
		move_hor(sel, sel->options->next);
	if (ft_strequ(UP, c))
		move_ver(sel, 1);
	if (ft_strequ(DOWN, c))
		move_ver(sel, 0);
	if (ft_strequ(DEL, c) || ft_strequ(BS, c))
		del_item(sel);
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}

static t_select	*ft_select(t_select *sel)
{
	char	c[4];

	tcsetattr(0, ICANON, sel->termios);
	sel_signals();
	print_opts(sel);
	while (!sel->status)
	{
		read_chars(c);
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
