/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:26:56 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/18 14:59:29 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

//	SET
void	set_parent_signals(void);
void	set_heredoc_signals(void);
void	set_child_signals(void);

//	HANDLER
void	handle_sigint_no_redisplay(int sig);
void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);
void	handle_signal(t_global_data *data);

#endif