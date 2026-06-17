// #include "list/list.h"


// __attribute__((no_instrument_function))
// int gns_scope_lock(int val)
// {
//     static int lock = UNLOCK;

//     if (val)
//         lock = val;
//     return lock;
// }

// __attribute__((no_instrument_function))
// t_list *get_p_frame(t_list *set)
// {
//     static t_list   *g_frame;
//     t_list *prec;

//     prec = g_frame;
//     if (set)
//         g_frame = set;
//     return (prec);
// }

// __attribute__((no_instrument_function))
// void    __cyg_profile_func_enter(void *fn, void *ret_adress)
// {
//     (void)ret_adress;
//     t_list *frame;

//     if (gns_scope_lock(0) == LOCK)
//         return ;
//     gns_scope_lock(LOCK);
//     frame = lst(0);
//     append(frame, (t_obj *)get_p_frame(frame));
//     obj_incref((t_obj *)frame);
//     gns_scope_lock(UNLOCK);
// }

// __attribute__((no_instrument_function))
// void    __cyg_profile_func_exit(void *this_fn, void *ret_adress)
// {
//     if (gns_scope_lock(0) == LOCK)
//         return ;
//     gns_scope_lock(LOCK);
//     obj_decref((t_obj *)get_p_frame((t_list *)get_p_frame(NULL)->members[0]));
//     gns_scope_lock(UNLOCK);
// }