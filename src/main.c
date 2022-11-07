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
#include "parse.h"

void	init(t_store *st)
{
	st->vp.mlx = mlx_init();
	st->vp.mlx_win = mlx_new_window(st->vp.mlx, st->vp.width, st->vp.height,
			"hello world!");
	st->vp.mlx_image = mlx_new_image(st->vp.mlx, st->vp.width, st->vp.height);
	st->vp.mlx_out_image = mlx_get_data_addr(st->vp.mlx_image,
			&st->vp.bits_per_pixel, &st->vp.mem_offset, &st->vp.endian);
	if (!st->vp.mlx_win || !st->vp.mlx_image || !st->vp.mlx_out_image)
		eject(st);
	recalculate_colors(st);
	st->light_boarder0 = 0.1;
	st->light_boarder1 = -0.2;
	st->fading_cof = (st->light_boarder0 + 1 - st->amb_str)
		/ (st->light_boarder0 - st->light_boarder1);
}

int	cast_ray_by_pos(t_store *st, int x, int y, t_v3 step)
{
	t_v3	rd;
	t_v3	ro;

	rd.x = step.x * (x - st->vp.width / 2);
	rd.y = step.y * (y - st->vp.height / 2) * step.z;
	rd.z = 1;
	rd = v3_norm(rd);
	rd = rotate(rd, &st->basis);
	ro = st->cam_pos;
	return (ray_cast(st, rd, ro, st->ref_count).i);
}

void	temp_draw_scene(t_store *st)
{
	t_v3	step;
	t_v3i	it;

	create_basis(st, st->cam_dir);
	st->vp.diff = tan(st->vp.fov / 2);
	step.x = 2.0 / st->vp.width * st->vp.diff;
	step.y = 2.0 / st->vp.height * st->vp.diff;
	step.z = (double)st->vp.height / st->vp.width;
	it.x = 0;
	while (it.x < st->vp.width)
	{
		it.y = 0;
		while (it.y < st->vp.height)
		{
			pixel_put(st, it.x, it.y, cast_ray_by_pos(st, it.x, it.y, step));
			it.y++;
		}
		it.x++;
	}
}

int	update(void *store)
{
	t_store	*st;

	st = (t_store *)store;
	temp_draw_scene(st);
	mlx_put_image_to_window(st->vp.mlx, st->vp.mlx_win, st->vp.mlx_image, 0,
		0);
	st->dt++;
	return (0);
}

int	main(int argc, char **argv)
{
	t_store	st;

	preparse_setup(&st);
	if (argc != 2)
		ft_error(&st, "Error\nYou should give only one argument\n");
	parse(&st, argv[1]);
	if (!st.a_parsed || !st.c_parsed || !st.l_parsed)
		ft_error(&st, "Error\nNot every needed obj was declaired\n");
	init(&st);
	update(&st);
	mlx_put_image_to_window(st.vp.mlx, st.vp.mlx_win, st.vp.mlx_image, 0, 0);
	mlx_hook(st.vp.mlx_win, 17, 0, ft_close_red_cross, &st);
	mlx_key_hook(st.vp.mlx_win, ft_esc_close, &st);
	mlx_loop(st.vp.mlx);
}
