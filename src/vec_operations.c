#include "minirt.h"

t_v3	v3f(double x, double y, double z)
{
	t_v3	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

t_v3	v3_sign(t_v3 v1)
{
	v1.x = -v1.x;
	v1.y = -v1.y;
	v1.z = -v1.z;
	return (v1);
}

t_v3	v3_sum(t_v3 v1, t_v3 v2)
{
	v1.x = v1.x + v2.x;
	v1.y = v1.y + v2.y;
	v1.z = v1.z + v2.z;
	return (v1);
}

t_v3	v3_sumv(t_v3 v1, double v2)
{
	v1.x = v1.x + v2;
	v1.y = v1.y + v2;
	v1.z = v1.z + v2;
	return (v1);
}

t_v3	v3_sub(t_v3 v1, t_v3 v2)
{
	v1.x = v1.x - v2.x;
	v1.y = v1.y - v2.y;
	v1.z = v1.z - v2.z;
	return (v1);
}

t_v3	v3_subv(t_v3 v1, double v2)
{
	v1.x = v1.x - v2;
	v1.y = v1.y - v2;
	v1.z = v1.z - v2;
	return (v1);
}

t_v3	v3_mult(t_v3 v1, t_v3 v2)
{
	v1.x = v1.x * v2.x;
	v1.y = v1.y * v2.y;
	v1.z = v1.z * v2.z;
	return (v1);
}

t_v3	v3_multv(t_v3 v1, double v2)
{
	v1.x = v1.x * v2;
	v1.y = v1.y * v2;
	v1.z = v1.z * v2;
	return (v1);
}

double	v3_dot(t_v3 v1, t_v3 v2)
{
	double	out;

	out = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (out);
}

double	v3_len(t_v3 v1)
{
	double	length;

	length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return (length);
}

t_v3	v3_norm(t_v3 v1)
{
	v1 = v3_multv(v1, 1.0f / v3_len(v1));
	return (v1);
}

t_v3	v3_ref(t_v3 v, t_v3 n)
{
	return (v3_sub(v, v3_multv(n, (2 * v3_dot(n, v)))));
}

t_v3i	v3i(int x, int y, int z)
{
	t_v3i	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}