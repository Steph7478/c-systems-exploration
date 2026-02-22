# C Systems Exploration: Under the Hood

A specialized laboratory for exploring low-level systems programming. This project is a hands-on journey to understand exactly what happens "under the hood" of modern web frameworks, moving from raw bytes on a socket to structured application logic.

---

### 🧠 Core Learning Objectives

The primary focus of this repository is the deep-seated understanding of:

* **Multithreading & Concurrency:** Implementing the **Producer-Consumer pattern**. I'm exploring how to manage a pool of worker threads using Win32 `CRITICAL_SECTION` and `CONDITION_VARIABLE` to handle synchronization without CPU-heavy busy-waiting.
* **Memory Architecture:** Studying the lifecycle of data between the **Stack** (request parsing) and the **Heap** (dynamic JSON serialization and Repository data mapping). 
* **Networking Internals (Winsock):** Moving beyond high-level HTTP libraries to manually manage **Berkeley Sockets**. This includes the full flow: `socket` -> `bind` -> `listen` -> `accept` -> `recv`.
* **Protocol Anatomy:** Deconstructing the **HTTP/1.1 protocol** by building a custom parser that identifies request lines, headers, and body pointers through direct memory manipulation and pointer arithmetic.
* **Systems Design:** Implementing a clean **MVC/Repository architecture** in C to see how high-level design patterns translate to low-level, performance-critical code.

---

### 🛠️ How it Works (The Flow)

1.  **The Queue:** A thread-safe circular buffer (`ClientQueue`) acts as the bridge between the network and the logic.
2.  **The Workers:** A pool of threads sleeps on a condition variable, waking up only when a new client is enqueued, ensuring efficient resource usage.
3.  **The Parser:** Uses `sscanf` and `strstr` to slice the raw buffer into an `HttpRequest` struct.
4.  **The Router:** Matches methods and paths to function pointers, mimicking modern routing engines.
5.  **The Data:** Uses a `UserService` and `UserRepository` to simulate database interactions, serializing C structs into JSON strings manually.



### 🔍 Key Technical Takeaways
* **Low-Level Sync:** Understanding `SleepConditionVariableCS` to pause threads until data is ready.
* **Memory Safety:** Managing buffers and string lengths (`strncpy`) to prevent overflows.
* **Data Alignment:** Using `offsetof` for generic JSON serialization of C structs.

---
*This is an educational project focused on de-abstracting the web stack.*
