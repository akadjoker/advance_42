#include "ft_nm.h"

/**
 * Processes an ELF file at the specified path.
 *
 * This function opens the file at the given path, retrieves its metadata using
 * fstat, and maps it into memory using mmap. It then calls the printer function
 * to print the symbols in the ELF file. Finally, it unmaps the file and closes
 * the file descriptor.
 *
 * If any error occurs during these operations (e.g., opening the file, mapping
 * it into memory), an appropriate error message is printed, and the function
 * returns an error code.
 *
 * @param[in] path A string containing the file path to the ELF file.
 *
 * @return 0 if the file is processed successfully, or an error code if an
 * error occurs.
 */
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

/**
 * The main function for the program.
 *
 * This function takes the command line arguments, and processes each file
 * specified in the arguments. If a file is not specified, the default file path
 * is used.
 *
 * @param[in] argc The number of command line arguments.
 * @param[in] argv The command line arguments, where each argument is a string
 *                 containing the file path to the ELF file to be processed.
 *
 * @return 0 if all files are processed successfully, or the sum of the error
 *         codes of each file if an error occurs.
 */
int main(int argc, char **argv)
{
	int ret;

	if (argc < 2)
		return process_file(DEFAULT_FILE_PATH);
	if (argc == 2)
		return process_file(argv[1]);
	ret = 0;
	for (int i = 1; i < argc; ++i)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(":\n", 1);
		ret += process_file(argv[i]);
	}
	return ret;
}
