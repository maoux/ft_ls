/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:56:03 by heynard           #+#    #+#             */
/*   Updated: 2017/06/16 12:11:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			ls_display_content(t_files_list *content, t_options *opt)
{
	t_files_list	*tmp;

	tmp = content;
	while (tmp != NULL)
	{
		if (tmp->info->name[0] == '.')
		{
			if (opt->a)
				ft_printf("%s%s%s\n", ls_color(tmp, opt),
									tmp->info->name, ls_clear(opt));
			else if (opt->aless && ft_strcmp(tmp->info->name, ".") &&
						ft_strcmp(tmp->info->name, ".."))
				ft_printf("%s%s%s\n", ls_color(tmp, opt),
									tmp->info->name, ls_clear(opt));
		}
		else
		{
			ft_printf("%s%s%s\n", ls_color(tmp, opt),
							tmp->info->name, ls_clear(opt));
		}
		tmp = tmp->next;
	}
}

static t_max		ls_init_display(t_dir_list *tmp_dir, int no_path,
											t_root *root, t_max max)
{
	if (no_path > 0)
		ft_printf("%s:\n", tmp_dir->path);
	if ((root->opt->l || root->opt->g) && ls_print_total(tmp_dir, root->opt))
	{
		max = ls_calc_max(max, tmp_dir->content, root->opt);
		ft_printf("total %d\n", tmp_dir->blocks);
	}
	if (tmp_dir->norightx || tmp_dir->norightr || tmp_dir->norightoth)
		ft_printf("ft_ls: %s: Permission denied\n", tmp_dir->path);
	else
	{
		if (root->opt->l || root->opt->g)
			ls_display_content_l(root, tmp_dir->content, root->opt, max);
		else if (root->opt->m)
			ls_display_content_m(root, tmp_dir->content);
		else
			ls_display_content(tmp_dir->content, root->opt);
	}
	return (max);
}

static void			ls_recursive_display(t_root *root, t_dir_list *dir,
											int no_path, t_options *opt)
{
	t_dir_list		*tmp_dir;
	t_max			max;

	tmp_dir = dir;
	while (tmp_dir != NULL)
	{
		max = ls_init_display(tmp_dir, no_path, root, max);
		if (tmp_dir->dir != NULL)
		{
			ft_printf("\n");
			ls_recursive_display(root, tmp_dir->dir, 1, opt);
		}
		tmp_dir = tmp_dir->next;
		if (tmp_dir != NULL)
			ft_printf("\n");
	}
}

void				ls_display(t_root *root)
{
	t_max			max;

	if (root->files)
	{
		if (root->opt->l || root->opt->g)
		{
			max = ls_calc_max(max, root->files, root->opt);
			ls_display_content_l(root, root->files, root->opt, max);
		}
		else if (root->opt->m)
			ls_display_content_m(root, root->files);
		else
			ls_display_content(root->files, root->opt);
		if (root->dir)
			ft_printf("\n");
	}
	ls_recursive_display(root, root->dir, root->no_path, root->opt);
}
