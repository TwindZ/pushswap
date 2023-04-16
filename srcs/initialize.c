/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:29:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/04/13 09:49:48 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_data	*ft_init(int argc, char **argv)
{
	static t_data *data;	
	
	if(!data)
	{
		data = malloc(sizeof(t_data));
		data->stack_a = NULL;
		data->stack_b = NULL;
		data->arg = NULL;
		data->free_flag = 0;
		data->stacksize = 0;
		ft_arg(argc, argv, data);
		data->stacksize = ft_stacksize(data->stack_a);
	}
	return(data);
}

void	ft_arg(int argc, char **argv, t_data *data)
{
	if(argc == 2)
	{
		data->arg = ft_split(argv[1], ' ');
		data->free_flag = 1;
		ft_stack(data, 0);
	}
	else
	{
		data->arg = argv;
		ft_stack(data, 1);
	}
}

void	ft_stack(t_data *data, int i)
{
	long int nb;
	t_stack *temp;

	temp = NULL;

	if(ft_empty(data->arg + i) == TRUE && ft_only_number(data->arg, i) == TRUE)
	{
		while (data->arg[i])
		{
			nb = ft_atoi(data->arg[i]);
			if(data->stack_a == NULL && nb <= INT_MAX && nb >= INT_MIN)
			{
				data->stack_a = ft_lstnew_int(nb);
				i++;
			}
			else if(nb <= INT_MAX && nb >= INT_MIN)
			{			
				temp = data->stack_a;
				temp = ft_stacklast(temp);
				temp->next = ft_lstnew_int(nb);
				i++;
			}
			else
			{
				ft_pushswap_free(1);
			}
		}
	}
}

void	ft_index(t_data *data)
{
	int i;
	int nb;
	t_stack *temp;

	temp = data->stack_a;
	nb = INT_MAX;
	i = 0;
	while(i <= data->stacksize)
	{
		while(temp != NULL)
		{
			if(nb > temp->content && temp->index == 0)
				nb = temp->content;
			temp = temp->next;
		}
		temp = data->stack_a;
		while(temp->content != nb)
			temp = temp->next;
		temp->index = i;
		temp = data->stack_a;
		nb = INT_MAX;
		i++;
	}	
}