/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		check_coos(t_lemin *lem, int i, int x)
{
	char	*s1;
	char	*s2;

	while (lem->arr[++i])
	{
		if (lem->arr[i][0] != '#' && (s1 = (ft_strchr(lem->arr[i], ' '))))
		{
			++s1;
			x = 0;
			while (lem->arr[++x] && x < i)
			{
				if (lem->arr[x][0] != '#' &&
				(s2 = (ft_strchr(lem->arr[x], ' '))))
				{
					++s2;
					if (ft_strequ(s1, s2))
						cut_array(lem, i);
				}
			}
		}
	}
}

int			check_pipes(t_lemin *lem, char *s1, int empty1, int empty2)
{
	char	**arr1;
	t_slist	*t;

	lem->error = 0;
	if ((arr1 = ft_strsplit(s1, '-')) && s1[0] != '#' &&
		(t = lem->list) && ft_words_count(s1) == 1 && ft_strchr(s1, '-'))
	{
		while (!lem->error)
		{
			if (t && !ft_strequ(arr1[0], t->room) &&
			!ft_strequ(arr1[0], lem->end) && !ft_strequ(arr1[0], lem->start))
				empty1++;
			if (t && !ft_strequ(arr1[1], t->room) &&
			!ft_strequ(arr1[1], lem->end) && !ft_strequ(arr1[1], lem->start))
				empty2++;
			if (ft_slist_length(lem->list) != 0 && (((ft_slist_length(lem->list)
			== empty1 || ft_slist_length(lem->list) == empty2)) || (!t &&
			!ft_strequ(arr1[0], lem->end) && !ft_strequ(arr1[0], lem->start))))
				lem->error = 1;
			if (!t || !(t = t->next))
				break ;
		}
	}
	clean_array(arr1);
	return (lem->error);
}

static int	check_the_same(t_lemin *lem, int x, int i, int error)
{
	char	*s;
	char	**arr1;

	if (lem->arr[x][0] != '#' && ft_words_count(lem->arr[x]) == 1 &&
		ft_strchr(lem->arr[x], '-'))
	{
		arr1 = ft_strsplit(lem->arr[x], '-');
		if (ft_strequ(arr1[0], arr1[1]))
			error = 1;
		clean_array(arr1);
	}
	while (!error && (s = lem->arr[++i]) && i < x)
	{
		arr1 = ft_strsplit(s, '-');
		if (s[0] != '#' && ft_strequ(s, lem->arr[x]))
			error = 1;
		clean_array(arr1);
	}
	return (error);
}

void		check_lines(t_lemin *lem, int i, int words, int pipe)
{
	char	*s;

	while (lem->arr[++i])
	{
		s = lem->arr[i];
		words = ft_words_count(lem->arr[i]);
		if (s && (s[0] == 'L' || (s[0] != '#' && words != 1 && words != 3) ||
		(!ft_isdigit_str(s) && words == 1 && !ft_strchr(s, '-') && s[0] != '#')
		|| s[0] == ' ' || ((!ft_strcmp(s, "##start") || !ft_strcmp(s, "##end"))
		&& lem->arr[i + 1] && ft_words_count(lem->arr[i + 1]) != 3) ||
		check_pipes(lem, s, 0, 0) || check_the_same(lem, i, -1, 0)))
		{
			cut_array(lem, i);
			break ;
		}
		if (s[0] != '#' && words == 1 && ft_strchr(s, '-'))
			pipe++;
	}
	if (i < 6 || !pipe)
		error_exit(lem, 0);
}

void		check_main(t_lemin *lem, int i, int room, int pipe)
{
	char	**t;
	char	*s;

	while (!lem->error && (s = lem->arr[++i]))
	{
		if (ft_isdigit_str(s))
		{
			if (pipe || room)
				cut_array(lem, i);
			else
				lem->ants = ft_atoi(s);
		}
		if (s && s[0] != '#' && ft_words_count(s) == 3 && ++room)
		{
			t = ft_strsplit(s, ' ');
			if (!ft_isint_str(t[2]) || !ft_isint_str(t[1]))
			{
				cut_array(lem, i);
				lem->error = 1;
			}
			clean_array(t);
		}
		if (s && s[0] != '#' && ft_words_count(s) == 1 && ft_strchr(s, '-'))
			pipe++;
	}
}
