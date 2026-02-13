/*
===============================================================================
                    ADVANCED OPERATING SYSTEM KERNEL CONCEPTS
===============================================================================

Topics Covered:
1. Context Switching (Saving Registers)
2. Process Control Block (PCB)
3. Multicore Scheduling
4. NUMA Architecture
5. Kernel Modules
6. Syscall Table
7. Trap Handling
8. Page Replacement (FIFO, LRU)
9. Copy-On-Write
10. Kernel Panic Analysis
11. SELinux / AppArmor Concept
12. Rootkit Detection Concept

This is an EDUCATIONAL STRUCTURAL SIMULATION.
===============================================================================
*/

#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10
#define MAX_CORES 4
#define MEMORY_PAGES 5

/* =============================================================================
   1️⃣ CONTEXT SWITCHING (Saving Registers)
   =============================================================================

   When CPU switches from Process A → Process B:
   - Save registers of A
   - Load registers of B
*/

typedef struct {
    int rax, rbx, rcx, rdx;
    int rip;   // instruction pointer
    int rsp;   // stack pointer
} CPURegisters;

void save_context(CPURegisters *regs) {
    printf("Saving CPU registers...\n");
}

void restore_context(CPURegisters *regs) {
    printf("Restoring CPU registers...\n");
}

/* =============================================================================
   2️⃣ PROCESS CONTROL BLOCK (PCB)
   =============================================================================

   Stores process metadata.
*/

typedef struct {
    int pid;
    char state[20];
    CPURegisters registers;
    int priority;
} PCB;

PCB process_table[MAX_PROCESSES];

/* =============================================================================
   3️⃣ MULTICORE SCHEDULING
   =============================================================================

   Each core can run a different process.
*/

void schedule_on_core(int core_id, PCB *process) {
    printf("Scheduling PID %d on Core %d\n", process->pid, core_id);
}

/* =============================================================================
   4️⃣ NUMA (Non-Uniform Memory Access)
   =============================================================================

   In NUMA:
   - Each CPU has local memory
   - Access time differs per region
*/

void access_memory(int core_id, int memory_node) {
    if (core_id == memory_node)
        printf("Fast local memory access\n");
    else
        printf("Slow remote memory access\n");
}

/* =============================================================================
   5️⃣ KERNEL MODULES
   =============================================================================

   Loadable kernel modules extend kernel dynamically.
*/

void load_kernel_module(char *module_name) {
    printf("Loading kernel module: %s\n", module_name);
}

/* =============================================================================
   6️⃣ SYSCALL TABLE
   =============================================================================

   Maps syscall number → kernel function
*/

typedef void (*syscall_func)();

void sys_write() { printf("sys_write called\n"); }
void sys_read()  { printf("sys_read called\n"); }

syscall_func syscall_table[2] = { sys_write, sys_read };

void invoke_syscall(int syscall_number) {
    syscall_table[syscall_number]();
}

/* =============================================================================
   7️⃣ TRAP HANDLING
   =============================================================================

   Trap = exception (divide by zero, page fault, etc.)
*/

void trap_handler(int trap_number) {
    printf("Handling trap: %d\n", trap_number);
}

/* =============================================================================
   8️⃣ PAGE REPLACEMENT ALGORITHMS
   =============================================================================
*/

int memory_pages[MEMORY_PAGES] = {0};

/* FIFO Page Replacement */
void fifo_replace(int page) {
    static int index = 0;
    memory_pages[index] = page;
    index = (index + 1) % MEMORY_PAGES;
    printf("FIFO replaced with page %d\n", page);
}

/* LRU Page Replacement */
void lru_replace(int page) {
    printf("LRU replacing least recently used page with %d\n", page);
}

/* =============================================================================
   9️⃣ COPY-ON-WRITE (COW)
   =============================================================================

   Used during fork().
   Child shares memory until write occurs.
*/

void copy_on_write() {
    printf("Memory shared. Copy only if modified.\n");
}

/* =============================================================================
   🔟 KERNEL PANIC ANALYSIS
   =============================================================================

   Kernel panic occurs when:
   - Null pointer dereference
   - Invalid memory access
   - Driver failure
*/

void kernel_panic(char *reason) {
    printf("KERNEL PANIC: %s\n", reason);
}

/* =============================================================================
   1️⃣1️⃣ SELINUX / APPARMOR (MAC)
   =============================================================================

   Mandatory Access Control.
*/

void enforce_security_policy(char *process) {
    printf("Applying MAC policy to process: %s\n", process);
}

/* =============================================================================
   1️⃣2️⃣ ROOTKIT DETECTION
   =============================================================================

   Detect hidden kernel modules or syscall hooks.
*/

void detect_rootkit() {
    printf("Checking syscall table integrity...\n");
    printf("Scanning for hidden modules...\n");
}

/* =============================================================================
   MAIN SIMULATION
   =============================================================================
*/

int main() {

    PCB p1 = {1, "READY"};
    PCB p2 = {2, "READY"};

    save_context(&p1.registers);
    restore_context(&p2.registers);

    schedule_on_core(0, &p1);
    access_memory(0, 1);

    load_kernel_module("net_driver");

    invoke_syscall(0);

    trap_handler(13);

    fifo_replace(10);
    lru_replace(20);

    copy_on_write();

    enforce_security_policy("process_1");

    detect_rootkit();

    kernel_panic("Null pointer dereference");

    return 0;
}
