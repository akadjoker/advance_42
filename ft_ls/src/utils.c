#include "ft_ls.h"

int alpha_cmp (void *p1, void *p2)
{
	return (ft_strcmp(ft_strrchr(p1, '/'), ft_strrchr(p2, '/')));
}

int date_cmp (void *p1, void *p2)
{
	struct stat		st;
	unsigned long	t1;
	unsigned long	t2;

	lstat(p1, &st);
	t1 = st.st_ctime;
	lstat(p2, &st);
	t2 = st.st_ctime;

	if (t1 > t2)
		return (-1);
	else
		return (1);
}

node *sort_dir (node *lst, unsigned int options)
{
	if (options & LOWERT)
		lst = ft_lst_sort(lst, date_cmp);
	else
		lst = ft_lst_sort(lst, alpha_cmp);
	if (options & LOWERR)
		ft_lst_rev(lst);
	return (lst);
}


// int date_cmp (void *p1, void *p2)
// {
//     struct stat st1, st2;
    
//     lstat(p1, &st1);
//     lstat(p2, &st2);
    
//     if (st1.st_mtime > st2.st_mtime)
//         return (-1);
//     else if (st1.st_mtime < st2.st_mtime)
//         return (1);
    
//     return (ft_strcmp(ft_strrchr(p1, '/'), ft_strrchr(p2, '/')));
// }


// node *sort_dir (node *lst, unsigned int options)
// {
//     if (options & LOWERT)
//     {
//         lst = ft_lst_sort(lst, date_cmp);
//     }
//     else
//     {
//         lst = ft_lst_sort(lst, alpha_cmp);
//     }
    
//     if (options & LOWERR)
//         ft_lst_rev(lst);
        
//     return (lst);
// }