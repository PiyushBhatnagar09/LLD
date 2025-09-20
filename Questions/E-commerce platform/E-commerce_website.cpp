#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <algorithm>
#include <uuid/uuid.h>

using namespace std;

// ----------------------------- Utility -----------------------------
string generateUUID()
{
        uuid_t uuid;
        uuid_generate_random(uuid);
        char str[37];
        uuid_unparse(uuid, str);
        return string(str);
}

// ----------------------------- Forward declarations -----------------------------
class Product;
class Order;
class Payment;
class Cart;
class User;

// ----------------------------- OrderStatus -----------------------------
enum class OrderStatus
{
        PENDING,
        PLACED,
        SHIPPED,
        DELIVERED,
        CANCELLED
};

// ----------------------------- OrderItem -----------------------------
class OrderItem
{
public:
        OrderItem(shared_ptr<Product> product, int quantity)
            : product(product), quantity(quantity) {}

        shared_ptr<Product> getProduct() const { return product; }
        int getQuantity() const { return quantity; }

private:
        shared_ptr<Product> product;
        int quantity;
};

// ----------------------------- Product -----------------------------
class Product
{
public:
        Product(const string &name, const string &description, double price, int stock)
            : id(generateUUID()), name(name), description(description), price(price), stock(stock) {}

        string getId() const { return id; }
        string getName() const { return name; }
        string getDescription() const { return description; }
        double getPrice() const { return price; }

        bool isAvailable(int quantity) const
        {
                lock_guard<mutex> lock(stockMutex);
                return stock >= quantity;
        }

        void decreaseStock(int quantity)
        {
                lock_guard<mutex> lock(stockMutex);
                if (stock < quantity)
                        throw runtime_error("Insufficient stock");
                stock -= quantity;
        }

        void increaseStock(int quantity)
        {
                lock_guard<mutex> lock(stockMutex);
                stock += quantity;
        }

        int getStock() const
        {
                lock_guard<mutex> lock(stockMutex);
                return stock;
        }

private:
        string id, name, description;
        double price;
        mutable int stock;
        mutable mutex stockMutex;
};

// ----------------------------- Cart -----------------------------
class Cart
{
public:
        void add(shared_ptr<Product> product, int quantity)
        {
                lock_guard<mutex> lock(cartMutex);
                items[product] += quantity;
        }

        map<shared_ptr<Product>, int> getItems() const
        {
                lock_guard<mutex> lock(cartMutex);
                return items;
        }

        void clear()
        {
                lock_guard<mutex> lock(cartMutex);
                items.clear();
        }

private:
        map<shared_ptr<Product>, int> items;
        mutable mutex cartMutex;
};

// ----------------------------- Order -----------------------------
class Order
{
public:
        Order(shared_ptr<User> user, vector<OrderItem> items)
            : id(generateUUID()), user(user), items(items), status(OrderStatus::PENDING)
        {
                totalAmount = 0.0;
                for (const auto &item : items)
                {
                        totalAmount += item.getProduct()->getPrice() * item.getQuantity();
                }
        }

        string getId() const { return id; }
        vector<OrderItem> getItems() const { return items; }
        double getTotalAmount() const { return totalAmount; }
        OrderStatus getStatus() const { return status; }

        void cancel()
        {
                if (status == OrderStatus::SHIPPED)
                        throw runtime_error("Cannot cancel shipped order");
                status = OrderStatus::CANCELLED;
        }

        void setStatus(OrderStatus status_)
        {
                status = status_;
        }

private:
        string id;
        shared_ptr<User> user;
        vector<OrderItem> items;
        double totalAmount;
        OrderStatus status;
};

// ----------------------------- Payment Interface -----------------------------
class Payment
{
public:
        virtual bool processPayment(double amount) = 0;
        virtual ~Payment() {}
};

// ----------------------------- CreditCardPayment -----------------------------
class CreditCardPayment : public Payment
{
public:
        bool processPayment(double amount) override
        {
                cout << "Processing credit card payment for amount: " << amount << endl;
                return true;
        }
};

// ----------------------------- UPIPayment -----------------------------
class UPIPayment : public Payment
{
public:
        bool processPayment(double amount) override
        {
                cout << "Processing UPI payment for amount: " << amount << endl;
                return true;
        }
};

// ----------------------------- User -----------------------------
class User
{
public:
        User(const string &name, const string &email, const string &password)
            : id(generateUUID()), name(name), email(email), password(password), cart(make_shared<Cart>()) {}

        string getId() const { return id; }
        shared_ptr<Cart> getCart() const { return cart; }
        vector<shared_ptr<Order>> &getOrders() { return orders; }

        void addOrder(shared_ptr<Order> order)
        {
                orders.push_back(order);
        }

private:
        string id, name, email, password;
        shared_ptr<Cart> cart;
        vector<shared_ptr<Order>> orders;
};

