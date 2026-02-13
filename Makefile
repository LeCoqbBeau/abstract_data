MAKEFLAGS		=	--no-print-directory
.DEFAULT_GOAL	:=	all

NAME			=	abstract_data

INC				=	include

INCLUDES		=	-I$(INC) #$(foreach d, $(INC), -I$d)

CFLAGS			=	$(INCLUDES) -Wall -Werror -Wextra -g -std=c++98 -MMD -MP
CXX				=	c++

SRC_DIR			=	tests/
SRC_NAME		=	main.cpp

DOXYGEN_SRCS	=	include/deque.hpp			\
					include/list.hpp			\
					include/queue.hpp			\
					include/stack.hpp			\
					include/vector.hpp			\
					include/set.hpp				\
					include/unordered_set.hpp	\
					include/unordered_map.hpp	\
					include/map.hpp				\
					include/grid.hpp

DOXYFILE		=	Doxyfile
DOXYGEN_DIR		=	.doxygen/
DOXYGEN_DOC		=	$(DOXYGEN_DIR)doc/
DOXYGEN_HTML	=	$(DOXYGEN_DOC)index.html
DOXYGEN_LATEX	=	$(DOXYGEN_DIR)latex/
DOXYGEN_SUBDIR	=	$(DOXYGEN_DOC) $(DOXYGEN_LATEX)

GTEST_LINK		=	https://github.com/google/googletest/archive/refs/tags/release-1.8.1.tar.gz
GTEST_TAR		=	release-1.8.1.tar.gz
GTEST_OLDDIR	=	googletest-release-1.8.1
GTEST_DIR		=	gtest/
GTEST_GTEST		=	$(GTEST_DIR)googletest/
GTEST_BUILD		=	$(GTEST_GTEST)build/
GTEST_ALL_A		=	$(GTEST_BUILD)libgtest.a
GTEST_MAIN_A	=	$(GTEST_BUILD)libgtest_main.a
GTEST_INCLUDE	=	$(GTEST_GTEST)include


CFLAGS			+= -I$(GTEST_INCLUDE)

OBJ_DIR			=	.build/
OBJ_NAME		=	$(SRC_NAME:.cpp=.o)
DEPS_NAME		=	$(SRC_NAME:.cpp=.d)
OBJ				=	$(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))
DEPS			=	$(patsubst %, $(OBJ_DIR)%, $(DEPS_NAME))

CLR				=	"\033[1;0m"

all: $(NAME) doc

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) $(CLR)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) $(GTEST_ALL_A) $(GTEST_MAIN_A)
	@echo "\033[1;32m Executable" $(NAME) "created" $(CLR)

clean: dclean gclean
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;31m Deleted all object files" $(CLR)

dclean:
	@rm -rf $(DOXYGEN_SUBDIR)
	@echo "\033[1;31m Deleted documentation" $(CLR)

gclean:
	@rm -rf $(GTEST_TAR)
	@echo "\033[1;31m Deleted gtest tar" $(CLR)

fclean: clean dclean gclean
	@rm -f $(NAME)
	@echo "\033[1;31m Deleted $(NAME)" $(CLR)

re: fclean all

run: $(NAME)
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all -q ./$(NAME)

$(DOXYGEN_HTML): $(DOXYFILE) $(DOXYGEN_SRCS)
	@echo "\033[0;35m Updated Doxygen documentation" $(CLR)
	@doxygen $(DOXYFILE)

doc: $(DOXYGEN_HTML)

$(GTEST_TAR):
	@wget $(GTEST_LINK)

$(GTEST_DIR): $(GTEST_TAR)
	@tar -xf $(GTEST_TAR)
	@mv $(GTEST_OLDDIR) $(GTEST_DIR)

$(GTEST_ALL_A) $(GTEST_MAIN_A): $(GTEST_DIR)
	@mkdir -p $(GTEST_BUILD)
	@cd $(GTEST_BUILD)
	@cmake -S $(GTEST_GTEST) -B $(GTEST_BUILD)
	@sed -i '1222s/int dummy;/int dummy = 0;/; 1223s/bool result;/bool result = false;/' $(GTEST_GTEST)src/gtest-death-test.cc
	@make -j -C $(GTEST_BUILD)

gtest: $(GTEST_ALL_A)

bear:
	bear -- make

-include $(DEPS)
