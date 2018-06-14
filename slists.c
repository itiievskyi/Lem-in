/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slists.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_slist	*ft_slist_new(char *room, int num)
{
	t_slist	*list;

	list = (t_slist*)malloc(sizeof(t_slist));
	list->room = ft_strdup(room);
	list->num = num;
	list->next = NULL;
	return (list);
}

void	ft_slist_pushback(t_slist **begin, void *room, int num)
{
	t_slist *temp;

	temp = *begin;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = ft_slist_new(room, num);
	}
	else
		*begin = ft_slist_new(room, num);
}

void	ft_slist_pushfront(t_slist **begin, void *room, int num)
{
	t_slist *temp;

	temp = *begin;
	if (begin)
	{
		temp = ft_slist_new(room, num);
		temp->next = *begin;
		*begin = temp;
	}
	else
		*begin = ft_slist_new(room, num);
}
