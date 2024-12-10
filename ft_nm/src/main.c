#include "ft_nm.h"

static int process_file(char *path)
{
	int fd;
	struct stat s;
	char *ptr;
	int ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		return print_error(strerror(errno), path);
	}
	if (fstat(fd, &s) < 0)
	{
		close(fd);
		return print_error(strerror(errno), "fstat");
	}
	ptr = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
	{
		close(fd);
		return print_error(strerror(errno), "mmap");
	}
	ret = printer(ptr, path, s);
	if (munmap(ptr, s.st_size) < 0)
	{
		close(fd);
		return print_error(strerror(errno), "munmap");
	}
	close(fd);
	return ret;
}

int main(int argc, char **argv)
{
	int ret;

	if (argc < 2)
		return process_file(DEFAULT_FILE_PATH);
	if (argc == 2)
		return process_file(argv[1]);
	for (int i = 1; i < argc; ++i)
	{
		ret = 0;
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(":\n", 1);
		ret += process_file(argv[i]);
	}
	return ret;
}
