
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
GTEST_FILTER	=	*
GTEST_REPEAT	=	1
GTEST_SHUFFLE	=	#--gtest_shuffle=yes
GTEST_FLAGS		=	--gtest_color=yes --gtest_filter=$(GTEST_FILTER) --gtest_repeat=$(GTEST_REPEAT) $(GTEST_SHUFFLE) #--gtest_output=json:$_
VALGRIND_FLAGS	=	--error-exitcode=1 --exit-on-first-error=yes --leak-check=full --show-leak-kinds=all --log-file=.valgrind -q
CACHEGRIND_FLAGS=	-q --tool=cachegrind -q --cachegrind-out-file=cachegrind.out


#-----------------------------------------------------------------------------------------------------------#
#	Compilation																								#
#-----------------------------------------------------------------------------------------------------------#

NAME				=	abstract_data
NAME_FT				=	ft_$(NAME)
NAME_STD			=	std_$(NAME)

INC					=	include/
SRC_DIR				=	src/
SRC_NAME			=	main.cpp

INCLUDES			=	-I$(INC) -I$(GTEST_INCLUDE)
CFLAGS				=	$(INCLUDES) -Wall -Werror -Wextra -g -std=c++98 -MMD -MP
CXX					=	c++

OBJ_DIR				=	.build/
OBJ_FT_DIR			=	$(OBJ_DIR)ft/
OBJ_STD_DIR			=	$(OBJ_DIR)std/
OBJ_FT				=	$(addprefix $(OBJ_FT_DIR), $(SRC_NAME:.cpp=.o))
OBJ_STD				=	$(addprefix $(OBJ_STD_DIR), $(SRC_NAME:.cpp=.o))

DEPS_FT_SRC			=	$(SRC_NAME:.cpp=.d)
DEPS_STD_SRC		=	$(SRC_NAME:.cpp=.d)
DEPS_FT				=	$(patsubst %, $(OBJ_FT_DIR)%, $(DEPS_FT_SRC))
DEPS_STD			=	$(patsubst %, $(OBJ_STD_DIR)%, $(DEPS_STD_SRC))


NAME_BONUS_FT		= ft_$(NAME)_bonus
NAME_BONUS_STD		= std_$(NAME)_bonus

SRC_BONUS_NAME		= main_bonus.cpp
CFLAGS_BONUS		= $(INCLUDES) -Wall -Werror -Wextra -g -std=c++11 -MMD -MP

OBJ_BONUS_FT_DIR	= $(OBJ_DIR)ft_bonus/
OBJ_BONUS_STD_DIR	= $(OBJ_DIR)std_bonus/
OBJ_BONUS_FT		= $(addprefix $(OBJ_BONUS_FT_DIR), $(SRC_BONUS_NAME:.cpp=.o))
OBJ_BONUS_STD		= $(addprefix $(OBJ_BONUS_STD_DIR), $(SRC_BONUS_NAME:.cpp=.o))

DEPS_BONUS_FT_SRC	=	$(SRC_BONUS_NAME:.cpp=.d)
DEPS_BONUS_STD_SRC	=	$(SRC_BONUS_NAME:.cpp=.d)
DEPS_BONUS_FT		=	$(patsubst %, $(OBJ_BONUS_FT_DIR)%, $(DEPS_BONUS_FT_SRC))
DEPS_BONUS_STD		=	$(patsubst %, $(OBJ_BONUS_STD_DIR)%, $(DEPS_BONUS_STD_SRC))


#-----------------------------------------------------------------------------------------------------------#
#	Doxygen																									#
#-----------------------------------------------------------------------------------------------------------#

DOXYFILE				=	Doxyfile
DOXYGEN_SRCS			=	$(INC)grid.hpp
DOXYGEN_DIR				=	.doxygen/
DOXYGEN_DOC				=	$(DOXYGEN_DIR)doc/
DOXYGEN_HTML			=	$(DOXYGEN_DOC)index.html
DOXYGEN_AWESOME			=	$(DOXYGEN_DIR)doxygen-awesome-css/
DOXYGEN_LATEX			=	$(DOXYGEN_DIR)latex/
DOXYGEN_SUBDIR			=	$(DOXYGEN_DOC) $(DOXYGEN_LATEX)
DOXYGEN_AWESOME_LINK	=	https://github.com/jothepro/doxygen-awesome-css.git


#-----------------------------------------------------------------------------------------------------------#
#	Targets																									#
#-----------------------------------------------------------------------------------------------------------#

$(OBJ_FT_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -DTESTED_NAMESPACE=ft -DUSE_FT $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) $(CLR)

$(OBJ_STD_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -DTESTED_NAMESPACE=std $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) $(CLR)

$(OBJ_BONUS_FT_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS_BONUS) -DTESTED_NAMESPACE=ft -DUSE_FT $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) "(bonus)" $(CLR)

$(OBJ_BONUS_STD_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS_BONUS) -DTESTED_NAMESPACE=std $< -c -o $@
	@echo "\033[1;36m Compiled" $(*F) "(bonus)" $(CLR)


all: $(NAME) doc


$(NAME): $(NAME_FT) $(NAME_STD)

