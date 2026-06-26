#include "tuple.h"
#include "../list/list.h"
#include "../dict/dict.h"

t_obj *get_at_index(t_tuple *self, int index)
{
    if (self->size < 1)
		return (NULL);
    if (index < 0)
		index = (int)self->size + index;
	if (index >= (int)self->size || self->size == 0 || index < 0) 
        return (display_error("Out_of_Range index: ", &index, 10), NULL);
    return (self->members[index]);
}
