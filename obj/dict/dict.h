/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:01:53 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/24 17:06:09 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include "../obj.h"
# include "../../runtime/arena.h"
# include "../list/list.h"
# include "../tuple/tuple.h"

# define EMPTY 1
# define FILLED 2
# define DELETED 4

typedef struct s_abcd
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}	t_abcd;

typedef struct s_entry
{
	t_obj		base;
	const char	*key;
	t_obj		*value;
	uint8_t		state;
}	t_entry;

typedef struct s_dict
{
	t_obj	base;
	size_t	cap;
	size_t	size;
	t_entry	*tab_entry[];
}	t_dict;

t_dict		*new_dict(t_dict *src, size_t len, t_arena *arena);
t_entry		*get(t_dict *self, const char *key);
void		set(t_dict *self, t_entry *entry);
void		print_dict(t_dict *self);

///// hash functions
uint32_t	rol(uint32_t x, uint32_t s);
uint32_t	f(t_abcd var, uint32_t *key, int i);
size_t		hash(size_t cap, const char *s);

//////////dict

t_dict		*copy_dict(t_dict *self, t_arena *arena);
t_dict		*new_dict(t_dict *src, size_t len, t_arena *arena);
t_entry		*new_entry(const char *key, t_obj *val, t_arena *arena);
void		print_entry(t_entry *self);

#endif
