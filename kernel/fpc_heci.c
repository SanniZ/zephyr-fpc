
#include <linux/clk.h>
#include <linux/module.h>

#include <linux/pm_wakeup.h>
#include <linux/pm_runtime.h>
#include <linux/wakelock.h>
#include <linux/platform_device.h>



static int fpc_heci_probe(struct platform_device *pldev)
{
	int rc;

    dev_info(pldev, "%s() is called()\n", __func__);

	return rc;
}

static int fpc_heci_remove(struct platform_device *pldev)
{
     dev_info(dev, "%s() is called()\n", __func__);
     return 0;
}


static void fpc_heci_dev_release(struct device *dev)
{
	dev_info(dev, "%s() is called()\n", __func__);
	return;
}

static struct device_node fpc_heci_node = {
	.name = "fpc_heci",
};


static struct of_device_id drv_of_match[] = {
	{ .compatible = "fpc,fpc_heci", },
	{}
};
MODULE_DEVICE_TABLE(of, drv_of_match);


static struct platform_driver driver = {
	.driver = {
		.name	= "fpc_heci",
		.owner	= THIS_MODULE,
		.of_match_table = drv_of_match,
	},
	.probe	= fpc_heci_probe,
	.remove	= fpc_heci_remove,
};

static struct platform_device heci_device = {
	.name = "fpc_heci",
	.id   = -1,
	.num_resources = 0,
	.dev = {
		.release = fpc_heci_dev_release,
		.of_node = &fpc_heci_node,
	},
};

static struct platform_device *devices[] __initdata = {
	&heci_device,
};


static int __init fpc_heci_init(void)
{
	int rval;

	rval = platform_add_devices(devices, ARRAY_SIZE(devices));
	if (rval)
		return rval;

	return platform_driver_register(&driver);
}

static void __exit fpc_heci_exit(void)
{
	platform_driver_unregister(&driver);
	platform_device_unregister(&heci_device);
}

module_init(fpc_heci_init);
module_exit(fpc_heci_exit);

MODULE_LICENSE("GPL");

