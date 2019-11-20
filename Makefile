PS_NAME = push_swap
CKR_NAME = checker
LFT = libft
SRC_PATH = ./srcs/
LFT_PATH = ./libft/
INC_PATH = ./includes/
FLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -Wall -Werror -Wextra -g

RED  = "\033[0;31m"
GREEN  = "\033[0;32m"
BLUE = "\033[0;34m"
CYAN = "\033[0;36m"
CLEAR = "\033[0m"

INC = $(addprefix -I, $(INC_PATH))

CKR_SRC_NAME = checker.c
CKR_SRC = $(addprefix $(SRC_PATH), $(CKR_SRC_NAME))
CKR_OBJ = $(CKR_SRC_NAME:.c=.o)

PS_SRC_NAME = push_swap.c
PS_SRC = $(addprefix $(SRC_PATH), $(PS_SRC_NAME))
PS_OBJ = $(PS_SRC_NAME:.c=.o)

LFT_SRC_NAME =	ft_atoi.c\
				ft_err_exit.c\
        		ft_isascii.c\
				ft_memchr.c\
				ft_memset.c\
				ft_strcpy.c\
				ft_strncat.c\
				ft_strrchr.c\
				ft_bzero.c\
				ft_isdigit.c\
				ft_memcmp.c\
				ft_strcat.c\
				ft_strdup.c\
				ft_strncmp.c\
				ft_strstr.c\
				ft_isalnum.c\
				ft_isprint.c\
				ft_memcpy.c\
				ft_strchr.c\
				ft_strlcat.c\
				ft_strncpy.c\
				ft_tolower.c\
				ft_isalpha.c\
				ft_memccpy.c\
				ft_memmove.c\
				ft_strcmp.c\
				ft_strlen.c\
				ft_strnstr.c\
				ft_toupper.c\
				ft_memalloc.c\
				ft_memdel.c\
				ft_strnew.c\
				ft_strdel.c\
				ft_strclr.c\
				ft_striter.c\
				ft_striteri.c\
				ft_strmap.c\
				ft_strmapi.c\
				ft_strequ.c\
				ft_strnequ.c\
				ft_strsub.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_strsplit.c\
				ft_itoa.c\
				ft_putchar.c\
				ft_putstr.c\
				ft_putendl.c\
				ft_putnbr.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_lstadd.c\
				ft_lstdel.c\
				ft_lstdelone.c\
				ft_lstiter.c\
				ft_lstmap.c\
				ft_lstnew.c\
				ft_lstadd_bk.c\
				ft_lstinsert.c\
				ft_lstdelat.c\
				ft_lstlen.c\
				ft_lstat.c\
				ft_ulltoa_base.c\
				ft_lltoa_base.c\
				ft_strup.c\
				ft_stradd.c\
				ft_strtrimc.c\
				get_next_line.c\
				stack.c\
				queue.c
LFT_OBJ_NAME = $(LFT_SRC_NAME:.c=.o)
LFT_SRC = $(addprefix $(LFT_PATH), $(LFT_SRC_NAME))
LFT_OBJ = $(addprefix $(LFT_PATH), $(LFT_OBJ_NAME))

.PHONY = all clean fclean re

all: $(CKR_NAME) $(PS_NAME)

$(CKR_NAME):
	@gcc $(FLAGS) $(INC) -o $(CKR_NAME) $(CKR_SRC) $(LFT_SRC)
	@echo $(GREEN)"Checkers executable compiled" $(CLEAR)

$(PS_NAME):
	@gcc $(FLAGS) $(INC) -o $(PS_NAME) $(PS_SRC) $(LFT_SRC)
	@echo $(GREEN)"Push_Swap executable compiled" $(CLEAR)

clean:
	@/bin/rm -f $(LFT_OBJ) $(CKR_OBJ) $(PS_OBJ)
	@echo $(RED)"Cleaned all object files" $(CLEAR)

fclean: clean
	@/bin/rm -f $(CKR_NAME) $(PS_NAME)
	@echo $(RED)"Deleted executable files" $(CLEAR)

re: fclean all
