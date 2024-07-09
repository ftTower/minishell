# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/05/20 17:05:51 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include $(CURDIR)/src/mini_parsing/mini_parsing.mk
include $(CURDIR)/src/gears/gears.mk
include $(CURDIR)/src/parsing/parsing.mk
include $(CURDIR)/src/pipex/pipex.mk

SRC_DIR		=	$(CURDIR)/src

LIB_HEADER	=	$(addprefix $(SRC_DIR)/, minishell.h)
SRC_HEADER	=	types.h all.h
SRC_FILES	=	minishell.c

DIR			+= $(MINI_PARSING_DIR)
DIR			+= $(GEARS_DIR)
DIR			+= $(PARSING_DIR)
DIR			+= $(PIPEX_DIR)

SRC_HEADER	+= $(MINI_PARSING_HEAD)
SRC_HEADER	+= $(GEARS_HEAD)
SRC_HEADER	+= $(PARSING_HEAD)
SRC_HEADER	+= $(PIPEX_HEAD)

SRC_FILES	+= $(MINI_PARSING)
SRC_FILES	+= $(GEARS)
SRC_FILES	+= $(PARSING)
SRC_FILES	+= $(PIPEX)

HEADERS		=	$(addprefix $(SRC_DIR)/, $(SRC_HEADER))
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
FOLDERS		=	$(addprefix $(SRC_DIR)/, $(DIR))
FOLDERS		+=	$(SRC_DIR)
