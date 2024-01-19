#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x4c260c62, "cdev_alloc" },
	{ 0x76cce6d6, "cdev_init" },
	{ 0xff0d65c6, "cdev_add" },
	{ 0x31a64363, "pci_get_device" },
	{ 0x122c3a7e, "_printk" },
	{ 0x43d34239, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x3930d519, "pci_select_bars" },
	{ 0xde80cd09, "ioremap" },
	{ 0xedc03953, "iounmap" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xa19b956, "__stack_chk_fail" },
	{ 0xad9e8d10, "pci_dev_put" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x453e7dc, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "76D1D417B316EAEB67AAFC0");
