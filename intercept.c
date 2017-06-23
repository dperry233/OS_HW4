#include <linux/module.h>
#include <linux/kernel.h>
// TODO: add more #include statements as necessary
#include <linux/utsname.h>


MODULE_LICENSE("GPL");

// TODO: add command-line arguments
void** sys_call_table = NULL;

// TODO: import original syscall and write new syscall

void find_sys_call_table(int scan_range) {
   unsigned long **sysCallTable;
   unsigned long ptrAsNum=(unsigned long)&system_utsname;
   int i=0;
   unsigned long *ptr;
   sysCallTable = NULL;
   for (i=0; i<scan_range,i++)
   {
	 ptrAsNum += sizeof(void *)
	 ptr = (unsigned long *)ptrAsNum;
	  
     if (ptr == &sys_read())
     {
        sysCallTable = (unsigned long **)ptr;  //read is actually number 3, so might want to return num0 or num1
		return &sysCallTable[0];
     }
   }

   return NULL;
}

int init_module(void) {
   // TODO: complete the function
}

void cleanup_module(void) {
   // TODO: complete the function
}

