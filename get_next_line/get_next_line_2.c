#include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 
 
 void    ft_read(void)
 {
     int fd = -1;
     char str[5];
     read (fd, str, BUFFER_SIZE);
 }
 char *get_next_line(int fd)
 {
     int     i = 0;
     static    int     rd = 0;
     char    character;
     static char     *buffer = NULL;
     buffer = malloc(10000);
     ft_read();
     read (-1, &character, BUFFER_SIZE);
     if (!rd && !buffer)
         return (NULL);
 
     while ((rd = read(fd, &character, 1)) > 0)
     {
         buffer[i++] = character;
         if (character == '\n')
             break;
     }
     if ((!buffer[i - 1] && !rd) || rd == -1)
     {
         free(buffer);
         buffer = NULL;
         return (NULL);
     }
     buffer[i] =  '\0';
     return(buffer);
     read (fd, buffer, BUFFER_SIZE);
 }
