

#include <stdio.h>

int ft_strchr_last(char *line, char c)
{
	int	i;
	int r;
	// char *line2;
	

	// line2 = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	i = 0;
	r = -1;
	while (line[i])
	{
		if (line[i] == c)
			r = i;
		i++;
	}
	return (r);
}


int main()
{
	char str[1024] = "ciaociaociacdcoaciacoacc";

	printf("index: %d\n", ft_strchr_last(str, 'i'));
	printf("line:%s\n", str);
	
}
