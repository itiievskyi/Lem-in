/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		clean_all(t_lemin *lem, int way, int x)
{
	t_slist		*temp;

	free(lem->string);
	free(lem->line);
	free(lem->start);
	free(lem->end);
	while (lem->arr[x])
		free(lem->arr[x++]);
	free(lem->arr);
	while ((temp = lem->list))
	{
		lem->list = lem->list->next;
		free(temp->room);
		free(temp);
	}
	while (lem->ways[++way])
	{
		while (lem->ways[way])
		{
			temp = lem->ways[way];
			lem->ways[way] = (lem->ways[way])->next;
			free(temp->room);
			free(temp);
		}
	}
}

void		error_exit(t_lemin *lem, int x)
{
	t_slist		*temp;

	x = 0;
	free(lem->string);
	if (lem->start)
		free(lem->start);
	if (lem->line)
		free(lem->line);
	if (lem->end)
		free(lem->end);
	clean_array(lem->arr);
	while (lem->list)
	{
		temp = lem->list;
		lem->list = lem->list->next;
		free(temp->room);
		free(temp);
	}
	lem->col == 0 ? ft_printf("ERROR\n") : ft_printf(CB_RED "ERROR\n" C_RESET);
	exit(-1);
}

void		cut_array(t_lemin *lem, int x)
{
	while (lem->arr[x])
	{
		free(lem->arr[x]);
		lem->arr[x++] = NULL;
	}
}

void		clean_array(char **arr)
{
	int a;

	a = -1;
	if (arr)
	{
		while (arr[++a])
			free(arr[a]);
		free(arr);
	}
}
