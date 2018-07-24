/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:54 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:56 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		validate(t_lemin *lem, int i, int x)
{
	if (!lem)
		error_exit(lem, 0);
	while (lem->arr[i] && lem->arr[i][0] == '#')
		i++;
	while (lem->arr[i] && (lem->arr[i])[x] != '\0')
		if (!ft_isdigit(lem->arr[i][x++]) || ft_atoi(lem->arr[i]) == 0 ||
		!ft_isint_str(lem->arr[i]))
			error_exit(lem, 0);
	while ((lem->arr[++i]) &&
			!(ft_words_count(lem->arr[i]) == 1 && ft_strchr(lem->arr[i], '-')))
	{
		if ((ft_strequ(lem->arr[i], "##start") ||
			ft_strequ(lem->arr[i], "##end")) && !lem->arr[i + 1])
			error_exit(lem, 0);
		if (ft_strequ(lem->arr[i], "##start") && lem->arr[i + 1][0] != '#')
			lem->start = get_word(lem->arr[i + 1], 1);
		else if (ft_strequ(lem->arr[i], "##end") && lem->arr[i + 1][0] != '#')
			lem->end = get_word(lem->arr[i + 1], 1);
	}
	check_main(lem, -1, 0, 0);
	check_coos(lem, 0, 0);
	check_lines(lem, -1, 0, 0);
}

static void	write_string(t_lemin *lem)
{
	char	ch;
	int		lines;

	lines = 0;
	while (read(0, &ch, 1) > 0)
	{
		lem->string[lem->index] = ch;
		if (ch == '\n')
		{
			if (lem->string[lem->index - 1] == '\n' || lem->index == 0)
				break ;
			lines++;
		}
		lem->index++;
	}
	if (!lem->index || lines < 6)
		error_exit(lem, 0);
	lem->string[lem->index] = '\0';
	lem->index++;
	lem->arr = ft_strsplit(lem->string, '\n');
	validate(lem, 0, 0);
}

void		reinit_list(t_lemin *lem)
{
	t_slist		*temp;

	temp = lem->list;
	while (temp)
	{
		if (!ft_strcmp(temp->room, lem->end))
			temp->num = lem->rooms - 1;
		if (!ft_strcmp(temp->room, lem->start))
			temp->num = 0;
		if (!temp->used && temp->num != 0 && temp->num != lem->rooms - 1)
			temp->num = -1;
		temp = temp->next;
	}
}

static void	init_struct(t_lemin *lem)
{
	lem->ants = 0;
	lem->index = 0;
	lem->error = 0;
	lem->string = (char*)malloc(sizeof(char) * BUF);
	lem->arr = NULL;
	lem->rooms = 0;
	lem->y = 0;
	lem->done = 0;
	lem->iter = 0;
	lem->col = 0;
	lem->cycle_error = 0;
	ft_bzero(lem->ways, sizeof(lem->ways));
}

int			main(int argc, char **argv)
{
	t_lemin		*lem;

	lem = (t_lemin*)malloc(sizeof(t_lemin));
	init_struct(lem);
	if (argc == 2 && ft_strequ(argv[1], "color"))
		lem->col = 1;
	if (argc > 2 || (argc == 2 && !ft_strequ(argv[1], "color")))
	{
		ft_printf(C_RED "Wrong argument!\nUse [color] to highlight output.\n");
		error_exit(lem, 0);
	}
	write_string(lem);
	parse(lem, 0);
	while (!lem->done)
	{
		bfs(lem, 0, 0);
		if (lem->done || (lem->iter > 0 && ft_slist_length(lem->ways[0]) == 2))
			break ;
		find_way(lem);
		reinit_list(lem);
		lem->iter += 1;
	}
	set_turns(lem);
	clean_all(lem, -1, 0);
	return (0);
}
