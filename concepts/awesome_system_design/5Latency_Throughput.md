Bandwidth is the maximum amount of data that can be transmitted over a network connection in a given amount of time.

Think of it like a highway:

🚗 The number of lanes = bandwidth
🚗 The cars on the road = actual data being transferred

More lanes → more cars can travel at the same time.
Higher bandwidth → more data can move per second.

### IMP Example to understand
- Bandwidth is the number of lanes on the highway. More lanes mean more cars can travel simultaneously.
- Throughput is how many cars actually pass through per hour. This depends on traffic conditions, not just the number of lanes.
- Latency is the time it takes for a single car to travel from one city to the other.

### Measuring Latency
🔢 What Do Percentiles Mean?
Metric	Meaning
p50 (median)	50% of requests are faster than this value
p95	95% of requests are faster than this
p99	99% of requests are faster than this
p99.9	99.9% of requests are faster than this

Think of it like this:
If your p99 latency is 500ms, it means:

- 99% of users experience latency below 500ms
- But 1% experience latency worse than 500ms

And in large systems, 1% can mean thousands of users.

### Connection Pooling
Connection pooling means:

Reusing already-open network connections instead of creating new ones for every request.

Instead of:
Request → Open connection → Close connection
Request → Open connection → Close connection

We do:
Open connection once
Reuse it for multiple requests
Close when no longer needed

## Protocol optimization: Use HTTP/2, HTTP/3 (QUIC)
### HTTP/1.1 (Older)

Problems:
- One request per connection (blocking behavior)
- Head-of-line blocking
- Requires multiple TCP connections for parallel requests
- Higher latency

### HTTP/2

HTTP/2 improves performance significantly.
Key Features
1️⃣ Multiplexing
Multiple requests and responses can travel simultaneously over one TCP connection.
No need to open many connections.

2️⃣ Header Compression
Reduces size of HTTP headers.

3️⃣ Server Push
Server can send resources before client asks.

Result:
Fewer connections
Faster page loads
Better resource usage

### HTTP/3 (QUIC)
HTTP/3 uses QUIC, which runs over UDP instead of TCP.
This is a major upgrade.

Why QUIC is better
1️⃣ Faster connection setup

Combines:
Transport handshake
TLS handshake
Into fewer round trips.

2️⃣ No Head-of-Line Blocking

In HTTP/2, if one packet is lost:
All streams pause (TCP limitation)

In HTTP/3:

Only the affected stream pauses
Others continue normally
Huge performance improvement on:
Mobile networks
High-latency networks
Unstable connections

3️⃣ Built-in encryption

QUIC includes TLS 1.3 by default.