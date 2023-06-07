#include "get_next_line.h"

static int	ft_newline(char *str)
{
	int i = -1;

	while (str[++i])
	{
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

static int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

static char	*ft_strdup(char *str)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	while (str[i++])
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

static char	*ft_join(char *str1, char *str2)
{
	int		i = -1;
	int		j = 0;
	char	*new;
	if (!str1)
		return(ft_strdup(str2));
	new = malloc (1000);
	while (str1[++i])
		new[i] = str1[i];
	while(str2[j])
		new[i++] = str2[j++];
	new[i] = '\0';
	free(str1);
	return (new);
}

char	*get_next_line(int	fd)
{
	static int	i = 1;
	static char	*conta = 0;
	char	temp[BUFFER_SIZE + 1];

	if (fd < 0)
		return (NULL);
	while (i > 0)
	{
		i = read (fd, temp, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		if (i <= 0)
			break ;
		temp[i] = '\0';
		conta = ft_join(conta, temp);
		if (ft_newline(conta))
			break ;
	}
	if (!conta)
		return (NULL);
	int	j = 0;
	char	*ret;
	ret = malloc (1000);
	while (conta[j] && conta[j] != '\n')
	{
		ret[j] = conta[j];
		j++;
	}
	if (conta[j] == '\n')
	{
		ret[j++] = '\n';
		ret[j] = '\0';
	}
	else
	{
		ret[j] = '\0';
		free(conta);
		conta = NULL;
		return (ret);
	}
	int k = 0;
	if (conta[j])
	{
		char	*new;
		new = malloc(1000);
		while (conta[j])
			new[k++] = conta[j++];
		new[k] = '\0';
		free(conta);
		conta = new;
		return (ret);
	}
	else
	{
		free(conta);
		conta = NULL;
		return (ret);
	}
	return (NULL);
}
/*
int main()
{
	int fd = open("a.txt", O_RDONLY);
	int n = 3;
	char *str;
	while (n--)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		free(NULL);
	}
}
*/
