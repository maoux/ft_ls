/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:44:31 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 12:01:38 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			ls_print_line_cb(t_options *opt,
									t_files_list *current, t_max max)
{
	if (opt->g)
	{
		ft_printf("%s %*d %-*s   %*d, %*d %s %s%s%s", current->info->mode,
				max.links, current->info->links,
				max.group, current->info->group,
				max.major, current->info->major,
				max.minor, current->info->minor,
				current->info->date,
				ls_color(current, opt), current->info->name, ls_clear(opt));
	}
	else
	{
		ft_printf("%s %*d %-*s  %-*s   %*d, %*d %s %s%s%s",
				current->info->mode,
				max.links, current->info->links,
				max.user, current->info->user,
				max.group, current->info->group,
				max.major, current->info->major,
				max.minor, current->info->minor,
				current->info->date,
				ls_color(current, opt), current->info->name, ls_clear(opt));
	}
}

static void			ls_print_line_other(t_options *opt,
										t_files_list *current, t_max max)
{
	if (opt->g)
	{
		ft_printf("%s %*d %-*s  %*d %s %s%s%s", current->info->mode,
				max.links, current->info->links,
				max.group, current->info->group,
				max.size, current->info->size,
				current->info->date,
				ls_color(current, opt), current->info->name, ls_clear(opt));
	}
	else
	{
		ft_printf("%s %*d %-*s  %-*s  %*d %s %s%s%s", current->info->mode,
				max.links, current->info->links,
				max.user, current->info->user,
				max.group, current->info->group,
				max.size, current->info->size,
				current->info->date,
				ls_color(current, opt), current->info->name, ls_clear(opt));
	}
}

static void			ls_print_line(t_root *root, t_files_list *current,
									t_options *opt, t_max max)
{
	size_t			sizeoflink;
	char			*link;

	if (current->info->type == 'c' || current->info->type == 'b')
		ls_print_line_cb(opt, current, max);
	else
	{
		if (max.minor && max.major)
			max.size = (max.major + max.minor + 3 > max.size ?
						max.major + max.minor + 3 : max.size);
		ls_print_line_other(opt, current, max);
	}
	if (current->info->type == 'l')
	{
		if ((link = (char *)malloc(sizeof(char) * 255)) == NULL)
			ls_undifined_error(root);
		sizeoflink = readlink(current->info->path, link, 255);
		link[sizeoflink] = '\0';
		ft_printf(" -> %s", link);
		free(link);
	}
	ft_printf("\n");
}

int					ls_print_total(t_dir_list *dir, t_options *opt)
{
	t_files_list	*tmp;

	if (dir->norightr || dir->norightx || dir->norightoth)
		return (0);
	if (opt->a)
		return (1);
	tmp = dir->content;
	while (tmp != NULL)
	{
		if (tmp->info->name[0] != '.')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void				ls_display_content_l(t_root *root, t_files_list *content,
											t_options *opt, t_max max)
{
	t_files_list	*tmp;

	tmp = content;
	while (tmp != NULL)
	{
		if (tmp->info->name[0] == '.')
		{
			if (opt->a)
				ls_print_line(root, tmp, opt, max);
			else if (opt->aless && ft_strcmp(tmp->info->name, ".")
						&& ft_strcmp(tmp->info->name, ".."))
				ls_print_line(root, tmp, opt, max);
		}
		else
			ls_print_line(root, tmp, opt, max);
		tmp = tmp->next;
	}
}
