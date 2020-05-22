/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:52:14 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:02:58 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define PF_BUFF_SIZE	4096
# define L_H			1
# define L_HH			2
# define L_L			3
# define L_LL			4
# define L_LLL			5
# define L_J			6
# define L_Z			7
# define END_COLOR	"\033[0m"
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define BBLACK		"\033[1;30m"
# define BRED		"\033[1;31m"
# define BGREEN		"\033[1;32m"
# define BYELLOW		"\033[1;33m"
# define BBLUE		"\033[1;34m"
# define BPURPLE		"\033[1;35m"
# define BCYAN		"\033[1;36m"
# define BWHITE		"\033[1;37m"
# define UBLACK		"\033[4;30m"
# define URED		"\033[4;31m"
# define UGREEN		"\033[4;32m"
# define UYELLOW		"\033[4;33m"
# define UBLUE		"\033[4;34m"
# define UPURPLE		"\033[4;35m"
# define UCYAN		"\033[4;36m"
# define UWHITE		"\033[4;37m"
# define ON_BLACK		"\033[40m"
# define ON_RED		"\033[41m"
# define ON_GREEN		"\033[42m"
# define ON_YELLOW		"\033[43m"
# define ON_BLUE		"\033[44m"
# define ON_PURPLE		"\033[45m"
# define ON_CYAN		"\033[46m"
# define ON_WHITE		"\033[47m"
# define IBLACK		"\033[0;90m"
# define IRED		"\033[0;91m"
# define IGREEN		"\033[0;92m"
# define IYELLOW		"\033[0;93m"
# define IBLUE		"\033[0;94m"
# define IPURPLE		"\033[0;95m"
# define ICYAN		"\033[0;96m"
# define IWHITE		"\033[0;97m"
# define BIBLACK		"\033[1;90m"
# define BIRED		"\033[1;91m"
# define BIGREEN		"\033[1;92m"
# define BIYELLOW		"\033[1;93m"
# define BIBLUE		"\033[1;94m"
# define BIPURPLE		"\033[1;95m"
# define BICYAN		"\033[1;96m"
# define BIWHITE		"\033[1;97m"
# define ON_IBLACK		"\033[0;100m"
# define ON_IRED		"\033[0;101m"
# define ON_IGREEN		"\033[0;102m"
# define ON_IYELLOW		"\033[0;103m"
# define ON_IBLUE		"\033[0;104m"
# define ON_IPURPLE		"\033[0;105m"
# define ON_ICYAN		"\033[0;106m"
# define ON_IWHITE		"\033[0;107m"

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

# include <stdio.h>

typedef struct		s_flags
{
	unsigned		d:1;
	unsigned		plus:1;
	unsigned		minus:1;
	unsigned		zero:1;
	unsigned		s:1;
	int				p;
	int				m;
	char			c;
	int				length;
	int				len;
}					t_flags;

typedef struct		s_counts
{
	int				s;
	int				b;
	int				t;
	int				fd;
	int				bs;
}					t_counts;

void				shitty_o(t_flags *f, unsigned long long *n2
					, unsigned long long *nbr);
int					regular_color(char *buf, char *color, t_counts *c);
int					bold_color(char *buf, char *color, t_counts *c);
int					underline_color(char *buf, char *color, t_counts *c);
void				flush_buff(char *buf, t_counts *c);
int					ft_printf(const char *str, ...);
int					ft_dprintf(int fd, const char *str, ...);
int					ft_vprintf(const char *str, va_list ap);
int					ft_vdprintf(int fd, const char *str, va_list ap);
int					ft_bdprintf(int buff_size, int fd, const char *str, ...);
void				read_flag(char *buf, const char *str, t_counts *c, va_list
					ap);
void				read_color(char *buf, const char *str, t_counts *c);
void				get_number(long long n, char *s, int i);
void				get_number_unsigned(unsigned long long n, char *s, int i);
void				write_nbr(char *buf, t_counts *c, long long n);
void				write_unsigned(char *buf, t_counts *c, unsigned long long n)
					;
void				write_float(char *buf, t_counts *c, long double n, int p);
int					get_opts(t_flags *f, const char *str, t_counts *c);
int					opt_parser(t_flags *f, const char *str);
int					precision_parser(t_flags *f, const char *str);
int					taille_parser(t_flags *f, const char *str);
int					towp_checker(char c, int check_type);
int					width_parser(t_flags *f, const char *str);
void				write_in_buff(char *buf, char ch, t_counts *c);
void				write_str(char *buf, t_counts *c, char *s);
long long			convert_int_arg(va_list ap, t_flags f);
unsigned long long	convert_u_arg(va_list ap, t_flags f);
void				convert_hex(char *buf, t_counts *c, long long n, char ch);
void				handler(char *buf, t_flags *f, t_counts *c, va_list ap);
void				print_ox(char *buf, t_counts *c, char ch);
void				handler_i(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_u(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_c(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_s(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_p(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_x(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_o(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_f(char *buf, t_flags *f, t_counts *c, va_list ap);
void				handler_percent(char *buf, t_flags *f, t_counts *c);
#endif
