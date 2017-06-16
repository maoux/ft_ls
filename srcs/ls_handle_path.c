/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_handle_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 17:01:13 by heynard           #+#    #+#             */
/*   Updated: 2017/06/14 23:44:40 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				ls_handle_path(t_info *info, t_dir_list *new)
{
	char			*tmp;

	if (!ft_strcmp(new->path, "/"))
	{
		info->path = ft_strjoin(new->path, info->name);
		return ;
	}
	tmp = ft_strjoin("/", info->name);
	info->path = ft_strjoin(new->path, tmp);
	free(tmp);
}
