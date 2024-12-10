#include "ft_nm.h"


static void print_sym(struct s_symbol *sym)
{
	char type;

	type = get_sym_type(sym);
	if (type != 'u' && type != 'U' && type != 'w')
		ft_putnbr_hex_fd(sym->st_value,
						 sym->ei_class == ELFCLASS32 ? 8 : 16, 1);
	else
		ft_putchar_width_fd(' ', sym->ei_class == ELFCLASS32 ? 8 : 16,
							1);
	ft_putchar_fd(' ', 1);
	ft_putchar_fd(get_sym_type(sym), 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(sym->st_name, 1);
	ft_putchar_fd('\n', 1);
}

static int sym_name_comp(char *n1, char *n2)
{
	char *n1_low;
	char *n2_low;
	int res;

	n1_low = ft_strdup_ex(n1, "_@.", 1);
	n2_low = ft_strdup_ex(n2, "_@.", 1);
	res = ft_strcmp(n1_low, n2_low);
	free(n1_low);
	free(n2_low);
	return res;
}

static void sort_sym_list(t_list *sym_list)
{
	t_list *current;
	struct s_symbol *curr_symb;
	struct s_symbol *next_symb;
	size_t size;
	int name_cmp;
	int value_cmp;
	void *tmp;

	size = ft_lstsize(sym_list);
	if (size <= 0)
		return;
	for (size_t i = 0; i < size - 1; ++i)
	{
		current = sym_list;
		for (size_t j = 0; j < size - i - 1; ++j)
		{
			curr_symb = (struct s_symbol *)current->content;
			next_symb = (struct s_symbol *)current->next->content;
			name_cmp = sym_name_comp(curr_symb->st_name,
									 next_symb->st_name);
			value_cmp = curr_symb->st_value - next_symb->st_value;
			if (name_cmp > 0 || (name_cmp == 0 && value_cmp > 0))
			{
				tmp = current->content;
				current->content = current->next->content;
				current->next->content = tmp;
			}
			current = current->next;
		}
	}
}

int print_error(const char *s, const char *prefix)
{
	char *err_str;

	err_str = ft_strdup("ft_nm: ");
	if (prefix != NULL) {
		err_str = ft_strappend(err_str, prefix);
		err_str = ft_strappend(err_str, ": ");
	}
	err_str = ft_strappend(err_str, s);
	err_str = ft_strappend(err_str, "\n");
	ft_putstr_fd(err_str, 2);
	free(err_str);
	return 1;
}


int printer(const char *ptr, char *path, struct stat s)
{
	char *ei_mag;
	int ei_class;
	t_list *sym_list;

	ei_mag = ft_substr(ptr, 0, 4);
	if (ft_strcmp(ei_mag, ELFMAG))
		return print_error("file format not recognized", path);
	free(ei_mag);
	ei_class = ptr[4];
	if (ei_class == ELFCLASS32)
		sym_list = parse_32(ptr, path, s);
	else if (ei_class == ELFCLASS64)
		sym_list = parse_64(ptr, path, s);
	else
		return print_error("wrong ei_class", NULL);
	if (!sym_list)
		return print_error("no symbols", path);
	sort_sym_list(sym_list);
	ft_lstiter(sym_list, (void (*)(void *))print_sym);
	free_sym_list(sym_list);
	return 0;
}

void free_symbol(struct s_symbol *sym)
{
	free(sym->sh_name);
	free(sym->st_name);
	free(sym);
}

void free_sym_list(t_list *syms)
{
	t_list *next;

	while (syms != NULL) {
		next = syms->next;
		free_symbol(syms->content);
		free(syms);
		syms = next;
	}
}
