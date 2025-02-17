/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lskraber <lskraber@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/03/13 18:17:40 by lskraber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec	calculate_x_y_ccb(t_ray *ray, t_cylinder *cyl)
{
	float	u;
	float	v;

	u = get_angle_0_to_1(vec_unit(ray->point_at), (t_vec){1, 0, 0});
	if (ray->point_at.y < 0)
		ray->point_at.y *= -1;
	v = fmod(ray->point_at.y, 1);
	if (!((u + v) < 0.5 || ((u + v) > 1 && (u + v) < 1.5)))
		return ((t_vec){255, 255, 255});
	return ((t_vec) cyl->colors);
}

static void	get_u_v_cy(t_cylinder *cy, t_ray *ray, float *u, float *v)
{
	t_vec	hit_vec;
	float	theta;

	hit_vec = vec_subs(ray->point_at, cy->center);
	theta = atan2(hit_vec.x, hit_vec.z);
	if (theta < 0)
		theta += 2 * M_PI;
	*u = theta / (2 * M_PI);
	*v = (hit_vec.y + cy->hgt / 2) / cy->hgt;
}

int	get_color_pixel_cy(int x, int y, t_cylinder *cy)
{
	int	pixel_color;

	pixel_color = cy->pix_arr[y * cy->xpm.wdth + x];
	return (pixel_color);
}

t_vec	get_x_y_color_cy(t_cylinder *cy, float u, float v)
{
	int	x;
	int	y;

	x = (int)(u * cy->xpm.wdth);
	y = (int)((1 - v) * cy->xpm.hgt);
	if ((y * cy->xpm.wdth + x) > cy->xpm.wdth * cy->xpm.hgt)
	{
		x = cy->xpm.wdth - 1;
		y = cy->xpm.hgt - 1;
	}
	return (decimal_to_rgb(cy->pix_arr[y * cy->xpm.wdth + x]));
}

t_vec	set_cy_xpm_color(t_ray *ray, t_cylinder *cy)
{
	t_vec	pixel_color;
	float	u;
	float	v;

	get_u_v_cy(cy, ray, &u, &v);
	pixel_color = get_x_y_color_cy(cy, u, v);
	return (pixel_color);
}
