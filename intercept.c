#include <linux/module.h>
#include <linux/kernel.h>
// TODO: add more #include statements as necessary
#include <linux/utsname.h>
#include <sys/syscall.h>
#include <linux/syscall.h>
MODULE_LICENSE("GPL");

#define MAX_PATH_LENGTH 100
// TODO: add command-line arguments
void** sys_call_table = NULL;

int scan_range=150;
MODULE_PARM(scan_range,"i");
char* filepath = "";
// TODO: import original syscall and write new syscall
MODULE_PARM(filepath,"s");
void find_sys_call_table(int scan_range) {
   unsigned long ptrAsNum=(unsigned long)&system_utsname;
   int i=0;
   unsigned long *ptr;
   sys_call_table = NULL;
   for (i=0; i<scan_range; i++)
   {
	 ptrAsNum += sizeof(void *);
	 ptr = (unsigned long *)ptrAsNum;
	  
     if (ptr[__NR_read] == (unsigned long )sys_read)
     {

		 ptr = (unsigned long *)ptrAsNum;
        sys_call_table = (void **)ptr; 

		return;
     }
   }
   
}


asmlinkage long (*original_sys_unlink)(const char* pathname);
asmlinkage long our_sys_unlink(const char* pathname) {

	if(!strncmp(filepath,pathname,MAX_PATH_LENGTH)){
		return -EACCES;
	}else{
	    /*call original syscall and return its value*/
		return original_sys_unlink(pathname);
	}

}


int init_module(void) {
   // TODO: complete the function
   find_sys_call_table(scan_range);
   original_sys_unlink=sys_call_table[__NR_unlink];
   sys_call_table[__NR_unlink]=our_sys_unlink;
   return 0;
}

void cleanup_module(void) {
   // TODO: complete the function

   sys_call_table[__NR_unlink] = original_sys_unlink;
}

