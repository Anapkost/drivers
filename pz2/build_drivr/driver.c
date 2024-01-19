#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define SUCCESS 0
#define DEVICE_NAME "mogus_char" /* Dev name as it appears in /proc/devices   */
#define BUF_LEN 100              /* Max length of the message from the device */

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release};

static int Major;           /* Major number assigned to our device driver */
static int Device_Open = 0; /* Is device open?
                             * Used to prevent multiple access to device */
static char msg[BUF_LEN];   /* The msg the device will give when asked */
static char *msg_Ptr;

MODULE_LICENSE("GPL");

int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0)
    {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);

    return SUCCESS;
}

void cleanup_module(void)
{
    /* Удаление символьного драйвера  */
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_ALERT "Сleanup_module OK \n");
}

static int device_open(struct inode *inode, struct file *file)
{
    static int counter = 0;
    if (Device_Open)
        return -EBUSY;
    Device_Open++;
    sprintf(msg, "[from device_open] I already told you %d times Hello world!\n", counter++);
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--; /* We're now ready for our next caller */
                   /** Decrement the usage count, or else once you opened the file, you'll
                     never get get rid of the module.   */
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *filp, /* see include/linux/fs.h   */
                           char *buffer,      /* buffer to fill with data */
                           size_t length,     /* length of the buffer     */
                           loff_t *offset)
{

    printk(KERN_ALERT "[driver] im being readed \n");

    static int counter = 0;
    sprintf(msg, "[from device_read] I already told you %d times Hello world!\n", counter++);
    msg_Ptr = msg;

    if (length <= BUF_LEN)
    {
        copy_to_user(buffer, msg_Ptr, length);
        return length;
    }
    else
    {
        copy_to_user(buffer, msg_Ptr, BUF_LEN);
        return BUF_LEN;
    }
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}
