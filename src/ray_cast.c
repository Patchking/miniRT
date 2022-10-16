#include "minirt.h"

// static int  ray_cast_sphere(t_store *st, t_obj *obj, t_v3 rd)
// {
// 	double	dist;
// 	double	dif;

// 	dist = sphIntersect(st->cam_pos, rd, obj->pos, obj->par1); // with sphere in 0, 0, 0 rd = 1.0f
// 	if (dist == -1)
// 		return (color(0, 0, 0, 0).i);
// 	dif = v3_dot(st->ld, v3_norm(v3_sum(st->cam_pos, v3_multv(rd, dist))));
// 	if (dif < 0)
// 		return (color(0, 0, 0, 0).i); 
// 	return (color(0, (int)(dif * 255), (int)(dif * 255), (int)(dif * 255)).i);
// }

// static t_color	get_color_sphere(t_store *st, t_obj *obj, t_v3 rd, t_v3 norm)
// {
// 	double	dif;

// 	// return (obj->color);
// 	dif = v3_dot(st->ld, norm);
// 	if (dif <= 0)
// 		return (obj->color);
// 	return (color_blend(obj->color, color(0, 255, 255, 255), dif));
// }

t_v3	get_normal_circle(t_v3 ro, t_v3 rd, double dist, t_v3 pos)
{
	return (v3_norm(v3_sub(v3_sum(ro, v3_multv(rd, dist)), pos)));
}

double	find_intersect(t_store *st, t_v3 rd, t_v3 ro, t_obj **obj)
{
	t_list	*cur;
	double	curmin;
	double	dist;

	cur = st->scobj;
	dist = DBL_MAX;
	while (cur)
	{
		if (cur->data->type == CIRCLE)
			curmin = sphIntersect(ro, rd, cur->data->pos, cur->data->par1);
		else if (cur->data->type == PLAIN)
			curmin = plnIntersect(ro, rd, cur->data->ang, cur->data->par1);
		if (curmin < dist && curmin > 0.00000001)
		{
			*obj = cur->data;
			dist = curmin;
		}
		cur = cur->next;
	}
	return (dist);
}

t_color	find_additional_info(t_store *st, t_raycast	*rc, t_v3 rd, t_v3 ro)
{
	t_raycast	rcl;
	double		ld;

	rc->intersect = v3_sum(ro, v3_multv(rd, rc->dist));
	if (rc->obj->type == CIRCLE)
		rc->norm = v3_norm(v3_sub(rc->intersect, rc->obj->pos));
	else if (rc->obj->type == PLAIN)
		rc->norm = rc->obj->ang;
	rcl.norm = v3_sub(st->lo, rc->intersect);
	rcl.dist = v3_len(rcl.norm);
	rcl.norm = v3_norm(rcl.norm);
	if (rcl.dist > find_intersect(st, rcl.norm, rc->intersect, &rcl.obj))
	{
		return (color_blend(rc->obj->color, st->amb_light, 0.1));
	}
	ld = v3_dot(rcl.norm, rc->norm);
	ld = 0.5 * (ld + 1);
	const double cof = 10;
	return (color_blend(rc->obj->color, st->amb_light, ld / (rcl.dist + cof) * cof));
	// if (ld < 0)
	// {
	// 	ld = -ld;
	// 	return (color_blend(rc->obj->color, color(0, 0, 0, 0), 1 - ld / 2));
	// }
	// return (color_blend(rc->obj->color, color(0, 255, 255, 255), 1 - (ld / (rcl.dist + cof) * cof)));
}

t_color	ray_cast(t_store *st, t_v3 rd, t_v3 ro, int d)
{
	t_raycast	rc;
	t_color		out;

	rc.obj = st->scobj->data;
	// calculate dist till intersection
	rc.dist = find_intersect(st, rd, ro, &rc.obj);
	if (rc.dist == DBL_MAX)
	{
		return (st->skyc);
	}
	out = find_additional_info(st, &rc, rd, ro);
	// find reflected ray direction
	rc.norm = v3_ref(rd, rc.norm);
	if (d > 0 && rc.obj->ref != 0)
		out = color_blend(ray_cast(st, rc.norm, rc.intersect, d - 1), out, rc.obj->ref);
	return (out);
}
