/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 21:29:25 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 11:46:55 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		ls_inner_parse_options(char *arg, int i, t_options *opt)
{
	if (arg[i] == 'l')
		opt->l = TRUE;
	else if (arg[i] == 'R')
		opt->rec = TRUE;
	else if (arg[i] == 'a')
		opt->a = TRUE;
	else if (arg[i] == 'r')
		opt->r = TRUE;
	else if (arg[i] == 't')
		opt->t = TRUE;
	else if (arg[i] == 'm')
		opt->m = TRUE;
	else if (arg[i] == 'g')
		opt->g = TRUE;
	else if (arg[i] == 'A')
		opt->aless = TRUE;
	else if (arg[i] == 'S')
		opt->ssort = TRUE;
	else if (arg[i] == 'G')
		opt->color = TRUE;
	else if (arg[i] == '1')
		;
	else
		return (FALSE);
	return (TRUE);
}

void			ls_set_options_false(t_options *opt)
{
	opt->l = FALSE;
	opt->rec = FALSE;
	opt->a = FALSE;
	opt->r = FALSE;
	opt->t = FALSE;
	opt->m = FALSE;
	opt->g = FALSE;
	opt->aless = FALSE;
	opt->ssort = FALSE;
	opt->color = FALSE;
}

int				ls_parse_options(t_options *opt, char *arg)
{
	int			i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (ls_inner_parse_options(arg, i, opt))
			i++;
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", arg[i]);
			return (FALSE);
		}
	}
	return (TRUE);
}
