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




void	find_intersect(t_store *st, t_v3 rd, t_v3 ro, t_raycast *rc)
{
	t_list	*cur;
	double	curmin;

	cur = st->scobj;
	while (cur)
	{
		if (cur->data->type == CIRCLE)
			curmin = sphIntersect(ro, rd, cur->data->pos, cur->data->par1);
		else if (cur->data->type == PLAIN)
			curmin = plnIntersect(ro, rd, cur->data->ang, cur->data->par1);
		if (curmin < rc->dist && curmin > 0.00000001)
		{
			rc->obj = cur->data;
			rc->dist = curmin;
		}
		cur = cur->next;
	}
}

void	find_additional_info(t_store *st, t_raycast	*rc, t_v3 rd, t_v3 ro)
{
	double		dif;
	t_raycast	rcl;

	rc->intersect = v3_sum(ro, v3_multv(rd, rc->dist));
	if (rc->obj->type == CIRCLE)
		rc->norm = v3_norm(v3_sub(rc->intersect, rc->obj->pos));
	else if (rc->obj->type == PLAIN)
		rc->norm = rc->obj->ang;
	rc->out = rc->obj->color;
	//
}

t_color	ray_cast(t_store *st, t_v3 rd, t_v3 ro, int d)
{
	t_raycast rc;

	rc.obj = st->scobj->data;
	rc.dist = DBL_MAX;
	find_intersect(st, rd, ro, &rc);
	if (rc.dist == DBL_MAX)
	{
		return (st->skyc);
	}
	find_additional_info(st, &rc, rd, ro);
	rc.norm = v3_ref(rd, rc.norm);
	if (d > 0 && rc.obj->ref != 0)
		rc.out = color_blend(ray_cast(st, rc.norm, rc.intersect, d - 1), rc.out, rc.obj->ref);
	return (rc.out);
}
