/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:35:21 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/25 00:17:41 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

t_select			*store_sel(t_select *sel)
{
	static t_select *stored;

	if (sel == NULL)
		return (stored);
	else
		stored = sel;
	return (sel);
}

static t_sel_list	*new_item(char *item)
{
	t_sel_list	*new;

	if ((new = (t_sel_list *)malloc(sizeof(t_sel_list))))
	{
		new->option = item;
		new->col = 0;
		new->row = 0;
		new->len = ft_strlen(item);
		new->sel = 0;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

t_sel_list			*make_list(int ac, char **av)
{
	int			i;
	t_sel_list	*list;
	t_sel_list	*item;

	if (ac > 1)
	{
		i = 0;
		if ((list = new_item(av[++i])))
		{
			item = list;
			while (++i < ac)
			{
				list->next = new_item(av[i]);
				list->next->prev = list;
				list = list->next;
			}
			item->prev = list;
			list->next = item;
			return (item);
		}
	}
	return (NULL);
}

t_select			*make_select(t_sel_list *options)
{
	t_select				*sel;
	static struct termios	termios;
	static struct termios	old;

	if ((sel = (t_select *)malloc(sizeof(t_select))) && !tcgetattr(0, &termios))
	{
		ft_memcpy(&old, &termios, sizeof(struct termios));
		sel->first = options;
		sel->options = options;
		sel->termios = &termios;
		sel->len = sel_list_len(options);
		sel->old = &old;
		sel->status = 0;
		return (sel);
	}
	else if (!sel)
		ft_dprintf(STDERR_FILENO, "Error: failed to generate selection list.\n");
	else
		ft_dprintf(STDERR_FILENO, "Error: Couldn't get terminal attributes\n");
	return (NULL);
}

void				free_sel(t_select *sel)
{
	t_sel_list	*tmp;

	if (sel->options)
	{
		tmp = sel->options->next->next;
		while (tmp != sel->options)
		{
			free(tmp->prev);
			tmp = tmp->next;
		}
		if (tmp->prev != tmp)
			free(tmp->prev);
		free(tmp);
	}
	free(sel);
}
