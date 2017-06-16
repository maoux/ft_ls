/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_bonus_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 11:48:37 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 12:21:43 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char			*ls_clear(t_options *opt)
{
	if (opt->color)
		return (CLEAR);
	return ("");
}

char			*ls_color(t_files_list *file, t_options *opt)
{
	if (opt->color)
	{
		if (file->info->type == 'd')
			return (CYAN);
		if (file->info->type == 'l')
			return (PINK);
		if (file->info->type == 'p')
			return (YELLOW);
		if (file->info->type == 'b')
			return (ft_strjoin(SBLUE, BLUE));
		if (file->info->type == 'c')
			return (ft_strjoin(SYEL, BLUE));
		if (file->info->type == '-' && file->info->mode[3] == 'x')
			return (RED);
	}
	return ("");
}
