/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:49:36 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:49:40 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "./libft/libft.h"

typedef struct		s_slist
{
	void			*room;
	int				num;
	int				used;
	int				ant;
	struct s_slist	*next;
}					t_slist;
typedef struct		s_lemin
{
	char			*string;
	char			*line;
	int				ants;
	int				index;
	int				error;
	char			**arr;
	int				rooms;
	int				y;
	int				done;
	int				iter;
	char			*start;
	char			*end;
	t_slist			*list;
	t_slist			*ways[100];
}					t_lemin;
void				validate(t_lemin *lem);
void				parse(t_lemin *lem, int i);
t_slist				*ft_slist_new(char *room, int num);
int					ft_slist_pushback(t_slist **begin, char *room, int num);
void				ft_slist_pushfront(t_slist **begin, char *room, int num);
void				bfs(t_lemin *lem, int i, int index);
void				find_way(t_lemin *lem);
char				*get_pair(char *str, char *find, int a);
void				set_turns(t_lemin *lem);
int					ft_slist_length(t_slist *list);
void				clean_all(t_lemin *lem, int way, int x);
void				error_exit(t_lemin *lem, int x);
void				cut_array(t_lemin *lem, int x);
void				check_parse(t_lemin *lem, int i);
void				check_bfs(t_lemin *lem, int i);
void				clean_array(char **arr);
#endif
