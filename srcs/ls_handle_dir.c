/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_handle_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:29:33 by heynard           #+#    #+#             */
/*   Updated: 2017/06/14 23:36:45 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_check_right_on_dir(t_dir_list *new, struct stat *buf)
{
	if (!(S_IRUSR & buf->st_mode))
		new->norightr = TRUE;
	else
		new->norightr = FALSE;
	if (!(S_IXUSR & buf->st_mode))
		new->norightx = TRUE;
	else
		new->norightx = FALSE;
	new->norightoth = FALSE;
}

t_dir_list		*ls_inner_add_dir(t_dir_list *list,
									t_dir_list *new, t_options *opt)
{
	t_dir_list	*tmp;
	t_dir_list	*sort;

	tmp = list;
	if (ls_cmp_dir(tmp, new, opt) > 0)
	{
		new->next = list;
		return (new);
	}
	while (tmp->next != NULL)
	{
		sort = tmp;
		tmp = tmp->next;
		if (ls_cmp_dir(tmp, new, opt) > 0)
		{
			sort->next = new;
			new->next = tmp;
			return (list);
		}
	}
	tmp->next = new;
	return (list);
}

void			ls_add_dir(t_root *root, struct stat *buf, const char *name)
{
	t_dir_list	*new;

	if ((new = malloc(sizeof(t_dir_list))) == NULL)
		ls_undifined_error(root);
	new->name = ft_strdup(name);
	new->path = ft_strdup(name);
	new->size = buf->st_size;
	new->blocks = 0;
	new->dir = NULL;
	new->content = NULL;
	new->next = NULL;
	ls_check_right_on_dir(new, buf);
	ls_handle_content(root, new);
	if (!(root->dir))
		root->dir = new;
	else
		root->dir = ls_inner_add_dir(root->dir, new, root->opt);
}
