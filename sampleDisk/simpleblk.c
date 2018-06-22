#include <linux/module.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>

static int simpleblk_major;
#define SIMPLEBLK_MINOR 1
static int simpleblk_sect_size = 512;
static int simpleblk_nsects = 1024 * 1024;

struct simpleblk_dev {
    int minor;
    spinlock_t lock;
    struct request_queue *queue;
    struct gendisk *disk;
    ssize_t size;
    void *data;
};

struct simpleblk_dev *simpleblk_dev = NULL;

//Do an IO operation for each segment
static int simpleblk_handle_io(struct simpleblk_dev *sdev, uint64_t pos, ssize_t size,
                               void *buffer, int write)
{
    if (write) {
        memcpy(sdev->data + pos, buffer, size);
    } else {
        memcpy(buffer, sdev->data + pos, size);
    }

    return 0;
}

static void simpleblk_request(struct request_queue *q)
{
    struct request *rq = NULL;
    int rv = 0;
    uint64_t pos = 0;
    ssize_t size = 0;
    struct bio_vec bvec;
    struct req_iterator iter;
    void *kaddr = NULL;

    while ((rq = blk_fetch_request(q)) != NULL) {
        spin_unlock_irq(q->queue_lock);

        if (rq->cmd_type != REQ_TYPE_FS) {
            rv = -EIO;
            goto skip;
        }

        BUG_ON(simpleblk_dev != rq->rq_disk->private_data);

        pos = blk_rq_pos(rq) * simpleblk_sect_size;
        size = blk_rq_bytes(rq);
        if (pos + size > simpleblk_dev->size) {
            pr_crit("simpleblk: Beyond end write (%llu %zx)\n", pos, size);
            rv = -EIO;
            goto skip;
        }

        rq_for_each_segment(bvec, rq, iter) {
            kaddr = kmap(bvec.bv_page); //ͨ��kmap������ Segment ����ҳ�������ַ

            rv = simpleblk_handle_io(simpleblk_dev, pos, bvec.bv_len, kaddr + bvec.bv_offset, rq_data_dir(rq));
            if (rv < 0) {
                goto skip;
            }

            pos += bvec.bv_len;
            kunmap(bvec.bv_page);
        }

skip:
        blk_end_request_all(rq, rv);

        spin_lock_irq(q->queue_lock);

    }

}

static int simpleblk_ioctl(struct block_device *bdev, fmode_t mode, unsigned command,
                           unsigned long argument)
{
    return 0;
}

static int simpleblk_open(struct block_device *bdev, fmode_t mode)
{
    return 0;
}

static void simpleblk_release(struct gendisk *disk, fmode_t mode)
{
}

static const struct block_device_operations simpleblk_fops = {
    .owner = THIS_MODULE,
    .open = simpleblk_open,
    .release = simpleblk_release,
    .ioctl = simpleblk_ioctl,
};

static int simpleblk_alloc(int minor)
{
    struct gendisk *disk;
    int rv = 0;

    simpleblk_dev = kzalloc(sizeof(struct simpleblk_dev), GFP_KERNEL);
    if (!simpleblk_dev) {
        rv = -ENOMEM;
        goto fail;
    }

    simpleblk_dev->size = simpleblk_sect_size * simpleblk_nsects;
    simpleblk_dev->data = vmalloc(simpleblk_dev->size);
    if (!simpleblk_dev->data) {
        rv = -ENOMEM;
        goto fail_dev;
    }

    simpleblk_dev->minor = minor;

    spin_lock_init(&simpleblk_dev->lock);
    //��ʼ�����������Ҫ������һ�������������̺ͱ�����������е�������
    //������������simpleblk_request����ִ�п��豸��read��write IO��������ξ���request_queue
    simpleblk_dev->queue = blk_init_queue(simpleblk_request, &simpleblk_dev->lock);
    if (!simpleblk_dev->queue) {
        rv = -ENOMEM;
        goto fail_data;
    }

    blk_set_stacking_limits(&simpleblk_dev->queue->limits);

    disk = alloc_disk(minor);
    if (!disk) {
        rv = -ENOMEM;
        goto fail_queue;
    }
    simpleblk_dev->disk = disk;

    disk->major = simpleblk_major;
    disk->first_minor = minor;
    disk->fops = &simpleblk_fops; //��ͨ�ô��̵Ŀ��豸����������ֵ��gendisk
    disk->private_data = simpleblk_dev;
    disk->queue = simpleblk_dev->queue;
    sprintf(disk->disk_name, "simpleblk%d", minor);
    set_capacity(disk, simpleblk_nsects);
    add_disk(disk);

    return 0;

fail_queue:
    blk_cleanup_queue(simpleblk_dev->queue);
fail_data:
    vfree(simpleblk_dev->data);
fail_dev:
    kfree(simpleblk_dev);
fail:
    return rv;
}

static void simpleblk_free(struct simpleblk_dev *sdev)
{
    del_gendisk(sdev->disk); //�ô�����ϵͳ�в��ٿɼ��������Ȱβ�uevent
    blk_cleanup_queue(sdev->queue); //�ͷſ��豸IO������У����ͷ�֮ǰ�Ѵ������IO�������
    put_disk(sdev->disk); //���ٴ������ü���
    vfree(sdev->data); //�ͷ�vmalloc�������������
    kfree(sdev); //�ͷ�ȫ�����ݽṹ
}

static int __init simpleblk_init(void)
{
    int rv = 0;
    //������豸�ŷ����ע�ᣬ��һ������Ϊ0����ʾ���ں˷���һ���豸��
    simpleblk_major = register_blkdev(0, "simpleblk");
    if (simpleblk_major < 0) {
        return simpleblk_major;
    }

    rv = simpleblk_alloc(SIMPLEBLK_MINOR);
    if (rv < 0) {
        pr_info("simpleblk: disk allocation failed with %d\n", rv);
    }

    pr_info("simpleblk module loaded\n");
    return 0;
}

static void __exit simpleblk_exit(void)
{
    simpleblk_free(simpleblk_dev);
    unregister_blkdev(simpleblk_major, "simpleblk");

    pr_info("simpleblk: module unloaded\n");
}


module_init(simpleblk_init);
module_exit(simpleblk_exit);
MODULE_LICENSE("GPL");

