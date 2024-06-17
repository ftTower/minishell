/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/06/10 20:49:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPRINTF_H
# define SOPRINTF_H

# include <sotypes/all.h>

int		soprintf(const char *str, ...);
void	soprintf_select(va_list list_arg, const char **str, size_t *len);
size_t	soprint_strlen(const char *str);
void	soprintf_putcolor_len(const char **s, va_list list_arg, size_t *len);
void	ft_putchar_len(char c, size_t *len);
void	ft_putstr_len(char *s, size_t *len);
void	ft_putstrs_len(char **strs, size_t *len);
void	ft_putbool_len(int boolean, size_t *len);
void	ft_putnbr_len(int n, size_t *len);
void	ft_putnbr_len_base(unsigned int n, char *base, size_t *len);
void	ft_putptr_len(unsigned long n, char *base, size_t *len);
char	*hex_to_ansi(char *hex, int is_background);
char	*ansi_format(int cc, int is_background);
char	*ansi_concat(char *base, char *cc, char *out);
int		ansi_16_basic_colors(int r, int g, int b);
void	ansi_16_basic_colors_blue(int b, int *cc);
void	ansi_16_basic_colors_green(int g, int *cc);
void	ansi_16_basic_colors_red(int r, int *cc);
int		ansi_grey_ramp(int r, int g, int b);
void	soconvert_hex_to_rgb(char *hex, int *r, int *g, int *b);
int		hex_char_to_int(char hex_char);
char	*ansi_itoa(int n);
size_t	ansi_nbrlen(int n);
void	ansi_strmcat(char **dst, char *src);
int		soconvert_rgb_to_ansi(int r, int g, int b);

#endif
