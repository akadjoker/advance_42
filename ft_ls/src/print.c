#include "ft_ls.h"
int first = 1;

void print_dir (node *lst, char *path, unsigned int options)
{
	max		max_length;

	if (options & UPPERR || options & MULTIARG)
	{
		if (first)
			ft_printf("%s:\n", path);
		else
			ft_printf("\n%s:\n", path);
		first = 0;
	}
	if (options & LOWERL)
	{
		prep_long(lst, &max_length);
		ft_printf("total %d\n", max_length.bltot / 2);
		for (node *c = lst->next ; c != lst ; c = c->next)
			print_long(c->data, max_length, M_DIR);
	}
	else
	{
		for (node *c = lst->next ; c != lst ; c = c->next)
			ft_printf("%s\n", ft_strrchr(c->data, '/') + 1);
	}
}


void print_file (node *files, unsigned int options)
{
	max		max_length;

	if (options & LOWERL)
	{
		prep_long(files, &max_length);
		for (node *c = files->next ; c != files ; c = c->next)
			print_long(c->data, max_length, M_FILE);
	}
	else
	{
		for (node *c = files->next ; c != files ; c = c->next)
			ft_printf("%s\n", c->data);
	}
	first = 0;
}


// void print_file(node *files, unsigned int options)
// {
//     max     max_length;
//     int     first_item = 1;

//     if (options & LOWERL)
//     {
//         prep_long(files, &max_length);
//         for (node *c = files->next ; c != files ; c = c->next)
//             print_long(c->data, max_length, M_FILE);
//     }
//     else
//     {
//         for (node *c = files->next ; c != files ; c = c->next)
//         {
//             if (!first_item)
//                 ft_printf("  ");
//             ft_printf("%s", c->data);
//             first_item = 0;
//         }
//         ft_printf("\n");
//     }
//     first = 0;
// }
// void print_dir(node *lst, char *path, unsigned int options)
// {
//     max     max_length;
//     int     first_item = 1;
//     char    *filename;

//     if (options & UPPERR || options & MULTIARG)
//     {
//         if (first)
//             ft_printf("%s:\n", path);
//         else
//             ft_printf("\n%s:\n", path);
//         first = 0;
//     }
    
//     if (options & LOWERL)
//     {
//         prep_long(lst, &max_length);
//         ft_printf("total %d\n", max_length.bltot / 2);
//         for (node *c = lst->next ; c != lst ; c = c->next)
//             print_long(c->data, max_length, M_DIR);
//     }
//     else
//     {
//         for (node *c = lst->next ; c != lst ; c = c->next)
//         {
//             filename = ft_strrchr(c->data, '/') + 1;
//             // Se é um arquivo oculto (começa com '.') ou está em um diretório oculto
//             if (filename[0] == '.' || ft_strstr(path, "/."))
//                 ft_printf("%s\n", filename);
//             else
//             {
//                 if (!first_item)
//                     ft_printf("  ");
//                 ft_printf("%s", filename);
//                 first_item = 0;
//             }
//         }
//         // Adiciona nova linha apenas se não estiver listando arquivos ocultos
//         if (!ft_strstr(path, "/.") && first_item == 0)
//             ft_printf("\n");
//     }
// }

void print_help (void)
{
	ft_printf("Usage: ft_ls [OPTION]... [FILE]...\n");
	ft_printf("Lists information about the FILEs (the current directory by default).\n");
	ft_printf("Sorts entries alphabetically if -t is not specified.\n\n");
	ft_printf("Options :\n");
	ft_printf("  -a            do not ignore entries starting with .\n");
	ft_printf("  -l            use a long listing format\n");
	ft_printf("  -r            reverse order while sorting\n");
	ft_printf("  -R            list subdirectories recursively\n");
	ft_printf("  -t            sort by modification time, newest first\n\n");
	ft_printf("  --help        display this help and exit\n\n");
	ft_printf("Exit status:\n");
	ft_printf(" 0  if OK,\n");
	ft_printf(" 1  if minor problems (e.g., cannot access subdirectory),\n");
	ft_printf(" 2  if serious trouble (e.g., cannot access command-line argument).\n");
	exit(0);
}

void print_unrecognized (char *s)
{
	ft_printf("ls: unrecognized option \'%s\'\n", s);
	ft_printf("Try \'ft_ls --help\' for more information.\n");
	exit(2);
}

void print_invalid (char c)
{
	ft_printf("ls: invalid option -- \'%c\'\n", c);
	ft_printf("Try \'ft_ls --help\' for more information.\n");
	exit(2);
}
