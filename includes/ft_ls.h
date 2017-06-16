/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:12:58 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 12:19:47 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TRUE	1
# define FALSE	0

# define CLEAR	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PINK	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define SBLUE	"\033[46m"
# define SYEL	"\033[43m"

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <errno.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

typedef struct	s_root
{
	short int				no_path;
	int						win_width;
	struct s_files_list		*files;
	struct s_dir_list		*dir;
	struct s_options		*opt;

}				t_root;

typedef struct	s_files_list
{
	struct s_info			*info;
	struct s_files_list		*next;
}				t_files_list;

typedef struct	s_dir_list
{
	int					blocks;
	char				*path;
	char				*name;
	intmax_t			size;
	short int			norightr;
	short int			norightx;
	short int			norightoth;
	struct s_files_list	*content;
	struct s_dir_list	*dir;
	struct s_dir_list	*next;
}				t_dir_list;

typedef struct	s_options
{
	short int	l;
	short int	rec;
	short int	a;
	short int	r;
	short int	t;
	short int	m;
	short int	g;
	short int	aless;
	short int	ssort;
	short int	color;
}				t_options;

typedef struct	s_info
{
	char		*path;
	char		*name;
	char		type;
	char		*mode;
	char		*date;
	time_t		date_cmp;
	char		*user;
	char		*group;
	int			blocks;
	intmax_t	size;
	int			links;
	int			minor;
	int			major;
}				t_info;

typedef struct	s_max
{
	int			links;
	int			user;
	int			group;
	int			size;
	int			minor;
	int			major;
}				t_max;

/*
** fonctions parsing ligne de commande
*/

void			ls_set_options_false(t_options *opt);
int				ls_parse_options(t_options *opt, char *arg);
void			ls_parse_argument(t_root *root, int ac, char **av);
struct stat		ls_stat(t_options *opt, struct stat buffer, char *arg, int *t);

/*
** fonctions gestions d'erreurs
*/

void			ls_undifined_error(t_root *root);
void			ls_error_null_parameter(t_root *root, int ac, char **av);
void			ls_error_file(t_root *root, char *arg, int *error);

/*
** fonctions traitement du contenu de la branche contenu dir
*/

void			ls_handle_content(t_root *root, t_dir_list *new);
void			ls_add_content(t_root *root, t_dir_list *new,
										struct dirent *current);
void			ls_inner_add_content(t_dir_list *new,
										t_files_list *file, t_options *opt);
void			ls_handle_path(t_info *info, t_dir_list *new);
int				ls_cmp_files(t_files_list *f1, t_files_list *f2,
									t_options *opt);

/*
** fonctions traitement des listes de repertoire
*/

void			ls_add_dir(t_root *root, struct stat *buf, const char *name);
t_dir_list		*ls_inner_add_dir(t_dir_list *list,
										t_dir_list *new, t_options *opt);
void			ls_check_right_on_dir(t_dir_list *new, struct stat *buf);
int				ls_cmp_size_files(t_files_list *f1,
									t_files_list *f2, t_options *opt);
int				ls_cmp_dir(t_dir_list *d1, t_dir_list *d2, t_options *opt);
char			ls_get_type(struct stat *buffer);
t_files_list	*ls_malloc_files_list(t_root *root);
void			ls_handle_blocks(t_dir_list *new, t_info *info, t_root *root);

/*
** fonctions traitement option l
*/

void			ls_handle_list(t_root *root, t_info *info,
										struct stat *buffer);
char			*ls_get_mode(t_root *root, t_info *info, struct stat *buffer);

/*
** fonctions affichage
*/

void			ls_display(t_root *root);
int				ls_print_total(t_dir_list *dir, t_options *opt);
void			ls_display_content_l(t_root *root, t_files_list *content,
											t_options *opt, t_max max);
t_max			ls_calc_max(t_max max, t_files_list *content, t_options *opt);
void			ls_display_content_m(t_root *root, t_files_list *content);
char			*ls_color(t_files_list *file, t_options *opt);
char			*ls_clear(t_options *opt);

/*
** fonction de sortie de programme
*/

void			ls_exit(t_root *root);

#endif
