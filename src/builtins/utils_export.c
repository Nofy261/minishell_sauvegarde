/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:33:00 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/15 09:54:56 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_node(t_envp *i, t_envp *j)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = i->name;
	i->name = j->name;
	j->name = tmp_name;
	tmp_value = i->value;
	i->value = j->value;
	j->value = tmp_value;
}

void	ft_sort_params(t_envp *env)
{
	t_envp	*i;
	t_envp	*j;

	if (!env || !env->next)
		return ;
	i = env;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (ft_strcmp(i->name, j->name) > 0)
				swap_node(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

// ajout
// Cas classique sans '+='
static int	is_classic_var_invalid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || (str[i] >= '0' && str[i] <= '9'))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

//ajout
static int is_plus_equal_var_invalid(char *str, char *plus_equal)
{
    int i;
    int len;
	
	i = 0;
    len = plus_equal - str; // Longueur du nom avant le '+'

    if (len == 0 || (str[0] >= '0' && str[0] <= '9'))
        return (1); // Invalide : vide ou commence par chiffre
    while (i < len)
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (1); // caractère non autorisé
        i++;
    }
    return (0);
}

// modifié
int is_var_valid(char *str)
{
    int     result;
    char   *plus_equal;

    plus_equal = ft_strnstr(str, "+=", ft_strlen(str));
    if (plus_equal)
    {
        result = is_plus_equal_var_invalid(str, plus_equal);
        return (result);
    }
    result = is_classic_var_invalid(str);
    return (result);
}


int	is_var_exist(char *argv, t_global_data *data)
{
	t_envp	*tmp;
	size_t	len;
	char	*val;

	if (!data->envp)
		return (1);
	tmp = data->envp;
	val = ft_strchr(argv, '=');
	if (val)
		len = ft_strlen(argv) - ft_strlen(val);
	else
		len = ft_strlen(argv);
	while (tmp)
	{
		if (ft_strncmp(argv, tmp->name, len) == 0
			&& ft_strlen(tmp->name) == len)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
