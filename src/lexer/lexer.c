/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:58:02 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/16 15:47:04 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_token(t_token **head, int *index)
{
	t_token	*new_token;

	new_token = create_token(TK_PIPE, NULL);
	if (!new_token)
		return (0);
	add_token(head, new_token);
	*index = *index + 1;
	return (1);
}

static int	parse(t_token **head, char *input, int *index, t_global_data *data)
{
	if (input[*index] == '|')
		return (new_token(head, index));
	else if (input[*index] == '<' || input[*index] == '>')
		return (parse_redirect(head, index, input));
	else
		return (parse_word(head, input, index, data));
}

t_token	*lexer(char *input, t_global_data *data)
{
	t_token	*head;
	int		index;

	head = NULL;
	index = 0;
	while (input[index])
	{
		while (input[index] && is_whitespace(input[index]))
			index++;
		if (!input[index])
			return (head);
		if (!parse(&head, input, &index, data))
		{
			free_token_list(head);
			return (NULL);
		}
	}
	return (head);
}
