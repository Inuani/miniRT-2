/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_eman.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lskraber <lskraber@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/03/19 17:48:24 by lskraber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	get_plane(t_data *d)
{
	t_object	*tmp;
	int			i;

	i = 2 + d->count.l_count + d->count.sp_count;
	tmp = d->chaos;
	while (tmp)
	{
		if (tmp->type == PLANE)
		{
			d->objs[i] = tmp;
			i++;
		}
		tmp = tmp->next;
	}
}

void	pl_img_init(t_data *d, t_tok **lst, t_plane *cur)
{
	char	*xpm;

	xpm = NULL;
	*lst = (*lst)->next;
	set_xpm_path(&xpm, &(*lst)->s);
	cur->xpm.img = mlx_xpm_file_to_image(d->mlx, xpm,
			&cur->xpm.wdth, &cur->xpm.hgt);
	if (cur->xpm.img == NULL)
		exit_err(ERR_XPM_IMG, 1);
	cur->xpm.addr = mlx_get_data_addr(cur->xpm.img,
			&cur->xpm.bits_per_pixel, &cur->xpm.line_length, &cur->xpm.endian);
	cur->pix_arr = set_pixel_color_array(d,
			&cur->xpm, cur->xpm.hgt, cur->xpm.wdth);
	free(xpm);
}

void	set_plane_prop(t_tok **lst, t_plane *inst)
{
	*lst = (*lst)->next;
	inst->point.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->point.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->point.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->orient.z = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.x = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.y = ft_atof((*lst)->s);
	*lst = (*lst)->next;
	inst->colors.z = ft_atof((*lst)->s);
	inst->orient = vec_unit(inst->orient);
	inst->pix_arr = NULL;
}

int	add_plane(t_data *d, t_tok *lst)
{
	t_object	*new;
	t_plane		inst;
	int			nb;

	nb = calc_nb_prop(lst);
	if (nb != 9 && nb != 10)
		exit_error(ERR_PROPERTIES, 1);
	only_one_zero_type(lst);
	inst.flg = 0;
	set_plane_prop(&lst, &inst);
	if (nb == 10)
	{
		if (!ft_strncmp(lst->next->s, "damier", 6))
			inst.flg = 1;
		else
		{
			pl_img_init(d, &lst, &inst);
			inst.flg = 2;
		}
	}
	new = create_object(PLANE, &inst);
	add_object_to_list(&d->chaos, new);
	free_tok(d);
	return (1);
}
