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
			if (lem->string[lem->index - 1] == '\n')
				break ;
			lines++;
		}
		lem->index++;
	}
	lem->string[lem->index] = '\0';
	lem->index++;
	lem->arr = ft_strsplit(lem->string, '\n');
	validate(lem);
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
	lem->string = (char*)malloc(sizeof(char) * 1000000);
	lem->arr = NULL;
	lem->rooms = 0;
	lem->y = 0;
	lem->done = 0;
	lem->iter = 0;
	ft_bzero(lem->ways, sizeof(lem->ways));
}

int			main(void)
{
	t_lemin		*lem;

	lem = (t_lemin*)malloc(sizeof(t_lemin));
	init_struct(lem);
	write_string(lem);
	parse(lem, 0);
	while (!lem->done)
	{
		bfs(lem, 0, 0);
		if (lem->done)
			break ;
		find_way(lem);
		reinit_list(lem);
		lem->iter += 1;
	}
	set_turns(lem);
	clean_all(lem, -1, 0);
	return (0);
}
