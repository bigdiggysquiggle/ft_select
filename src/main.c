/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/25 22:09:24 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			screen_save_clear(int mode, t_select *sel)
{
	if (!mode)
	{
		sel->termios->c_lflag &= ~(ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, sel->termios);
		store_sel(sel);
		ft_do_cap("cl");
		ft_do_cap("ti");
		ft_do_cap("vi");
	}
	else
	{
		ft_do_cap("te");
		ft_do_cap("ve");
		tcsetattr(STDIN_FILENO, TCSANOW, sel->old);
	}
}

static char		*read_chars(char *msg)
{
	int		ret;

	ret = read(STDIN_FILENO, msg, 4);
	if (ret >= 0)
		msg[ret] = 0;
	else
		ft_bzero(msg, 4);
	return (msg);
}

static void		handle_input(t_select *sel, char *c)
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
	if (ft_strequ("i", c))
		invert_selection(sel);
	if (ft_strequ("a", c) || ft_strequ("d", c))
		select_all(sel, c[0] == 'a');
	if (ft_strequ("s", c))
		secret(sel);
	if (ft_strequ("h", c))
		print_help(sel);
}

static t_select	*ft_select(t_select *sel)
{
	static char	c[5];

	sel_signals();
	print_opts(sel);
	while (!sel->status)
	{
		ft_bzero(c, 5);
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
	error_checks();
	if (ac > 1 && (list = make_list(ac, av)))
	{
		if ((sel = make_select(list)))
		{
			screen_save_clear(0, sel);
			sel = ft_select(sel);
		}
	}
	else
		return (1);
	screen_save_clear(1, sel);
	print_selected(sel);
	return (0);
}
