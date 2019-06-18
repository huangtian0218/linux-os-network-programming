#ifndef _SEM_H_
#define _SEM_H_

int create_sem(int nsems);
void init_sem(int semid, int semnum, int val);
void del_sem(int semid, int nsems);
void p_sem(int semid, int semnum_buf[], int nsops);
void v_sem(int semid, int semnum_buf[], int nsops);

#endif
