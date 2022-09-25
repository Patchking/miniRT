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

static t_color	get_color_sphere(t_store *st, t_obj *obj, t_v3 rd, t_v3 norm)
{
	double	dif;

	// return (obj->color);
	dif = v3_dot(st->ld, norm);
	if (dif <= 0)
		return (obj->color);
	return (color_blend(obj->color, color(0, 255, 255, 255), dif));
}

t_v3	get_normal_circle(t_v3 ro, t_v3 rd, double dist, t_v3 pos)
{
	return (v3_norm(v3_sub(v3_sum(ro, v3_multv(rd, dist)), pos)));
}

void	find_intersect(t_store *st, t_v3 rd, t_v3 ro, t_raycast *rc)
{
	t_list	*cur;

	cur = st->scobj;
	while (cur)
	{
		if (cur->data->type == CIRCLE)
			rc->curmin = sphIntersect(ro, rd, cur->data->pos, cur->data->par1);
		else if (cur->data->type == PLAIN)
			rc->curmin = plnIntersect(ro, rd, cur->data->ang, cur->data->par1);
		if (rc->curmin < rc->dist && rc->curmin > 0.00000001)
		{
			rc->obj = cur->data;
			rc->dist = rc->curmin;
		}
		cur = cur->next;
	}
}

void	find_additional_info(t_store *st, t_raycast	*rc, t_v3 rd, t_v3 ro)
{
	double	dif;

	rc->intersect = v3_sum(ro, v3_multv(rd, rc->dist));
	if (rc->obj->type == CIRCLE)
	{
		rc->norm = v3_norm(v3_sub(rc->intersect, rc->obj->pos));
		dif = v3_dot(st->ld, rc->norm);
		if (dif <= 0)
			rc->out = rc->obj->color;
		else
			rc->out = color_blend(color(0, 255, 255, 255), rc->obj->color, pow(dif, 10));
		// rc->out = rc->obj->color;
	}
	else if (rc->obj->type == PLAIN)
	{
		rc->norm = rc->obj->ang;
		dif = v3_dot(st->ld, rc->norm);
		if (dif <= 0)
			rc->out = rc->obj->color;
		else
			rc->out = color_blend(color(0, 255, 255, 255), rc->obj->color, pow(dif, 10));
	}
}

t_color	ray_cast(t_store *st, t_v3 rd, t_v3 ro, int d)
{
	// t_list	*rc.cur;
	// t_obj	*obj;
	// t_color	out;
	// t_v3	norm;
	t_raycast rc;

	// rc.cur = st->scobj;
	rc.obj = st->scobj->data;
	rc.dist = DBL_MAX;
	// while (rc.cur)
	// {
	// 	if (rc.cur->data->type == CIRCLE)
	// 		rc.cur->data->parf = sphIntersect(st->cam_pos, rd, rc.cur->data->pos, rc.cur->data->par1);
	// 	if (rc.cur->data->parf < rc.obj->parf)
	// 		rc.obj = rc.cur->data;
	// 	rc.cur = rc.cur->next;
	// }
	// if (temp1 == 360 && temp2 == 240)
	// 	printf("%d, %d) blue: 1 - %f, 2 - %f\n", temp1, temp2, st->scobj->data->parf, st->scobj->next->data->parf);
	// if (rc.obj->parf == DBL_MAX)
	// 	return (color(0, 0, 0, 0));
	find_intersect(st, rd, ro, &rc);
	if (rc.dist == DBL_MAX)
	{
		// printf("sky hitted\n");
		return (st->skyc);
	}
	// if (rc.obj->type == CIRCLE)
	// {
	// 	norm = get_normal_circle(st->cam_pos, rd, rc.obj->parf, rc.obj->pos);
	// 	out = get_color_sphere(st, rc.obj, rd, norm);
	// }
	find_additional_info(st, &rc, rd, ro);
	// if (temp2 == st->vp.height / 2) {
	// 	// printf("%d, %d) blue: 1 - %f\n", temp1, temp2, v3_dot(rd, get_normal_circle(st->cam_pos, rd, rc.obj->parf, rc.obj->pos))); 
	// 	printf("%d, %d) blue: 1 - %f\n", temp1, temp2, 1.0); 
	// 	print_vec(v3_multv(rd, rc.obj->parf));
	// 	print_vec(v3_sub(v3_multv(rd, rc.obj->parf), rc.obj->pos)); }
	// // printf("ref = %f\n", rc.obj->ref);
	// if (d < 3)
	// {
	// 	printf("%d, %d) blue: 1 - \n", temp1, temp2); 
	// 	print_vec(rd);
	// }
	// mlx_im
	rc.norm = v3_ref(rd, rc.norm);
	if (d > 0 && rc.obj->ref != 0)
		rc.out = color_blend(ray_cast(st, rc.norm, rc.intersect, d - 1), rc.out, rc.obj->ref);
	return (rc.out);
}
