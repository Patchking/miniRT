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

void	create_basis(t_store *st, t_v3 v)
{
	if (v.y >= 0.999)
		v = v3f(0.0001, 0.999, 0.0001);
	if (v.y <= -0.999)
		v = v3f(0.0001, -0.999, 0.0001);
	v = v3_norm(v);
	st->basis.x = v;
	st->basis.y = v3f(0, -1, 0);
	st->basis.z = v3_norm(v3_multv(st->basis.y, st->basis.x));
	st->basis.y = v3_multv(st->basis.z, st->basis.x);
}

t_v3	rotate(t_v3 v, t_basis *b)
{
	t_v3	out;

	out.z = b->x.x * v.x + b->y.x * v.y + b->z.x * v.z;
	out.y = b->x.y * v.x + b->y.y * v.y + b->z.y * v.z;
	out.x = b->x.z * v.x + b->y.z * v.y + b->z.z * v.z;
	return (out);
}

void	recalculate_colors(t_store *st)
{
	t_list	*lst;

	lst = st->scobj;
	while (lst)
	{
		lst->data->pos.x = -lst->data->pos.x;
		lst->data->color = v3_multd(lst->data->color, st->lth_str);
		lst->data->color_dark = v3_multd(lst->data->color, 0.5);
		lst = lst->next;
	}
}

void	eject(t_store *st)
{
	free_list(st->scobj);
	if (st->vp.mlx && st->vp.mlx_image)
		mlx_destroy_image(st->vp.mlx, st->vp.mlx_image);
	if (st->vp.mlx && st->vp.mlx_win)
		mlx_destroy_window(st->vp.mlx, st->vp.mlx_win);
	exit(0);
}

void	preparse_setup(t_store *st)
{
	st->vp.mlx = NULL;
	st->vp.mlx_win = NULL;
	st->vp.mlx_image = NULL;
	st->vp.mlx_out_image = NULL;
	st->scobj = NULL;
	st->split = NULL;
	st->vp.width = 1280;
	st->vp.height = 720;
	st->vp.bits_per_pixel = 0;
	st->vp.mem_offset = 0;
	st->vp.fov = PI / 2;
	st->dt = 0;
	st->ref_count = 0;
	st->objs_ref_power = 0;
	st->skyc = c_to_v3(color(0, 5, 5, 35));
}
