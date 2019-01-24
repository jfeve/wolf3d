/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/22 17:52:46 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 17:14:52 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

void			check_camera_move(t_input *in, t_begin **begin)
{
	if (in->key[SDL_SCANCODE_LEFT])
	{
		if ((*begin)->angle + (M_PI / 64) >= M_PI)
			(*begin)->angle = -1 * M_PI;
		else
			(*begin)->angle += M_PI / 64;
		(*begin)->plane = init_plane((*begin)->angle);
		(*begin)->dir = init_vector(cos((*begin)->angle), -1 *
				sin((*begin)->angle));
	}
	if (in->key[SDL_SCANCODE_RIGHT])
	{
		if ((*begin)->angle - (M_PI / 64) <= -1 * M_PI)
			(*begin)->angle = M_PI;
		else
			(*begin)->angle -= M_PI / 64;
		(*begin)->plane = init_plane((*begin)->angle);
		(*begin)->dir = init_vector(cos((*begin)->angle), -1 *
				sin((*begin)->angle));
	}
}

void			check_chara_move(t_begin **begin, t_input *in)
{
	if (in->key[SDL_SCANCODE_UP])
	{
		if ((*begin)->worldmap[(int)(*begin)->pos.y][(int)((*begin)->pos.x +
					0.5f * (*begin)->dir.x)] == 0)
			(*begin)->pos.x += 0.25f * (*begin)->dir.x;
		if ((*begin)->worldmap[(int)((*begin)->pos.y + 0.5 * (*begin)->dir.y)]
				[(int)(*begin)->pos.x] == 0)
			(*begin)->pos.y += 0.25f * (*begin)->dir.y;
	}
	if (in->key[SDL_SCANCODE_DOWN])
	{
		if ((*begin)->worldmap[(int)(*begin)->pos.y][(int)((*begin)->pos.x -
					0.5f * (*begin)->dir.x)] == 0)
			(*begin)->pos.x -= 0.25f * (*begin)->dir.x;
		if ((*begin)->worldmap[(int)((*begin)->pos.y - 0.5f * (*begin)->dir.y)]
				[(int)(*begin)->pos.x] == 0)
			(*begin)->pos.y -= 0.25f * (*begin)->dir.y;
	}
}

void			run_event(t_begin *begin, t_input *in)
{
	if (in->key[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	check_camera_move(in, &begin);
	check_chara_move(&begin, in);
	if (in->key[SDL_SCANCODE_R])
	{
		begin->angle = M_PI;
		begin->pos = init_vector(22, 12);
		begin->dir = init_vector(cos(begin->angle), -1 * sin(begin->angle));
		begin->plane = init_plane(begin->angle);
	}
	SDL_Delay(20);
}

void			update_event(t_input *in)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		else if (event.type == SDL_KEYDOWN)
			in->key[event.key.keysym.scancode] = SDL_TRUE;
		else if (event.type == SDL_KEYUP)
			in->key[event.key.keysym.scancode] = SDL_FALSE;
	}
}
