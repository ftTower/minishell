# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fork.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 20:23:13 by marvin            #+#    #+#              #
#    Updated: 2024/04/07 20:23:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src/parsing/stringbuilder/stringbuilder.mk
include src/parsing/cellmaker/cellmaker.mk
include src/parsing/cellparser/cellparser.mk
include src/parsing/envpl/envpl.mk


PARSING_DIR		=	parsing

PARSING_HEADER	=	parsing.h
PARSING_FILE	=	parsing.c parsing_error.c \
					  parsing_print.c parsing_utils.c 

PARSING_FILE	+=	$(STRINGBUILDER)
PARSING_FILE	+=	$(CELLMAKER)
PARSING_FILE	+=	$(CELLPARSER)
PARSING_FILE	+=	$(ENVPL)

PARSING			=	$(addprefix $(PARSING_DIR)/, $(PARSING_FILE))
PARSING_HEAD	=	$(addprefix $(PARSING_DIR)/, $(PARSING_HEADER))