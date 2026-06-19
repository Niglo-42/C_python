/*documentation*/
    j'ai ajouté les objects, donc toute variable est un object
    qui a:
        -un type (ENUM)
        -un refcount qui n'est plus utiliser mais qui pourra etre reajouter pour garbage collector plus tard

    j'ai ajouté les objets dynamique, les tuples, list, generators (sans stack) et dict.

    Voici les objets de base:

    typedef struct s_obj
    {
        int32_t refcnt;
        uint32_t type;
    }   t_obj;

    typedef struct s_string
    {
        t_obj   base;
        size_t  size;
        char    s[];
    }   t_string;

    typedef struct s_chr
    {
        t_obj   base;
        char    c;
    }   t_chr;


    typedef struct s_int
    {
        t_obj   base;
        int     val;
    }   t_int;

    typedef struct s_float
    {
        t_obj   base;
        float   val;
    }   t_float;

    LES containers:

    typedef struct s_tuple
    {
        t_obj   base;
        size_t  size;
        t_obj   *members[];
    }   t_tuple;

    typedef struct s_list
    {
        t_obj   base;
        size_t  size;
        size_t  cap;
        t_obj   *members[];
    }   t_list;

    typedef struct s_dict
    {
        t_obj   base;
        size_t  cap;
        t_abcd  vars;
        size_t  size;
        t_entry *tab_entry[];
    } t_dict;

    TOUS
    -Heritent d'objet
    -Ont une size et une cap (sauf tuple qui est fixe par nature)
    -Ont un flexible array de pointeurs a la fin (externe a la struct mais contigue).

    tuple peut:
        count(t_tuple *self, t_obj *elem, t_type type) count le nombre d'occurence d'une valeur dans l'object donné
        (peut etre recursiv si tuple a l'interieur)
        int    __index__(t_tuple *self, t_obj elem, t_type type) return l'index où se trouve la valeur.
    il s'utilise:
        t_tuple *tuple = tup(arena, nb_elem, new_str("je suis une string", arena));
        count(tuple, new_str("je suis une string", V_STRING));

    List peut:
        -   t_list *slice(t_list *self, int start, int end, int flag)
        // s'utilise comme en python list[1:-1, 0], pour reverse faire list[:-1, 1]
        // Le flag permet d'inclure ou non end ce qui permet de reverse la liste entière
        // return toujours une list avec une partie ou l'intégralité de la liste passé en paramètre.

        -   t_list *handle_error(t_list *self, int start, int end, int flag)
        // helper de slice il permet de vérifier tous les ranges et renvoie une list avec un obj VERROR
        // qui permet de catch plus haut

        -   void print_list(t_list *self)
        // output [eleme1, elem2] ou rien si liste avec une size à 0.

        -   t_obj pop(t_list *self, int index)
        // return l'object à l'index voulu et reconstruit la liste en fonction, pop(&list, -1) donne le dernier elem -2 l'avant dernier etc..

        -   void    append(t_list *self, t_obj data)
        // ajoute un object à la suite d'une liste

        -   void    realloc_list(t_list *self)
        // si le append sort de la cap alors on réalloue.

        -   void    destructeur_list(t_list *self)
        // free les members puis la list

        -   t_list *list_init(size_t n, t_obj *data)
        // malloc list et members avec la bonne taille et de manière automatique via cette macro
        # define LIST(...) \
            list_init( \
                sizeof((t_obj[]){__VA_ARGS__}) / sizeof(t_obj), \
                (t_obj[]){__VA_ARGS__} \
            )
        // c'est en variadique et cela calcul la taille de la liste et ajoute chaque elements.

    **Dict a:**
        t_list *buffer; // tableau de list qui devrait être un tableau de list de tuple (key: value)
        size_t len_buf; // cap
        size_t cur_use; // size
        t_list items;   // list qui mémorise l'ordre d'ajout pour ctrl + z (popitem)
        t_abcd *vars;   // pas le droit aux globales donc ajout à chaque création, des const et vars.
        t_const *cst;   // idem
    
    il peut:
        -   t_obj popitem(t_dict *self) // return le dernier elem ajouté et le détruit dans le buffer
        // IMPORTANT " self->buffer[obj.data.d].size--;
            return self->buffer[obj.data.d].members[self->buffer[obj.data.d].size];"
        // la list qui hold les elem dans l'ordre, hold l'index et on assume que le dernier element est forcement le dernier tout court
        // si on avait les tuple on aurait pu faire autrement mais ça aurait été moins opti que comme cela.

        -   void set(t_dict *self, t_obj val)
        // set une valeur (object) a un index et l'append à la list en cour
        // si pas encore de list ça va realloc et donc créer une list
        // le set aussi realloc si la list du buffer du dict est devenue trop petite.

        -   t_obj get(t_dict *self, char *key)
        // via une clé return l'object, si pas trouvé return un obj VNULL

main de test:

int main(void)
{
    t_arena *arena = new_arena();

    t_list *t = lst(arena, 2, int_new(0xff, arena), str_new("yolo", arena));
    print_list(t);

    pop(t, -1);
    print_list(t);

    append(t, float_new(42.1, arena), arena);
    print_list(t);
    
    t_dict *dict = new_dict(NULL, 10, arena);
    set(dict, arena, new_entry("jesaispo", int_new(42, arena), arena));
    print_dict(dict);
    
    t_entry *x = get(dict, "jeaispo");
    print_obj((t_obj *)x);

    t_tuple *tuple = tup(arena, 2, str_new("steven", arena), int_new(48676453, arena));
    print_tuple(tuple);
    printf("count = %d\n", count(tuple, str_new("steven", arena), V_STRING));
    printf("index = %d\n", __index__(tuple, str_new("steven", arena), V_STRING));
    t_dict *dict_cpy = copy_dict(dict, arena);
    print_dict(dict_cpy);
    free_all(arena);
}