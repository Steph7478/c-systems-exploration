# C Systems Exploration: Under the Hood

A specialized laboratory for exploring low-level systems programming. This project is a hands-on journey to understand exactly what happens "under the hood" of modern web frameworks, moving from raw bytes on a socket to structured application logic.

---

### 🧠 Core Learning Objectives

The primary focus of this repository is the deep-seated understanding of:

* **Multithreading & Concurrency:** Implementing the **Producer-Consumer pattern**. I'm exploring how to manage a pool of worker threads using Win32 `CRITICAL_SECTION` and `CONDITION_VARIABLE` to handle synchronization without CPU-heavy busy-waiting.
* **Hardware Performance Profiling (x86-64 Assembly):** Moving beyond software-based timers by interfacing directly with the CPU. Using the `RDTSC` instruction to measure execution cost in raw clock cycles for nanosecond-level precision.
* **Memory Architecture:** Studying the lifecycle of data between the **Stack** (request parsing) and the **Heap** (dynamic JSON serialization and Repository data mapping). 
* **Networking Internals (Winsock):** Moving beyond high-level HTTP libraries to manually manage **Berkeley Sockets**. This includes the full flow: `socket` -> `bind` -> `listen` -> `accept` -> `recv`.
* **Protocol Anatomy:** Deconstructing the **HTTP/1.1 protocol** by building a custom parser that identifies request lines, headers, and body pointers through direct memory manipulation and pointer arithmetic.

---

### 🛠️ How it Works (The Flow)

1.  **The Queue:** A thread-safe circular buffer (`ClientQueue`) acts as the bridge between the network and the logic.
2.  **Hardware Timestamping:** As soon as a connection is accepted, we call a custom Assembly function to grab the current CPU clock cycle using the `RDTSC` instruction.
    
3.  **The Workers:** A pool of threads sleeps on a condition variable, waking up only when a new client is enqueued, ensuring efficient resource usage.
4.  **The Parser:** Uses memory-efficient techniques to slice the raw buffer into an `HttpRequest` struct.
5.  **Performance Logging:** The worker calculates the delta between the entry timestamp and the processing end time, providing a precise "Hardware Profile" of the request latency.

---

### 🔍 Key Technical Takeaways

* **Assembly Integration:** Implementing a NASM-compiled module to read the Time Stamp Counter (TSC).
    * *Technique:* Using `SHL` (Shift Left) to move high-order bits and `OR` bitwise operations to merge `EDX:EAX` into a single 64-bit `RAX` register.
    
* **Low-Level Sync:** Utilizing `SleepConditionVariableCS` to pause threads effectively, preventing race conditions during queue access.
* **Memory Safety:** Managing buffers and string lengths carefully to prevent overflows in a language without a garbage collector.

---
