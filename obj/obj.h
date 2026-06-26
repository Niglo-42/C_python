/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:14:07 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/24 22:03:06 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <assert.h>
# include <stddef.h>
# include <stdarg.h>

typedef enum s_type
{
	V_INT,
	V_CHR,
	V_FLOAT,
	V_STRING,
	V_LIST,
	V_TUP,
	V_DICT,
	V_ARENA,
	V_ENTRY,
	V_NODE,
	V_NULL
}	t_type;

typedef struct s_list	t_list;
typedef struct s_tuple	t_tuple;
typedef struct s_dict	t_dict;
typedef struct s_arena	t_arena;

typedef struct s_obj
{
	int32_t		refcnt;
	uint32_t	type;
}	t_obj;

typedef struct s_string
{
	t_obj	base;
	size_t	size;
	char	s[];
}	t_string;

typedef struct s_nul
{
	t_obj	base;
}	t_nul;

typedef struct s_chr
{
	t_obj	base;
	char	c;
}	t_chr;

typedef struct s_int
{
	t_obj	base;
	int		val;
}	t_int;

typedef struct s_node
{
	t_int	integer;
	uint8_t	red;
	t_obj	*right;
	t_obj	*left;
}	t_node;

typedef struct s_float
{
	t_obj	base;
	float	val;
}	t_float;

typedef struct s_error
{
	char	e[100];
}	t_error;

void	display_error(char *s, int *val, size_t base);
void	print_obj(t_obj *obj);

int		minmax(int a, int b);
char	*ft_itoa(char *buf, long n, size_t base);

t_obj	*int_new(int val, t_arena *arena);
t_obj	*float_new(float val, t_arena *arena);
t_obj	*str_new(char *s, t_arena *arena);

void	free_all(t_arena *arena);
t_arena	*new_arena(void);

// creation d'objets
t_obj	*chr_new(char c, t_arena *arena);
t_obj	*int_new(int val, t_arena *arena);
t_obj	*str_new(char *s, t_arena *arena);
t_obj	*float_new(float val, t_arena *arena);
t_obj	*new_node(int val, t_arena *arena);
t_obj	*new_null(t_arena *arena);
size_t	ft_max(size_t a, size_t b);

void	wrap_default(size_t n, t_obj *_val_default, t_list *self);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		*ft_atoi(int *res, char *s);
int		ft_atoi_base(int *flag, char *s, char *base, t_arena *arena);
#endif
