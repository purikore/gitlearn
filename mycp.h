#ifndef __MYCP_H__
#define __MYCP_H__
#define MAX 256
typedef struct cp_directory
{
        char src[MAX];
        char dest[MAX];
}Dcp;
void * pthread_cp_regfile(void * argv);
void * pthread_cp(void * argv);
#endif
