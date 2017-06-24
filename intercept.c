#include <linux/module.h>
#include <linux/kernel.h>
// TODO: add more #include statements as necessary
#include <linux/utsname.h>
#include <sys/syscall.h>
#include <linux/syscall.h>
MODULE_LICENSE("GPL");

// TODO: add command-line arguments
void** sys_call_table = NULL;

// TODO: import original syscall and write new syscall
int scan_range=150;
MODULE_PARM(scan_range,"i");
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

//this is just a test syscall (which is getpid) should be changed to unlink
asmlinkage long (*original_sys_getpid)(void);
asmlinkage long our_sys_getpid(void) {
    printk("sys_getpid was called\n");
    /*call original syscall and return its value*/
    return original_sys_getpid();
}


int init_module(void) {
   // TODO: complete the function
   find_sys_call_table(scan_range);
   original_sys_getpid=sys_call_table[__NR_getpid];
   sys_call_table[__NR_getpid]=our_sys_getpid;
   return 0;
}

void cleanup_module(void) {
   // TODO: complete the function

   sys_call_table[__NR_getpid] = original_sys_getpid;
}

