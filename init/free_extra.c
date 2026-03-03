/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:11:40 by mcabeto           #+#    #+#             */
/*   Updated: 2026/03/03 14:11:44 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_env(t_data *data)
{
    t_env *aux;

    aux = data->b_env;
    if(aux)
    {
        while(aux)
        {
            data->b_env = aux->next;
            free(aux->name);
            free(aux->value);
            free(aux);
            aux = data->b_env;
        }
        data->b_env = NULL;
    }
}

void free_all(t_data *data)
{
    clear_hdoc(data);
	free_cmd_token(data);
	free_token(data);
    if(data->prev_fd != 0 && data->prev_fd != -1)
        close(data->prev_fd);
}

void free_env_all(t_data *data)
{
    free_env(data);
    free_all(data);
}