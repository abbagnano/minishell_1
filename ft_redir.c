/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/08 10:36:49 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_type_of_redir(char *line, int flag, int *i)
{
	ft_slide_quotes(line, i);
	if ((line[*i] == '>' && line[*i + 1] && line[*i + 1] != '>' && \
		line[*i + 1] == '<') || \
		(line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>' && \
		line[*i + 2] && line[*i + 2] == '>') || \
		(line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<' && \
		line[*i + 2] && line[*i + 2] == '<') || \
		((line[*i] == '<' || line[*i] == '>') && !(line[*i + 1])))
		flag = -1;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<' && \
	line[*i + 1] == '>')
		flag = 5;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<')
		flag = 1;
	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] != '>')
		flag = 2;
	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
		flag = 3;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
		flag = 4;
	if (flag >= 3)
		(*i)++;
	return (flag);
}

char	*ft_name_of_file(char *line, int i, int *x)
{
	int	c;

	(i)++;
	while (line[i] && line[i] == ' ')
		(i)++;
	if (line[i] == '"')
		ft_quottes(line, &i, &c, x);
	else if (line[i] == '\'')
		ft_quottes(line, &i, &c, x);
	else
	{
		c = (i);
		while (line[c] && line[c] != '<' && line[c] != '>' && line[c] != ' ')
			c++;
		*x = c;
	}
	if (c == (i) || c == i + 1)
		return (NULL);
	return (ft_substr(line, i, c - i));
}

int	ft_open_file(char *file, int flag, t_data *data)
{
	int	ret;

	if (file == NULL)
	{
		errno = 2;
		return (0);
	}		
	ret = 0;
	if (flag == 1)
		ret = ft_flag_1(file);
	else if (flag == 2)
		ret = ft_flag_2(file);
	else if (flag == 3)
		ret = ft_flag_3(file);
	else if (flag == 4)
		ret = ft_flag_4(file, data);
	else if (flag == 5)
		ret = ft_flag_5(file);
	free(file);
	return (ret);
}

int	ft_boh(t_redir *norm, t_data *data, char **line)
{
	char	*join;

	if ((norm->i > norm->x) && (norm->i == 0 || norm->flag < 3)
		&& ft_clean_line(*line, &norm->new_line, norm->i, norm->x) == 0)
		return (ft_redir_error(norm->new_line));
	else if ((norm->i > norm->x) && !(norm->i == 0 || norm->flag < 3)
		&& ft_clean_line(*line, &norm->new_line, norm->i - 1, norm->x) == 0)
		return (ft_redir_error(norm->new_line));
	norm->file = ft_name_of_file(*line, norm->i, &norm->x);
	while ((*line)[norm->x] && (*line)[norm->x] != ' '
		&& (*line)[norm->x] != '>' && (*line)[norm->x] != '<')
	{
		norm->i = norm->x - 1;
		join = ft_name_of_file(*line, norm->i, &norm->x);
		ft_strjoin_over(&norm->file, join);
		free(join);
	}
	if (ft_open_file(norm->file, norm->flag, data) == 0)
		return (ft_redir_error(norm->new_line));
	return (1);
}

int	ft_redir(char **line, t_data *data)
{
	t_redir	norm;

	norm.i = -1;
	norm.x = 0;
	norm.new_line = NULL;
	while ((*line)[++(norm.i)])
	{
		norm.flag = ft_type_of_redir(*line, 0, &(norm.i));
		if (norm.flag > 0)
		{
			if (ft_boh(&norm, data, line) == 0)
				return (0);
		}
		if (norm.flag == -1)
			return (ft_redir_error(norm.new_line));
	}
	if (norm.i > norm.x
		&& ft_clean_line(*line, &norm.new_line, norm.i, norm.x) == 0)
		return (ft_redir_error(norm.new_line));
	free(*line);
	*line = norm.new_line;
	return (1);
}
