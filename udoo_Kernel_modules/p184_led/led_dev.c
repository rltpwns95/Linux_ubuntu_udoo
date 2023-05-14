#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>

#define CALL_DEV_NAME	"leddev"
#define CALL_DEV_MAJOR	240

static int led_open(struct inode *inode, struct file *filp)
{
	int num0 = MAJOR(inode->i_rdev);
	printk("led open-> major : %d\n", num0);
	int num1 = MINOR(inode->i_rdev);
	printk("led open-> minor : %d\n", num1);
	return 0;
}
static loff_t led_llseek(struct file *filp, loff_t off, int whence)
{
	printk("led llseek -> off : %08X, whence : %08X\n",(unsigned int)off,whence);
	return 0x23;
}
static ssize_t led_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	printk("led read -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
	return 0x33;
}
static ssize_t led_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	printk("led write -> buf : %08X, count : %08X\n",(unsigned int)buf, count);
	return 0x43;
}
static long led_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("led ioctl -> cmd : %08X, arg : %08X\n", cmd, (unsigned int)arg);
	return 0x53;
}
static int led_release(struct inode *inode, struct file *filp)
{
	printk("led release\n");
	return 0;
}
struct file_operations call_fops =
{
	.owner = THIS_MODULE,
	.llseek = led_llseek,
	.read = led_read,
	.write = led_write,
	.unlocked_ioctl = led_ioctl,
	.open = led_open,
	.release = led_release,			//close를 의미
};
static int led_init(void)
{
	int result;
	printk("led led_init\n");
	result = register_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
	if(result < 0) return result;
	return 0;
}
static int led_exit(void)
{
	printk("led led_exit\n");
	unregister_chrdev(CALL_DEV_MAJOR,CALL_DEV_NAME);
}
module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("Dual BSD/GPL");

