#include <linux/init.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("feixiaoxing");
MODULE_DESCRIPTION("This is just a hello module!\n");

static wait_queue_head_t wait;
static int read_flag;

static ssize_t pw_char_read(struct file *filp, char __user *data,
                              size_t len, loff_t *ppose)
{
        printk("%s in.\n",__func__);
	read_flag++;
	wake_up_interruptible(&wait);
//	read_flag++;
	wake_up_interruptible(&wait);
        printk("%s exit.\n",__func__);

	return len;
}

static unsigned int pw_char_poll (struct file *filp, struct poll_table_struct *table)
{
	unsigned mask = 0;

        printk("%s in, %d.\n",__func__, read_flag);
//	poll_wait(filp, &wait, table);
	if (read_flag) {
		read_flag--;
		mask = POLLIN | POLLRDNORM;
	}
	
        printk("%s exit.\n",__func__);

	return mask;
}

static int pw_char_open (struct inode *node, struct file *filp)
{
        printk("%s.\n",__func__);
	read_flag = 0;
	init_waitqueue_head(&wait);

	return 0;
}

static int pw_char_release (struct inode *node, struct file *filp)
{
        printk("%s.\n",__func__);
	return 0;
}

static const struct file_operations pw_char_driver_ops = {
        .owner          = THIS_MODULE,
        .read          = pw_char_read,
        .open           = pw_char_open,
        .release        = pw_char_release,
	.poll		= pw_char_poll,
};

static struct miscdevice pw_char_driver = {
        .minor          = MISC_DYNAMIC_MINOR,
        .name           = "pw",
        .fops           = &pw_char_driver_ops
};      

static int __init pw_init(void)
{
	int ret;

        printk("%s.\n",__func__);
	ret = misc_register(&pw_char_driver);
        return 0;
}

static void __exit pw_exit(void)
{
        printk("%s.\n",__func__);
	misc_deregister(&pw_char_driver);
}

module_init(pw_init);
module_exit(pw_exit);
