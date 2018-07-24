/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 09:29:14 by itiievsk          #+#    #+#             */
/*   Updated: 2018/07/23 09:29:15 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			connected(t_lemin *lem)
{
	t_slist	*temp;
	int		conn;

	temp = lem->list;
	conn = 0;
	while (temp)
	{
		if (temp->num > -1)
			conn++;
		temp = temp->next;
	}
	return (conn);
}
