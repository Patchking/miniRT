/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:01:15 by cojacque          #+#    #+#             */
/*   Updated: 2022/11/03 21:29:00 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	cyl_intersect_part_2(t_v3 ro, t_v3 rd, t_obj *o, t_cylinder *c)
{
	c->h = sqrt(c->h);
	c->t = (-c->k1 - c->h) / c->k2;
	c->y = c->baoc + c->t * c->bard;
	if (c->y > 0 && c->y < c->baba)
		return (cyl_intersect1(&ro, &rd, c, o));
	if (c->y < 0)
		c->t = -c->baoc / c->bard;
	else
		c->t = (c->baba - c->baoc) / c->bard;
	if (fabs(c->k1 + c->k2 * c->t) < c->h)
		return (cyl_intersect2(&ro, &rd, c, o));
	return (DBL_MAX);
}
