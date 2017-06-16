/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_handle_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 21:56:55 by heynard           #+#    #+#             */
/*   Updated: 2017/06/16 12:13:00 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ls_get_date_hours(char *date, char *tmp, int *i, int *j)
{
	(*i) = 11;
	while ((*i) < 16)
	{
		date[(*j)++] = tmp[(*i)];
		(*i)++;
	}
}

static void		ls_get_date_year(char *date, char *tmp, int *i, int *j)
{
	date[(*j)++] = ' ';
	(*i) = 20;
	while ((*i) < 24)
	{
		date[(*j)++] = tmp[(*i)];
		(*i)++;
	}
}

static char		*ls_get_date(t_root *root, t_info *info)
{
	char		*date;
	char		*tmp;
	int			j;
	int			i;

	i = 4;
	j = 0;
	if ((date = (char *)malloc(sizeof(char) * 13)) == NULL)
		ls_undifined_error(root);
	tmp = ctime((const time_t *)(&(info->date_cmp)));
	while (i < 11)
	{
		date[j++] = tmp[i];
		i++;
	}
	if (info->date_cmp < time(0) - 15778800 ||
		info->date_cmp > time(0) + 15778800)
		ls_get_date_year(date, tmp, &i, &j);
	else
		ls_get_date_hours(date, tmp, &i, &j);
	date[j] = '\0';
	return (date);
}

static void		ls_set_list_to_null(t_info *info)
{
	info->date = NULL;
	info->group = NULL;
	info->user = NULL;
	info->mode = NULL;
}

void			ls_handle_list(t_root *root, t_info *info, struct stat *buffer)
{
	info->blocks = buffer->st_blocks;
	info->size = buffer->st_size;
	info->date_cmp = buffer->st_mtime;
	info->minor = 0;
	info->major = 0;
	ls_set_list_to_null(info);
	info->mode = ls_get_mode(root, info, buffer);
	if (root->opt->l || root->opt->g)
	{
		info->links = buffer->st_nlink;
		info->date = ls_get_date(root, info);
		if (getgrgid(buffer->st_gid) != NULL)
			info->group = ft_strdup(getgrgid(buffer->st_gid)->gr_name);
		else
			info->group = ft_itoa(buffer->st_gid);
		if (getpwuid(buffer->st_uid) != NULL)
			info->user = ft_strdup(getpwuid(buffer->st_uid)->pw_name);
		else
			info->user = ft_itoa(buffer->st_uid);
		if (info->type == 'c' || info->type == 'b')
		{
			info->minor = minor(buffer->st_rdev);
			info->major = major(buffer->st_rdev);
		}
	}
}
