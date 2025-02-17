/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	cylinder_init(t_data *d, t_cylinder *cy)
{
	cy->h = vec_subs(vec_add(cy->center,
				vec_scale(cy->hgt, cy->orient)), cy->center);
	cy->cam2cyl = vec_subs(d->objs[1]->u_data.camera.pos, cy->center);
	cy->top_cyl = vec_add(cy->center, vec_scale(cy->hgt, cy->orient));
}

void	cyl_light_hit(t_ray *ray, t_data *data, t_cylinder cyl, t_light light)
{
	if (!light_hit_objs(data, ray->point_at, light))
		return ;
	ray->shiny = 100;
	phong(data, ray, light, cyl.colors);
}

float	cylinder_eman(t_data *data, t_ray *ray, t_cylinder cyl)
{
	int		i;
	t_vec	dist;
	t_vec	proj;
	t_vec	ambient_color;

	dist = vec_subs(ray->point_at, cyl.center);
	proj = vec_subs(dist, vec_scale(vec_dot(dist, cyl.orient), cyl.orient));
	ray->normal = vec_unit(proj);
	if (cyl.flg == 2)
		cyl.colors = set_cy_xpm_color(ray, &cyl);
	else if (cyl.flg == 1)
		cyl.colors = calculate_x_y_ccb(ray, &cyl);
	i = 0;
	while (i < data->count.l_count)
		cyl_light_hit(ray, data, cyl, data->objs[2 + i++]->u_data.light);
	ambient_color = add_color(vec_scale(K_LIGHT, cyl.colors),
			vec_scale(1 - K_LIGHT, data->objs[0]->u_data.ambiant.colors));
	data->final_color = add_colors(data->final_color,
			ambient_color, data->objs[0]->u_data.ambiant.light_ratio);
	return (0);
}

float	cyl_intersec_delta(t_vec ray_dir, t_cylinder *cy, t_vec origin)
{
	float	t[3];
	float	max;
	t_vec	len;
	t_vec	point_at;

	t[1] = (-cy->b - sqrt(cy->delta)) / (2.0 * cy->a);
	t[2] = (-cy->b + sqrt(cy->delta)) / (2.0 * cy->a);
	if (t[2] < 0)
		return (-1);
	if (t[1] > 0)
		t[0] = t[1];
	max = sqrtf(powf(cy->hgt / 2, 2) + powf(cy->radius, 2));
	point_at = vec_add(origin, vec_scale(t[0], ray_dir));
	len = vec_subs(point_at, cy->center);
	if (vec_len(len) > max)
		t[0] = t[2];
	point_at = vec_add(origin, vec_scale(t[0], ray_dir));
	len = vec_subs(point_at, cy->center);
	if (vec_len(len) > max)
		return (-1);
	return (t[0]);
}

float	hit_cylinder(t_vec ray_dir, t_cylinder *cy, t_vec origin, t_vec ori2cy)
{
	cy->a = vec_dot(ray_dir, ray_dir) - powf(vec_dot(ray_dir, cy->orient), 2);
	cy->b = 2.0 * ((vec_dot(ray_dir, ori2cy))
			- (vec_dot(ray_dir, cy->orient) * vec_dot(ori2cy, cy->orient)));
	cy->c = vec_dot(ori2cy, ori2cy) - powf(vec_dot(ori2cy, cy->orient), 2)
		- powf(cy->radius, 2.0);
	cy->delta = (cy->b * cy->b) - (4 * cy->a * cy->c);
	if (cy->delta == 0.0)
		return (-(cy->b / (2.0 * cy->a)));
	else if (cy->delta > 0)
		return (cyl_intersec_delta(ray_dir, cy, origin));
	return (-1.0);
}

// int	is_inside_cyl(t_cylinder *cyl, t_light *light, t_ray *ray)
// {
// 	// t_vec	h_point;
// 	// float	cyl_dist;
// 	// float	cyl_radius;
// 	// float	orth_distance;

// 	// h_point = vec_add(cyl.center, vec_scale(cyl.hgt, cyl.orient));
// 	// cyl_dist = vec_dot(vec_subs(ray->point_at, h_point), cyl.orient);
// 	// cyl_radius = (cyl_dist / cyl.hgt) * cyl.radius;
// 	// orth_distance = vec_len(vec_subs(vec_subs(ray->point_at, h_point),
// 	// 			vec_scale(cyl_dist, cyl.orient)));
// 	// return (orth_distance <= cyl_radius);

// 	dist = vec_subs(ray->point_at, cyl.center);
// 	proj = vec_subs(dist, vec_scale(vec_dot(dist, cyl.orient), cyl.orient));

// 	t_vec	c2hit;
// 	t_vec	l2hit;

// 	c2hit = vec_subs(cyl->center, ray->point_at);
// 	l2hit = vec_subs(cyl->center, light->pos);

// 	float	len_lgt2cy;

// 	len_lgt2cy = vec_len(vec_subs(light->pos, cyl->center));

// 	if ()
// }

// void	cyl_light_hit(t_ray *ray, t_data *data, t_cylinder cyl, t_light light)
// {
// 	// t_vec	lght2cy;
// 	// t_vec	lght2hit;

// 	// lght2cy = vec_subs(cyl.center, light.pos);
// 	// lght2hit = vec_unit(vec_subs(ray->point_at, light.pos));
// 	// // cyl.lght_flg = 0;
// 	// hit_cylinder2(lght2hit, &cyl, light.pos, lght2cy);
// 	if (!light_hit_objs(data, ray->point_at, light))
// 		return ;
// 	// printf("flg : %d\n", cyl.lght_flg);
// 	// if (cyl.lght_flg == 1)
// 	// 	return ;
// 	// if (!is_inside_cyl(&ray, &cyl, &ray))
// 	// 	return ;
// 	ray->shiny = 100;
// 	phong(data, ray, light, cyl.colors);
// }

// float	cyl_intersec_delta2(t_vec ray_dir, t_cylinder *cy, t_vec origin)
// {
// 	float	t[3];
// 	float	max;
// 	t_vec	len;
// 	t_vec	point_at;

// 	cy->lght_flg = 0;
// 	t[1] = (-cy->b - sqrt(cy->delta)) / (2.0 * cy->a);
// 	t[2] = (-cy->b + sqrt(cy->delta)) / (2.0 * cy->a);
// 	if (t[2] < 0)
// 		return (-1);
// 	// printf("ici2\n");
// 	if (t[1] > 0)
// 		t[0] = t[1];
// 	// else
// 	// {
// 	// 	printf("ici\n");
// 	// 	t[0] = t[2];
// 	// 	cy->lght_flg = 1;
// 	// }
// 	max = sqrtf(powf(cy->hgt / 2, 2) + powf(cy->radius, 2));
// 	point_at = vec_add(origin, vec_scale(t[0], ray_dir));
// 	len = vec_subs(point_at, cy->center);
// 	if (vec_len(len) > max)
// 	{
// 		printf("ici2\n");
// 		t[0] = t[2];
// 		cy->lght_flg = 1;
// 	}
// 	point_at = vec_add(origin, vec_scale(t[0], ray_dir));
// 	len = vec_subs(point_at, cy->center);
// 	if (vec_len(len) > max)
// 		return (-1);
// 	return (t[0]);
// }
