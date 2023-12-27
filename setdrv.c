#include <linux/fs.h>       
#include <linux/if.h> 
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/cdev.h> 
#include <linux/netdevice.h>  
#include <linux/pci.h>     
#include <linux/init.h>  

#define DRIVER_NAME "r8169"
#define MAX_USER_INPUT_SIZE 10

static int major_number;
static struct cdev r8169;
static char value_from_user[MAX_USER_INPUT_SIZE];

// Первый параметр - файловый дескриптор, второй параметр - команда, третий параметр - аргументы
long my_ioctl(struct file *filep, unsigned int cmd, unsigned long arg) {
	switch (cmd) {
	case 0:
	memset(value_from_user, 0, sizeof(value_from_user));
		if (copy_from_user(value_from_user, (char *)arg, MAX_USER_INPUT_SIZE - 1) != 0) {
		return -EFAULT;
		};
	printk(KERN_INFO "Значение от пользователя: %s\n", value_from_user);
	break;
	default:
	return -ENOTTY;
	}
return 0;
}



static int r8169_open(struct inode* inode, struct file* file) { 
    return 0;
}

static struct file_operations r8169_fops = {
    .owner = THIS_MODULE,
    .open = r8169_open,
    .unlocked_ioctl = my_ioctl
};


static int __init r8169_init(void) {
    major_number = register_chrdev(0, DRIVER_NAME, &r8169_fops);
    	if (major_number < 0) {
        	printk(KERN_ALERT "Failed to register a major number\n");
        	return major_number;
    	}
    printk(KERN_INFO "Registered a major number %d\n", major_number);
    return 0;
}

static void __exit r8169_exit (void) {
	unregister_chrdev(major_number, DRIVER_NAME);
	printk(KERN_ALERT "Сleanup_module OK \n");
}

module_init(r8169_init);
module_exit(r8169_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anastasia");
MODULE_DESCRIPTION("Linux char driver for the Realtek 8169");
MODULE_VERSION("0.1");
