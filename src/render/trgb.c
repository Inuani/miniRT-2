/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lskraber <lskraber@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:05:42 by lskraber          #+#    #+#             */
/*   Updated: 2023/03/12 14:08:22 by lskraber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec	decimal_to_rgb(int color)
{
	t_vec	rgbcolor;

	rgbcolor.x = (color >> 16) & 0xFF;
	rgbcolor.y = (color >> 8) & 0xFF;
	rgbcolor.z = color & 0xFF;
	return (rgbcolor);
}

t_vec	add_colors(t_vec c1, t_vec c2, float intensity)
{
	t_vec	c_res;

	c_res.x = c1.x + c2.x * intensity;
	c_res.y = c1.y + c2.y * intensity;
	c_res.z = c1.z + c2.z * intensity;
	return (c_res);
}

t_vec	add_color(t_vec c1, t_vec c2)
{
	t_vec	c_res;

	c_res.x = c1.x + c2.x;
	c_res.y = c1.y + c2.y;
	c_res.z = c1.z + c2.z;
	return (c_res);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
