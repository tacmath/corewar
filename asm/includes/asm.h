/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 13:24:57 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/29 14:15:17 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../../libft/includes/libft.h"
# include "op.h"

# define LABEL_NDEF "Error line %d : label doesn't exist\n"
# define WRONG_FORMAT "Error line %d : wrong argument format\n"
# define MANY_ARGS "Error line %d : too many arguments\n"
# define WRONG_TYPE "Error line %d : wrong argument type\n"

struct							s_arg_encoded
{
	uint32_t					arg;
	char						nb_bytes;
};
typedef struct s_arg_encoded	t_arg_encoded;

struct							s_label
{
	char						*label;
	int							pos;
	int							pos_oct;
	int							line;
};
typedef struct s_label			t_label;

struct							s_instr
{
	char						*command;
	char						nb_arg;
	char						*args[MAX_ARGS_NUMBER];
	int							pos;
	int							line;
};
typedef struct s_instr			t_instr;

struct							s_instr_asm
{
	char						op_code;
	unsigned char				ocp;
	t_arg_encoded				op_args[3];
};
typedef struct s_instr_asm		t_instr_asm;

struct							s_asm
{
	t_header					header;
	t_label						*labels;
	t_instr						*instrs;
	int							nb_instrs;
	char						*file_name;
	t_instr_asm					*instrs_asm;
	int							size;
	int							line;
};
typedef struct s_asm			t_asm;

extern t_op						g_op_tab[NB_OPS];

int								handle_pos(t_asm *sam);
int								compile(t_asm *sam);
int								write_champ(t_asm *sam);
int								get_command(t_asm *parse, char *line);
int								get_comment_and_name(t_asm *parse, int fd);
int								get_command_and_label(t_asm *parse, int fd);
int								get_pos_label(char *label, t_label *labels);
int								get_labels_value(t_asm *sam);

/*
** UTILS
*/
int								free_asm(t_asm *parse);
char							*jump_space(char *line);
int								remove_comment(char *line);
int								ft_search_char(char *str, char c);
void							print_instrs(t_asm sam);

/*
**	UTILS 2
*/
t_arg_type						get_arg_type(t_arg_type *arg);
char							get_arg_code(t_arg_type *arg);
int								search_op(char *command);

/*
** ENCODE_ARG
*/
void							encode_arg(t_arg_type *arg,
								t_arg_encoded *arg_encoded);

/*
** VALID ARG
*/
char							*valid_arg(t_arg_type *arg, t_label *labels);

/*
** CHECKS
*/
int								check_instrs(t_instr *instrs, int nb_instrs,
								t_label *labels);
int								check_args(t_instr instr, t_label *labels);
int								check_command(t_instr instr);

/*
** GET_STR
*/
char							*get_str(int fd, char *line,
								t_asm *parse, int n);

#endif
