/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/29 13:58:14 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 18:45:17 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

#define INVALID_MAGIC 666
#define INVALID_HEADER 118
#define USAGE 218
#define MAX_PLAYER 999

int		print_error(int error)
{
	if (error == ERROR)
		ft_putendl_fd("Error", 2);
	if (error == ALLOC_FAILED)
		ft_putendl_fd("Allocation failed", 2);
	if (error == OPEN_FAILED)
		ft_putendl_fd("Open failed", 2);
	if (error == READ_FAILED)
		ft_putendl_fd("Read failed", 2);
	if (error == BAD_FORMAT)
		ft_putendl_fd("Only .cor files are allowed", 2);
	if (error == SMALL_FILE)
		ft_putendl_fd("The file is too small", 2);
	if (error == BIG_FILE)
		ft_putendl_fd("The file is too big", 2);
	if (error == BAD_HEADER)
		ft_putendl_fd("The header is missing", 2);
	if (error == INVALID_MAGIC)
		ft_putendl_fd("Wrong magic number", 2);
	if (error == INVALID_HEADER)
		ft_putendl_fd("The header is invalid", 2);
	if (error == USAGE)
		ft_putendl_fd("./corewar ....", 2);
	if (error == MAX_PLAYER)
		ft_putendl_fd("Too many player selected", 2);
	return (1);
}

void	*error_null(int error_code)
{
	print_error(error_code);
	return (NULL);
}

int		error_int(int error_code)
{
	print_error(error_code);
	return (0);
}
