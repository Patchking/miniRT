/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaggard <ohaggard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:42:13 by ohaggard          #+#    #+#             */
/*   Updated: 2022/01/21 16:42:13 by ohaggard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minirt.h"

// void	cord_sum(t_point3 *p0, t_point3 *p1)
// {
// 	p0->x += p1->x;
// 	p0->y += p1->y;
// 	p0->z += p1->z;
// }

// int	color_blend_int_t(t_color c0, t_color c1, double ratio)
// {
// 	int	out;

// 	out = (int)(c0.r * ratio + c1.r * (1 - ratio)) << 16;
// 	out |= (int)(c0.g * ratio + c1.g * (1 - ratio)) << 8;
// 	out |= (int)(c0.b * ratio + c1.b * (1 - ratio));
// 	return (out);
// }

t_color	color_blend(t_color c0, t_color c1, double ratio)
{
	t_color	out;

	out.t = 0;
	out.r = (int)(c0.r * ratio + c1.r * (1.0 - ratio));
	out.g = (int)(c0.g * ratio + c1.g * (1.0 - ratio));
	out.b = (int)(c0.b * ratio + c1.b * (1.0 - ratio));
	return (out);
}

t_color	color_multv(t_color c, double v)
{
	t_color	out;

	out.t = 0;
	out.r = v * c.r;
	out.g = v * c.g;
	out.b = v * c.b;
	return (out);
}

t_color	color(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b)
{
	t_color	c;

	c.t = t;
	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

// int	create_color_t(t_color in)
// {
// 	return (in.t << 24 | in.r << 16 | in.g << 8 | in.b);
// }
