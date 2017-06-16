/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_handle_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:37:48 by heynard           #+#    #+#             */
/*   Updated: 2017/06/13 18:43:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_max		ls_init_t_max(t_max max)
{
	max.links = 0;
	max.user = 0;
	max.group = 0;
	max.size = 0;
	max.minor = 0;
	max.major = 0;
	return (max);
}

static t_max		ls_calc_list_max(t_max max, t_files_list *tmp)
{
	if (ft_count_digits(tmp->info->links) > max.links)
		max.links = ft_count_digits(tmp->info->links);
	if (ft_strlen(tmp->info->user) > max.user)
		max.user = ft_strlen(tmp->info->user);
	if (ft_strlen(tmp->info->group) > max.group)
		max.group = ft_strlen(tmp->info->group);
	if (ft_count_digits(tmp->info->size) > max.size)
		max.size = ft_count_digits(tmp->info->size);
	return (max);
}

static t_max		ls_calc_device_max(t_max max, t_files_list *tmp)
{
	if (ft_count_digits(tmp->info->minor) > max.minor)
		max.minor = ft_count_digits(tmp->info->minor);
	if (ft_count_digits(tmp->info->major) > max.major)
		max.major = ft_count_digits(tmp->info->major);
	return (max);
}

t_max				ls_calc_max(t_max max,
									t_files_list *content, t_options *opt)
{
	t_files_list	*tmp;

	max = ls_init_t_max(max);
	tmp = content;
	while (tmp != NULL)
	{
		if (tmp->info->name[0] == '.' && !(opt->a))
			;
		else
			max = ls_calc_list_max(max, tmp);
		if (tmp->info->type == 'c' || tmp->info->type == 'b')
			max = ls_calc_device_max(max, tmp);
		tmp = tmp->next;
	}
	return (max);
}
