#include "ft_ls.h"

char get_type (mode_t m)
{
	if (S_ISBLK(m))
		return ('b');
	else if (S_ISCHR(m))
		return ('c');
	else if (S_ISDIR(m))
		return ('d');
	else if (S_ISLNK(m))
		return ('l');
	else if (S_ISFIFO(m))
		return ('p');
	else if (S_ISSOCK(m))
		return ('s');
	return ('-');
}
 
void get_permissions (mode_t m, char *perm)
{
	ft_memset(perm, '-', 9);
	if (m & S_IRUSR)
		perm[0] = 'r';
	if (m & S_IWUSR)
		perm[1] = 'w';
	if (m & S_IXUSR)
		perm[2] = 'x';
	if (m & S_IRGRP)
		perm[3] = 'r';
	if (m & S_IWGRP)
		perm[4] = 'w';
	if (m & S_IXGRP)
		perm[5] = 'x';
	if (m & S_IROTH)
		perm[6] = 'r';
	if (m & S_IWOTH)
		perm[7] = 'w';
	if (m & S_IXOTH)
		perm[8] = 'x';
	perm[9] = 0;
}

void get_time (const time_t *timeptr, char *timestr)
{
	char	*timetmp;

	timetmp = ctime(timeptr);
	ft_memset(timestr, ' ', 12);
	ft_memcpy(timestr, timetmp + 4, 12);
	if (*timeptr + 15780000 < time(NULL))
		ft_memcpy(timestr + 7, timetmp + 19, 5);
	timestr[12] = 0;
}

void prep_long (node *lst, max *max_length) 
{
	struct stat		st;
	struct passwd	*pw;
	struct group	*gr;

	ft_memset(max_length, 0, sizeof(max));
	for (node *c = lst->next ; c != lst ; c = c->next)
	{
		lstat(c->data, &st);
		pw = getpwuid(st.st_uid);
		gr = getgrgid(st.st_gid);
		max_length->bltot += st.st_blocks;
		if ((unsigned int)ft_nbrlen(st.st_nlink) > max_length->lnmax)
			max_length->lnmax = ft_nbrlen(st.st_nlink);
		if (ft_strlen(pw->pw_name) > max_length->pwmax)
			max_length->pwmax = ft_strlen(pw->pw_name);
		if (ft_strlen(gr->gr_name) > max_length->grmax)
			max_length->grmax = ft_strlen(gr->gr_name);
		if ((unsigned int)ft_nbrlen(st.st_size) > max_length->szmax)
			max_length->szmax = ft_nbrlen(st.st_size);
	}
}

void print_long (char *path, max ml, int mode)
{
	struct stat		st;
	char			type;
	char			perm[10];
	struct passwd	*pw;
	struct group	*gr;
	char			time[13];
	char			*islnk = "";
	char			lnk[PATH_MAX] = "";

	lstat(path, &st);
	type = get_type(st.st_mode);
	get_permissions(st.st_mode, perm);
	pw = getpwuid(st.st_uid);
	gr = getgrgid(st.st_gid);
	get_time(&st.st_ctime, time);
	if (type == 'l')
	{
		islnk = " -> ";
		readlink(path, lnk, PATH_MAX);
	}
	if (mode == M_DIR)
		path = ft_strrchr(path, '/') + 1;
	ft_printf("%c%s %*d %-*s %-*s %*d %s %s%s%s\n", type, perm, ml.lnmax, st.st_nlink,
	ml.pwmax, pw->pw_name, ml.grmax, gr->gr_name, ml.szmax, st.st_size,
	time, path, islnk, lnk);
}
