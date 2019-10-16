/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/28 15:09:43 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 13:53:21 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define FRAME_LEN 1000
# define FRAME_WIDTH 382

# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ncurses.h>
# include "../../libft/includes/libft.h"
# include "op.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include "SDL_image.h"
# include "SDL.h"
# include "errors.h"

# define INVALID_MAGIC 666
# define INVALID_HEADER 118
# define USAGE 218
# define MAX_PLAYER 999

# define ASSET_PATH		"asset/"
# define IMAGE_PATH		"image/"
# define FONT_PATH		"font/"
# define SOUND_PATH		"Sound/"

# define WINDOWS_HEIGHT	1100
# define FONT			"TeraThin.ttf"
# define MUSIC			"Toxic.mid"
# define TEXT_COLOR		0x000000
# define BACKGROUND		0x000000
# define NO_PLAYER		0xFFFFFF
# define PROCESS_COLOR 0xFF0000
# define CYCLE1 0xFF0000
# define CYCLE2 0xFF00
# define PRINT 0
# define RESET 1
# define NEXT_PROCESS 2
# define PREVIOUS_PROCESS 3
# define NORMAL	0
# define KITSH	1

extern t_op	g_op_tab[NB_OPS];

struct							s_options
{
	uint32_t					num_champs[MAX_PLAYERS];
	char						verbose;
	char						visu;
	char						visu_intro;
	int							cycle_dump;
	int							nb_champs;
	char						*players_file[MAX_PLAYERS];
};
typedef struct s_options		t_options;

struct							s_instr_ret
{
	int							code;
	uint32_t					data;
	char						ocp;
	int32_t						args[3];
};
typedef struct s_instr_ret		t_instr_ret;

struct							s_instr_vars
{
	char						op;
	char						ocp;
	int							index_op;
	int32_t						args[3];
	int32_t						f_args[3];
	int32_t						c_args[3];
	int							idx;
	char						transform;
	char						ind_size;
	char						swap;
};
typedef struct s_instr_vars		t_instr_vars;

struct							s_champ_decoded
{
	t_header					header;
	char						*prog;
	uint32_t					id;
	int							visu_id;
	int							start;
};
typedef struct s_champ_decoded	t_champ_decoded;

struct							s_process
{
	uint32_t					champ_id;
	int							visu_id;
	int							pc;
	unsigned char				carry;
	uint32_t					regs[REG_NUMBER];
	int							cycles_left;
	char						op;
	char						live;
	uint32_t					num;
	uint32_t					cycle_last_live;
};
typedef struct s_process		t_process;

struct							s_process_list
{
	t_process					process;
	struct s_process_list		*next;
};
typedef struct s_process_list	t_process_list;

struct							s_arena
{
	unsigned char				mem[MEM_SIZE];
	unsigned char				champs[MEM_SIZE];
	unsigned char				processes[MEM_SIZE];
};
typedef struct s_arena			t_arena;

struct							s_len
{
	int h;
	int w;
};
typedef struct s_len			t_len;

struct							s_visu
{
	SDL_Window					*window;
	t_len						win_len;
	t_len						mem_len;
	int							speed;
	int							frame_speed;
	SDL_Surface					*window_surface;
	SDL_Surface					*arena_background;
	SDL_Surface					*arena;
	SDL_Rect					arena_coord;
	SDL_Rect					memory_coord;
	SDL_Surface					*log_background;
	SDL_Surface					*log;
	SDL_Rect					log_coord;
	SDL_Surface					*little_info;
	TTF_Font					*info_font;
	int							info_pages;
	SDL_Surface					*hex[16];
	SDL_Surface					*cycle;
	SDL_Surface					*process_src;
	SDL_Surface					*process;
	SDL_Surface					*highlight;
	SDL_Surface					*info_text[4];
	SDL_Surface					*process_text[3][8];
	SDL_Surface					*command_text[6];
	SDL_Color					text_color;
	SDL_Surface					*champ_name[MAX_PLAYERS];
	SDL_Surface					*champ_src[MAX_PLAYERS];
	SDL_Surface					*champ[MAX_PLAYERS];
	SDL_Surface					*champ_jauge_src[MAX_PLAYERS];
	SDL_Surface					*champ_jauge[MAX_PLAYERS];
	SDL_Surface					*champ_jauge_halo_src[MAX_PLAYERS];
	SDL_Surface					*champ_jauge_halo[MAX_PLAYERS];
	char						*path;
	Mix_Music					*mus;
	char						mode;
};
typedef struct s_visu			t_visu;

