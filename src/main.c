/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/15 15:15:41 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** us 'mr' to reverse colours and 'us' to underline instead
** 'me' and 'ue' to normal
** 'vi' to remove cursor 've' to make it normal'
** 'ti' for nonsequential cursor movement, 'te' for normal
*/

void			screen_save_clear(int mode, t_select *sel)
{
	static char	buf[2048];

	if (!mode)
	{
		ft_bzero(buf, 2048);
		tgetent(buf, getenv("TERM"));
		sel->termios->c_iflag &= ~(ECHO | ICANON);
		tcsetattr(sel->termfd, TCSANOW, sel->termios);
		store_sel(sel);
		ft_do_cap("cl");
		ft_do_cap("ti");
		ft_do_cap("vi");
	}
	else
	{
		tputs(buf, 1, selchar);
		ft_do_cap("te");
		ft_do_cap("ve");
	}
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
		sel->status = 2;
	if (ft_strequ(ENTER, c))
		sel->status = 1;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}

static t_select	*ft_select(t_select *sel)
{
	static char	c[5];

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

	sel = NULL;
	if (!isatty(0))
		ft_printf("Error: Not a tty\n");
	else if ((list = make_list(ac, av)))
	{
		if ((sel = make_select(list)))
		{
			screen_save_clear(0, sel);
			sel = ft_select(sel);
		}
	}
	else
		return (1);
	tcsetattr(1, TCSANOW, sel->old);
	screen_save_clear(1, sel);
	print_selected(sel);
	return (0);
}
