PS_NAME = push_swap
CKR_NAME = checker
SRC_PATH = ./srcs/
LFT_PATH = ./libft/
PFT_PATH = ./ft_printf/
LIB_PATH = ./libft/
MLX_PATH = ./minilibx_macos/
INC_PATH = ./includes/

LFT = libft.a
PFT = libftprintf.a
MLX = libmlx.a

PROJ_INC = -I $(INC_PATH)
LFT_INC = -I $(LFT_PATH)
PFT_INC = -I $(PFT_PATH)
MLX_INC = -I $(MLX_PATH)

LFT_LINK = -L $(LFT_PATH) -l ft
PFT_LINK = -L $(PFT_PATH) -l ftprintf
MLX_LINK = -L $(MLX_PATH) -l mlx -framework OpenGL -framework AppKit

FLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -g

RED  = "\033[0;31m"
GREEN  = "\033[0;32m"
BLUE = "\033[0;34m"
CYAN = "\033[0;36m"
CLEAR = "\033[0m"

CKR_SRC_NAME =	checker.c\
				checker_util.c\
				general_util.c\
				instructions.c\
				swap_instructions.c\
				push_instructions.c\
				rotate_instructions.c\
				r_rotate_instructions.c
				
CKR_SRC = $(addprefix $(SRC_PATH), $(CKR_SRC_NAME))
CKR_OBJ = $(CKR_SRC_NAME:.c=.o)

PS_SRC_NAME =	push_swap.c\
				ps_util.c\
				ordering.c\
				final_step.c\
				selection_sort.c\
				sort_small.c\
				radix_sort.c\
				general_util.c\
				instructions.c\
				swap_instructions.c\
				push_instructions.c\
				rotate_instructions.c\
				r_rotate_instructions.c

PS_SRC = $(addprefix $(SRC_PATH), $(PS_SRC_NAME))
PS_OBJ = $(PS_SRC_NAME:.c=.o)

.PHONY = all clean fclean re

all: $(LFT) $(CKR_NAME) $(PS_NAME)

$(LFT):
	@make -C $(LFT_PATH)
	@make -C $(PFT_PATH)
	@make -C $(MLX_PATH)

$(CKR_NAME): $(CKR_SRC)
	@gcc $(FLAGS) $(INC) -o $(CKR_NAME) $(PROJ_INC) $(LFT_INC) $(PFT_INC) $(MLX_INC) $(CKR_SRC) $(LFT_LINK) $(PFT_LINK) $(MLX_LINK)
	@echo $(GREEN)"Checker executable compiled" $(CLEAR)

$(PS_NAME): $(PS_SRC)
	@gcc $(FLAGS) $(INC) -o $(PS_NAME) $(PROJ_INC) $(LFT_INC) $(PFT_INC) $(MLX_INC) $(PS_SRC) $(LFT_LINK) $(PFT_LINK) $(MLX_LINK)
	@echo $(GREEN)"Checker executable compiled" $(CLEAR)
	@echo $(GREEN)"Push_Swap executable compiled" $(CLEAR)

clean:
	@make -C $(LFT_PATH) clean
	@make -C $(PFT_PATH) clean
	@make -C $(MLX_PATH) clean
	@/bin/rm -f $(CKR_OBJ) $(PS_OBJ)
	@echo $(RED)"Removed all object files" $(CLEAR)

fclean: clean
	@make -C $(LFT_PATH) fclean
	@make -C $(PFT_PATH) fclean
	@/bin/rm -f $(CKR_NAME) $(PS_NAME)
	@/bin/rm -rf a.out a.out.dSYM $(CKR_NAME).dSYM $(PS_NAME).dSYM
	@echo $(RED)"Deleted executable files" $(CLEAR)

re: fclean all

test: fclean $(LFT) test_ckr test_ps

test_ckr:
	@gcc $(TEST_FLAGS) $(INC) -o $(CKR_NAME) $(CKR_SRC) -L $(LIB_PATH) $(LIBS)
	@echo $(GREEN)"Checkers test compiled" $(CLEAR)

test_ps:
	@gcc $(TEST_FLAGS) $(INC) -o $(PS_NAME) $(PS_SRC) -L $(LIB_PATH) $(LIBS)
	@echo $(GREEN)"Push Swap test compiled" $(CLEAR)