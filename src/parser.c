/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:05:32 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:34 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

t_instr			*init_instr(t_serv *s)
{
	t_instr		*new;

	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s);
	new->label = NULL;
	new->op = NULL;
	new->next = NULL;
	return (new);
}

t_op			*get_op(char *name)
{
	int		i;

	i = 0;
	while (i < (sizeof(g_op) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op[i].name, name))
			return (&g_op[i]);
		i++;
	}
	return (NULL);
}

static void		add_instr(t_serv *s, t_instr *new)
{
	t_instr		*ptr;

	if (!s->instr)
		s->instr = new;
	else
	{
		ptr = s->instr;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

static void	parse_prog_comment(t_serv *s)
{
	size_t		len;

	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == STRING)
	{
		len = ft_strlen(s->tok_ptr->content);
		if (!len || len > COMMENT_LENGTH)
			ft_error(ERR_COMMENT_LEN, s);
		ft_strcpy(s->header.comment, s->tok_ptr->content);
	}
	else
		ft_error(ERR_COMMENT_LEN, s);
}

static void	parse_prog_name(t_serv *s)
{
	size_t		len;

	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == STRING)
	{
		len = ft_strlen(s->tok_ptr->content);
		if (!len || len > PROG_NAME_LENGTH)
			ft_error(ERR_NAME_LEN, s);
		ft_strcpy(s->header.prog_name, s->tok_ptr->content);
	}
	else
		ft_error(ERR_NAME_LEN, s);
}
static void	parse_reg(t_serv *s)
{

}

static void	parse_ind(t_serv *s, int i)
{
	s->last_instr->args[i].type = T_IND;
	s->last_instr->args[i].value = ft_atoi(s->tok_ptr->content);
}

static void	parse_dir(t_serv *s, int i)
{
	s->last_instr->args[i].type = DIRECT;
	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == NUM)
		s->last_instr->args[i].value = ft_atoi(s->tok_ptr->content);
	else if (s->tok_ptr->type == LABEL)
	{
		s->tok_ptr = s->tok_ptr->next;
		if (s->tok_ptr->type == STRING || s->tok_ptr->)
			s->last_instr->args[i].label = s->tok_ptr->content;
		else
	}
}

static int8_t	get_arg_type(t_type type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}

static void	parse_arg(t_serv *s, int i)
{
	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == DIRECT)
		parse_dir(s, i);
	else if (s->tok_ptr->type == STRING)
	{

	}
	else if (s->tok_ptr->type == NUM)
		parse_ind(s);
	else
		ft_error(ERR_PARSE_ARG, s);
}

static void	parse_arguments(t_serv *s)
{
	int			i;
	t_op		*op;

	i = -1;
	op = s->last_instr->op;
	while (++i < op->args_num)
	{
		parse_arg(s, i);
		if (op->args_types[i] == T_REG)
			parse_reg(s);
		else if (op->args_types[i] == T_DIR)
			parse_dir(s);
		else if (op->args_types[i] == T_IND)
			parse_ind(s);
	}
}

static void	parse_str(t_serv *s)
{
	t_instr		*new;
	int			i;
	int			set;
	t_op		*op;

	if (s->tok_ptr->next->type == LABEL)
	{
		new = init_instr(s);
		new->label = s->tok_ptr->content;
		add_instr(s, new);
		s->last_instr = new;
		s->tok_ptr = s->tok_ptr->next;
	}
	else if ((op = get_op(s->tok_ptr->content)))
	{
		if (s->last_instr)
			s->last_instr->op = op;
		else
		{
			new = init_instr(s);
			new->op = op;
			add_instr(s, new);
			s->last_instr = new;
		}
		parse_arguments(s);
	}
	else
		ft_error(ERR_PARSE_STRING, s);
}

static void	parse_all_labels(t_serv *s)
{

}

void		parser(t_serv *s)
{
	s->tok_ptr = s->tokens;
	while (s->tok_ptr)
	{
		ft_printf("%s ", s->tok_ptr->content);
		if (s->tok_ptr->type == PROG_NAME)
			parse_prog_name(s);
		else if (s->tok_ptr->type == PROG_COMMENT)
			parse_prog_comment(s);
		else if (s->tok_ptr->type == STRING)
			parse_str(s);
		else if (s->tok_ptr->type == COMMENT)
		{
			s->tok_ptr = s->tok_ptr->next;
			continue;
		}
		s->tok_ptr = s->tok_ptr->next;
	}
	parse_all_labels(s);
}
