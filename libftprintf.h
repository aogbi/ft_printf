
#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <unistd.h>

int ft_printf(const char *str, ...);

size_t	ft_strlen(const char *s);

void	ft_putchar_fd(char c, int fd);

int		ft_putstr(char *s);

#endif
