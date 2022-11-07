/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:01:15 by cojacque          #+#    #+#             */
/*   Updated: 2022/11/07 18:44:22 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"
#include "../header/parse.h"

void	parse_sphere(t_store *st)
{
	t_obj	*sphere;

	if (count_split(st->split) != 4)
		ft_error(st, "Error\nParse error. Sphere has 3 params\n");
	sphere = (t_obj *)malloc(sizeof(t_obj));
	sphere->type = CIRCLE;
	sphere->pos = str_to_vec(st->split[1], st);
	sphere->par1 = ft_atof(st->split[2]);
	sphere->color = split_rgb(st->split[3], st);
	if (sphere->par1 <= 0)
		ft_error(st, "Error\nRadius of sphere should be more then 0\n");
	push_back(&st->scobj, sphere);
	st->sp_parsed = 1;
}

void	parse_plane(t_store *st)
{
	t_obj	*plane;

	if (count_split(st->split) != 4)
		ft_error(st, "Error\nParse error. Plane has 3 params\n");
	plane = (t_obj *)malloc(sizeof(t_obj));
	plane->type = PLAIN;
	plane->pos = str_to_vec(st->split[1], st);
	plane->ang = str_to_vec(st->split[2], st);
	plane->ang = v3_norm(plane->ang);
	plane->par1 = -v3_dot(plane->pos, plane->ang);
	plane->color = split_rgb(st->split[3], st);
	push_back(&st->scobj, plane);
	st->pl_parsed = 1;
}

void	parse_cylindre(t_store *st)
{
	t_obj	*cylind;

	if (count_split(st->split) != 6)
		ft_error(st, "Error\nParse error. Cylinder has 5 params\n");
	cylind = (t_obj *)malloc(sizeof(t_obj));
	cylind->type = CYLINDER;
	cylind->ang = v3_norm(str_to_vec(st->split[2], st));
	cylind->pos = str_to_vec(st->split[1], st);
	cylind->ang = v3_sum(cylind->pos, v3_multd(cylind->ang, \
		ft_atof(st->split[4])));
	cylind->par1 = ft_atof(st->split[3]);
	cylind->color = split_rgb(st->split[5], st);
	push_back(&st->scobj, cylind);
	st->cy_parsed = 1;
}
