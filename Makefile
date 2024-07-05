# ================================ VARIABLES ================================= #

# The name of the executable
NAME	= froggers

# Compiler and compiling flags
CC	= g++
CFLAGS	= -Wall -Wextra -Wpedantic -std=gnu++17

# Debug, use with `make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3 -fsanitize=address
endif

# Folder name
SRCDIR	= srcs/
INCDIR	= includes/
OBJDIR	= bin/

# Add include folder
CFLAGS	+= -I $(INCDIR)

# Linking stage flags
LDFLAGS = -lfltk

SRCS =\
	./srcs/main.cpp\
	./srcs/Rectangle.cpp\
	./srcs/Canvas.cpp\
	./srcs/Cell.cpp\
	./srcs/Frog.cpp\

HEADERS =\
	./includes/

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.cpp=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(NAME)

# Compiling
$(OBJDIR)%.o : %.cpp
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking
$(NAME)	: $(SRCS) $(HEADERS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Cleaning
clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# This specifies the rules that does not correspond to any filename
.PHONY	= all clean fclean re