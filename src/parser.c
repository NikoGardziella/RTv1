/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:03:41 by ngardzie          #+#    #+#             */
/*   Updated: 2022/09/21 13:03:44 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

void	check_numbers(char **line_arr, int len, t_scene *scene)
{	
	int	i;
	int	j;

	i = 1;
	while (i < len)
	{
		j = 0;
		while (line_arr[i][j] != '\0')
		{
			if (!ft_isdigit(line_arr[i][j]))
			{
				if (line_arr[i][j] != '-')
					ft_fail_and_free("input error: not a number", scene);
			}
			j++;
		}
		i++;
	}
}

void	parse_more(t_scene *scene, char **line_arr)
{
	if (!ft_strcmp(line_arr[0], "plane"))
	{
		parse_obj(scene, line_arr, scene->obj_count);
		scene->obj[scene->obj_count].shape = 4;
		scene->obj_count++;
	}
	else if (!ft_strcmp(line_arr[0], "cam"))
		parse_cam(scene, line_arr);
	else if (!ft_strcmp(line_arr[0], "light"))
		parse_light(scene, line_arr);
	else
		ft_fail_and_free("input error: wrong name", scene);
}

void	parse_line(t_scene *scene, char **line_arr)
{
	if (line_arr[0] == NULL)
		return ;
	if (!ft_strcmp(line_arr[0], "sphere"))
	{
		parse_obj(scene, line_arr, scene->obj_count);
		scene->obj[scene->obj_count].shape = 1;
		scene->obj_count++;
	}
	else if (!ft_strcmp(line_arr[0], "cone"))
	{
		parse_obj(scene, line_arr, scene->obj_count);
		scene->obj[scene->obj_count].shape = 2;
		scene->obj_count++;
	}
	else if (!ft_strcmp(line_arr[0], "cylinder"))
	{
		parse_obj(scene, line_arr, scene->obj_count);
		scene->obj[scene->obj_count].shape = 3;
		scene->obj_count++;
	}
	else
		parse_more(scene, line_arr);
}

int	get_obj_count(char *file)
{
	int		object_count;
	int		fd;
	char	*line;

	object_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("parser error");
		exit(0);
	}
	while ((get_next_line(fd, &line) == 1))
	{
		object_count++;
		free(line);
	}
	close(fd);
	return (object_count);
}

void	parser(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	char	**line_arr;

	scene->obj_count = get_obj_count(file);
	scene->obj = (t_object *)malloc(sizeof(t_object) * scene->obj_count);
	if (scene->obj == NULL)
		ft_fail("malloc fail");
	scene->obj_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_fail("error opening the file");
	while ((get_next_line(fd, &line) == 1))
	{
		line_arr = ft_strsplit(line, ' ');
		if (line_arr != NULL)
		{
			parse_line(scene, line_arr);
			free_arr(line_arr);
		}
		free(line);
	}
	close(fd);
}
