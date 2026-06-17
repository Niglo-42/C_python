/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:06:16 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/17 18:50:22 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj/dict/dict.h"
#include "obj/tuple/tuple.h"
#include "obj/list/list.h"
#include "obj/gen/gen.h"

// int main()
// {
//     t_string  *str;
// 	t_arena	*arena;
//     t_obj   *x;

// 	arena = new_arena();
//     str = (t_string *)str_new("je suis une string", arena);
//     while(1)
//     {
//         x = for_each((t_obj *)str, arena);
//         if (x)
//         {
//             print_obj(x);
//             write(1, "\n", 1);
//         }
//         else
//             break ;
//     }

//     t_list *list;
//     t_list *list2;

//     list = lst(arena, 3, int_new(42, arena), int_new(12, arena), str_new("elliot", arena));
//     list2 = slice(list, (int[4]){0, -1, 2, 1}, arena);

//     print_list(list2);
//     free_all(arena);
// }

#define NB_LISTS 1000

int main(void)
{
    t_arena *arena = new_arena();

    for (int i = 0; i < 5000; ++i)
    {
        lst(arena, 1, int_new(i, arena));
    }

    free_all(arena);
}