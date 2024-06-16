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

GEARS_DIR		=	gears

GEARS_HEADER	=	gears.h
GEARS_FILE		=	gears.c

GEARS			=	$(addprefix $(GEARS_DIR)/, $(GEARS_FILE))
GEARS_HEAD		=	$(addprefix $(GEARS_DIR)/, $(GEARS_HEADER))