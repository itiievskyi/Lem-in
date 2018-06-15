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
		lem->string[lem->index] = (char)malloc(sizeof(char));
		lem->string[lem->index] = ch;
		lem->index++;
		if (ch == '\n')
			lines++;
	}
	lem->string[lem->index] = (char)malloc(sizeof(char));
	lem->string[lem->index] = '\0';
	lem->index++;
	if (lines < 6)
		lem->error = 1;
	validate(lem);
	ft_printf("%s\n", lem->string);
	lem->arr = ft_strsplit(lem->string, '\n');
}

static void	init_struct(t_lemin *lem)
{
	lem->ants = 0;
	lem->index = 0;
	lem->error = 0;
	lem->string = (char*)malloc(sizeof(char));
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
		bfs(lem, 0);
		if (lem->done)
			break ;
		find_way(lem);
		lem->iter += 1;
	}
	int x = -1;
	while (lem->ways[++x])
	{
		ft_printf("WAY # %d\n", x);
		t_slist *w = lem->ways[x];
		while (w)
		{
			ft_printf("room = \'%s\', its index = %d, is used? = %d\n", w->room, w->num, w->used);
			w = w->next;
		}
	}
	free(lem);
	return (0);
}