$(NAME_FT): $(OBJ_FT)
	@$(CXX) $(CFLAGS) -o $(NAME_FT) $(OBJ_FT) $(GTEST_ALL_A)
	@echo "\033[1;32m Executable" $(NAME_FT) "created" $(CLR)

$(NAME_STD): $(OBJ_STD)
	@$(CXX) $(CFLAGS) -o $(NAME_STD) $(OBJ_STD) $(GTEST_ALL_A)
	@echo "\033[1;32m Executable" $(NAME_STD) "created" $(CLR)


bonus: $(NAME_BONUS_FT) $(NAME_BONUS_STD)

$(NAME_BONUS_FT): $(OBJ_BONUS_FT)
	@$(CXX) $(CFLAGS_BONUS) -o $(NAME_BONUS_FT) $(OBJ_BONUS_FT) $(GTEST_ALL_A)
	@echo "\033[1;32m Executable" $(NAME_BONUS_FT) "created" $(CLR)

$(NAME_BONUS_STD): $(OBJ_BONUS_STD)
	@$(CXX) $(CFLAGS_BONUS) -o $(NAME_BONUS_STD) $(OBJ_BONUS_STD) $(GTEST_ALL_A)
	@echo "\033[1;32m Executable" $(NAME_BONUS_STD) "created" $(CLR)


clean: dclean gclean
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;31m Deleted all object files" $(CLR)
	@rm -rf "$(NAME_FT).json"
	@rm -rf "$(NAME_STD).json"
	@rm -rf "$(NAME_BONUS_FT).json"
	@rm -rf "$(NAME_BONUS_STD).json"
	@rm -rf cachegrind.out

dclean:
	@rm -rf $(DOXYGEN_SUBDIR)
	@echo "\033[1;31m Deleted documentation" $(CLR)

gclean:
	@rm -rf $(GTEST_TAR)
	@echo "\033[1;31m Deleted gtest tar" $(CLR)

fclean: clean dclean gclean
	@rm -f $(NAME_FT)
	@rm -f $(NAME_STD)
	@rm -f $(NAME_BONUS_FT)
	@rm -f $(NAME_BONUS_STD)
	@echo "\033[1;31m Deleted $(NAME_FT)" $(CLR)
	@echo "\033[1;31m Deleted $(NAME_STD)" $(CLR)
	@echo "\033[1;31m Deleted $(NAME_BONUS_FT)" $(CLR)
	@echo "\033[1;31m Deleted $(NAME_BONUS_STD)" $(CLR)

re: fclean all
bre: fclean bonus


ft: $(NAME_FT)
	@rm -rf "$(NAME_FT).json"
	./$(NAME_FT) $(GTEST_FLAGS)

std: $(NAME_STD)
	@rm -rf "$(NAME_STD).json"
	./$(NAME_STD) $(GTEST_FLAGS)

valft: $(NAME_FT)
	@rm -rf "$(NAME_FT).json"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME_FT) $(GTEST_FLAGS)

valstd: $(NAME_STD)
	@rm -rf "$(NAME_STD).json"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME_STD) $(GTEST_FLAGS)

cft: $(NAME_FT)
	@rm -rf cachegrind.out
	@valgrind $(CACHEGRIND_FLAGS) ./$(NAME_FT) $(GTEST_FLAGS)

cstd: $(NAME_STD)
	@rm -rf cachegrind.out
	@valgrind $(CACHEGRIND_FLAGS) ./$(NAME_STD) $(GTEST_FLAGS)

bft: $(NAME_BONUS_FT)
	@rm -rf "$(NAME_BONUS_FT).json"
	./$(NAME_BONUS_FT) $(GTEST_FLAGS)

bstd: $(NAME_BONUS_STD)
	@rm -rf "$(NAME_BONUS_STD).json"
	./$(NAME_BONUS_STD) $(GTEST_FLAGS)

valbft: $(NAME_BONUS_FT)
	@rm -rf "$(NAME_BONUS_FT).json"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME_BONUS_FT) $(GTEST_FLAGS)

valbstd: $(NAME_BONUS_STD)
	@rm -rf "$(NAME_BONUS_STD).json"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME_BONUS_STD) $(GTEST_FLAGS)

cbft: $(NAME_BONUS_FT)
	@rm -rf cachegrind.out
	@valgrind $(CACHEGRIND_FLAGS) ./$(NAME_BONUS_FT) $(GTEST_FLAGS)

cbstd: $(NAME_BONUS_STD)
	@rm -rf cachegrind.out
	@valgrind $(CACHEGRIND_FLAGS) ./$(NAME_BONUS_STD) $(GTEST_FLAGS)



$(DOXYGEN_AWESOME):
	@mkdir -p $(DOXYGEN_DIR)
	@git clone -q $(DOXYGEN_AWESOME_LINK) $(DOXYGEN_AWESOME)
	@echo "\033[1;32m Cloned Doxygen Awesome CSS" $(CLR)

$(DOXYGEN_HTML): $(DOXYFILE) $(DOXYGEN_SRCS) $(DOXYGEN_AWESOME)
	@echo "\033[0;35m Updated Doxygen documentation" $(CLR)
	@doxygen $(DOXYFILE)

doc: $(DOXYGEN_HTML)

odoc: doc
	@open $(DOXYGEN_HTML)


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
-include $(DEPS_BONUS_FT)
-include $(DEPS_BONUS_STD)
