// #include "obj/dict/dict.h"
// #include "obj/tuple/tuple.h"
// #include "obj/list/list.h"
// #include "obj/gen/gen.h"
// #include "runtime/arena.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>
// #include <signal.h>
// #include <execinfo.h>

// static void handler(int sig)
// {
//     void *array[20];
//     size_t size;

//     fprintf(stderr, "\n🔥 SEGFAULT DETECTED (signal %d)\n", sig);

//     size = backtrace(array, 20);
//     backtrace_symbols_fd(array, size, 2);

//     exit(1);
// }

// #define LOOP 500
// #define SMALL_LOOP 200
// #define XXSMALL_LOOP 50
// #define RUN(name, fn, arena)
//     do {
//         printf("\n--- RUN: %s ---\n", name);
//         fn(arena);
//         printf("--- OK: %s ---\n", name);
//     } while (0)

// // helpers pseudo-random stables
// static int rng(int *seed)
// {
//     *seed = (*seed * 1103515245 + 12345) & 0x7fffffff;
//     return *seed;
// }

// static void stress_list(t_arena *arena)
// {
//     int seed = 42;
//     t_list *l = lst(arena, 0);

//     for (int i = 0; i < LOOP; i++)
//     {
//         int r = rng(&seed);

//         if (r % 3 == 0)
//             append(&l, int_new(r, arena), arena);
//         else if (r % 3 == 1)
//         {
//             char c[9];
//             memmove(c, &r, 8);
//             append(&l, str_new(c, arena), arena);
//         }
//         else
//             append(&l, float_new((float)r * 0.1f, arena), arena);
//         if (i % 50 == 0)
//             pop(l, -1);
//     }
//     for (int i = 0; i < LOOP / 2; i++)
//         pop(l, -1);
//     t_list *tamereenslip = slice(l, (int[]){-1, 0, -1, 1}, arena);
//     write(1, "=== list poped ===\n\n", 21);
//     print_list(l);
//     write(1, "=== list sliced inverted ===\n\n", 31);
//     print_list(tamereenslip);
// }

// static void stress_dict(t_arena *arena)
// {
//     int seed = 1337;
//     t_dict *d = new_dict(NULL, 128, arena);

//     for (int i = 0; i < LOOP; i++)
//     {
//         int r = rng(&seed);

//         char key[32];
//         sprintf(key, "k%d", r % 200);

//         if (r % 4 == 0)
//             set(d, new_entry(key, int_new(r, arena), arena));
//         else if (r % 4 == 1)
//             set(d, new_entry(key, str_new("val", arena), arena));
//         else if (r % 4 == 2)
//             set(d, new_entry(key, float_new(r * 0.5f, arena), arena));
//         else
//             set(d, new_entry(key, NULL, arena)); // edge NULL value

//         if (i % 100 == 0)
//         {
//             t_entry *e = get(d, key);
//             if (e)
//                 print_obj((t_obj *)e);
//         }
//     }

//     print_dict(d);
// }

// static void stress_tuple(t_arena *arena)
// {
//     for (int i = 0; i < SMALL_LOOP; i++)
//     {
//         t_tuple *t = tup(
//             arena,
//             3,
//             int_new(i, arena),
//             str_new("tuple", arena),
//             float_new(i * 3.14f, arena)
//         );

//         assert(count(t, int_new(i, arena), V_INT) >= 1);
//         __index__(t, str_new("tuple", arena), V_STRING);
//         print_tuple(t);
//     }
// }

// static void stress_copy(t_arena *arena)
// {
//     t_dict *d = new_dict(NULL, 32, arena);

//     for (int i = 0; i < 1000; i++)
//         set(d, new_entry("a", int_new(i, arena), arena));

//     t_dict *cpy = copy_dict(d, arena);

//     set(d, new_entry("a", int_new(99999, arena), arena));

//     print_dict(d);
//     print_dict(cpy);
// }

// static void null_attack()
// {
//     printf("NULL ATTACK TEST\n");

//     t_list *l = NULL;
//     t_dict *d = NULL;
//     t_tuple *t = NULL;

//     // ces appels doivent PAS segfault (ou être protégés)
//     if (l) print_list(l);
//     if (d) print_dict(d);
//     if (t) print_tuple(t);
// }

// int main(void)
// {
//     printf("=== ARENA STRESS TEST START ===\n");
//     signal(SIGSEGV, handler);
//     signal(SIGABRT, handler);
//     t_arena *arena = new_arena();
//     RUN("list", stress_list, arena);
//     RUN("tuple", stress_tuple, arena);
//     RUN("dict", stress_dict, arena);
//     RUN("copy", stress_copy, arena);
//     free_all(arena);
//     null_attack();
//     printf("=== DONE ===\n");
//     return 0;
// }
