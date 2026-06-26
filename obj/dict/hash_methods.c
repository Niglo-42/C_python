#include "dict.h"

uint32_t	rol(uint32_t x, uint32_t s)
{
	s &= 31;
	return ((x << s) | (x >> (32 - s)));
}

uint32_t	f(t_abcd var, uint32_t *key, int i)
{
	if (i < 16)
		return (((var.b & var.c) | (~var.b & var.d)) + key[i]);
	if (i >= 16 && i <= 31)
		return (((var.b & var.d) | (var.c & ~var.d)) + key[(5 * i) & 15]);
	if (i >= 32 && i <= 47)
		return ((var.b ^ var.c ^ var.d) + key[(3 * i) & 15]);
	if (i >= 48)
		return ((var.c ^ (var.b | ~var.d)) + key[(7 * i) & 15]);
	return (0);
}
