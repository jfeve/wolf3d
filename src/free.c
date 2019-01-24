/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/12 17:33:25 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 17:56:34 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

int				sdl_free_all(int flag, t_begin *begin)
{
	if (flag >= 1)
		SDL_DestroyWindow(begin->sdl.window);
	if (flag >= 2)
		SDL_DestroyRenderer(begin->sdl.renderer);
	SDL_Quit();
	return (0);
}

int			usage(void)
{
	ft_putstr("Usage\n");
	return (0);
}
