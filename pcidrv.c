#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/fs.h>       
#include <linux/if.h> 
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/cdev.h> 
#include <linux/netdevice.h>  
#include <linux/pci.h>       

#define MY_DRIVER "my_pci_driver"
#define DRIVER_NAME "r8169"
#define MAX_USER_INPUT_SIZE 1400

static int major_number = 510;
static dev_t dev_num;
static struct cdev cdev;
static struct pci_device_id my_driver_id_table[] = {
	{ PCI_DEVICE(0x10ec, 0x8168) },
	{0,}
};

MODULE_DEVICE_TABLE(pci, my_driver_id_table);

static int my_driver_probe(struct pci_dev *pdev, const struct pci_device_id *ent);
static void my_driver_remove(struct pci_dev *pdev);

static struct pci_driver my_driver = {
	.name = MY_DRIVER,
	.id_table = my_driver_id_table,
	.probe = my_driver_probe,
	.remove = my_driver_remove
};

struct my_driver_priv {
	u8 __iomem *hwmem;
};


static int __init mypci_driver_init(void)
{
	
	if (cdev_add(&cdev, dev_num, 1) < 0) {
        pr_err("Failed to add character device\n");
        return -1;
        }
    return 0;    
    }
    

static void __exit mypci_driver_exit(void)
{
	pci_unregister_driver(&my_driver);
}

void release_device(struct pci_dev *pdev)
{
	pci_release_region(pdev, pci_select_bars(pdev, IORESOURCE_MEM));
	pci_disable_device(pdev);
}

static char value_from_user[MAX_USER_INPUT_SIZE];

static int r8169_open(struct inode* inode, struct file* file) { 
    return 0;
}
	
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

	
	static struct file_operations r8169_fops = {
    .owner = THIS_MODULE,
    .open = r8169_open,
    .unlocked_ioctl = my_ioctl
};

static void __exit r8169_exit (void) {
	unregister_chrdev(major_number, DRIVER_NAME);
	printk(KERN_ALERT "Сleanup_module OK \n");
}

static int my_driver_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int bar, err;
	u16 vendor, device;
	unsigned long mmio_start,mmio_len;
	struct my_driver_priv *drv_priv;
	
	if (register_chrdev(510, "DRIVER_NAME", &r8169_fops) < 0) {
        printk(KERN_ALERT "Failed to register character driver\n");
        }
    return 0;
}

static void my_driver_remove(struct pci_dev *pdev)
{
	struct my_driver_priv *drv_priv = pci_get_drvdata(pdev);
    unregister_chrdev(0, "my_pci_device");
    cdev_del(&cdev);
        unregister_chrdev_region(dev_num, 1);  

	if (drv_priv) {
		if (drv_priv->hwmem) {
			iounmap(drv_priv->hwmem);
		}

		kfree(drv_priv);
	}

	release_device(pdev);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anastasia");
MODULE_DESCRIPTION("Test PCI driver");
MODULE_VERSION("0.1");

module_init(mypci_driver_init);
module_exit(mypci_driver_exit);
