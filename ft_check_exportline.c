#include "my_minishell.h"
#include "my_minishell2.h"

// int	ft_check_exportline2(char *str)
// {
// 	int 	x;	

// 	x = 1;	//saltiamo '='
// 	while (str[x])
// 	{
// 		if (str[x] == ' ')
// 		{
// 			while (str[x] == ' ')
// 				x++;
// 			if (!str[x])
// 				break ;
// 		}
// 		if (str[x] == 39)
// 		{
// 			x++;
// 			if (!str[x])
// 				return (1);
// 			while (str[x] && str[x] != 39)
// 				x++;
// 		}
// 		else if (str[x] == 34)
// 		{
// 			x++;
// 			if (!str[x])
// 				return (1);
// 			while (str[x] && str[x] != 34)
// 				x++;
// 		}
// 		if (str[x] == '(' || str[x] == ')' || str[x] == '&')
// 		{
// 			ft_write("33 export: \'");
// 			ft_write(str + x);
// 			ft_write("\': not a valid identifier\n");
// 			return (0);
// 		}
// 		x++;
// 	}
// 	return (1);
// }

void	ft_env_join(char **str, t_data *data)
{
	t_read	*tmp;
	int		len;
	// char	*save;

	len = ft_strchr('=', *str);
	tmp = *data->env_head;
	while (tmp)
	{
			// printf("\t%s\t%d\t%d\n", tmp->line, ft_strncmp(*str, tmp->line, len), ft_strncmp(*str, tmp->line, len - 1));
		if (tmp && ft_strncmp(*str, tmp->line, len) == -18 && !ft_strncmp(*str, tmp->line, len - 1))
		{
			// save = *str;
			*str = ft_strjoin(tmp->line, *str + len + 1);
			// printf("new:%s\n", *str);
			// free(save);			
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_check_exportline(char *str, t_data *data)
{
	int 	x;
	int		fix;

	fix = 0;
	x = 0;
	if (str[x] == '=')
	{
		ft_write("export: \'");
		ft_write(str /*+ x*/);
		ft_write("\': not a valid identifier\n");
		// ft_write(strerror(errno));	//	Undefined error: 0
		// ft_write("\n");
		errno = 1;
		return ;
	}
	while (str[x] && str[x] != '=')		//-export ARG =ciao NON DEVE FUNZ
	{
		if (str[x] == ' ')
		{
			while (str[x] == ' ')
				x++;
			if (!str[x])
				break ;
			// ft_write(strerror(errno));	//operation not permitted
			// ft_write("\n");
			ft_write("export: \'");
			ft_write(str /*+ x*/);
			ft_write("\': not a valid identifier\n");
			errno = 1;
			return ;
		}
		if (x != 0 && str[x] == '+' && str[x + 1] == '=')
		{
			ft_env_join(&str, data);
			fix++;
			break ;
		}
		// if (str[x] == 39)
		// {
		// 	x++;
		// 	while (str[x] && str[x] != 39 && str[x] != ' ' && str[x] != '=')
		// 		x++;
		// 	if (str[x] == '=')
		// 		break ;
		// }
		// else if (str[x] == 34)
		// {
		// 	x++;
		// 	while (str[x] && str[x] != 34 && str[x] != ' ' && str[x] != '=')
		// 		x++;
		// 	if (str[x] == '=')
		// 		break ;
		// }
		if (str[x] == '_' || (str[x] >= 'A' && str[x] <= 'Z') || (str[x] >= 'a' && str[x] <= 'z') || (str[x] >= '0' && str[x] <= '9') || str[x] == '=' || str[x] == 39 | str[x] == 34)
			x++;
		else
		{
			ft_write("export: \'");
			ft_write(str /*+ x*/);
			ft_write("\': not a valid identifier\n");
			errno = 1;
			return ;
		}
	}
	if (!str[x + 1])
	{
		str[x] = '\0';
		ft_fix_env(&str);
		fix++;
		// ft_add_env(str, data);
	}
	// else if (ft_check_exportline2(str + x))
	// printf("addenv:%s\n", str);
		ft_add_env(str, fix, data);
		// free(str);
}

void	ft_len_new(char **new, char *str)
{
	int	z;

	z = 0;
	while (str[z] && str[z] != ' ')
	{
		if (str[z] == 39)
		{
			z++;
			while (str[z] && str[z] != 39)
				z++;
		}
		else if (str[z] == 34)
		{
			z++;
			while (str[z] && str[z] != 34)
				z++;
		}
		z++;
	}
	*new = (char *)malloc(sizeof(char) * (z + 1));
}

void	ft_find_arg(char *str, int *x, int y, char ***matr)
{
	char	**new;
	char	**tmp;
	int		z;
	int		a;

	new = (char **)malloc(sizeof(char *) * (y + 2));
	tmp = *matr;
	y = 0;
	while (tmp && tmp[y])
	{
		new[y] = tmp[y];
		y++;
	}
	ft_len_new(&new[y], str);
	a = 0;
	z = 0;
	while (str[z + a] && str[z + a] != ' ')
	{
		if (str[z + a] == 39)
		{
			// new[y][z + a] = str[z + a];
			a++;
			while (str[z + a] && str[z + a] != 39)
			{
				new[y][z] = str[z + a];
				z++;
			}
			a++;
		}
		else if (str[z + a] == 34)
		{
			// new[y][z + a] = str[z + a];
			a++;
			while (str[z + a] && str[z + a] != 34)
			{
				new[y][z] = str[z + a];
				z++;
			}
			a++;
		}
		if (!str[z + a])
			break ;
		new[y][z] = str[z + a];
		z++;
	}
	new[y][z] = '\0';
	y++;
	new[y] = NULL;
	if (str[z + a] == ' ')
		z++;
	*x += z + a;
	free(*matr);
	*matr = new;
}

void	ft_matrline(char *str, t_data *data)
{
	char	**matr;
	int		x;
	int		y;

	// ft_check_exportline(str, data);			///  gestire   export ZZ AA =123
						/// 			fa export delle var ZZ=''  AA=''  e poi error!

	matr = NULL;
	x = 0;
	y = 0;
	while (str[x])
	{
		// printf("matrline:-%s-\tx:%d\n", str + x, x);
		ft_find_arg(str + x, &x, y, &matr);
		y++;
	}
	// x = 0;
	// while (matr[x])
	// 	printf("-%s-\n", matr[x++]);
	x = 0;
	while (matr[x])
		ft_check_exportline(matr[x++], data);
	x = 0;
	while (matr[x])
		free(matr[x++]);
	free(matr);
}