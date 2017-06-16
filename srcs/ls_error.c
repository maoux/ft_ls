/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 21:44:25 by heynard           #+#    #+#             */
/*   Updated: 2017/06/14 12:46:28 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_undifined_error(t_root *root)
{
	perror("ft_ls");
	if (root)
		ls_exit(root);
	exit(1);
}

void		ls_error_null_parameter(t_root *root, int ac, char **av)
{
	int		i;

	i = ac;
	while (ac--)
	{
		if (av[ac][0] == '\0')
		{
			ft_printf("ft_ls: fts_open: No such file or directory\n");
			if (root)
				ls_exit(root);
			exit(1);
		}
	}
}

void		ls_error_file(t_root *root, char *arg, int *error)
{
	ft_printf("ft_ls: %s: No such file or directory\n", arg);
	root->no_path = 1;
	*error = 0;
}
