PS_NAME = push_swap
CKR_NAME = checker
SRC_PATH = ./srcs/
LFT_PATH = ./libft/
PFT_PATH = ./ft_printf/
LIB_PATH = ./lib/
INC_PATH = ./includes/
FLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -Wall -Werror -Wextra -g

RED  = "\033[0;31m"
GREEN  = "\033[0;32m"
BLUE = "\033[0;34m"
CYAN = "\033[0;36m"
CLEAR = "\033[0m"

INC = $(addprefix -I, $(INC_PATH))

LIBS = -lft

LFT = libft.a
PFT = libft.a

CKR_SRC_NAME =	checker.c\
				checker_util.c\
				checker_struct.c\
				instructions.c\
				swap_instructions.c\
				push_instructions.c\
				rotate_instructions.c\
				r_rotate_instructions.c
				
CKR_SRC = $(addprefix $(SRC_PATH), $(CKR_SRC_NAME))
CKR_OBJ = $(CKR_SRC_NAME:.c=.o)

PS_SRC_NAME = push_swap.c
PS_SRC = $(addprefix $(SRC_PATH), $(PS_SRC_NAME))
PS_OBJ = $(PS_SRC_NAME:.c=.o)

.PHONY = all clean fclean re

all: $(LFT) $(CKR_NAME) $(PS_NAME)

$(LFT):
	@make -C $(LFT_PATH)

$(CKR_NAME):
	@gcc $(FLAGS) $(INC) -o $(CKR_NAME) $(CKR_SRC) -L $(LIB_PATH) $(LIBS)
	@echo $(GREEN)"Checkers executable compiled" $(CLEAR)

$(PS_NAME):
	@gcc $(FLAGS) $(INC) -o $(PS_NAME) $(PS_SRC) -L $(LIB_PATH) $(LIBS)
	@echo $(GREEN)"Push_Swap executable compiled" $(CLEAR)

clean:
	@make -C $(LFT_PATH) clean
	@/bin/rm -f $(CKR_OBJ) $(PS_OBJ)
	@echo $(RED)"Removed all object files" $(CLEAR)

fclean: clean
	@make -C $(LFT_PATH) fclean
	@/bin/rm -f $(CKR_NAME) $(PS_NAME)
	@/bin/rm -rf a.out a.out.dSYM
	@echo $(RED)"Deleted executable files" $(CLEAR)

re: fclean all

test: fclean $(LFT) test_ckr test_ps

test_ckr:
	@gcc $(TEST_FLAGS) $(INC) -o $(CKR_NAME) $(CKR_SRC) -L $(LIB_PATH) $(LIBS)
	@echo $(GREEN)"Checkers test compiled" $(CLEAR)

test_ps:
	@gcc $(TEST_FLAGS) $(INC) -o $(PS_NAME) $(PS_SRC) -L $(LIB_PATH) $(LIBS)
	@echo $(GREEN)"Push Swap test compiled" $(CLEAR)