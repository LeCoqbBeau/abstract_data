MAKEFLAGS		=	--no-print-directory
.DEFAULT_GOAL	:=	all

NAME			=	abstract_data

INC				=	include

INCLUDES		=	-I$(INC)#$(foreach d, $(INC), -I$d)

CFLAGS			=	$(INCLUDES) -Wall -Werror -Wextra -g -std=c++98 -MMD -MP
CXX				=	c++

SRC_DIR			=	src/
SRC_NAME		=	main.cpp

DOXYGEN_SRCS	=	include/deque.hpp			\
					include/list.hpp			\
					include/queue.hpp			\
					include/stack.hpp			\
					include/vector.hpp			\
					include/bonus/matrix.hpp

DOXYFILE		=	Doxyfile
DOXYGEN_DOC		=	.doxygen_doc/
DOXYGEN_HTML	=	$(DOXYGEN_DOC)index.html
DOXYGEN_LATEX	=	.doxygen_latex/
DOXYGEN_DIR		=	$(DOXYGEN_DOC) $(DOXYGEN_LATEX)

OBJ_DIR			=	.build/
OBJ_NAME		=	$(SRC_NAME:.cpp=.o)
DEPS_NAME		=	$(SRC_NAME:.cpp=.d)
OBJ				=	$(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))
DEPS			=	$(patsubst %, $(OBJ_DIR)%, $(DEPS_NAME))

all: $(NAME) doc

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

dclean:
	@rm -rf $(DOXYGEN_DIR)
	@echo "\033[1;31m Deleted documentation"

fclean: clean dclean
	@rm -f $(NAME)
	@echo "\033[1;31m Deleted $(NAME)"

re: fclean all

run: $(NAME)
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all -q ./$(NAME)


$(DOXYGEN_HTML): $(DOXYFILE) $(DOXYGEN_SRCS)
	@echo "\033[0;35m Updated Doxygen documentation"
	@doxygen $(DOXYFILE)

doc: $(DOXYGEN_HTML)

bear:
	bear -- make

-include $(DEPS)
