#include "minirt.h"
#include "parse.h"

void eject(t_store *st)
{
	free_list(st->scobj);
	free(st->vp.mlx_image);
	free(st->vp.mlx_win);
	free(st->vp.mlx);
	exit(0);
}

void temp_setup_vars(t_store *st)
{
	st->vp.width = 1280;
	st->vp.height = 720;
	st->vp.bits_per_pixel = 0;
	st->vp.mem_offset = 0;
	st->vp.fov = PI / 2;
	st->dt = 0;
}

void	pixel_put(t_store *st, int x, int y, unsigned int color)
{
	*(unsigned int *)((char *)st->vp.mlx_out_image + (y * st->vp.mem_offset + x *
					(st->vp.bits_per_pixel / 8))) = color;
}

void	init_set_zero(t_store *st)
{
	st->vp.mlx = NULL;
	st->vp.mlx_win = NULL;
	st->vp.mlx_image = NULL;
	st->vp.mlx_out_image = NULL;
	st->scobj = NULL;
	st->split = NULL;
	st->ref_count = 0;
	st->skyc = c_to_v3(color(0, 5, 5, 35));
}

// void	scene_setup(t_store *st)
// {
// 	t_obj	*c1;
// 	t_color	wall_color = color(0, 30, 30, 70);


// 	const float	wall_mirror = 0.8;
// 	const float sphere_mirror = 0.1;
// 	// create_cylinder_to_scene(st, v3f(-1, 0, 4), v3f(1, 0, 4), 1, color(0, 100, 0, 0), 0);
// 	// create_circle_to_scene(st, v3f(0, 0, 5), color(0, 100, 0, 0), 1, sphere_mirror);
// 	// create_circle_to_scene(st, v3f(0, 1, 1), color(0, 0, 100, 0), 1, sphere_mirror);
// 	// create_circle_to_scene(st, v3f(-1, -1, 1), color(0, 0, 0, 100), 1, sphere_mirror);
// 	// create_plain_to_scene(st, -4, wall_color, v3f(0, 1, 0), wall_mirror);
// 	// create_plain_to_scene(st, -4, wall_color, v3f(0, -1, 0), wall_mirror);
// 	// create_plain_to_scene(st, -10, wall_color, v3f(0, 0, -1), wall_mirror);
// 	// create_plain_to_scene(st, -7, wall_color, v3f(0, 0, 1), wall_mirror);
// 	// create_plain_to_scene(st, -4, wall_color, v3f(1, 0, 0), wall_mirror);
// 	// create_plain_to_scene(st, -4, wall_color, v3f(-1, 0, 0), wall_mirror);
// 	// st->cam_pos = v3f(0, 0, 0);
// 	// st->cam_dir = v3_norm(v3f(0, 1, 0));
// 	// st->lo = v3f(3, 3, 2);
// 	// st->amb_light = v3f(1, 1, 1);
// 	// st->amb_str = 0;
// 	// st->lth_color = v3f(1, 1, 1);
// 	// st->lth_str = 1;
// }

void	init(t_store *st)
{
	st->vp.mlx = mlx_init();
	st->vp.mlx_win = mlx_new_window(st->vp.mlx, st->vp.width, st->vp.height, "hello world!");
	st->vp.mlx_image = mlx_new_image(st->vp.mlx, st->vp.width, st->vp.height);
	st->vp.mlx_out_image = mlx_get_data_addr(st->vp.mlx_image, &st->vp.bits_per_pixel, &st->vp.mem_offset, &st->vp.endian);
	if (!st->vp.mlx_win || !st->vp.mlx_image || !st->vp.mlx_out_image)
		eject(st);
}

void	create_basis(t_store *st, t_v3 v)
{
	if (v.z >= 0.99)
		v = v3f(0.01, 0.01, 0.98);
	v = v3_norm(v);
	st->basis.x = v;
	st->basis.y = v3f(-1, 0, 0);
	st->basis.z = v3_norm(v3_multv(st->basis.x, st->basis.y));
	st->basis.y = v3_multv(st->basis.x, st->basis.z);
}

t_v3	rotate(t_v3 v, t_basis *b)
{
	t_v3	out;

	out.x = b->x.x * v.x + b->y.x * v.y + b->z.x * v.z;
	out.y = b->x.y * v.x + b->y.y * v.y + b->z.y * v.z;
	out.z = b->x.z * v.x + b->y.z * v.y + b->z.z * v.z;
	return (out);
}

int	cast_ray_by_pos(t_store *st, int x, int y, t_v3 step)
{
	t_v3	rd;
	t_v3	ro;

	rd.x = step.x * (x - st->vp.width / 2);
	rd.y = step.y * (y - st->vp.height / 2) * step.z;
	rd.z = 1;
	rd = v3_norm(rd);
	// rd = rotate(rd, &st->basis);
	ro = st->cam_pos;
	return (ray_cast(st, rd, ro, st->ref_count).i);
}

void	temp_draw_scene(t_store *st)
{
	t_v3	step;
	t_v3	rd;
	t_v3i	it;
	t_v3	ro;

	if (!st->scobj)
	{
		ft_putstr_fd("scene is empty\n", 1);
		return ;
	}
	create_basis(st, v3f(0, 0, 1));
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

int	main(int argc, char **argv) {
	t_store st;

	init_set_zero(&st);
	temp_setup_vars(&st);
	if (argc != 2)
		ft_error(&st, "Error\nInvalid scene\n");
	parse(&st, argv[1]);
	init(&st);
	update(&st);
	mlx_put_image_to_window(st.vp.mlx, st.vp.mlx_win, st.vp.mlx_image, 0, 0);
	mlx_hook(st.vp.mlx_win, 17, 0, ft_close_red_cross, &st);
	mlx_key_hook(st.vp.mlx_win, ft_esc_close, &st);
	mlx_loop(st.vp.mlx);
}
