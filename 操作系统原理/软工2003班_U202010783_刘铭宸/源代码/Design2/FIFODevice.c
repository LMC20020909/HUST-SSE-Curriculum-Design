#include <linux/miscdevice.h>
#include <linux/kfifo.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/mutex.h>

#define DEV_NAME "BlockFIFODevV3"
#define BUFFER_SIZE 32
MODULE_LICENSE("GPL");

DEFINE_KFIFO(FIFOBuffer, char, BUFFER_SIZE);
struct mutex Mutex;
static struct device *my_miscdevice;
wait_queue_head_t read_queue;
wait_queue_head_t write_queue;

static int DevOpen(struct inode *inode, struct file *file) {
	return 0;
}

static int DevRelease(struct inode *inode, struct file *filp) {
    return 0;
}

static ssize_t
DevRead(struct file *file,char __user *buf, size_t count,loff_t *ppos) {
    int actual_readed = 0, ret = 0;
    if (kfifo_is_empty(&FIFOBuffer)) {
        if(file->f_flags & O_NONBLOCK)
            return 0;
        wait_event_interruptible(read_queue, !kfifo_is_empty(&FIFOBuffer));
    }
    mutex_lock(&Mutex); 
    ret = kfifo_to_user(&FIFOBuffer, buf, count, &actual_readed);
    mutex_unlock(&Mutex);
    if (!kfifo_is_full(&FIFOBuffer))
        wake_up_interruptible(&write_queue);
    return actual_readed;
}

static ssize_t
DevWrite(struct file *file,const char __user *buf, size_t count, loff_t *ppos) {
    int actual_write = 0, ret = 0;
    if (kfifo_is_full(&FIFOBuffer)) {
        if(file->f_flags & O_NONBLOCK)
            return 0;
        wait_event_interruptible(write_queue,!kfifo_is_full(&FIFOBuffer));
    }
    mutex_lock(&Mutex);
    ret = kfifo_from_user(&FIFOBuffer, buf, count, &actual_write);
    mutex_unlock(&Mutex);
    if(!kfifo_is_empty(&FIFOBuffer))
        wake_up_interruptible(&read_queue);
    
    return actual_write;
}

static const struct file_operations DevFops = {
	.owner = THIS_MODULE,
	.open = DevOpen,
    .release = DevRelease,
	.read = DevRead,
	.write = DevWrite, 
};

static struct miscdevice miscDeviceFIFOBlock = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEV_NAME,
	.fops = &DevFops,
};

static int __init DevInit(void){
    int ret = misc_register(&miscDeviceFIFOBlock);
    mutex_init(&Mutex);
    //BlockDevice = (struct _BlockDevice *)malloc(sizeof(_BlockDevice));
    my_miscdevice = miscDeviceFIFOBlock.this_device;
    init_waitqueue_head(&read_queue);
    init_waitqueue_head(&write_queue);
    printk("succeeded register char device: %s\n", DEV_NAME);
    return ret;
}

static void __exit DevExit(void) {
    misc_deregister(&miscDeviceFIFOBlock);
	printk("removing device: %s\n", DEV_NAME);
}

module_init(DevInit);
module_exit(DevExit);
