#include <sys/types.h>
#include <grp.h>
#include <stdio.h>

int main()
{
#if 0
	struct group {
		char   *gr_name;        /* group name */
		char   *gr_passwd;      /* group password */
		gid_t   gr_gid;         /* group ID */
		char  **gr_mem;         /* NULL-terminated array of pointers
								   to names of group members */
	};
#endif
	
	struct group* p = getgrnam("lichen");
	printf("name: %s\npwd = %s\ngid = %d\n", p->gr_name, p->gr_passwd, p->gr_gid);

	return 0;
}

