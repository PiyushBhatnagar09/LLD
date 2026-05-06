## Functional Requirement
- User can search for Restaurants based on location
- User can add items to Cart
- User can checkout by making Payment
- User should be notified once oredr is placed successfully


## Non-functional Requirement
- Each part of design should be scalable & Modifiable


## LLD Approach
- Bottom up approach: Make small objects first, identify relationships and then make bigger objects.
- Top dowm approach: Opposite of above.


## Objects
- Restaurant (id, name, addr, vector<MenuItem>) 
[Modal class because it only has getter setters, no special function]

- Menu item (code, name, price) 
[Modal class because it only has getter setters, no special function]

- Restaurant manager (vector<Restaurant>, CRUD ops, searchByLocation)
[Singleton Class because it should only has 1 instances. Because if multiple instances then every instance can have different set of restaurants]
- User (id, name, addr, Cart cart) [Modal]
- Cart (Restaurant Rs, vector<MenuItem> items, addToCart(item), clearCart, isEmpty)
- Order (id, Restaurant Rs, vector<MenuItem>, User user, PaymentStrategy ps, getType [delivery type, pickup type])
- PaymentStrategy -> UPI, Bank
- Order -> DeliveryOrder, PickupOrder (override getType())
- OrderFactory -> NewOrderFactory, ScheduledOrderFactory
- OrderManager (vector<Order> order, addOrder)
= to manage orders, like storing in database, fetching bunch of orders. NOTE: these responsibilities or functions, we shouldn't make in Order or we cannot ideally. Because we will be maintaining some hashmap of order id -> order in this manager

- We can assume notification service exists and we will call it.
- NotificationService (notify(Order))

- Zomato Class (Orchestrator class) - A single point of contact for frontend application. Client should be unable of all available objects


## Relationship
- Restaurant has menu item (1..*)
- Menu item cannot exist without restaurant
- So, it's not association (basically both classes are independent), it's composition (one class owns another). [Filled Diamond icon]
- Restaurant can exist independently. But restaurants comes under restaurant manager. So, Aggregation (One class contains another class but doesn't fully own it like Team->Player). [Blank Diamond icon]
- User and Cart will have 1..1 relationship and Cart cannot exist independently without User. So, this is Composition.
- Cart and Restaurant can exisit independently - Association (1..1)
- Cart & Menu items can exisit independently - Association (1..*)
- PaymentStrategy is abstract. And UPI, Bank as derived classes
- Order has a User, REstaurant, menuitems, paymentstrategy. Both can exist independently.
- Order -> Delivery Order, Pickup Order. Override getType() method
- NotificationService has a Order


## Patterns
- Order can created, deleted. So, we can create a Order Manager which will use Order factory to create different type of orders

39:30


## IMP POINTS
- Static id increments
💡 Interview gold line
“A static counter is not safe in distributed or multi-threaded systems. I would prefer AtomicInteger for in-memory cases, and database-generated IDs or UUIDs in production.”

😏 One more thing (important)
Even if you fix multithreading…
👉 It still fails in distributed systems

Why?

Each server has its own idCounter
Duplicate IDs across machines 💀
❤️ Final takeaway
Static + increment → ❌ unsafe in threads
Use AtomicInteger → ✅ safe locally
Use DB/UUID → ✅ safe at scale