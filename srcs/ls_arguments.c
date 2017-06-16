/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_arguments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:26:26 by heynard           #+#    #+#             */
/*   Updated: 2017/06/16 12:14:31 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			ls_inner_add_file(t_root *root, t_files_list *file)
{
	t_files_list		*sort;
	t_files_list		*tmp;

	tmp = root->files;
	if (ls_cmp_files(tmp, file, root->opt) > 0)
	{
		file->next = tmp;
		root->files = file;
		return ;
	}
	while (tmp->next != NULL)
	{
		sort = tmp;
		tmp = tmp->next;
		if (ls_cmp_files(tmp, file, root->opt) > 0)
		{
			sort->next = file;
			file->next = tmp;
			return ;
		}
	}
	tmp->next = file;
}

static void			ls_add_file(t_root *root, struct stat *buffer,
												const char *name)
{
	t_files_list	*file;
	t_info			*info;

	if ((file = malloc(sizeof(t_files_list))) == NULL)
		ls_undifined_error(root);
	if ((info = malloc(sizeof(t_info))) == NULL)
		ls_undifined_error(root);
	info->path = ft_strdup(name);
	info->name = ft_strdup(info->path);
	info->type = ls_get_type(buffer);
	ls_handle_list(root, info, buffer);
	file->info = info;
	file->next = NULL;
	if (!(root->files))
		root->files = file;
	else
		ls_inner_add_file(root, file);
}

static void			ls_inner_parse_argument(t_root *root, int error)
{
	struct stat		buffer;

	if (root->dir == NULL && root->files == NULL && error)
	{
		stat(".", &buffer);
		ls_add_dir(root, &buffer, ".");
	}
	if (root->dir && root->files)
		root->no_path = 1;
	if (root->dir)
	{
		if (root->dir->next)
			root->no_path = 1;
	}
}

char				ls_get_type(struct stat *buffer)
{
	if (S_ISREG(buffer->st_mode))
		return ('-');
	if (S_ISDIR(buffer->st_mode))
		return ('d');
	if (S_ISCHR(buffer->st_mode))
		return ('c');
	if (S_ISBLK(buffer->st_mode))
		return ('b');
	if (S_ISFIFO(buffer->st_mode))
		return ('p');
	if (S_ISLNK(buffer->st_mode))
		return ('l');
	if (S_ISSOCK(buffer->st_mode))
		return ('s');
	return ('d');
}

void				ls_parse_argument(t_root *root, int ac, char **av)
{
	struct stat		buffer;
	int				error;
	int				test;
	int				isoption;
	int				i;

	i = 0;
	error = 1;
	isoption = 1;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			isoption = 0;
		if (av[i][0] != '-' || !isoption || !ft_strcmp(av[i], "-"))
		{
			buffer = ls_stat(root->opt, buffer, av[i], &test);
			if (test)
				ls_error_file(root, av[i], &error);
			else if (S_ISDIR(buffer.st_mode))
				ls_add_dir(root, &buffer, (const char *)(av[i]));
			else
				ls_add_file(root, &buffer, (const char *)(av[i]));
		}
	}
	ls_inner_parse_argument(root, error);
}
