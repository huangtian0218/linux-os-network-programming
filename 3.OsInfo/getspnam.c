#include <stdio.h>
#include <shadow.h>
#include <stdlib.h>

int main()
{
#if 0
	struct spwd {
               char *sp_namp;     /* Login name */
               char *sp_pwdp;     /* Encrypted password */
               long  sp_lstchg;   /* Date of last change
                                     (measured in days since
                                     1970-01-01 00:00:00 +0000 (UTC)) */
               long  sp_min;      /* Min # of days between changes */
               long  sp_max;      /* Max # of days between changes */
               long  sp_warn;     /* # of days before password expires
                                     to warn user to change it */
               long  sp_inact;    /* # of days after password expires
                                     until account is disabled */
               long  sp_expire;   /* Date when account expires
                                     (measured in days since
                                     1970-01-01 00:00:00 +0000 (UTC)) */
               unsigned long sp_flag;  /* Reserved */
           };	
#endif
	
	//考虑到/etc/shadow文件的特殊性，请使用sudo运行程序
	struct spwd* puser = getspnam("lichen");
	printf("pwd = %s\n", puser->sp_pwdp);

	return 0;
}
