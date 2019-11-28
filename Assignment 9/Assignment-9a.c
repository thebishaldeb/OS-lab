/*
Loadable Kernel Modules:
    -flexible-->can be loaded and unloaded with a single line of command
    -only loaded when needed
    -helps in diagnosing
    -calling-->simply loading code from a different part of memory
 */

#include <linux/module.h>     /* Needed by all modules */ 
#include <linux/kernel.h>     /* Needed for KERN_INFO */ 
#include <linux/param.h>

///< The license type -- this affects runtime behavior 
MODULE_LICENSE("GPL"); 
///< The author -- visible when you use modinfo 
MODULE_AUTHOR("Bishal"); 
///< The description -- see modinfo 
MODULE_DESCRIPTION("LKM to log messages into /var/log/messages !"); 

char *string="HelloWorld!";
module_param(string,charp,0000);
MODULE_PARM_DESC(string, "A character string");

int  init_module(void) { 
    printk(KERN_INFO "%s\n",string); 
    //printk(KERN_INFO "HelloWorldDA************\n"); 
    return 0; 
} 

void cleanup_module(void) { 
    printk(KERN_INFO "Module Testing Ended!********"); 
} 