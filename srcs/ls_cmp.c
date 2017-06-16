/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 17:25:30 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 01:09:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int			ls_cmp_date(t_dir_list *d1, t_dir_list *d2)
{
	struct stat		buf1;
	struct stat		buf2;

	stat(d1->path, &buf1);
	stat(d2->path, &buf2);
	if (buf1.st_mtime < buf2.st_mtime)
		return (1);
	if (buf1.st_mtime == buf2.st_mtime)
		return (ft_strcmp(d1->name, d2->name));
	return (-1);
}

static int			ls_cmp_date_file(t_files_list *f1,
									t_files_list *f2, t_options *opt)
{
	if (f1->info->date_cmp < f2->info->date_cmp)
	{
		if (opt->r)
			return (-1);
		return (1);
	}
	else if (f1->info->date_cmp == f2->info->date_cmp)
	{
		if (opt->r)
			return (-1 * ft_strcmp(f1->info->name, f2->info->name));
		return (ft_strcmp(f1->info->name, f2->info->name));
	}
	else
	{
		if (opt->r)
			return (1);
		return (-1);
	}
	return (0);
}

static int			ls_cmp_size(t_dir_list *d1, t_dir_list *d2, t_options *opt)
{
	if (d1->size > d2->size)
		return (-1);
	else if (d1->size == d2->size)
	{
		if (opt->r)
			return (-1 * ft_strcmp(d1->name, d2->name));
		return (ft_strcmp(d1->name, d2->name));
	}
	else
		return (1);
}

int					ls_cmp_dir(t_dir_list *d1, t_dir_list *d2, t_options *opt)
{
	if (opt->ssort)
	{
		if (opt->r)
			return (-ls_cmp_size(d1, d2, opt));
		else
			return (ls_cmp_size(d1, d2, opt));
	}
	else if (opt->t)
	{
		if (opt->r)
			return (-ls_cmp_date(d1, d2));
		else
			return (ls_cmp_date(d1, d2));
	}
	else
	{
		if (opt->r)
			return (-ft_strcmp(d1->name, d2->name));
		else
			return (ft_strcmp(d1->name, d2->name));
	}
	return (0);
}

int					ls_cmp_files(t_files_list *f1,
								t_files_list *f2, t_options *opt)
{
	if (opt->ssort)
		return (ls_cmp_size_files(f1, f2, opt));
	if (opt->t)
		return (ls_cmp_date_file(f1, f2, opt));
	else
	{
		if (opt->r)
			return (-ft_strcmp(f1->info->name, f2->info->name));
		else
			return (ft_strcmp(f1->info->name, f2->info->name));
	}
	return (0);
}
