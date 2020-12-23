#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/ktime.h>

#include <hello1.h>
struct shvachko_list_head {
	struct list_head list_node;
	ktime_t time;
	ktime_t time1;
};

MODULE_AUTHOR("Savichev D");
MODULE_DESCRIPTION("Hello world");
MODULE_LICENSE("Dual BSD/GPL");

static struct list_head header = LIST_HEAD_INIT(header);


static uint count_hw = 1;
module_param(count_hw, uint, 0444);//S_IRUGO
MODULE_PARM_DESC(count_hw, "This parameter is responsible for number of hello world printed");
int print_hello(uint count_hw)
{
uint i;
struct shvachko_list_head *tmp1;
struct shvachko_list_head *variable, *tmp;

if (count_hw == 0)
	pr_warn("You cannot enter 0");
if (count_hw >= 5 && count_hw <= 10)
	pr_warn("You should enter number below 5");

BUG_ON(count_hw > 10);
  // else if (count_hw > 10) {
  //  printk(KERN_ERR "The parameter is greater than 10");
  //  return -EINVAL;
  //}

for (i = 0; i < count_hw; i++) {
	tmp1 = kmalloc(sizeof(struct list_head), GFP_KERNEL);
if (i == 5) {
	tmp1 = NULL;
if (ZERO_OR_NULL_PTR(tmp1))
	goto show_error;
}
list_add_tail(&(tmp1->list_node), &header);
tmp1->time = ktime_get();
pr_info("Hello World!");
tmp1->time1 = ktime_get();
}

pr_info("count: %d\n", count_hw);
return 0;
show_error:
//При нестачі пам'яті для
//чергового елементу списку,
//не можна відразу
//виходити з кодом помилки...

	list_for_each_entry_safe(variable, tmp, &header, list_node) {
		list_del(&variable->list_node);
		kfree(variable);
	}
	BUG_ON(!list_empty(&header));
	pr_warn("Zero or null pointer on");
	return -ENOMEM; /*out of memory(12)*/
}
EXPORT_SYMBOL(print_hello);

static int __init initter(void)
{
return 0;
}
static void __exit exitter(void)
{
struct shvachko_list_head *variable, *tmp;
list_for_each_entry_safe(variable, tmp, &header, list_node) {
	pr_info("Time : %lld", variable->time);
	pr_info("Deltha time: %lld", variable->time1-variable->time);
	list_del(&variable->list_node);
	kfree(variable);
}
BUG_ON(!list_empty(&header));
}

module_init(initter);
module_exit(exitter);
