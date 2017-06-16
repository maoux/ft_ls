/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 21:34:15 by heynard           #+#    #+#             */
/*   Updated: 2017/06/13 22:09:43 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			ls_free_info(t_info *info)
{
	if (info)
	{
		if (info->name)
			free(info->name);
		if (info->path)
			free(info->path);
		if (info->mode)
			free(info->mode);
		if (info->date)
			free(info->date);
		if (info->user)
			free(info->user);
		if (info->group)
			free(info->group);
		free(info);
	}
}

static void			ls_free_files_list(t_files_list *list)
{
	t_files_list	*tmp;
	t_files_list	*next;

	if (list)
	{
		tmp = list;
		while (tmp != NULL)
		{
			ls_free_info(tmp->info);
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
	}
}

static void			ls_free_dir_list(t_dir_list *list)
{
	t_dir_list		*tmp;
	t_dir_list		*next;

	if (list)
	{
		tmp = list;
		while (tmp != NULL)
		{
			if (tmp->name)
				free(tmp->name);
			if (tmp->path)
				free(tmp->path);
			if (tmp->content)
				ls_free_files_list(tmp->content);
			if (tmp->dir)
				ls_free_dir_list(tmp->dir);
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
	}
}

void				ls_exit(t_root *root)
{
	if (root)
	{
		if (root->opt)
			free(root->opt);
		if (root->files)
			ls_free_files_list(root->files);
		if (root->dir)
			ls_free_dir_list(root->dir);
		free(root);
	}
}
