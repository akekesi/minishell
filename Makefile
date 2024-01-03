# NAME = minishell
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror

# all: $(NAME)

# $(NAME):
#     $(CC) $(CFLAGS) -o $(NAME) ./src/main2.c $(LDFLAGS)

# clean:
#     rm -f $(NAME)

# fclean: clean

# re: fclean all

NAME 		=	minishell
INCLUDE		=	-I ./inc
H_FILE		=	minishell.h

CC 			=	cc
CFLAGS 		=	#-Wall -Wextra -Werror
VALGRIND	=	valgrind
RM			=	rm
LDFLAGS		=	-lreadline

SRCS_DIR	=	./src/
OBJS_DIR	=	./obj/

SRC_FILES	=	main pipe parse

SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -g $(OBJS) -o $(NAME) $(LDFLAGS)

# $(NAME):	$(OBJS)
#			$(CC) -g $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
# 			$(CC) -g $(OBJS) -o $(NAME) $(LDFLAGS)
# 			@echo "# **************************************************************************** #"
# 			@echo "#                                                                              #"
# 			@echo "#                            SS  H  H EEE L   L           SSS      iiiiiiii    #"
# 			@echo "#                           S  S H  H E   L   L         SHS      ini    ini    #"
# 			@echo "#              i         i  S    H  H E   L   L       HSH HSH         nin      #"
# 			@echo "#                            S   HHHH EEE L   L     HEH  HSH       nEn         #"
# 			@echo "#    m mm mm  ii  n nn  ii    S  H  H E   L   L   HEHEHEHEHEH   nEn            #"
# 			@echo "#     m  m  m  i   n  n  i  S  S H  H E   L   L        EHE    EiE              #"
# 			@echo "#     m  m  m iii  n  n iii  SS  H  H EEE LLL LLL     EEE   EEEEEEEE.sh        #"
# 			@echo "#                                                                              #"
# 			@echo "# **************************************************************************** #"
# 			@echo "Type: % ./minishell"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c ./inc/$(H_FILE)
			@mkdir -p $(@D)
			$(CC) -g $(INCLUDE) -c $< -o $@

clean:
			$(RM) -rf $(OBJS_DIR)
	
fclean: 	clean
			$(RM) -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
