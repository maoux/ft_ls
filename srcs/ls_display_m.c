/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 22:17:20 by heynard           #+#    #+#             */
/*   Updated: 2017/06/15 11:58:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			ls_display_content_m_a(t_root *root, int *test, int *disp,
											t_files_list *tmp)
{
	int				len;

	if (root->opt->a || (root->opt->aless && ft_strcmp(tmp->info->name, ".")
						&& ft_strcmp(tmp->info->name, "..")))
	{
		len = ft_strlen(tmp->info->name);
		if (len + 2 + (*disp) > root->win_width)
		{
			*disp = 0;
			ft_putchar('\n');
		}
		ft_printf("%s%s%s", ls_color(tmp, root->opt), tmp->info->name,
								ls_clear(root->opt));
		if (tmp->next != NULL)
			ft_putstr(", ");
		*disp += len + 2;
		*test = TRUE;
	}
}

static void			ls_display_content_m_oth(t_root *root, int *test,
											int *disp, t_files_list *tmp)
{
	int				len;

	len = ft_strlen(tmp->info->name);
	if (len + 3 + (*disp) > root->win_width)
	{
		*disp = 0;
		ft_putchar('\n');
	}
	ft_printf("%s%s%s", ls_color(tmp, root->opt), tmp->info->name,
									ls_clear(root->opt));
	if (tmp->next != NULL)
		ft_putstr(", ");
	*disp += len + 2;
	*test = TRUE;
}

int					ls_get_window_size(void)
{
	struct winsize	sizes;

	ioctl(0, TIOCGWINSZ, &sizes);
	return (sizes.ws_col);
}

void				ls_display_content_m(t_root *root, t_files_list *content)
{
	t_files_list	*tmp;
	int				test;
	int				disp;

	tmp = content;
	disp = 0;
	test = FALSE;
	root->win_width = ls_get_window_size();
	while (tmp != NULL)
	{
		if (tmp->info->name[0] == '.')
			ls_display_content_m_a(root, &test, &disp, tmp);
		else
			ls_display_content_m_oth(root, &test, &disp, tmp);
		tmp = tmp->next;
	}
	if (test)
		ft_putchar('\n');
}
