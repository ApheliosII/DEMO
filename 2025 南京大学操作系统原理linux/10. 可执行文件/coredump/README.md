**Core Dump**: 通过设置 core dump size，我们可以在程序发生 core dump 时保存到文件系统，并且在后续使用 gdb 调试它。

注意：在原生linux系统运行，不要在/mnt/e/里面运行。

```bash
ulimit -c unlimited
echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern
./crash
```