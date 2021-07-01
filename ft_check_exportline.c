#include "my_minishell.h"
#include "my_minishell2.h"


void	ft_check_exportline(char *str, t_data *data)
{
	int 	x;	

	x = 0;
	while (str[x] && str[x] != '=')		//-export ARG =ciao NON DEVE FUNZ
	{
		if (str[x] == ' ')
		{
			while (str[x] == ' ')
				x++;
			if (!str[x])
				break ;
			ft_write("export: \'");
			ft_write(str + x);
			ft_write("\': not a valid identifier\n");
			return ;
		}
		x++;
	}
	ft_add_env(str, data);
}

void	ft_matrline(char *str, t_data *data)
{
	// char	**matr;
	int		x;

	ft_check_exportline(str, data);			///  gestire   export ZZ AA =123
						/// 			fa export delle var ZZ=''  AA=''  e poi error!

	// matr = NULL;
	// x = 0;
	// matr[x] = str;
	// x = 0;
	// while (matr[x])
		// ft_check_exportline(matr[x++], data);
}