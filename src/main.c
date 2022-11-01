/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:41:02 by ngardzie          #+#    #+#             */
/*   Updated: 2022/06/22 11:41:04 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/rtv1.h"

t_ray	cam_and_ray(t_scene *scene)
{
	t_ray	new_ray;

	scene->cam.up = v_new(0, 1, 0);
	if (scene->cam.direction.y && scene->cam.direction.x
		== 0 && scene->cam.direction.z == 0)
		scene->cam.up = v_new(0, 0, 1);
	scene->cam.left = v_normalize(vector_cross_product
			(scene->cam.direction, scene->cam.up));
	scene->cam.up = v_normalize(vector_cross_product
			(scene->cam.direction, scene->cam.left));
	scene->cam.forward = v_normalize(scene->cam.direction);
	new_ray.origin = scene->cam.origin;
	return (new_ray);
}

void	raytrace(t_scene *scene, t_ray ray, int x, int y)
{
	int	res;

	res = 0;
	object_t(scene, ray);
	object_normal(scene, ray);
	res = get_closest(scene);
	scene->obj[res].inshadow = check_shadow(scene,
			scene->obj[res], scene->obj[res].lightray);
	if (scene->obj[res].t)
		put_pixel(scene->data, x, y, add_color(scene->obj[res].light,
				scene->obj[res].inshadow, scene->obj[res]));
}

void	draw(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;

	ray = cam_and_ray(scene);
	y = 0;
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (x < SCREEN_HEIGHT)
		{
			ray.dir = v_sub(scene->cam.forward, v_scale(scene->cam.left,
						((float)x / SCREEN_WIDTH * 2 - 1)));
			ray.dir = v_add(ray.dir, v_scale(scene->cam.up, ((float)y
							/ SCREEN_HEIGHT * 2 - 1)));
			ray.dir = v_normalize(ray.dir);
			raytrace(scene, ray, x, y);
			x++;
		}
		y++;
	}
}

t_sdl	start_sdl(t_scene *scene)
{
	int		pitch;
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_fail("Failed to initialize SDL");
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
			0, &sdl.window, &sdl.renderer) == -1)
		ft_fail("sdl window&renderer error");
	sdl.buffer = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_BGR888,
			SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (sdl.buffer == NULL)
		ft_fail("sdl buffer error");
	SDL_LockTexture(sdl.buffer, NULL, &scene->data, &pitch);
	draw(scene);
	SDL_UnlockTexture(sdl.buffer);
	SDL_RenderCopy(sdl.renderer, sdl.buffer, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);
	return (sdl);
}

int	main(int ac, char **av)
{
	int		quit_bool;
	t_scene	*scene;
	t_sdl	sdl;

	if (ac != 2)
		return (0);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		ft_fail("malloc fail");
	ft_bzero(scene, sizeof(t_scene));
	quit_bool = 0;
	parser(scene, av[1]);
	sdl = start_sdl(scene);
	while (!quit_bool)
	{
		while (SDL_PollEvent(&sdl.event))
		{
			if (sdl.event.type == SDL_QUIT || sdl.event.key.keysym.scancode
				== SDL_SCANCODE_ESCAPE)
				quit_bool = 1;
		}
	}
	shutdown(sdl.renderer, sdl.window, scene, "");
	return (0);
}
