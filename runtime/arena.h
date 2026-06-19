/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:21:42 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 10:31:44 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include "../obj/obj.h"

typedef struct s_block
{
	struct s_block	*next;
	size_t			rsp;
	size_t			cap;
	uint8_t			data[];
}	t_block;

typedef struct s_arena
{
	t_obj	base;
	t_block	*block;
}	t_arena;

void	*get_memory(size_t size, t_arena *arena);

#endif
