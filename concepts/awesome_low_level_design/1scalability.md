# Scalability
Theory: https://algomaster.io/learn/system-design/scalability

## More Concepts
---
**Vertical Scaling:** |4CPU, 16GB RAM| -> |32CPU, 256GB RAM|
- cpu means core. So, 4 cpu means 4 cores i.e. 4 tasks can run parallelly.
- 1 cpu can handle 1 thread.
- 1 task can use multiple cpus only if it's multi-threaded.
- More CPUs ≠ faster unless the software is designed for parallelism.
- RAM is computer's short term working memory. It stores the data and programs that the CPU is actively using right now. Increasing RAM allows the system to do more work at once and avoid slow disk usage.
