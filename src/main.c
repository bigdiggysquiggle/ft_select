/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:47:17 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/23 09:25:57 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** us 'mr' to reverse colours and 'us' to underline instead
** 'me' and 'ue' to normal
** 'vi' to remove cursor 've' to make it normal'
** 'ti' for nonsequential cursor movement, 'te' for normal
*/

void			echo_bytes(char *s, int len)
{
	int		i = 0;

	while (i < len)
		ft_printf("%d\t", s[i++]);
	ft_printf("\n");
}

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

/*
** it's getting stuck here cuz it's stupid af
*/

char			*read_chars(char *msg, t_select *sel)
{
	int		ret;

	ret = read(sel->termfd, msg, 4);
//	printf("ret %d\n", ret); important for key checking
	if (ret >= 0)
		msg[ret] = 0;
	else
		ft_bzero(msg, 4);
//	printf("at 4 %d\n", msg[ret]); important for key checking
	return (msg);
}

void			handle_input(t_select *sel, char *c)
{
//	int i = 0; important for key checking
//	while (c[i]) important for key checking
//		printf("%d\n", c[i++]);	important for key checking
//	printf("--------\n"); important for key checking
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
}

/*
** UP    - 27	91	65	0
** DOWN  - 27	91	66	0
** LEFT  - 27	91	68	0
** RIGHT - 27	91	67	0
*/

static t_select	*ft_select(t_select *sel)
{
	static char	c[5];

	sel_signals();
	sel->options->sel |= 2;
	print_opts(sel);
//	ft_printf("UP    - ");
//	echo_bytes(UP, 4);
//	ft_printf("DOWN  - ");
//	echo_bytes(DOWN, 4);
//	ft_printf("LEFT  - ");
//	echo_bytes(LEFT, 4);
//	ft_printf("RIGHT - ");
//	echo_bytes(RIGHT, 4);
	while (!sel->status)
	{
		ft_bzero(c, 5);
		read_chars(c, sel);
//		ft_printf("READ  - ");//
//		echo_bytes(c, 4);//
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
