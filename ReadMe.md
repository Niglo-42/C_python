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

        -   void print_dict(t_dict *self)
        print les index du buffer du dict même si vide et les list si trouvant
        exemple:
            0: 
            1: 
            2: [bchdfjgcfdhi]
            3: [str_chose, str_beta]
            4: 
            5: 
            6: [str_gamma]
            7: [str_alpha]
            8: 
            9: 
            10: 
            11: 

        -   void    copy_dict(t_dict *new_dict, t_dict self)
        // init un nouveau dict avec les attributs d'un autre et copy proprement toutes les listes (nouvelles adresses)

        -   void __destructeur__dict(t_dict *self)
        // free: (toutes les list du buffer | tous les obj du tableau d'objets "items" | 
        le buffer | les vars et const)

        -   void __init__dict(t_dict *self, t_dict *src, size_t len)
        // peut soit init avec un dict à copier NULL ou non.
        // calloc du buffer pour que tout soit à 0
        // items n'est pas malloc
        // et on init func et vars, const

        LES VARS ET CONST peuvent rester des boites noires, elles viennent d'une formule mathématique qui hache bien.

        
        la politique d'organisation est qu'on évite les malloc, on joue un max avec les tableaux,
        on rend tout dynamique et on imbrique les éléments pour créer de la compléxité, donc 
        abtraction et ensuite complexification. Moins de mots et plus de sens.

        PROBLEME:
            tout les buffers des objects sont des tableaux vers soit des lists soit des objects.
            donc ils ne peuvent accueillir que ces derniers. il faut qu'il soit des pointeurs (void *)
            pour accueillir n'importe quoi ce qui permet l'imbrication.

            car là un dict ne peut actuellement store que [obj, obj..etc]
            et rien d'autre.. alors qu'il devrait pouvoir store [(key_obj, val_obj), (key_obj, val_obj), etc..]
            Mais la liste l'interdit car on a malloc un tableau de n * sizeof(obj) // n * 24oct
            si c'était un tableau de pointeurs (n * 8 oct) void *.
            
            Une solution serait de passer de "typedef struct s_obj {
                                                t_type type;
                                                char *key;
                                                union {
                                                    int d;
                                                    double f;
                                                    void *p;
                                                    char c;
                                                    char *s;
                                                } data;
                                            } t_obj;"
            à :
                typedef struct s_obj {
                    t_type type;
                    void *data;
                } t_obj;

                ET l'object pourrait être un tuple, une list, un dict ou même une licorne s'il le souhaite.

                donc dict pourrait toujours être une list d'object mais chaque object serait de type tuple 
                et pointerait vers un tuple qui lui a une taille et un tableau d'object de type par exmple: (char *key et value_obj)
                on peut donc naviguer de pointeur en pointeur (i += 8 en interne), mais on s'attend à aller vers des
                tuples qui eux même pointent vers paire (k, v).


        compliationa vec le flag "-finstrument-functions"

        chaque frame = owner de ressources
        tout ce qui est créé dans une frame est “attaché” à elle
            à la sortie :
            soit libéré
            soit “retourné” vers la frame parent

        list sur main global_frame
        frame A
        ├── obj1
        ├── obj2
        └── frame B
                ├── obj3

        TOUT les objects doivent etre append a la list
        frame !

        ensuite 2 choix, soit on return en faisant un 
        append a la list parent, soit on decref //free

        en fait on decref la frame actuelle et si des
        obj ne sont pas append ailleurs alors leurs 
        refcnt sera a 0 au lieu de 1 et donc free.

        probleme faut sans globale ajouter la ref
        vers la frame parent a la frame actuelle.


        les frame peuvent etre considerer comme des arena.


        Arena
│
├─ t_list
│
├─ tableau de pointeurs
│   +------+------+------+
│   |  *   |  *   |  *   |
│   +------+------+------+
│
├─ t_int
│
├─ t_dict
│
└─ t_tuple

et au resize

Arena

ancien tableau
+----+----+----+----+
| a  | b  | c  | d  |
+----+----+----+----+

nouveau tableau
+----+----+----+----+----+----+----+----+
| a  | b  | c  | d  |    |    |    |    |
+----+----+----+----+----+----+----+----+
                ^
                |
           self->items
        