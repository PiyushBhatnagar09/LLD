# Scalability
Theory: https://algomaster.io/learn/system-design/scalability

## More Concepts
### Vertical Scaling:
**|4CPU, 16GB RAM| -> |32CPU, 256GB RAM|**
- cpu means core. So, 4 cpu means 4 cores i.e. 4 tasks can run parallelly.
- 1 cpu can handle 1 thread.
- 1 task can use multiple cpus only if it's multi-threaded.
- More CPUs ≠ faster unless the software is designed for parallelism.
- RAM is computer's short term working memory. It stores the data and programs that the CPU is actively using right now. Increasing RAM allows the system to do more work at once and avoid slow disk usage.
- Faster SSDs (especially NVMe) can read and write data much quicker than slow SSDs or HDDs. This means applications spend less time waiting for data.
- Upgrading network cards (NICs) increases the amount of data that can be transmitted per second, which improves overall system and network performance.

### Horizontal Scaling
- For horizontal scaling to work effectively, services should be stateless. A stateless service does not store any session data locally Each request can be handled by any server.
- **To make services stateless:** 
 - Use systems like Redis or Memcached to store session information Multiple service instances can access the same session data. Users are not tied to a single server. Easy to scale horizontally.
 - JWT (JSON Web Tokens) store user information inside a signed token sent with each request. Why this helps: No session data stored on the server, Servers only verify the token, Ideal for microservices and APIs.
 - Store uploaded files in object storage instead of local disk. Use object storage such as Amazon S3, Google Cloud Storage, or Azure Blob Storage. Why this helps: Files are shared across all service instances, Servers can be replaced or scaled without data loss, High durability and availability.


## Clients->Load Balancer->App Servers->Redis Caches->Database


**Redis Cluster partitions data across nodes using hash slots**
We have data in the form of keyspace 0-1Miliion (let's say account numbers)
- The keyspace is divided into 16,384 hash slots
- Each node (cache server) has given ownership of a subset of hash slots
- the key in the keyspace are passed to a hash function and based on the value of hash function, the hash slot is decided for that key
- When clients read or write a key, Redis routes the request to the node that owns that slot

### Message Queue Tier
- Normally, we send api call from one server to another and both should be active to send and catch the api call
- In Message queue, producer publishes message to message queue and consumer consumes the message once he is available. So, consumer need not to be active everytime.
