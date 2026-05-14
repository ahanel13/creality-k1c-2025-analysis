/* Zero external symbols — no printk, no module_param */
#include <linux/module.h>

MODULE_LICENSE("GPL");

/* Address passed as a build-time constant for testing */
#define SOC_TEXT 0xc08a4000UL

static int __init sc_patch_init(void)
{
	/* Just touch one address to confirm we can read module text */
	volatile u32 *p = (volatile u32 *)(SOC_TEXT + 0x148c);
	(void)*p; /* read only */
	return 0;
}

static void __exit sc_patch_exit(void) {}

module_init(sc_patch_init);
module_exit(sc_patch_exit);
