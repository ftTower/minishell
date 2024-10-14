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

PIPEX_DIR		=	pipex

PIPEX_HEADER	=	pipex.h
PIPEX_FILE		=	pipex.c soexec.c soexec2.c builtin.c pipex_utils.c

PIPEX			=	$(addprefix $(PIPEX_DIR)/, $(PIPEX_FILE))
PIPEX_HEAD		=	$(addprefix $(PIPEX_DIR)/, $(PIPEX_HEADER))