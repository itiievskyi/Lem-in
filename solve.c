/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	reinit_list(t_lemin *lem)
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

void		find_way(t_lemin *lem)
{
	t_slist		*temp;
	int			a;

	temp = lem->list;
	while (temp && ft_strcmp(temp->room, lem->end))
			temp = temp->next;
	a = temp->num - 1;
	ft_slist_pushback(&lem->ways[lem->iter], temp->room, temp->num);
	while (a >= 0)
	{
		temp = lem->list;
		while (temp)
		{
			if (temp->num == a && a >= 0 && !temp->used)
				break ;
			temp = temp->next;
		}
		ft_slist_pushfront(&lem->ways[lem->iter], temp->room, temp->num);
		a -= 1;
		if (ft_strcmp(temp->room, lem->start))
			temp->used = 1;
	}
	reinit_list(lem);
}

/*
	t_slist *t;
	t = lem->list;
	while (t)
	{
		ft_printf("room = \'%s\', its index = %d\n", t->room, t->num);
		t = t->next;
	}
*/
//	create_rooms_list(lem);
//	ft_printf("start = %s\n", lem->start);
//	ft_printf("end = %s\n", lem->end);
//	ft_printf("string = %s\n", lem->arr[4]);
//	ft_printf("word = %s\n", get_word(lem->arr[4], 3));


/* ============= PRINT CHECK ============= */
/*
	ft_printf("WAY\n");
	t_slist *w;

	w = lem->ways[lem->iter];
	ft_printf("lem->iter = %d\n", lem->iter);
	while (w)
	{
		ft_printf("room = \'%s\', its index = %d, is used? = %d\n", w->room, w->num, w->used);
		w = w->next;
	}

	ft_printf("LIST\n");
	t_slist *t;
	t = lem->list;
	while (t)
	{
		ft_printf("room = \'%s\', its index = %d, is used? = %d\n", t->room, t->num, t->used);
		t = t->next;
	}
*/
/* ============= PRINT CHECK ============= */
