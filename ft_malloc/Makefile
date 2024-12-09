


ifeq ($(HOSTTYPE), )
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


CC			= cc

NAME		= libft_malloc_$(HOSTTYPE).so

LIB_NAME	= libft_malloc.so

LIB_PATH	= src/libft

HEADER_PATH	= include

C_PATH 		= src

# ---------------- transformation ------------------ #

HEADER		= $(HEADER_PATH)/ft_malloc.h 

CFILES		= $(notdir $(foreach D, $(C_PATH), $(wildcard $(D)/*.c)))
LIBFILES	= $(notdir $(foreach D, $(LIB_PATH), $(wildcard $(D)/*.c)))

OBJS_NAME	= $(patsubst %.c, %.o, $(CFILES)) \
	     	  $(patsubst %.c, %.o, $(LIBFILES))
DFILES_NAME	= $(patsubst %.c, %.d, $(CFILES)) \
			  $(patsubst %.c, %.d, $(LIBFILES))

OBJ_PATH	= obj
DPFLAGS		= -MD -MP
# a ideia é so ter as funcoes visiveis que sao EXPORT #-fvisibility=hidden
CFLAGS		= -Wall -Wextra -Werror -fPIC  \
			  $(foreach D, $(HEADER_PATH), -I$(D)) $(DPFLAGS)


CFLAGS_DEBUG =  -O0 -g3 

CFLAGS_RELEASE = -O3              # Otimização agressiva
# CFLAGS_RELEASE += -flto            # Link Time Optimization
# CFLAGS_RELEASE += -march=native    # Otimizar para CPU atual
# #CFLAGS_RELEASE += -ffast-math         # Otimizações matemáticas
# CFLAGS_RELEASE += -funroll-loops      # Desenrola loops
# CFLAGS_RELEASE += -fomit-frame-pointer # Remove frame pointer quando possível
# #CFLAGS_RELEASE += -fno-stack-protector # Remove proteção de stack (nem sempre corre bem)
# CFLAGS_RELEASE += -falign-functions=32  # Alinha funções
# #CFLAGS_RELEASE += -falign-loops=32      # Alinha loops
# CFLAGS_RELEASE += -fdata-sections       # Coloca cada dado em sua própria seção
# CFLAGS_RELEASE += -ffunction-sections   # Coloca cada função em sua própria seção

# make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS += $(CFLAGS_DEBUG)
else
    CFLAGS += $(CFLAGS_RELEASE)
endif

LDFLAGS += -Wl,-O3              # Otimização no linking
LDFLAGS += -Wl,--gc-sections    # Remove seções não usadas
LDFLAGS += -Wl,--as-needed      # Link apenas bibliotecas necessárias

#CFLAGS = -Wall -Wextra -Werror -fPIC -fvisibility=hidden# a ideia é so ter as funcoes visiveis que sao EXPORT
SFLAGE		= -shared 
DEBUGF 		= #-fsanitize=address -g


SRCS = $(addprefix $(C_PATH)/,$(CFILES)) \
	   $(addprefix $(LIB_PATH)/,$(LIBFILES))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJS_NAME))
DFLS = $(addprefix $(OBJ_PATH)/,$(DFILES_NAME))

BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(SFLAGE) $(DEBUGF) $(OBJS) $(LDFLAGS) -o $@
	@rm -f $(LIB_NAME)
	@ln -s $(NAME) $(LIB_NAME)
	@printf $(GREEN)"$(NAME) Finish linking\n"$(EOC)

$(OBJ_PATH)/%.o:$(C_PATH)/%.c | $(OBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o:$(LIB_PATH)/%.c | $(OBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null

clean: 
	@rm -f $(OBJS) $(DFLS)
	@rm -rf $(OBJ_PATH) 2> /dev/null
	@printf $(GREEN)"$(NAME) clean\n"$(EOC)

fclean: clean
	@/bin/rm -f $(NAME) $(LIB_NAME)
	@printf $(GREEN)"$(NAME) fclean\n"$(EOC)

-include $(DFLS)

re: fclean all



.PHONY: clean fclean re norme all