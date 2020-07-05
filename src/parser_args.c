/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 22:49:53 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 22:49:57 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include <errno.h>

void	parse_reg(t_serv *s, int i)
{
	t_bytes			value;

	value.num = ft_atoi_check(&s->tok_ptr->content[1]);
	if (value.unum1 > REG_NUMBER)
	{
		errno = EDOM;
		ft_error(ERR_REG, s);
	}
	s->last_instr->args[i].type = T_REG;
	s->last_instr->args[i].value = value;
	s->last_instr->args[i].code = value;
	s->tok_ptr = s->tok_ptr->next;
}

void	parse_ind(t_serv *s, int i)
{
	t_bytes			value;
	t_list			*new;

	new = NULL;
	s->last_instr->args[i].type = T_IND;
	if (s->tok_ptr->type == LABEL_REF)
	{
		s->last_instr->args[i].label = s->tok_ptr->content;
		new = ft_memguru(sizeof(*new), &s->memguru);
		new->content = s->last_instr;
		ft_lstadd(&s->arg_labels, new);
	}
	else
	{
		value.num = ft_atoi_check(s->tok_ptr->content);
		s->last_instr->args[i].value = value;
		s->last_instr->args[i].code.unum4 = swap_bytes_old(value.unum4, 2);
	}
	s->tok_ptr = s->tok_ptr->next;
}

int		ft_is_bin(char *nb)
{
	size_t		i;

	errno = 0;
	i = ft_strlen(nb);
	if (i > 2 && nb[0] == '0' && nb[1] == 'b' && ft_isnumber(&nb[2]))
		return (1);
	errno = 33;
	return (0);
}

int		ft_is_hex(char *nb)
{
	size_t		i;

	errno = 0;
	i = ft_strlen(nb);
	if (i > 2 && nb[0] == '0' && (nb[1] == 'x' || nb[1] == 'X'))
	{
		nb = &nb[1];
		while (*(++nb))
		{
			if (!ft_strchr(HEX_CHARS, *nb))
			{
				errno = 33;
				return (0);
			}
		}
		return (1);
	}
	errno = 33;
	return (0);
}

void	parse_dir(t_serv *s, int i)
{
	t_list		*new;

	s->last_instr->args[i].type = T_DIR;
	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == NUM)
		s->last_instr->args[i].value.num = ft_atoi_check(s->tok_ptr->content);
	else if (s->tok_ptr->type == STRING && (ft_isnumber(s->tok_ptr->content) ||
	ft_is_hex(s->tok_ptr->content) || ft_is_bin(s->tok_ptr->content)))
		s->last_instr->args[i].value.num = ft_atoi_check(s->tok_ptr->content);
	else if (s->tok_ptr->type == LABEL_REF)
	{
		s->last_instr->args[i].label = s->tok_ptr->content;
		new = ft_memguru(sizeof(*new), &s->memguru);
		new->content = s->last_instr;
		ft_lstadd(&s->arg_labels, new);
	}
	else
		ft_error(ERR_PARSE_ARG, s);
	s->last_instr->args[i].code.unum4 = swap_bytes_old(s->last_instr->args[i]
			.value.unum4, s->last_instr->op->reduced_dir_size ? 2 : 4);
	s->tok_ptr = s->tok_ptr->next;
}

void	parse_arg(t_serv *s, int i)
{
	if (s->tok_ptr->type == DIRECT)
		parse_dir(s, i);
	else if (s->tok_ptr->type == STRING && s->tok_ptr->content[0] == REG_CHAR)
		parse_reg(s, i);
	else if (s->tok_ptr->type == NUM || s->tok_ptr->type == LABEL_REF
			|| s->tok_ptr->type == STRING)
		parse_ind(s, i);
	else
		ft_error(ERR_PARSE_ARG, s);
}

void	parse_arguments(t_serv *s)
{
	int			i;

	i = 0;
	s->tok_ptr = s->tok_ptr->next;
	while (s->tok_ptr->type != NEW_LINE)
	{
		parse_arg(s, i++);
		if (s->tok_ptr->type == SEPARATOR || s->tok_ptr->type == COMMENT)
			s->tok_ptr = s->tok_ptr->next;
		else if (s->tok_ptr->type == NEW_LINE)
			break ;
		else
			ft_error(ERR_PARSE_ARG, s);
	}
	add_instr(s, s->last_instr);
	s->last_instr = NULL;
}