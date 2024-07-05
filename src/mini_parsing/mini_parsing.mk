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

MINI_PARSING_DIR	=	mini_parsing
MINI_PARSING_HEADER	=	mini_parsing.h
MINI_PARSING_FILE	=	mini_parsing.c mini_parser.c

MINI_PARSING		=	$(addprefix $(MINI_PARSING_DIR)/, $(MINI_PARSING_FILE))
MINI_PARSING_HEAD	=	$(addprefix $(MINI_PARSING_DIR)/, $(MINI_PARSING_HEADER))