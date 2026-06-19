NAME = libobj.a

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror

AR = ar rcs
RM = rm -f

# sources
OBJ_DIR = obj
RUN = runtime
GEN = gen
DICT_DIR = dict
TUPLE_DIR = tuple
LIST_DIR = list

SRCS = \
	$(OBJ_DIR)/obj.c \
	$(OBJ_DIR)/basic_funcs.c \
	$(RUN)/arena.c \
	$(OBJ_DIR)/$(GEN)/gen.c \
	$(OBJ_DIR)/$(DICT_DIR)/dict.c \
	$(OBJ_DIR)/$(DICT_DIR)/init_dict.c \
	$(OBJ_DIR)/$(DICT_DIR)/hash.c \
	$(OBJ_DIR)/$(DICT_DIR)/hash_methods.c \
	$(OBJ_DIR)/$(TUPLE_DIR)/tuple.c \
	$(OBJ_DIR)/$(TUPLE_DIR)/tuple_count.c \
	$(OBJ_DIR)/$(TUPLE_DIR)/tuple_index.c \
	$(OBJ_DIR)/$(LIST_DIR)/list.c \
	$(OBJ_DIR)/$(LIST_DIR)/list_methods.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I.

# rules
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
# 	$(RM) $(TEST)

re: fclean all

TEST = test

$(TEST): main.c $(NAME)
	$(CC) main.c -L. -lobj -o $(TEST)
	./$(TEST)

.PHONY: all clean fclean re