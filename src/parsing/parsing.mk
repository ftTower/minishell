# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parsing.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 02:15:59 by marvin            #+#    #+#              #
#    Updated: 2024/06/10 21:33:43 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_DIR		=	parsing
PARSING_HEADER	=	parsing.h
PARSING_FILE	=	parsing.c parser.c

PARSING			=	$(addprefix $(PARSING_DIR)/, $(PARSING_FILE))
PARSING_HEAD	=	$(addprefix $(PARSING_DIR)/, $(PARSING_HEADER))