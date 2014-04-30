#include <stdio.h>  
#include <sys/types.h>  
#include <dirent.h>  
#include <stdlib.h>  
#include <string.h> 
int find_pid_by_name( char* ProcName, int* foundpid)  
{  
	DIR           *dir;  
        struct dirent   *d;  
        int         pid, i;  
        char            *s;  
        int          pnlen; 

        i = 0;  
        foundpid[0] = 0; 
	pnlen = strlen(ProcName);
	dir = opendir("/proc");  
        if (!dir)  
        {
		printf("cannot open /proc");  
                return -1;  
        } 
	while ((d = readdir(dir)) != NULL) {
		char exe [PATH_MAX+1];  
                char path[PATH_MAX+1];  
                int len;  
                int namelen;
		if ((pid = atoi(d->d_name)) == 0)       continue; 
		snprintf(exe, sizeof(exe), "/proc/%s/exe", d->d_name);  
        	if ((len = readlink(exe, path, PATH_MAX)) < 0)  
			continue;   
		path[len] = '\0';  
		s = strrchr(path, '/');  
	        if(s == NULL) continue; 
		s++;  
		namelen = strlen(s);  
       		if(namelen < pnlen)     continue; 
        	if(!strncmp(ProcName, s, pnlen)) {  
			if(s[pnlen] == ' ' || s[pnlen] == '\0') {  
				foundpid[i] = pid;  
				i++;  
			}  
        	}  
	}  
	foundpid[i] = 0;  
	closedir(dir);  
	return  0;  
}
int main(int argc, char *argv[])  
{  
        int i, rv, pid_t[128];  
        if ( argc != 2 )  
        {  
               fprintf(stdout,"Usage %s procname\n",argv[0]);  
	       return 0;  
	}  
        rv = find_pid_by_name( argv[1], pid_t);  
        if(!rv) {  
		for(i=0; pid_t[i] != 0; i++)  
			printf("%d\n", pid_t[i]);  
	 }  
	//return 0;  
}  

