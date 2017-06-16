/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:37:38 by heynard           #+#    #+#             */
/*   Updated: 2017/06/16 12:13:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_options	*ls_init_root_options(int ac, char **av, t_root *root)
{
	t_options		*opt;
	int				isoption;
	int				i;

	if ((opt = malloc(sizeof(t_options))) == NULL)
		return (NULL);
	ls_set_options_false(opt);
	i = 0;
	isoption = 1;
	while (++i < ac)
	{
		if (av[i][0] == '-' && isoption)
		{
			if ((ls_parse_options(opt, av[i])) == FALSE)
			{
				free(opt);
				free(root);
				ft_printf("usage: ./ft_ls [-AGRSaglmrt1] [file ...]\n");
				exit(1);
			}
		}
		else
			isoption = 0;
	}
	return (opt);
}

static t_root		*ls_init_root(int ac, char **av)
{
	t_root			*root;

	if ((root = malloc(sizeof(t_root))) == NULL)
		ls_undifined_error(NULL);
	root->no_path = 0;
	root->files = NULL;
	root->dir = NULL;
	if ((root->opt = ls_init_root_options(ac, av, root)) == NULL)
	{
		free(root);
		ls_undifined_error(root);
	}
	return (root);
}

int					main(int ac, char **av)
{
	t_root			*env;

	env = ls_init_root(ac, av);
	ls_error_null_parameter(env, ac, av);
	ls_parse_argument(env, ac, av);
	ls_display(env);
	ls_exit(env);
	return (0);
}