struct							s_instr_v
{
	uint16_t					beg;
	char						size;
	char						instr;
	unsigned char				ocp;
	char						nb_args;
	int32_t						args[3];
	char						valid;
};

typedef struct s_instr_v		t_instr_v;

struct							s_vm
{
	t_visu						visu;
	int							cycle;
	int							cycle_left_to_die;
	int							cycle_to_die;
	t_process_list				*list;
	t_arena						arena;
	int							nbr_champs;
	t_champ_decoded				*champs_decoded;
	char						nb_champs;
	int							nb_live;
	int							last_live;
	uint32_t					num_procs;
	uint32_t					nb_procs;
	char						*str_ctd;
	t_options					options;
	uint						live_champs[MAX_PLAYERS];
};
typedef struct s_vm				t_vm;

t_champ_decoded					*parser(char **players, int nb_champs,
									uint32_t *num_champs);
int								get_nb_champs(int ac, char **av);
t_instr_v						get_instr_info(int16_t mem, t_vm *vm);
void							*free_champs_decoded(t_champ_decoded
									*champs_decoded);
int								init_visu(t_vm *vm);
void							print_mem(t_vm *vm);
void							quit_visu(t_vm *vm);
void							print_end(t_vm *vm, char *end, char *font);
void							play_music(t_vm *vm);
int								ft_sqrt(int nb);
unsigned char					color_max(unsigned char c1, unsigned char c2);
void							fill_memory(t_vm *vm);
void							fill_log(t_vm *vm);
void							print_cycle(t_vm *vm);
void							print_memory(t_vm *vm);
void							print_log(t_vm *vm);
void							print_all(t_vm *vm);
void							resize_window(t_vm *vm, int x, int y);
SDL_Rect						treat_coord(t_vm *vm, int x, int y,
									int nb_info);
char							*get_champ_name(t_vm *vm, int id, int max_len);
void							pause_visu(t_vm *vm);
void							free_info(char **info);
int								print_info_mem(t_vm *vm, SDL_Rect coord,
									t_instr_v instr);
int								print_info_process(t_vm *vm, SDL_Rect coord,
									t_process process, int change);
int								init_text(t_vm *vm);
void							get_event(t_vm *vm);
SDL_Surface						*create_empty_frame(t_len
								frame_len, int frame_color, int len);
void							init_coord(t_vm *vm,
								int win_width, int win_height);
int								resize_all_images(t_vm *vm);
int								init_champ_name(t_vm *vm);
int								init_info_text(t_vm *vm);
int								init_info(t_vm *vm);
int								init_cycle(t_vm *vm);
void							free_text(t_vm *vm);
void							free_all_old_images(t_vm *vm);
void							free_images_src(t_vm *vm);
void							launch_intro(t_vm *vm);
int								init_cycle(t_vm *vm);
char							*ft_strtoupper(char *str);
void							get_width(t_vm *vm, int *w, int *h, int choice);
int								load_images(t_vm *vm);
int								print_info(t_vm *vm, int x, int y);
int								print_instr(t_vm *vm, int mem, int status);
int								highlight_mem(t_vm *vm, int start, int len);
int								get_max_process_num(t_process **process);
int								print_process_1(t_process ***process,
								int *process_num, int *old_mem);
int								print_process(t_vm *vm, int mem, int status);
int								rev_image(SDL_Surface **new, SDL_Surface *ref);
void							print_jauge(t_vm *vm);

/*
** error.c
*/
int								print_error(int error);
int								error_int(int error_code);
void							*error_null(int error_code);
/*
** PROCESS LIST
*/
t_process_list					*create_process_list();
int								add_process(t_process_list **list);
void							clear_process_list(t_process_list **list);
void							init_process(t_process *process, uint32_t id,
								int pc, int num);
