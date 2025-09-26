import mmap
import hexdump

with open('/dev/sda', 'rb') as fp:
    mm = mmap.mmap(fp.fileno(),
                   length=128 << 30,  # 映射128GB空间
                   prot=mmap.PROT_READ)
    hexdump.hexdump(mm[:512])  # 显示前512字节内容
    mm.close()  # 关闭内存映射