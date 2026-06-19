/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:56:04 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 10:56:27 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_H
# define GEN_H
# include "../obj.h"
# include "../../runtime/arena.h"

t_obj	*for_each(t_obj *iter, t_arena *arena);

#endif
