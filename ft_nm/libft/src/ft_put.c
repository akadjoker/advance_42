#include "libft.h"

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return;
	while (*s)
		ft_putchar_fd(*(s++), fd);
}

void ft_putchar_width_fd(char c, size_t width, int fd)
{
	while (width > 0) {
		ft_putchar_fd(c, fd);
		--width;
	}
}

void ft_putnbr_hex_fd(long long n, size_t width, int fd)
{
	char *digits = "0123456789abcdef";
	char d;

	if (n < 0) {
		write(fd, "-", 1);
		ft_putnbr_hex_fd(-n, width - 1, fd);
	} else {
		d = digits[n % 16];
		if (width > 1)
			ft_putnbr_hex_fd(n / 16, width - 1, fd);
		write(fd, &d, 1);
	}
}
