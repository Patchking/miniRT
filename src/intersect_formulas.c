#include "minirt.h"

double	sphIntersect(t_v3 ro, t_v3 rd, t_v3 ce, double ra)
{
	t_v3 oc = v3_sub(ce, ro);
	double b = v3_dot(oc, rd);
	double c = v3_dot(oc, oc) - ra * ra;
	double h = b * b - c;
	if(h <= 0.0 || b < 0.0)
		return (DBL_MAX);
	h = sqrt( h );
	return ((b - h));
}

double	plnIntersect(t_v3 ro, t_v3 rd, t_v3 a, double w)
{
	// double	d;

	// d = v3_dot(ro, v3_sign(a));
	// if (d <= 0)
	// 	return (DBL_MAX);
	// return (v3_dist(v3_sub(ce, ro)) / d);
	// return -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
	double	d;

	d = v3_dot(a, rd);
	if (d == 0)
		return (DBL_MAX);
	return (-(v3_dot(ro, a) - w) / d);
}

// vec2 sphIntersect( in vec3 ro, in vec3 rd, in vec3 ce, double ra )
// {
//     vec3 oc = ro - ce;
//     double b = dot( oc, rd );
//     double c = dot( oc, oc ) - ra*ra;
//     double h = b*b - c;
//     if( h<0.0 ) return vec2(-1.0); // no intersection
//     h = sqrt( h );
//     return vec2( -b-h, -b+h );
// }