/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solibft_t.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:45:02 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLIBFT_T_H
# define SOLIBFT_T_H

# include <unistd.h>
# include <stdlib.h>
# include <sotypes.h>

typedef struct s_solibft
{
	long			(*atoi)(const char *nptr);
	void			*(*calloc)(t_solib *solib, size_t nmemb, size_t size);
	char			*(*itoa)(t_solib *solib, int n);
	void			(*putchar)(char c, int fd);
	void			(*putendl)(char *s, int fd);
	void			(*putnbr)(int n, int fd);
	void			(*putstr)(char *s, int fd);
	int				(*isalnum)(int c);
	int				(*isalpha)(int c);
	int				(*isascii)(int c);
	int				(*isdigit)(int c);
	int				(*isprint)(int c);
	int				(*tolower)(int c);
	int				(*toupper)(int c);
	void			(*bzero)(void *s, size_t n);
	void			*(*memchr)(const void *s, int c, size_t n);
	int				(*memcmp)(const void *s1, const void *s2, size_t n);
	void			*(*memcpy)(void *dest, const void *src, size_t n);
	void			*(*memmove)(void *dest, const void *src, size_t n);
	void			*(*memset)(void *dst, int c, size_t n);
	char			**(*split)(t_solib *solib, char const *s, char c);
	char			*(*strchr)(const char *str, int c);
	char			*(*strdup)(t_solib *solib, const char *s);
	void			(*striteri)(char *s, void (*f)(unsigned int, char*));
	char			*(*strjoin)(t_solib *solib, char const *s1, char const *s2);
	size_t			(*strlen)(const char *s);
	char			*(*strmapi)(t_solib *solib,
			char const *s, char (*f)(unsigned int, char));
	void			(*strmcat)(t_solib *solib, char **dst, char *src);
	int				(*strncmp)(const char *s1, const char *s2, size_t n);
	char			*(*strnstr)(const char *s,	const char *needle, size_t n);
	char			*(*strrchr)(const char *s, int c);
	char			*(*strtrim)(t_solib *solib,
			char const *s1, char const *set);
	char			*(*substr)(t_solib *solib,
			char const *s, size_t start, size_t len);
	unsigned long	(*strlcat)(char *dst, const char *src, size_t size);
	unsigned long	(*strlcpy)(char *dst, const char *src, size_t sz);
}	t_solibft;

#endif