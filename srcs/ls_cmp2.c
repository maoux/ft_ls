/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:27:48 by heynard           #+#    #+#             */
/*   Updated: 2017/06/16 15:28:12 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					ls_cmp_size_files(t_files_list *f1,
									t_files_list *f2, t_options *opt)
{
	if (f1->info->size > f2->info->size)
	{
		if (opt->r)
			return (1);
		return (-1);
	}
	else if (f1->info->size == f2->info->size)
	{
		if (opt->r)
			return (-1 * ft_strcmp(f1->info->name, f2->info->name));
		return (ft_strcmp(f1->info->name, f2->info->name));
	}
	else
	{
		if (opt->r)
			return (-1);
		return (1);
	}
}
