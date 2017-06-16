/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_handle_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:52:30 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 00:53:33 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char			ls_handle_file_type(struct dirent *current)
{
	if (current->d_type == DT_FIFO)
		return ('p');
	else if (current->d_type == DT_SOCK)
		return ('s');
	else if (current->d_type == DT_DIR)
		return ('d');
	else if (current->d_type == DT_CHR)
		return ('c');
	else if (current->d_type == DT_BLK)
		return ('b');
	else if (current->d_type == DT_REG)
		return ('-');
	else if (current->d_type == DT_LNK)
		return ('l');
	else if (current->d_type == DT_WHT)
		return ('w');
	return ('d');
}

void				ls_inner_add_content(t_dir_list *new,
										t_files_list *file, t_options *opt)
{
	t_files_list		*tmp;
	t_files_list		*sort;

	tmp = new->content;
	if (ls_cmp_files(tmp, file, opt) > 0)
	{
		file->next = tmp;
		new->content = file;
		return ;
	}
	while (tmp->next != NULL)
	{
		sort = tmp;
		tmp = tmp->next;
		if (ls_cmp_files(tmp, file, opt) > 0)
		{
			sort->next = file;
			file->next = tmp;
			return ;
		}
	}
	tmp->next = file;
}

static void			ls_handle_dir_recursive(t_root *root, const char *path,
											t_dir_list *lst,
											struct stat *buffer)
{
	t_dir_list		*new;

	if ((new = malloc(sizeof(t_dir_list))) == NULL)
		ls_undifined_error(root);
	new->next = NULL;
	new->dir = NULL;
	new->content = NULL;
	new->size = buffer->st_size;
	ls_check_right_on_dir(new, buffer);
	new->path = ft_strdup(path);
	new->name = ft_strdup(path);
	if (lst->dir == NULL)
		lst->dir = new;
	else
		lst->dir = ls_inner_add_dir(lst->dir, new, root->opt);
}

void				ls_add_content(t_root *root, t_dir_list *new,
										struct dirent *current)
{
	t_files_list	*file;
	t_info			*info;
	struct stat		buf;

	file = ls_malloc_files_list(root);
	if ((info = malloc(sizeof(t_info))) == NULL)
		ls_undifined_error(root);
	info->name = ft_strdup(current->d_name);
	info->type = ls_handle_file_type(current);
	ls_handle_path(info, new);
	stat(info->path, &buf);
	if (info->type == 'l')
		lstat(info->path, &buf);
	info->type = ls_get_type(&buf);
	ls_handle_list(root, info, &buf);
	if (info->type == 'd' && root->opt->rec && info->name[0] != '.')
		ls_handle_dir_recursive(root, info->path, new, &buf);
	ls_handle_blocks(new, info, root);
	file->info = info;
	file->next = NULL;
	if (!(new->content))
		new->content = file;
	else
		ls_inner_add_content(new, file, root->opt);
}

void				ls_handle_content(t_root *root, t_dir_list *new)
{
	DIR				*current;
	struct dirent	*content;
	t_dir_list		*tmp;

	if (new->norightx || new->norightr)
		return ;
	if ((current = opendir(new->path)) == NULL)
	{
		new->norightoth = 1;
		return ;
	}
	while ((content = readdir(current)) != NULL)
		ls_add_content(root, new, content);
	if (closedir(current) < 0)
		ls_undifined_error(root);
	if (root->opt->rec)
	{
		tmp = new->dir;
		while (tmp != NULL)
		{
			ls_handle_content(root, tmp);
			tmp = tmp->next;
		}
	}
}
