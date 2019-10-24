/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 14:10:35 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			screen_save_clear(int mode, t_select *sel)
{
	if (!mode)
	{
		sel->termios->c_lflag &= ~(ECHO | ICANON);
		tcsetattr(0, TCSANOW, sel->termios);
		store_sel(sel);
		ft_do_cap("cl");
		ft_do_cap("ti");
		ft_do_cap("vi");
	}
	else
	{
		ft_do_cap("te");
		ft_do_cap("ve");
	}
}

char			*read_chars(char *msg, t_select *sel)
{
	int		ret;

	ret = read(sel->termfd, msg, 4);
	if (ret >= 0)
		msg[ret] = 0;
	else
		ft_bzero(msg, 4);
	return (msg);
}

void			handle_input(t_select *sel, char *c)
{
	if (ft_strequ(SPACE, c))
		select_item(sel);
	if (ft_strequ(LEFT, c))
		move_hor(sel, 1);
	if (ft_strequ(RIGHT, c))
		move_hor(sel, 0);
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
}

static t_select	*ft_select(t_select *sel)
{
	static char	c[5];

	sel_signals();
	print_opts(sel);
	while (!sel->status)
	{
		ft_bzero(c, 5);
		read_chars(c, sel);
		handle_input(sel, c);
	}
	return (sel);
}

int				main(int ac, char **av)
{
	t_select		*sel;
	t_sel_list		*list;
	static char		buf[2048];

	sel = NULL;
	if (!isatty(0))
		ft_printf("Error: Not a tty\n");
	else if ((list = make_list(ac, av)))
	{
		if ((sel = make_select(list)))
		{
			tgetent(buf, getenv("TERM"));
			screen_save_clear(0, sel);
			sel = ft_select(sel);
		}
	}
	else
		return (1);
	tcsetattr(0, TCSANOW, sel->old);
	screen_save_clear(1, sel);
	print_selected(sel);
	return (0);
}
