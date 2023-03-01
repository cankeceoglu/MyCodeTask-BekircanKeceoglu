#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CanK");
MODULE_DESCRIPTION("Test different connectors");

/* Buffer for data */
static char buffer[255];
static int buffer_pointer = 0;

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "connector_tester"
#define DRIVER_CLASS "ConnectorTesterClass"

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static long int tester_ioctl(struct file *file, unsigned cmd, unsigned long arg)
{
	switch(cmd)
	{
		case 1:
			if(gpio_get_value(4) == 1 &&
			   gpio_get_value(17) == 0 &&
			   gpio_get_value(22) == 1 &&
			   gpio_get_value(23) == 0 &&
			   gpio_get_value(26) == 1 &&
			   gpio_get_value(27) == 0 
			)
			{
				gpio_set_value(5,1);
				gpio_set_value(6,0);
				gpio_set_value(7,0);
				arg = 1;
			}
			break;
			
		case 2:
			if(gpio_get_value(4) == 1 &&
			   gpio_get_value(17) == 0 &&
			   gpio_get_value(22) == 0 &&
			   gpio_get_value(23) == 1 &&
			   gpio_get_value(26) == 1 &&
			   gpio_get_value(27) == 0 
			)
			{	
				gpio_set_value(5,0);
				gpio_set_value(6,1);
				gpio_set_value(7,0);
				arg = 2;
			}
			break;
			
		case 3:
			if(gpio_get_value(4) == 1 &&
			   gpio_get_value(17) == 1 &&
			   gpio_get_value(22) == 0 &&
			   gpio_get_value(23) == 1 &&
			   gpio_get_value(26) == 0 &&
			   gpio_get_value(27) == 1 
			)
			{	
				gpio_set_value(5,0);
				gpio_set_value(6,0);
				gpio_set_value(7,1);
				arg = 3;
			}
			break;
	}
	
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.unlocked_ioctl = tester_ioctl
};

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	int retval;
	printk("Connector Tester Driver!\n");

	/* Allocate a device nr */
	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

	/* Create device class */
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not be created!\n");
		goto ClassError;
	}

	/* create device file */
	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}

	/* Initialize device file */
	cdev_init(&my_device, &fops);

	/* Regisering device to kernel */
	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}
	
	if(gpio_request(4,"rpi-gpio-4"))
	{
		printk("Can not allocate gpio4 \n");
		goto Gpio4Error;
	}
	
	if(gpio_direction_input(4))
	{
		printk("Can not set gpio4 as input \n");
		goto Gpio4Error;
	}
	
	if(gpio_request(17,"rpi-gpio-17"))
	{
		printk("Can not allocate gpio17 \n");
		goto Gpio17Error;
	}
	
	if(gpio_direction_input(17))
	{
		printk("Can not set gpio17 as input \n");
		goto Gpio17Error;
	}
	
	if(gpio_request(27,"rpi-gpio-27"))
	{
		printk("Can not allocate gpio27 \n");
		goto Gpio27Error;
	}
	
	if(gpio_direction_input(27))
	{
		printk("Can not set gpio27 as input \n");
		goto Gpio27Error;
	}
	
	if(gpio_request(22,"rpi-gpio-22"))
	{
		printk("Can not allocate gpio22 \n");
		goto Gpio22Error;
	}
	
	if(gpio_direction_input(22))
	{
		printk("Can not set gpio22 as input \n");
		goto Gpio22Error;
	}
	
	if(gpio_request(26,"rpi-gpio-26"))
	{
		printk("Can not allocate gpio26 \n");
		goto Gpio26Error;
	}
	
	if(gpio_direction_input(26))
	{
		printk("Can not set gpio26 as input \n");
		goto Gpio26Error;
	}
	
	if(gpio_request(23,"rpi-gpio-23"))
	{
		printk("Can not allocate gpio23 \n");
		goto Gpio23Error;
	}
	
	if(gpio_direction_input(23))
	{
		printk("Can not set gpio23 as input \n");
		goto Gpio23Error;
	}
	
/**
 *  led decleration
 */
	if(gpio_request(5,"rpi-gpio-5"))
	{
		printk("Can not allocate gpio5 \n");
		goto Gpio5Error;
	}
	
	if(gpio_direction_output(5,0))
	{
		printk("Can not set gpio5 as output  \n");
		goto Gpio5Error;
	}
	
	if(gpio_request(6,"rpi-gpio-6"))
	{
		printk("Can not allocate gpio6 \n");
		goto Gpio6Error;
	}
	
	if(gpio_direction_output(6,0))
	{
		printk("Can not set gpio6 as output  \n");
		goto Gpio6Error;
	}
	
	if(gpio_request(7,"rpi-gpio-7"))
	{
		printk("Can not allocate gpio7 \n");
		goto Gpio7Error;
	}
	
	if(gpio_direction_output(7,0))
	{
		printk("Can not set gpio7 as output  \n");
		goto Gpio7Error;
	}
	
	
	return 0;
	
Gpio4Error:
	gpio_free(4);
Gpio17Error:
	gpio_free(17);
Gpio22Error:
	gpio_free(22);
Gpio23Error:
	gpio_free(23);
Gpio26Error:
	gpio_free(26);
Gpio27Error:
	gpio_free(27);
Gpio5Error:
	gpio_free(5);
Gpio6Error:
	gpio_free(6);
Gpio7Error:
	gpio_free(7);

AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
