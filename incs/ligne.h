#ifndef LIGNE_H
# define LIGNE_H

#ifndef NULL
# define 
#endif


# define BUFFSIZE				512
# define PROMPT_DEFAULT			"42sh> "
# define PROMPT_SUBLINE			"> "
# define PROMPT_HEREDOC			"heredoc> "

# if defined(__ITERM__)
#  define KEY_CTRL_LEFT_CODE	"\x1b\x1b[D"
#  define KEY_CTRL_RIGHT_CODE	"\x1b\x1b[C"
#  define KEY_CTRL_UP_CODE		"\x1b\x1b[A"
#  define KEY_CTRL_DOWN_CODE	"\x1b\x1b[B"
# elif defined(__APPLE__)
#  define KEY_CTRL_LEFT_CODE	"\x1b""b"
#  define KEY_CTRL_RIGHT_CODE	"\x1b""f"
#  define KEY_CTRL_UP_CODE		"\x1b""[a"
#  define KEY_CTRL_DOWN_CODE	"\x1b""[b"
# else
#  define KEY_CTRL_LEFT_CODE	"\033[1;5D"
#  define KEY_CTRL_RIGHT_CODE	"\033[1;5C"
#  define KEY_CTRL_UP_CODE		"\033[1;5A"
#  define KEY_CTRL_DOWN_CODE	"\033[1;5B"
# endif
# define KEY_UP_CODE			"\033[A"
# define KEY_DOWN_CODE			"\033[B"
# define KEY_RIGHT_CODE			"\033[C"
# define KEY_LEFT_CODE			"\033[D"
# define KEY_SUPR				"\177"
# define KEY_HOME				"\e[H"
# define KEY_END				"\e[F"

# define TERM_LEFT				"le"
# define TERM_RIGHT				"nd"
# define TERM_UP				"up"
# define TERM_DOWN				"do"
# define TERM_STARTLINE			"cr"
# define TERM_SAVE_CUR			"sc"
# define TERM_LOAD_CUR			"rc"
# define TERM_CLEAR_CUR_END		"cd"
# define TERM_CLEAR_CUR_LINE	"ce"
# define TERM_SCROLL_UP			"sf"
# define TERM_SCROLL_DOWN		"sr"
# define TERM_END				"ll"

# define READ_MODE_FULL			1
# define READ_MODE_LIMITED		2
# include <sys/ioctl.h>
# include "double_linked_list.h"
# include "historique.h"

typedef struct winsize t_winsize;
typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;
typedef struct	s_prompt
{
	char	*str;
	int		size;
}				t_prompt;
typedef struct	s_line
{
	char		*line;
	size_t		allocsize;
	int			index;
	t_prompt	*prompt;
}				t_line;
typedef struct	s_line_and_node
{
	t_dl_node	*node;
	t_line	*line;
}				t_line_and_node;

//t_line_and_node	g_for_resize;
char			*run_heredoc(char	*endstring);
char			*run_line_edit(void);

/*
**	term_misc.c
*/

int				init_term(void);
int				restore_term(void);
int				set_term_mode(void);
struct termios	*save_term(int act);
void			term_other(char *str, int iter);
void			cur_mov(int y, int x);

/*
**	controleur.c
*/

int				read_loop(t_line **line, t_dl_node **head, char mode);
void			arrow_line_action(t_line **line, char *buff, t_dl_node **head, char mode);

/*
**	move.c
*/

void			move_cur_on_newline(t_line *line);
void			move_cur_on_last_line(t_dl_node *head);
void			cur_move_to_index(t_line *line, int index);

/*
**	alloc.c
*/

t_dl_node			*dup_line_node(t_dl_node *src);
t_line			*dup_line(t_line *src);
t_prompt		*dup_prompt(t_prompt *src);
t_line			*init_line(t_line *tline, char *line, int index, t_prompt *prompt);
t_prompt		*new_prompt(char *str);

/*
**	garbage.c
*/

void			*ft_throw_err_free(int n, ...);
int				ft_isallprint(char *str);
int				is_multiline(t_dl_node *head);

/*
**	line_edit.c
*/

void			ft_insert_in_line(char *line, char *buff, int index);
void			write_on_line(t_line *line, int readsize, char *buff, t_dl_node **head);
void			print_historique(t_dl_node *historic);

/*
**	line_key1.c
*/

void			arrow_down_act(t_line **line, t_dl_node **head);
void			arrow_left_act(t_line *line);
void			arrow_right_act(t_line *line);
void			arrow_up_act(t_line **line, t_dl_node **head);

/*
**	line_key2.c
*/

void			arrow_ctrl_down(t_line **line, t_dl_node **head);
void			arrow_ctrl_up(t_line **line, t_dl_node **head);
void			suppr_act(t_line *line, t_dl_node **head);

/*
**	clear.c
*/

void			clear_line(t_line *line);
void			clear_node_line(t_line *current, t_dl_node *head);
void			free_line(t_line *line);

/*
**	get_things.c
*/

t_pos			get_cur_pos();
t_winsize		get_winsize();
int				get_last_word_index(t_line *line);
int				get_next_word_index(t_line *line);

/*
**	line_misc.c
*/
int				count_row_in_line(t_line *line, t_winsize winsize);
int				term_can_print(t_dl_node *head, int readsize);
void			handle_resize(int signo);
char			*concat_lines(t_dl_node *head);

#endif