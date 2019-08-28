/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwht.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:37:02 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/25 20:12:40 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** currently super buggy, not a needed function for this project tho
** if I feel like finishing this it'll get updated
*/

static int		wht_wordlen(char *s)
{
	int		i;

	i = 0;
	if (!s[0])
		return (0);
	while (s[i] != ' ' || s[i] != '\n' || s[i] != '\t')
		i++;
	return (i);
}

char			*ft_strwht(char *s)
{
	char	*trim;
	char	*res;
	int		i;

	trim = ft_strtrim(s);
	i = 0;
	res = ft_strnew(0);
	while (trim[i])
	{
		if (!(i = wht_wordlen(trim)))
			break ;
		if (res[0])
			res = swap_n_free(ft_strjoin(res, " "), &res);
		res = swap_n_free(ft_strjoin(res, ft_strndup(trim, i)), &res);
		trim += i;
		while (*trim == ' ' || *trim == '\n' || *trim == '\t')
			trim++;
	}
	return (res);
}
