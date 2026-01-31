# Content
### Cloud providers handle this automatically. AWS ALB, Google Cloud Load Balancer, and Azure Load Balancer are all managed services with built-in redundancy. On-premises, you might use keepalived with a virtual IP that floats between two HAProxy instances.
Explanation: Cloud providers handle load balancer high availability for you. Services like AWS Application Load Balancer (ALB), Google Cloud Load Balancer, and Azure Load Balancer are fully managed, meaning the cloud provider automatically runs multiple redundant instances behind the scenes. If one instance fails, traffic is seamlessly routed to another without you needing to configure or monitor failover.
In an on-premises setup, you must design this redundancy yourself. A common approach is to run two HAProxy servers and use keepalived to manage a virtual IP address (VIP). The VIP is active on only one HAProxy at a time. If the primary HAProxy fails, keepalived detects the failure and moves the VIP to the standby HAProxy, allowing traffic to continue with minimal disruption.

### Patroni is a high-availability solution for PostgreSQL. It continuously monitors the health of the primary (leader) database. If the primary becomes unavailable, Patroni automatically promotes a replica to become the new primary.

### How a circuit breaker works
A circuit breaker has three states:

1. Closed (Normal state)

Requests are allowed
Failures are counted
If failures exceed a threshold → switch to Open

Client → Service (OK)

2. Open (Fail-fast state)

Requests are blocked immediately
No call is made to the failing service
Prevents further damage
After a timeout → switch to Half-Open

Client ✖ Service (blocked)

3. Half-Open (Test state)

A limited number of requests are allowed
If they succeed → go back to Closed
If they fail → return to Open

Client → Service (test request)