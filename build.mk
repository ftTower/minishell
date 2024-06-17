# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    build.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 23:07:18 by marvin            #+#    #+#              #
#    Updated: 2024/05/16 14:30:56 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src/src.mk
include exemple/exemple.mk

#❖═══Setup══════════❖
NAME		= minishell

#❖═══Compilation════❖
CC			= cc
CFLAG		= -Wall -Wextra -Werror -I./$(BUILD_INCLUDES) -g3 -gdwarf-4
LDFLAGS 	= -lreadline
AR			= ar rc
LIB			= ranlib

#❖═══Objet══════════❖
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_OBJ)/%.o, $(SRC))

#❖═══Build══════════❖
BUILD_DIR		= build
LIBRARY			= $(BUILD_DIR)/$(NAME).a
BUILD_OBJ		= $(BUILD_DIR)/obj
BUILD_INCLUDES	= $(BUILD_DIR)/includes
ALL_B_INCLUDES	= $(BUILD_INCLUDES)/$(NAME)

#❖═══Libs═══════════❖
LIBS_DIR			=	libs
DEPENDENCIES		=	sotypes:https://github.com/zoyern/sotypes.git \
						solibft:https://github.com/zoyern/solibft.git
LIBRARYS			= 
LIBS_OBJ			= 
LIBS_INCLUDES		= 
LIBS_HEADER			=
ALL_L_INCLUDES		=
ifdef DEPENDENCIES
	DEPENDENCIES_RULES = dependencies
else
	DEPENDENCIES_RULES = 
endif

#❖═══Folders════════❖
$(BUILD_OBJ)/%.o: $(SRC_DIR)/%.c | $(BUILD_INCLUDES)
	mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

#❖═════Creat═════❖
$(NAME): $(DEPENDENCIES_RULES) $(OBJ)
	${AR} $(LIBRARY) ${OBJ} $(LIBRARYS)
	${LIB} $(LIBRARY)
	$(CC) $(SRC_EXEMPLE) $(OBJ) -o $(NAME) $(CFLAG) $(LIBRARYS) $(LIBRARY) $(LDFLAGS)

$(BUILD_INCLUDES):
	mkdir -p $(BUILD_DIR);
	mkdir -p $(BUILD_INCLUDES)
	mkdir -p $(ALL_B_INCLUDES)
	cp $(LIB_HEADER) $(BUILD_INCLUDES)
	cp $(HEADERS) $(ALL_B_INCLUDES)