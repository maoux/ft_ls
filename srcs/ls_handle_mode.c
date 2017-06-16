/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_handle_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 15:25:40 by heynard           #+#    #+#             */
/*   Updated: 2017/06/14 21:54:44 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ls_inner_set_right(char *mode, int *i, mode_t st)
{
	if (st & S_IWGRP)
		mode[(*i)++] = 'w';
	else
		mode[(*i)++] = '-';
	if (st & S_ISGID)
		mode[(*i)++] = 's';
	else if (st & S_IXGRP)
		mode[(*i)++] = 'x';
	else
		mode[(*i)++] = '-';
	if (st & S_IROTH)
		mode[(*i)++] = 'r';
	else
		mode[(*i)++] = '-';
	if (st & S_IWOTH)
		mode[(*i)++] = 'w';
	else
		mode[(*i)++] = '-';
	if (st & S_ISVTX)
		mode[(*i)++] = 't';
	else if (st & S_IXOTH)
		mode[(*i)++] = 'x';
	else
		mode[(*i)++] = '-';
}

static void		ls_set_right(char *mode, int *i, mode_t st)
{
	if (st & S_IRUSR)
		mode[(*i)++] = 'r';
	else
		mode[(*i)++] = '-';
	if (st & S_IWUSR)
		mode[(*i)++] = 'w';
	else
		mode[(*i)++] = '-';
	if (st & S_ISUID)
		mode[(*i)++] = 's';
	else if (st & S_IXUSR)
		mode[(*i)++] = 'x';
	else
		mode[(*i)++] = '-';
	if (st & S_IRGRP)
		mode[(*i)++] = 'r';
	else
		mode[(*i)++] = '-';
	ls_inner_set_right(mode, i, st);
}

static char		ls_set_attr(t_info *info)
{
	char		ret;
	acl_t		acl;
	acl_entry_t	entry;

	ret = ' ';
	if (listxattr(info->path, NULL, 0, XATTR_NOFOLLOW) == -1)
	{
		if (errno == EPERM || errno == EACCES || errno == EFAULT)
			return (ret);
	}
	else if (listxattr(info->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		ret = '@';
	else
	{
		acl = acl_get_file(info->path, ACL_TYPE_EXTENDED);
		if (acl)
		{
			acl_free(acl);
			acl = NULL;
			ret = '+';
		}
	}
	return (ret);
}

char			*ls_get_mode(t_root *root, t_info *info, struct stat *buffer)
{
	char		*mode;
	int			i;

	if ((mode = (char *)malloc(sizeof(char) * 13)) == NULL)
		ls_undifined_error(root);
	i = 0;
	mode[i++] = info->type;
	ls_set_right(mode, &i, buffer->st_mode);
	mode[i++] = ls_set_attr(info);
	mode[i] = '\0';
	return (mode);
}
