/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/05 21:43:34 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			ft_do_cap(char *cap)
{
	char	*s;

	s = tgetstr(cap, NULL);
	tputs(s, 1, selchar);
}

char			*read_chars(char *msg)
{
	int		ret;

	ret = read(0, msg, 4);
//	printf("ret %d\n", ret); important for key checking
	if (ret == -1)
		ft_bzero(msg, 4);
	msg[ret] = 0;
//	printf("at 4 %d\n", msg[ret]); important for key checking
	return (msg);
}

void			handle_input(t_select *sel, char *c)
{
//	int i = 0; important for key checking
//	while (c[i]) important for key checking
//		printf("%d\n", c[i++]);	important for key checking
//	printf("--------\n"); important for key checking
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
	if (ft_strequ(ESC, c))
		sel->status = 1;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}

static t_select	*ft_select(t_select *sel)
{
	char	c[5];

	sel->termios->c_iflag &= ~(ECHO | ICANON);
//	tcsetattr(0, TCSANOW, sel->termios); uncomment when not key checking
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
