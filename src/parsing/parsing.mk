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

include src/parsing/cellmaker/cellmaker.mk
include src/parsing/cellparser/cellparser.mk
include src/parsing/celltranslator/celltranslator.mk
include src/parsing/list_gears/list_gears.mk
include src/parsing/envpl/envpl.mk
include src/parsing/string_gears/string_gears.mk
include src/parsing/parsing_gears/parsing_gears.mk


PARSING_DIR		=	parsing

PARSING_HEADER	=	parsing.h
PARSING_FILE	=	parsing.c  

PARSING_FILE	+=	$(CELLMAKER)
PARSING_FILE	+=	$(CELLPARSER)
PARSING_FILE	+=	$(CELLTRANSLATOR)
PARSING_FILE	+=	$(ENVPL)
PARSING_FILE	+=	$(LIST_GEARS)
PARSING_FILE	+=	$(STRING_GEARS)
PARSING_FILE	+=	$(PARSING_GEARS)

PARSING			=	$(addprefix $(PARSING_DIR)/, $(PARSING_FILE))
PARSING_HEAD	=	$(addprefix $(PARSING_DIR)/, $(PARSING_HEADER))