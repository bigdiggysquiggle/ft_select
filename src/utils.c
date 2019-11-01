/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:25:42 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/01 02:05:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			error_checks(void)
{
	int		ret;
	char	buf[2048];

	if (!isatty(STDIN_FILENO))
	{
		ft_dprintf(STDERR_FILENO, "Error: Not a tty");
		exit(1);
	}
	else if ((ret = tgetent(buf, getenv("TERM"))))
		if (ret < 1)
		{
			ft_dprintf(STDERR_FILENO, ret ? "Error: Terminfo not found\n" :
					"Error: No terminal entry\n");
			exit(2);
		}
}

void			ft_do_cap(char *cap)
{
	char	*s;

	s = tgetstr(cap, NULL);
	tputs(s, 1, selchar);
}

void			ftgoto(int col, int row)
{
	char	*s;
	char	*t;

	t = tgetstr("cm", NULL);
	s = tgoto(t, col, row);
	tputs(s, 1, selchar);
}

int				selchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}

int				sel_list_len(t_sel_list *sel)
{
	t_sel_list	*curr;
	int			count;

	count = 1;
	curr = sel->next;
	while (curr != sel)
	{
		curr = curr->next;
		count++;
	}
	return (count);
}
