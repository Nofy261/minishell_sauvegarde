/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:32:33 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/15 11:48:56 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//	STRING
int		is_whitespace(char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_envpadd_back(t_envp **lst, t_envp *new);
char	*ft_strndup(char *s, size_t n);

//	ENV_UTILS
void	clear_env(t_envp *envp);
void	clear_env_array(char **envp);
int		ft_envlen(t_envp *envp);
t_envp	*ft_lastenv(t_envp *envp);
t_envp	*search_var(t_envp *envp, char *str);

//	ENV
t_envp	*init_var(char *envp);
t_envp	*init_env(char **envp);
char	**convert_env(t_envp *envp);
void	set_minishlvl(t_envp *envp);

#endif