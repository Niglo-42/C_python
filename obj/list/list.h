/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:43:17 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/22 16:36:09 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include "../obj.h"
# include "../../runtime/arena.h"

# define LOCK 1
# define UNLOCK 2

typedef struct s_list
{
	t_obj	base;
	size_t	size;
	size_t	cap;
	t_obj	*members[];
}	t_list;

t_list	*lst(t_arena *arena, int n, ...);
void	append(t_list **self, t_obj *data, t_arena *arena);
t_obj	*pop(t_list *self, int index);
t_list	*slice(t_list *self, int *range, t_arena *arena);
void	print_list(t_list *self);
int		handle_error(t_list *self, int start, int end);
void	append_index(t_list **self, t_obj *data, t_arena *arena, size_t index);
t_list	*realloc_list(t_list *old, t_arena *arena, size_t size);

#endif