t_process_list					*init_process_list(t_champ_decoded
								*champs_decoded, int nb_champs);

/*
** INSTRUCTIONS, please refer to corresponding .c
*/
void							live(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							ld(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							st(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							add(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							sub(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							and(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							or(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							xor(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							zjmp(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							ldi(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							sti(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							fork_i(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							lld(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							lldi(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							lfork(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);
void							aff(t_process *pro, t_arena *ar,
									t_instr_ret *ret, char verbose);

int								get_args(t_process *pro, t_arena *ar,
									t_instr_vars *vars);

/*
** VERBOSE, please refer to corresponding .c
*/
void							verbose(t_process *pro, t_instr_vars *vars);
void							generic_verbose(t_instr_vars *vars);
void							logical_verbose(t_instr_vars *vars);
void							ld_verbose(t_instr_vars *vars);
void							st_verbose(t_instr_vars *vars);
void							fork_verbose(t_process *pro,
									t_instr_vars *vars);
void							lfork_verbose(t_process *pro,
									t_instr_vars *vars);
void							zjmp_verbose(t_process *pro,
									t_instr_vars *vars);
void							sti_verbose(t_process *pro, t_instr_vars *vars);
void							ldi_verbose(t_process *pro, t_instr_vars *vars);
void							lldi_verbose(t_process *pro,
									t_instr_vars *vars);

/*
** instr_utils.c
*/
int								get_mempos(int nbr);
void							*memload(void *dst, void *src,
									size_t n, int off);
void							memstore(void *arena, void *src, size_t n,
									size_t off);
void							memsetcir(void *arena, char src, int n,
									int off);

/*
**  instr_utils2.c
*/

int								search_op(int opcode);
void							get_infos(t_process *pro, t_arena *ar,
									t_instr_vars *vars);
int								is_reg(char nb);

/*
**  instr_args.c
*/
int								get_args(t_process *pro, t_arena *ar,
									t_instr_vars *vars);
void							set_vars(t_instr_vars *vars, char transform,
									int idx, char ind_size);

/*
** options.c
*/
void							print_options(t_options *options);
int								get_options(int ac, char **av,
									t_options *options);

/*
** OPTIONS2
*/
int								is_uint(char *str);
int								is_int(char *str);
uint32_t						next_num(uint32_t *arr, int nb_champs);
void							print_options(t_options *options);

/*
** VM
*/
int								corewar(t_vm *vm);

/*
** VM 2
*/
void							decrease_ctd(t_vm *vm, int *last_cycle);
void							delete_processes(t_vm *vm);
void							del_process_ctd(t_vm *vm, t_process_list **temp,
								t_process_list **prev);
void							get_instr(t_vm *vm, t_process *process);

/*
** VM 3
*/
int								execute_instr(t_vm *vm, t_process *process);
int								get_size_args(char ocp, int index_op);

/*
** VERBOSE
*/
void							verbose_begin(t_vm *vm);
void							verbose_end(t_vm *vm);
void							print_adv(int size_instr, void *mem, int pc);

/*
** RET_INSTR
*/
int								ret_instr(t_vm *vm, t_instr_ret *instr_ret,
								t_process *process);

/*
** UTILS
*/
unsigned int					pow2(char n);
int								is_instr_without_ocp(int nb);
char							*get_exec_path(char *name);
void							clean(t_vm *vm);
int								search_champ(uint32_t *num_champs,
								int nb_champs, uint32_t id);

/*
** UTILS 2
*/
void							write_bytes(void *mem, size_t len, char byte);
void							print_bytes(void *mem, int size, int pc);
int								memdump(t_vm *vm);

/*
** GET_INSTR_INFO
*/
t_instr_v						get_instr_info(int16_t mem, t_vm *vm);

/*
** EXPLORER
*/
t_process						**get_process(int16_t mem, t_vm *vm);
void							get_multiple_args(t_vm *vm, t_instr_v *ret);
t_instr_v						complete_instr(t_vm *vm, t_instr_v *ret);

extern void						(*g_instrs_f[NB_OPS])(t_process *proc,
								t_arena *arena, t_instr_ret *ret, char verbose);
/*
**  CHECK_COR
*/

int								check_cor(char *filename);

#endif
