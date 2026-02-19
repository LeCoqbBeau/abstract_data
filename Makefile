
#-----------------------------------------------------------------------------------------------------------#
#	Makefile Config																							#
#-----------------------------------------------------------------------------------------------------------#

MAKEFLAGS		=	--no-print-directory
.DEFAULT_GOAL	:=	all


#-----------------------------------------------------------------------------------------------------------#
#	String Helpers																							#
#-----------------------------------------------------------------------------------------------------------#

CLR				=	"\033[1;0m"


#-----------------------------------------------------------------------------------------------------------#
#	Doxygen																									#
#-----------------------------------------------------------------------------------------------------------#

DOXYGEN_SRCS	=	$(INC)deque.hpp			\
					$(INC)list.hpp			\
					$(INC)queue.hpp			\
					$(INC)stack.hpp			\
					$(INC)vector.hpp		\
					$(INC)set.hpp			\
					$(INC)unordered_set.hpp	\
					$(INC)unordered_map.hpp	\
					$(INC)map.hpp			\
					$(INC)grid.hpp

DOXYFILE		=	Doxyfile
DOXYGEN_DIR		=	.doxygen/
DOXYGEN_DOC		=	$(DOXYGEN_DIR)doc/
DOXYGEN_HTML	=	$(DOXYGEN_DOC)index.html
DOXYGEN_LATEX	=	$(DOXYGEN_DIR)latex/
DOXYGEN_SUBDIR	=	$(DOXYGEN_DOC) $(DOXYGEN_LATEX)


#-----------------------------------------------------------------------------------------------------------#
#	Googletest																								#
#-----------------------------------------------------------------------------------------------------------#

GTEST_LINK		=	https://github.com/google/googletest/archive/refs/tags/release-1.8.1.tar.gz
GTEST_TAR		=	release-1.8.1.tar.gz
GTEST_OLDDIR	=	googletest-release-1.8.1
GTEST_DIR		=	gtest/
GTEST_GTEST		=	$(GTEST_DIR)googletest/
GTEST_BUILD		=	$(GTEST_GTEST)build/
GTEST_ALL_A		=	$(GTEST_BUILD)libgtest.a
GTEST_MAIN_A	=	$(GTEST_BUILD)libgtest_main.a
GTEST_INCLUDE	=	$(GTEST_GTEST)include/
GTEST_FILTER	=	*Erase*
GTEST_FLAGS		=	--gtest_color=yes --gtest_filter=$(GTEST_FILTER)


#-----------------------------------------------------------------------------------------------------------#
#	Compilation																								#
#-----------------------------------------------------------------------------------------------------------#

NAME			=	abstract_data
NAME_FT			=	ft_$(NAME)
NAME_STD		=	std_$(NAME)

INC				=	include/
SRC_DIR			=	src/
SRC_NAME		=	main.cpp

INCLUDES		=	-I$(INC) -I$(GTEST_INCLUDE)
CFLAGS			=	$(INCLUDES) -Wall -Werror -Wextra -g -std=c++98 -MMD -MP
CXX				=	c++

OBJ_DIR			=	.build/
OBJ_FT_DIR		=	$(OBJ_DIR)ft/
OBJ_STD_DIR		=	$(OBJ_DIR)std/
OBJ_FT			=	$(addprefix $(OBJ_FT_DIR), $(SRC_NAME:.cpp=.o))
OBJ_STD			=	$(addprefix $(OBJ_STD_DIR), $(SRC_NAME:.cpp=.o))

DEPS_FT_SRC		=	$(SRC_NAME:.cpp=.d)
DEPS_STD_SRC	=	$(SRC_NAME:.cpp=.d)
DEPS_FT			=	$(patsubst %, $(OBJ_FT_DIR)%, $(DEPS_FT_SRC))
DEPS_STD		=	$(patsubst %, $(OBJ_STD_DIR)%, $(DEPS_STD_SRC))


#-----------------------------------------------------------------------------------------------------------#
#	Targets																									#
#-----------------------------------------------------------------------------------------------------------#

all: $(NAME) doc

$(OBJ_FT_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -DTESTED_NAMESPACE=ft -DUSE_FT $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) $(CLR)

$(OBJ_STD_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -DTESTED_NAMESPACE=std $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) $(CLR)

$(NAME): $(NAME_FT) $(NAME_STD)

$(NAME_FT): $(OBJ_FT)
	@$(CXX) $(CFLAGS) -o $(NAME_FT) $(OBJ_FT) $(GTEST_ALL_A)
	@echo "\033[1;32m Executable" $(NAME_FT) "created" $(CLR)

$(NAME_STD): $(OBJ_STD)
	@$(CXX) $(CFLAGS) -o $(NAME_STD) $(OBJ_STD) $(GTEST_ALL_A)
	@echo "\033[1;32m Executable" $(NAME_STD) "created" $(CLR)

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
	@rm -f $(NAME_FT)
	@rm -f $(NAME_STD)
	@echo "\033[1;31m Deleted $(NAME_FT)" $(CLR)
	@echo "\033[1;31m Deleted $(NAME_STD)" $(CLR)

re: fclean all

ft: $(NAME_FT)
	./$(NAME_FT) $(GTEST_FLAGS)

std: $(NAME_STD)
	./$(NAME_STD) $(GTEST_FLAGS)

valstd: $(NAME_STD)
	valgrind --leak-check=full --show-leak-kinds=all --log-file=.valgrind -q ./$(NAME_STD) $(GTEST_FLAGS)

valft: $(NAME_FT)
	valgrind --leak-check=full --show-leak-kinds=all --log-file=.valgrind -q ./$(NAME_FT) $(GTEST_FLAGS)

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
	@cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -S $(GTEST_GTEST) -B $(GTEST_BUILD)
	@sed -i '1222s/int dummy;/int dummy = 0;/; 1223s/bool result;/bool result = false;/' $(GTEST_GTEST)src/gtest-death-test.cc
	@make -j -C $(GTEST_BUILD)

gtest: $(GTEST_ALL_A)

bear:
	bear -- make


#-----------------------------------------------------------------------------------------------------------#
#	Dependency																								#
#-----------------------------------------------------------------------------------------------------------#

-include $(DEPS_FT)
-include $(DEPS_STD)
