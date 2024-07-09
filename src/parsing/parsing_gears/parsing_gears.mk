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

PARSING_GEARS_DIR		=	parsing_gears

PARSING_GEARS_FILE		=  	parsing_utils.c  parsing_error.c parsing_printer.c
 
PARSING_GEARS			=	$(addprefix $(PARSING_GEARS_DIR)/, $(PARSING_GEARS_FILE))