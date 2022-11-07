#include "minirt.h"

void	pixel_put(t_store *st, int x, int y, unsigned int color)
{
	*(unsigned int *)((char *)st->vp.mlx_out_image + (y * st->vp.mem_offset +
				x * (st->vp.bits_per_pixel / 8))) = color;
}