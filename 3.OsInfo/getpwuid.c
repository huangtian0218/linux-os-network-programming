#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
#if 0
	struct passwd {
		char   *pw_name;       /* username */
		char   *pw_passwd;     /* user password */
		uid_t   pw_uid;        /* user ID */
		gid_t   pw_gid;        /* group ID */
		char   *pw_gecos;      /* user information */
		char   *pw_dir;        /* home directory */
		char   *pw_shell;      /* shell program */
	};
#endif

	struct passwd *puser = getpwuid(1001);
	printf("name: %s\npasswd: %s\nuid: %d\ngid: %d\ngecos: %s\ndir: %s\nshell: %s\n", puser->pw_name,
			puser->pw_passwd,
			puser->pw_uid,
			puser->pw_gid,
			puser->pw_gecos,
			puser->pw_dir,
			puser->pw_shell);

	return 0;
}
