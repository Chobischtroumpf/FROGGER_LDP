# ================================ VARIABLES ================================= #

# The name of the executable
NAME    = froggers

# Compiler and compiling flags
CC      = g++
CFLAGS  = -Wall -Wextra -Wpedantic -std=gnu++17

# Debug, use with `make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS  += -g3 -fsanitize=address
endif

# Folder name
SRCDIR  = srcs/
INCDIR  = includes/
OBJDIR  = bin/

# Add include folder
CFLAGS  += -I $(INCDIR)

# Detecting macOS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	# macOS specific include path for FLTK
	# Use fltk-config to get compiler and linker flags
	FLTK_CXXFLAGS := $(shell fltk-config --cxxflags)
	FLTK_LDFLAGS := $(shell fltk-config --ldflags)
	CFLAGS += $(FLTK_CXXFLAGS)
	LDFLAGS += $(FLTK_LDFLAGS)
endif

# Linking stage flags
LDFLAGS += -lfltk

# Sources and headers
SRCS = $(wildcard $(SRCDIR)*.cpp)
OBJS = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCS))

# ================================== RULES =================================== #

all : $(NAME)

# Compiling
$(OBJDIR)%.o : $(SRCDIR)%.cpp
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking
$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Cleaning
clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# This specifies the rules that does not correspond to any filename
.PHONY : all clean fclean re
