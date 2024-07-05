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

STRINGBUILDER_DIR		=	stringbuilder

STRINGBUILDER_FILE		=	stringbuilder.c stringbuilder_redirect.c stringbuilder_t_char.c \
							stringbuilder_gears.c stringbuilder_t_word.c
 
STRINGBUILDER			=	$(addprefix $(STRINGBUILDER_DIR)/, $(STRINGBUILDER_FILE))