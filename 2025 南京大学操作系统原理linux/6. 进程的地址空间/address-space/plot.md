# Registers

| Register | Hex Value | Decimal Value |
|----------|-----------|---------------|
| rax | 0x0000000000000000 | 0 |
| rbx | 0x00007fffffffdfe8 | 140737488347112 |
| rcx | 0x00000000004509bb | 4524475 |
| rdx | 0x00000000000ded90 | 912784 |
| rsi | 0x00000000000ded90 | 912784 |
| rdi | 0x00007ffff7f19000 | 140737353191424 |
| rbp | 0x00007fffffffddf0 | 140737488346608 |
| rsp | 0x00007fffffffdd20 | 140737488346400 |
| r8 | 0x00000000004ca270 | 5022320 |
| r9 | 0x0000000000000000 | 0 |
| r10 | 0x0000000000000010 | 16 |
| r11 | 0x0000000000000217 | 535 |
| r12 | 0x0000000000000001 | 1 |
| r13 | 0x00007fffffffdfd8 | 140737488347096 |
| r14 | 0x00000000004c37d0 | 4995024 |
| r15 | 0x0000000000000001 | 1 |
| rip | 0x00000000004019d1 | 4200913 |
| eflags | 0x0000000000000217 | 535 |

# Memory Mappings

| Start Address | End Address | Size | Permissions | Name |
|---------------|-------------|------|--------------|------|
| 0x400000 | 0x401000 | 0x1000 | r--p | /mnt/e/2025/learn/VS Code/2025 南京大学操作系统原理/6. 进程的地址空间/address-space/mmap-demo |
| 0x401000 | 0x499000 | 0x98000 | r-xp | /mnt/e/2025/learn/VS Code/2025 南京大学操作系统原理/6. 进程的地址空间/address-space/mmap-demo |
| 0x499000 | 0x4c2000 | 0x29000 | r--p | /mnt/e/2025/learn/VS Code/2025 南京大学操作系统原理/6. 进程的地址空间/address-space/mmap-demo |
| 0x4c3000 | 0x4c7000 | 0x4000 | r--p | /mnt/e/2025/learn/VS Code/2025 南京大学操作系统原理/6. 进程的地址空间/address-space/mmap-demo |
| 0x4c7000 | 0x4ca000 | 0x3000 | rw-p | /mnt/e/2025/learn/VS Code/2025 南京大学操作系统原理/6. 进程的地址空间/address-space/mmap-demo |
| 0x4ca000 | 0x4cf000 | 0x5000 | rw-p | [heap] |
| 0x4cf000 | 0x4f1000 | 0x22000 | rw-p | [heap] |
| 0x7ffff7ff9000 | 0x7ffff7ffd000 | 0x4000 | r--p | [vvar] |
| 0x7ffff7ffd000 | 0x7ffff7fff000 | 0x2000 | r-xp | [vdso] |
| 0x7ffffffde000 | 0x7ffffffff000 | 0x21000 | rw-p | [stack] |
