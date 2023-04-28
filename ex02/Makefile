# Variables
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98
IFLAGS	=	-I includes
DFLAGS	=	-g -DDEBUG
ifeq ($(findstring debug, $(MAKECMDGOALS)), debug)
	CFLAGS	+=	$(DFLAGS)
endif
NAME	=	PmergeMe
DEP_PATH=	deps/
OBJ_PATH=	objs/
SRC_PATH=	$(shell find srcs -type d)
SRCS	=	main.cpp \
			PmergeMe.cpp
OBJS	=	$(addprefix $(OBJ_PATH), $(SRCS:.cpp=.o))
DEPS	=	$(addprefix $(DEP_PATH), $(SRCS:.cpp=.d))
vpath %.cpp $(foreach rep, $(SRC_PATH), $(rep))

# Compilation
all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_PATH)%.o	:	%.cpp
	@mkdir -p $(OBJ_PATH) $(DEP_PATH)
	$(CC) -o $@ -c $<  $(CFLAGS) $(IFLAGS) -MMD
	@mv $(@:.o=.d) $(DEP_PATH)

-include $(DEPS)

# Rules
clean	:
	rm -rf $(OBJ_PATH) $(DEP_PATH)

fclean	:	clean
	@rm -f $(NAME)

re		:	fclean all

debug	:	re

.PHONY	:	all clean fclean re debug