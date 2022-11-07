/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:02:20 by cojacque          #+#    #+#             */
/*   Updated: 2022/11/04 21:18:10 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"
#include "../header/parse.h"

void	parse_type_id(t_store *st)
{	
	if ((ft_strcmp(st->split[0], "R") == 0) && st->r_parsed != 1)
		parse_resolution(st);
	else if ((ft_strcmp(st->split[0], "A") == 0) && st->a_parsed != 1)
		parse_ambient(st);
	else if ((ft_strcmp(st->split[0], "C") == 0) && st->c_parsed != 1)
		parse_camera(st);
	else if ((ft_strcmp(st->split[0], "L") == 0) && st->l_parsed != 1)
		parse_light(st);
	else if ((ft_strcmp(st->split[0], "sp") == 0))
		parse_sphere(st);
	else if ((ft_strcmp(st->split[0], "pl") == 0))
		parse_plane(st);
	else if ((ft_strcmp(st->split[0], "cy") == 0))
		parse_cylindre(st);
	// else
	// 	// ft_error("Error\nInvalid scene\n"); // Временно. Потом удалить или или смотреть по сабжу
	// 	ft_printf("Unidentifind obj \"%s\". ingoring.\n", st->split[0]);
}

void	check_file_extension(char *name, t_store *st)
{
	char	*format;

	format = ".rt";
	while (*name != '.' && *name != '\0')
		name++;
	if (ft_strncmp(name, format, 4) != 0)
		ft_error(st, "Error\nWrong file extansion\n");
}

void parse(t_store *st,  char* rt_file)
{
	int fd;
	char *line;

	check_file_extension(rt_file, st);
	fd = open(rt_file, O_RDONLY);
	line = get_next_line(fd);
	st->a_parsed = 0;
	st->c_parsed = 0;
	st->l_parsed = 0;
	while (line)
	{
		st->split = ft_split(line, ' ');
		if (!st->split)
			ft_close_red_cross(st);
		if (st->split[0])
			parse_type_id(st);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
