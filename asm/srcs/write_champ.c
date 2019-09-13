/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_champ.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 17:11:33 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 13:44:21 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	write_arg(t_arg_encoded *arg, char *buff, int *k)
{
	ft_memcpy(&buff[*k], (char *)mem_swap(&arg->arg, arg->nb_bytes),
			arg->nb_bytes);
	*k += arg->nb_bytes;
}

int		get_file_name(t_asm *sam)
{
	char *tmp;

	sam->file_name[ft_strlen(sam->file_name) - 1] = 'c';
	tmp = sam->file_name;
	if (!(sam->file_name = ft_strjoin(sam->file_name, "or")))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

char	*write_buffer(t_asm *sam)
{
	char			*buff;
	int				i;
	int				j;
	int				k;
	unsigned char	opcode;

	if (!(buff = ft_memalloc(sam->size)))
		return (NULL);
	i = -1;
	k = 0;
	while (++i < sam->nb_instrs && (j = -1))
	{
		opcode = sam->instrs_asm[i].op_code;
		buff[k] = opcode;
		k++;
		if (!(opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15))
		{
			buff[k] = sam->instrs_asm[i].ocp;
			k++;
		}
		while (++j < sam->instrs[i].nb_arg)
			write_arg(&(sam->instrs_asm[i].op_args[j]), buff, &k);
	}
	return (buff);
}

int		write_champ(t_asm *sam)
{
	int				fd;
	char			*buff;

	if (!get_file_name(sam))
		return (0);
	if (!(fd = open(sam->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666)))
		return (!ft_dprintf(2, "Open failed\n"));
	ft_printf("Writing output program to %s\n", sam->file_name);
	write(fd, &(sam->header), sizeof(t_header));
	mem_swap(&sam->size, sizeof(sam->size));
	if (!(buff = write_buffer(sam)))
	{
		close(fd);
		return (0);
	}
	write(fd, buff, sam->size);
	free(buff);
	close(fd);
	return (1);
}
