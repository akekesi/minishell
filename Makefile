# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 16:23:11 by tnakajo           #+#    #+#              #
#    Updated: 2023/12/05 17:32:44 by tnakajo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
INCLUDE		= -I ./include
H_FILE		= minishell.h

CC 			= cc
CFLAGS 		= #-Wall -Wextra -Werror
VALGRIND	=	valgrind
RM			=	rm

SRCS_DIR	=	./src/
OBJS_DIR	=	./obj/

SRC_FILES	=	main
# open_restaurant
#  OBJ = $(SRC:.c=.o)

SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "# **************************************************************************** #"
			@echo "#                                                                              #"
			@echo "#                            SS  H  H EEE L   L           SSS      iiiiiiii    #"
			@echo "#                           S  S H  H E   L   L         SHS      ini    ini    #"
			@echo "#              i         i  S    H  H E   L   L       HSH HSH         nin      #"
			@echo "#                            S   HHHH EEE L   L     HEH  HSH       nEn         #"
			@echo "#    m mm mm  ii  n nn  ii    S  H  H E   L   L   HEHEHEHEHEH   nEn            #"
			@echo "#     m  m  m  i   n  n  i  S  S H  H E   L   L        EHE    EiE              #"
			@echo "#     m  m  m iii  n  n iii  SS  H  H EEE LLL LLL     EEE   EEEEEEEE.sh        #"
			@echo "#                                                                              #"
			@echo "# **************************************************************************** #"
			@echo "Type: % ./minishell"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c ./include/$(H_FILE)
			@mkdir -p $(@D)
			$(CC) -g $(INCLUDE) -c $< -o $@

clean:
			$(RM) -rf $(OBJS_DIR)
	
fclean: 	clean
			$(RM) -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