// ----------------------------- OnlineShoppingService -----------------------------
class OnlineShoppingService
{
public:
        static OnlineShoppingService &getInstance()
        {
                static OnlineShoppingService instance;
                return instance;
        }

        shared_ptr<User> registerUser(const string &name, const string &email, const string &password)
        {
                auto user = make_shared<User>(name, email, password);
                users[user->getId()] = user;
                return user;
        }

        shared_ptr<Product> addProduct(const string &name, const string &description, double price, int stock)
        {
                auto product = make_shared<Product>(name, description, price, stock);
                products[product->getId()] = product;
                return product;
        }

        void addToCart(const string &userId, const string &productId, int quantity)
        {
                auto user = users[userId];
                auto product = products[productId];
                if (!user || !product)
                        throw runtime_error("User or product not found");
                user->getCart()->add(product, quantity);
        }

        vector<shared_ptr<Product>> searchProducts(const string &keyword)
        {
                vector<shared_ptr<Product>> result;
                for (const auto &[id, product] : products)
                {
                        if (product->getName().find(keyword) != string::npos)
                        {
                                result.push_back(product);
                        }
                }
                return result;
        }

        shared_ptr<Order> placeOrder(const string &userId, Payment &payment)
        {
                auto user = users[userId];
                if (!user)
                        throw runtime_error("User not found");

                auto items = user->getCart()->getItems();
                vector<OrderItem> orderItems;

                for (const auto &[product, quantity] : items)
                {
                        if (product->isAvailable(quantity))
                        {
                                product->decreaseStock(quantity);
                                orderItems.emplace_back(product, quantity);
                        }
                }

                auto order = make_shared<Order>(user, orderItems);
                orders[order->getId()] = order;
                user->getCart()->clear();
                user->addOrder(order);

                if (payment.processPayment(order->getTotalAmount()))
                {
                        order->setStatus(OrderStatus::PLACED);
                }
                else
                {
                        order->setStatus(OrderStatus::CANCELLED);
                        for (const auto &item : orderItems)
                        {
                                item.getProduct()->increaseStock(item.getQuantity());
                        }
                }

                return order;
        }

        void cancelOrder(const string &orderId)
        {
                auto order = orders[orderId];
                if (!order)
                        throw runtime_error("Order not found");
                order->cancel();
                for (auto &item : order->getItems())
                {
                        item.getProduct()->increaseStock(item.getQuantity());
                }
        }

        shared_ptr<User> getUser(const string &userId) { return users[userId]; }
        shared_ptr<Product> getProduct(const string &productId) { return products[productId]; }
        shared_ptr<Order> getOrder(const string &orderId) { return orders[orderId]; }

private:
        OnlineShoppingService() {}
        unordered_map<string, shared_ptr<User>> users;
        unordered_map<string, shared_ptr<Product>> products;
        unordered_map<string, shared_ptr<Order>> orders;
};

// ----------------------------- Demo -----------------------------
void runDemo()
{
        auto &service = OnlineShoppingService::getInstance();

        auto user1 = service.registerUser("John Doe", "john@example.com", "pass123");
        auto user2 = service.registerUser("Jane Smith", "jane@example.com", "pass456");

        auto product1 = service.addProduct("Smartphone", "High-end smartphone", 999.99, 10);
        auto product2 = service.addProduct("Laptop", "Gaming laptop", 1999.99, 5);

        service.addToCart(user1->getId(), product1->getId(), 2);
        service.addToCart(user1->getId(), product2->getId(), 1);

        CreditCardPayment payment;
        auto order1 = service.placeOrder(user1->getId(), payment);
        cout << "Order placed: " << order1->getId() << endl;

        auto results = service.searchProducts("Laptop");
        cout << "Search Results:" << endl;
        for (auto &product : results)
        {
                cout << product->getName() << endl;
        }

        cout << "Order History for user1:" << endl;
        for (auto &order : user1->getOrders())
        {
                cout << "Order ID: " << order->getId() << endl;
                cout << "Total Amount: $" << order->getTotalAmount() << endl;
                cout << "Status: ";
                switch (order->getStatus())
                {
                case OrderStatus::PENDING:
                        cout << "PENDING";
                        break;
                case OrderStatus::PLACED:
                        cout << "PLACED";
                        break;
                case OrderStatus::SHIPPED:
                        cout << "SHIPPED";
                        break;
                case OrderStatus::DELIVERED:
                        cout << "DELIVERED";
                        break;
                case OrderStatus::CANCELLED:
                        cout << "CANCELLED";
                        break;
                }
                cout << endl
                     << endl;
        }
}

// ----------------------------- Main -----------------------------
int main()
{
        try
        {
                runDemo();
        }
        catch (const exception &e)
        {
                cerr << "Error: " << e.what() << endl;
        }
        return 0;
}
