/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb_cam_lth.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:05:52 by cojacque          #+#    #+#             */
/*   Updated: 2022/11/07 18:28:23 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"
#include "../header/parse.h"

void	parse_resolution(t_store *st)
{
	if (count_split(st->split) != 4)
		ft_error(st, "Error\nParse error. Resolution must have 3 params.\n");
	st->vp.width = ft_atoi(st->split[1]);
	st->vp.height = ft_atoi(st->split[2]);
	st->ref_count = ft_atoi(st->split[3]);
	if (st->ref_count < 0)
		ft_error(st, "Error\nParse error. Screen ref count should be >= 0");
	if (st->vp.width < 100 || st->vp.height < 100)
		ft_error(st, "Error\nParse error. Min resolution is 100x100\n");
	if (st->vp.width > MAX_WIDTH)
		st->vp.width = MAX_WIDTH;
	if (st->vp.height > MAX_HEIGHT)
		st->vp.height = MAX_HEIGHT;
	st->r_parsed = 1;
}

void	parse_ambient(t_store *st)
{
	if (count_split(st->split) != 3)
		ft_error(st, "Error\nParse error. Ambient should have 2 params\n");
	st->amb_str = ft_atof(st->split[1]);
	st->amb_light = split_rgb(st->split[2], st);
	if (st->amb_str > 1 || st->amb_str < 0)
		ft_error(st, "Error\nAmbient second param is between 0 and 1\n");
	st->a_parsed = 1;
}

void	parse_camera(t_store *st)
{
	if (count_split(st->split) != 4)
		ft_error(st, "Error\nParse error. Camera has 3 params\n");
	st->cam_pos = str_to_vec(st->split[1], st);
	st->cam_dir = str_to_vec(st->split[2], st);
	st->cam_dir = v3_norm(st->cam_dir);
	st->cam_dir.z = -st->cam_dir.z;
	st->vp.fov = PI / 180 * ft_atoi(st->split[3]);
	if (st->vp.fov >= PI)
		st->vp.fov = PI - PI / 180;
	if (st->vp.fov < 0 || st->vp.fov > PI)
		ft_error(st, "Error\nParse error. Fov must be more 0 and less 180\n");
	st->c_parsed = 1;
}

void	parse_light(t_store *st)
{
	if (count_split(st->split) != 4)
		ft_error(st, "Error\nParse error. Light has 3 params\n");
	st->lo = str_to_vec(st->split[1], st);
	st->lth_str = ft_atof(st->split[2]);
	st->lth_color = split_rgb(st->split[3], st);
	if (st->lth_str > 1 || st->lth_str < 0)
		ft_error(st, "Error\nLight str should be more 0 and less 1\n");
	st->l_parsed = 1;
}
