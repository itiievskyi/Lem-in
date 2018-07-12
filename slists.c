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

int		ft_slist_length(t_slist *list)
{
	int		len;
	t_slist *temp;

	temp = list;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

t_slist	*ft_slist_new(char *room, int num)
{
	t_slist	*list;

	list = (t_slist*)malloc(sizeof(t_slist));
	list->room = ft_strdup(room);
	list->num = num;
	list->used = 0;
	list->ant = 0;
	list->next = NULL;
	return (list);
}

int		ft_slist_pushback(t_slist **begin, char *room, int num)
{
	t_slist *temp;

	temp = *begin;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = ft_slist_new(room, num);
	}
	else if (room)
		*begin = ft_slist_new(room, num);
	else
		return (0);
	return (1);
}

void	ft_slist_pushfront(t_slist **begin, char *room, int num)
{
	t_slist *temp;

	temp = *begin;
	if (begin)
	{
		temp = ft_slist_new(room, num);
		temp->next = *begin;
		*begin = temp;
	}
	else if (room)
		*begin = ft_slist_new(room, num);
}
