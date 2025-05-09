/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:12:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/21 13:32:42 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_empty_redirout(t_cmd *cmd)
{
	t_redir	*current;
	int		fd;

	current = cmd->redir;
	while (current)
	{
		fd = -1;
		if (current->type == REDIR_OUT || current->type == REDIR_OUT_APPEND)
		{
			fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd >= 0)
				close(fd);
		}
		current = current->next;
	}
}

void	prepare_execution(t_cmd *cmd, int index, t_pid_data *pdata, t_cmd *head)
{
	pdata->gdata->status = 0;
	dup_and_close(pdata, index, cmd);
	if (!cmd->argv)
	{
		create_empty_redirout(cmd);
		exit_clean_child(pdata, head, 0);
	}
	if (!apply_redirections(cmd, index))
		exit_clean_child(pdata, head, EXIT_FAILURE);
	if (is_builtin_child(cmd))
	{
		exec_builtin_child_and_free(cmd, pdata, head);
		exit(0);
	}
}

void	print_message(t_cmd *cmd, char *message)
{
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(message, 2);
}

void	exit_and_clean(t_cmd *head, t_pid_data *pdata, char **env, int status)
{
	clear_env_array(env);
	exit_clean_child(pdata, head, status);
}

void	path_error(t_cmd *cmd, t_cmd *head, t_pid_data *pdata, char **env)
{
	if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
	{
		if (access(cmd->argv[0], F_OK) == 0 && is_directory(cmd->argv[0]))
		{
			print_message(cmd, ": Is a directory\n");
			exit_and_clean(head, pdata, env, 126);
		}
		if (access(cmd->argv[0], F_OK) == 0 && access(cmd->argv[0], X_OK) != 0)
		{
			print_message(cmd, ": Permission denied\n");
			exit_and_clean(head, pdata, env, 126);
		}
		if (access(cmd->argv[0], F_OK) != 0)
		{
			print_message(cmd, ": No such file or directory\n");
			exit_and_clean(head, pdata, env, 127);
		}
	}
	print_message(cmd, ": command not found\n");
	exit_and_clean(head, pdata, env, 127);
}
