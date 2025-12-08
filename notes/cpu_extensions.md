# x86 CPU EXTENSIONS

A detailed list of modern CPU extensions.

## PCLMULQDQ (Packed Carry-Less Multiplication Quadword) (AMD/INTEL)
> Takes two 64-bit values and multiplies them as polynomials (with no carries), producing a 128-bit result.
> Used in GCM (Galois/Counter Mode - a popular encryption mode) & CRC (Cyclic Redundancy Check — a fast error-detecting checksum).

EXAMPLE of Carry-less Multiplication:

```
A = 0b0000.1110 -> A = x^3 + x^2 + x
B = 0b0000.1011 -> B = x^3 + x   + 1
```

```
Multiply using Shift:

bit 0 = 1 -> A << 0  = 0b0000.1110
bit 1 = 1 -> A << 1  = 0b0001.1100
bit 2 = 0 -> skip
bit 3 = 1 -> A << 3  = 0b0111.0000

XOR them:

(0) 0b0000.1110 ^ (1) 0b0001.1100 = 0b0001.0010
(=) 0b0001.0010 ^ (3) 0b0111.0000 = 0b0110.0010
```

## MONITOR (paired with MWAIT)
> Lets a thread wait efficiently for a write to a specific memory address.

```asm
mov rax, [address_to_watch]
MONITOR rax, rcx, rdx
MWAIT
```
> This means:
> CPU records the cache line containing the address in RAX.
> MWAIT puts the CPU into a sleep state.
> CPU wakes up instantly when ANY core writes to that cache line.

❌ Operating systems mostly disable it in user mode Because:

- It can be used for side-channel attacks.
- It interacts awkwardly with power states and scheduler heuristics.
- It can wake too easily on unrelated store traffic.

However Intel also
- Added UMONITOR/UMWAIT (user-mode variants, Tiger Lake+).
- Added power-management features that make MONITOR/MWAIT less necessary.

## DTES64 (64-bit Debug Store Area)
> The “Debug Store” (sometimes “DS”) is basically a hardware-assisted facility for logging certain CPU events, often:
> - Branches taken / not taken
> - Executed instruction addresses (branch-to / branch-from)
> - Other debug/tracing info
> 
> This helps profilers, debuggers, and performance-monitoring tools to record control-flow history efficiently — without needing software instrumentation at each branch.

## DS_CPL (CPL-qualified Debug Store) (CPL = Current Privilege Level)
> Meaning the CPU can selectively restrict which branch messages get stored into the Debug Store buffer depending on the current privilege level (CPL).

## VMX (Virtual Machine Extensions) (INTEL) (SVM (Secure Virtual Machine) on AMD)
It’s Intel’s hardware support for virtualization. allows to run virtual machines efficiently without emulation.

// SSE3, 
// SMX, EST, 
// TM2, SSSE3, SDBG, FMA, 
// CMPXCHG16B, xTPR_Upd_Ctrl, PDCM, PCID, 
// SSE41, SSE42, x2APIC, MOVBE, 
// POPCNT, TSC_Deadline, AES, XSAVE, 
// OSXSAVE, AVX, F16C, RDRAND, 
// FPU, VME, DE, PSE, 
// TSC, MSR, PAE, MCE, 
// CX8, APIC, SEP, MTRR, 
// PGE, MCA, CMOV, PAT, 
// PSE_36, CLFSH, DS, ACPI, 
// MMX, FXSR, SSE, SSE2, 
// SS, HTT, TM, PBE, 
// FSGSBASE, IA32_TSC_ADJUST, SGX, BMI1, 
// HLE, AVX2, SMEP, BMI2, 
// ERMS, INVPCID, RTM, Dep_FPU_CS_DS, 
// Intel_Mem_Prot_Exts, RDSEED, ADX, SMAP, 
// CLFLUSHOPT, Intel_Proc_Trace, SGX_LC, IBRS, 
// IBPB, STIBP, IA32_ARCH_CAP_MSR, SSBD, LAHF64, 
// LZCNT, PREFETCHW, SYSCALL64, SYSRET64, 
// EXE_DIS_BIT, OGBP, RDTSCP, LM64
