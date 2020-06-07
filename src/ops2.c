/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:34:38 by lshellie          #+#    #+#             */
/*   Updated: 2020/03/04 10:46:45 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_sti(t_o *o)
{
	if ((o->t[2] == REG || o->t[2] == DIR) && o->t[0] == REG)
		return (1);
	return (0);
}

static int	check_ldi(t_o *o)
{
	if ((o->t[1] == REG || o->t[1] == DIR) && o->t[2] == REG)
		return (1);
	return (0);
}

void		do_ldi(t_main *m, t_cursor *c, t_o *o)
{
	int		store;
	int		a;

	store = o->x[2];
	get_reg(c, o);
	if (check_ldi(o))
	{
		if (c->op == LDI)
		{
			a = c->pos + (o->x[0] + o->x[1]) % IDX_MOD;
			c->reg[store] = read_mem(m->field, a, 4);
		}
		else if (c->op == LLDI)
		{
			a = c->pos + o->x[0] + o->x[1];
			c->reg[store] = read_mem(m->field, a, 4);
			modify_carry(c, c->reg[store]);
		}
	}
	c->op = 0;
	c->pos = c_p(c->pos + o->step);
}

void		do_st(t_main *m, t_cursor *c, t_o *o)
{
	int		a;

	if (o->t[0] == REG && o->t[1] == REG)
		c->reg[o->x[1]] = c->reg[o->x[0]];
	else if (o->t[0] == REG && o->t[1] == IND)
	{
		a = c->pos + o->x[1] % IDX_MOD;
		set_mem(m->field, c->reg[o->x[0]], a);
	}
	c->op = 0;
	c->pos = c_p(c->pos + o->step);
}

void		do_sti(t_main *m, t_cursor *c, t_o *o)
{
	int		store;
	int		a;

	store = o->x[0];
	get_reg(c, o);
	if (check_sti(o))
	{
		a = c->pos + (o->x[1] + o->x[2]) % IDX_MOD;
		set_mem(m->field, c->reg[store], a);
	}
	c->op = 0;
	c->pos = c_p(c->pos + o->step);
}