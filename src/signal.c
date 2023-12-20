/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:20:29 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/20 18:20:47 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void sigint_handler(int sig) {
    write(1, "\nminishell> ", 12);
}

void setup_signal_handlers() {
    signal(SIGINT, sigint_handler);
}