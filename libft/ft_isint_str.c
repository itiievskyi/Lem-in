/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 11:27:21 by itiievsk          #+#    #+#             */
/*   Updated: 2018/07/23 11:27:23 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isint_str(char *s)
{
	if (s[0] != '-' && !ft_isdigit_str(s))
		return (0);
	if (s[0] == '-' && !ft_isdigit_str(&s[1]))
		return (0);
	if (ft_atoi(s) > 2147483647 || ft_atoi(s) < -2147483648)
		return (0);
	if ((*s != '-' && ft_strlen(s) > 10) || (*s == '-' && ft_strlen(s) > 11) ||
	(*s == '-' && ft_strlen(s) == 1))
		return (0);
	if (ft_strnequ(s, "214748364", 9) && s[9] != '\0' && s[9] > '7')
		return (0);
	if (ft_strnequ(s, "-214748364", 10) && s[10] != '\0' && s[10] > '8')
		return (0);
	return (1);
}
