#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>



static    int    ft_is_nl(char *str)
{
    int    i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '\n')
            return (1);
    }
    return (0);
}

static int    ft_len(char *str)
{
    int    i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

static    char    *ft_dup(char *str)
{
    int    i;
    char *new;

    new = malloc (sizeof(char) * (ft_len(str)+ 1));
    i = -1;
    while (str[++i])
        new[i] = str[i];
    new[i] = '\0';
    return (new);
}
static    char    *ft_merge(char *str1,char *str2)
{
    int    i = -1;
    int    j = 0;
    char    *new;
    if (!str1)
        return (ft_dup(str2));
    new = malloc (1000);
    while (str1[++i])
        new[i] = str1[i];
    while (str2[j])
        new[i++] = str2[j++];
    new[i] = '\0';
    free(str1);
    return (new);
}

char    *get_next_line(int fd)
{
    static int    i = 1;
    static char    *container = NULL;
    char    temp[BUFFER_SIZE + 1];

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
        container = ft_merge(container, temp);
        if (ft_is_nl(container))
            break ;
    }
    if (!container)
        return (NULL);
    int j = 0;
    char *ret;
    ret = malloc (1000);
    while (container[j] && container[j] != '\n')
    {
        ret[j] = container[j];
        j++;
    }
    if (container[j] == '\n')
    {
        ret[j++] = '\n';
        ret[j] = '\0';
    }
    else
    {
        ret[j] = '\0';
        free(container);
        container = NULL;
        return (ret);
    }
    int k = 0;
    if (container[j])
    {
        char *new;
        new = malloc (1000);
        while (container[j])
            new[k++] = container[j++];
        new[k] = '\0';
        free(container);
        container = new;
        return (ret);
    }
    else
    {
        free(container);
        container = NULL;
        return (ret);
    }
    return (NULL);
}

int main()
{
    int fd = open("burak.txt", O_RDONLY);
    int n = 20;
    char *str;
    while (n--)
    {
        str = get_next_line(fd);
        printf("%s", str);
        free(str);
        free(NULL);
    }
}
