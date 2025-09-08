MAKEFLAGS		=	--no-print-directory
.DEFAULT_GOAL	:=	all
THREAD_NUM		=	4

NAME			=	abstract_data

INC				=	include

INCLUDES		=	$(foreach d, $(INC), -I$d)

CFLAGS			=	$(INCLUDES) -Wall -Werror -Wextra -g -std=c++98 -MMD -MP
CXX				=	c++

SRC_DIR			=	src/
SRC_NAME		=	main.cpp

OBJ_DIR			=	.build/
OBJ_NAME		=	$(SRC_NAME:.cpp=.o)
DEPS_NAME		=	$(SRC_NAME:.cpp=.d)
OBJ				=	$(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))
DEPS			=	$(patsubst %, $(OBJ_DIR)%, $(DEPS_NAME))

all: $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[1;32m Executable" $(NAME) "created"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;31m Deleted all object files"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31m Deleted $(NAME)"

re: fclean all

-include $(DEPS)
