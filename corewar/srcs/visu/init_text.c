/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_text.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 15:54:35 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:28:04 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int			init_text(t_vm *vm)
{
	TTF_Font	*font;
	SDL_Color	color;
	char		*tmp;
	char		buf[2];
	int			n;

	if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, FONT_PATH, FONT))
			|| !(font = TTF_OpenFont(tmp, vm->visu.mem_len.h * 0.8)))
		return (0);
	free(tmp);
	color.r = TEXT_COLOR >> 16 & 0xFF;
	color.g = TEXT_COLOR >> 8 & 0xFF;
	color.b = TEXT_COLOR & 0xFF;
	color.a = 0;
	buf[1] = 0;
	n = -1;
	while (++n < 16)
	{
		buf[0] = n < 10 ? n + '0' : n + 'A' - 10;
		if (!(vm->visu.hex[n] = TTF_RenderText_Blended(font, buf, color)))
			return (0);
	}
	TTF_CloseFont(font);
	return (1);
}

int			init_info(t_vm *vm)
{
	int		w;
	int		h;
	char	*tmp;
	t_len	len;

	w = vm->visu.memory_coord.w / 5;
	h = vm->visu.memory_coord.h / 5;
	tmp = 0;
	if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, FONT_PATH, FONT))
			|| !(vm->visu.info_font = TTF_OpenFont(tmp,
					ft_min(w / 10, h / 10))))
		return (0);
	free(tmp);
	len.w = vm->visu.log_coord.w / 4;
	len.h = vm->visu.log_coord.h / 40;
	vm->visu.little_info = create_empty_frame(len, 0x00B8f1, 1);
	return (1);
}

int			init_champ_name(t_vm *vm)
{
	SDL_Color	color;
	int			n;
	SDL_Surface	*name;
	t_header	header;

	n = -1;
	color.r = 0;
	color.g = 184;
	color.b = 241;
	color.a = 0;
	while (++n < vm->nb_champs)
	{
		header = vm->champs_decoded[n].header;
		header.prog_name[20] = 0;
		ft_strtoupper(header.prog_name);
		name = TTF_RenderText_Blended(vm->visu.info_font,
				header.prog_name, color);
		if (!name)
			name = TTF_RenderText_Blended(vm->visu.info_font, "NO NAME",
					color);
		if (!rev_image(&vm->visu.champ_name[n], name))
			return (0);
	}
	return (1);
}

static int	init_info_text2(t_vm *vm, char info_text[8][14],
		char command_text[6][6], char process_text[3][8][8])
{
	int n;

	n = -1;
	while (++n < 24)
	{
		if (n < 4 && !(vm->visu.info_text[n] = TTF_RenderText_Blended(
						vm->visu.info_font, info_text[n],
						vm->visu.text_color)))
			return (0);
		if (n < 6 && !(vm->visu.command_text[n] = TTF_RenderText_Blended(
						vm->visu.info_font, command_text[n],
						vm->visu.text_color)))
			return (0);
		if (n != 7 && !(vm->visu.process_text[n / 8][n % 8] =
					TTF_RenderText_Blended(vm->visu.info_font,
						process_text[n / 8][n % 8],
						vm->visu.text_color)))
			return (0);
	}
	return (1);
}

int			init_info_text(t_vm *vm)
{
	static char	info_text[8][14] =
	{"CYCLE", "PROCESS", "CYCLE TO DIE", "SPEED"};
	static char	command_text[6][6] =
	{"type:", "name:", "ocp:", "arg1:", "arg2:", "arg3:"};
	static char	process_text[3][8][8] =
	{{"type:", "numero:", "champ:", "carry:", "live:", "instr:", "cycle:", {0}},
		{"Reg1:", "Reg2:", "Reg3:", "Reg4:", "Reg5:", "Reg6", "Reg7", "Reg8"},
	{"Reg9:", "Reg10:", "Reg11:", "Reg12:", "Reg13:", "Reg14", "Reg15", "Reg16"}
	};

	vm->visu.text_color.r = 0;
	vm->visu.text_color.g = 170;
	vm->visu.text_color.b = 232;
	vm->visu.text_color.a = 0;
	if (!init_info_text2(vm, info_text, command_text, process_text))
		return (0);
	return (1);
}
