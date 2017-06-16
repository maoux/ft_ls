/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 23:44:20 by heynard           #+#    #+#             */
/*   Updated: 2017/06/14 23:44:42 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files_list		*ls_malloc_files_list(t_root *root)
{
	t_files_list	*file;

	if ((file = malloc(sizeof(t_files_list))) == NULL)
		ls_undifined_error(root);
	return (file);
}

void				ls_handle_blocks(t_dir_list *new,
										t_info *info, t_root *root)
{
	if ((root->opt->aless && ft_strcmp(".", info->name) &&
		ft_strcmp(info->name, "..")) || (root->opt->a && info->name[0] == '.')
		|| info->name[0] != '.')
		new->blocks += info->blocks;
}

struct stat			ls_stat(t_options *opt, struct stat buffer,
									char *arg, int *t)
{
	if (opt->l)
		*t = lstat(arg, &buffer);
	else
		*t = stat(arg, &buffer);
	return (buffer);
}
