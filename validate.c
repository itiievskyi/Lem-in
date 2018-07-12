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

static void check_coos(t_lemin *lem, int i, int x)
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

static int	check_pipes(t_lemin *lem, char *s1)
{
	char	**arr1;
	t_slist	*temp;
	int		empty;

	temp = lem->list;
	empty = 0;
	arr1 = ft_strsplit(s1, '-');
	if (s1[0] != '#' && ft_words_count(s1) == 1 && ft_strchr(s1, '-'))
	{
		if (ft_strequ(arr1[0], arr1[1]))
		{
			clean_array(arr1);
			return (1);
		}
		while (temp)
		{
			if (!ft_strequ(arr1[0], temp->room) && !ft_strequ(arr1[1], temp->room))
				empty++;
			temp = temp->next;
		}
	}
	if (ft_slist_length(lem->list) != 0 && ft_slist_length(lem->list) == empty)
		lem->error = 1;
	clean_array(arr1);
	return (lem->error);
}

static void check_lines(t_lemin *lem, int i)
{
	int		words;
	char	*s;
	int		pipe;

	pipe = 0;
	while (lem->arr[i])
	{
		s = lem->arr[i];
		words = ft_words_count(lem->arr[i]);
		if (s && (s[0] == 'L' || (s[0] != '#' && words != 1 && words != 3) ||
			(i && words == 1 && !ft_strchr(s, '-') && s[0] != '#')||
			s[0] == ' ' || ((!ft_strcmp(s, "##start") || !ft_strcmp(s, "##end"))
			&& ft_words_count(lem->arr[i + 1]) != 3) || check_pipes(lem, s)))
		{
			cut_array(lem, i);
			break ;
		}
		if (s[0] != '#' && words == 1 && ft_strchr(s, '-'))
			pipe++;
		i++;
	}
	if (i < 6 || !pipe)
		error_exit(lem, 0);
}

void		validate(t_lemin *lem)
{
	int i;

	i = 0;
	if (!lem)
		error_exit(lem, 0);
	while ((lem->arr[0])[i] != '\0')
		if (!ft_isdigit(lem->arr[0][i++]) || ft_atoi(lem->arr[0]) == 0)
			error_exit(lem, 0);
	check_coos(lem, 0, 0);
	check_lines(lem, 0);
}

void		check_parse(t_lemin *lem, int i)
{
	int			x;
	char		*s1;
	char		*s2;

	lem->error = 0;
	if (!lem->start || !lem->end || ft_count_in_array(lem->arr, "##start") != 1
		|| ft_count_in_array(lem->arr, "##end") != 1)
			error_exit(lem, 0);
	while (lem->arr[++i])
	{
		x = 1;
		while (++x < i)
		{
			s1 = get_word(lem->arr[i], 1);
			s2 = get_word(lem->arr[x], 1);
			if (s1[0] != '#' && s2[0] != '#' && !ft_strcmp(s1, s2) &&
				ft_words_count(lem->arr[i]) != 1)
					lem->error = 1;
			free(s1);
			free(s2);
			if (lem->error) {
				cut_array(lem, i);
				break ;
			}
		}
		if (lem->arr[i] && check_pipes(lem, lem->arr[i]))
			cut_array(lem, i);
	}
}
