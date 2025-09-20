E-COMMERCE WEBSITE


Requirements - 
1. user should be able to view all products, add to cart, order products
2. product categories, and search functionality
3. users can see order history, update profile, track order status
4. Inventory management, see product details and update availability accordingly
5. multiple payment methods and secure transaction
6. concurrent user requests and ensure data consistency
7. handle large no. of products and users
8. user-friendly interface


Functional requirements - 
1. user should be able to view all products, add to cart, order products
2. product categories, and search functionality
3. users can see order history, update profile, track order status
4. Inventory management, see product details and update availability accordingly
5. multiple payment methods and secure transaction

Non-Functional requirements - 
6. concurrent user requests and ensure data consistency
7. handle large no. of products and users
8. user-friendly interface


NOTE: we will have access to AmazonSystem instance only, so we need to create all main functions in this system class only.
NOTE: you will buy products, so you need a single entity called Product for 1 item. You also need a collection of products that you will buy, so you need a Cart.
We don't need collection of Cart, so no upper class needed.
We will place order, so we need Order class for 1 order which will store user, products info, payment method, payment status, order status.
Users can place multiple orders, so we need a collection of Orders also, so we need a OrderManager.


Core Entities :-
1. user
2. product
3. AmazonSystem
4. Cart
5. Order
6. Payment Method

User
- id, name, email, Cart
- addToCart(product)
- deleteFromCart(product)

Product
- id, name, price, category
- setPrice

Cart 
- map<Product, int> productCount
- addItem(Product), removeItem(Product)

Order
- user, map<Product, int> productCount, totalPrice, paymentMethod, paymentStatus, orderStatus
- get/set for all fields
- pay

OrderManager
- map<user id, vector<Orders>> orders;

Payment -> upi, card

AmazonSystem
- OrderManager orderManager
- 

Enum - 
productStatus [Available, NotAvailable]
PaymentStatus [Pending, Completed, Cancelled]
OrderStatus [Pending, Placed, Cancelled]