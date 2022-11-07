/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:34:32 by cojacque          #+#    #+#             */
/*   Updated: 2022/11/07 18:47:14 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	ft_close_red_cross(t_store *st)
{
	eject(st);
	return (0);
}

int	ft_esc_close(int key, t_store *st)
{
	if (key == KEY_ESC)
		ft_close_red_cross(st);
	return (0);
}
