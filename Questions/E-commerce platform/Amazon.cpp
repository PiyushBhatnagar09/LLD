#include<iostream>
#include<vector>
using namespace std;

enum class CategoryType
{
        ELECTRONIC,
        FOOD,
        STATIONARY
};

class User
{
        string id;
        string name;
        string email;

        Cart* cart;

        public:
        User(string id, string name, string email): id(id), name(name), email(email) 
        {
                cart= new Cart();
        }

        void addToCart(Product product)
        {
                cart->addProduct(product);
        }

        string getId()
        {
                return id;
        }
        string getName()
        {
                return name;
        }
        string getEmail()
        {
                return email;
        }
        void setId(string id)
        {
                this->id=id;
        }
        void setName(string name)
        {
                this->name=name;
        }
        void setEmail(string email)
        {
                this->email=email;
        }
};

class Product
{
        string id, name;
        double price;
        CategoryType type;

        public:
        Product(string id, string name, double price, CategoryType type): id(id), name(name), price(price), type(type) {}

        string getId()
        {
                return id;
        }
        string getName()
        {
                return name;
        }
        double getPrice()
        {
                return price;
        }
        void setPrice(double price)
        {
                this->price=price;
        }
};

class Cart 
{
        

        public:
        Cart() {}

        vector<Product> getProducts()
        {
                return products;
        }
        void addProduct(Product product)
        {
                products.push_back(product);
        }
};

class Order
{

};

int main()
{

}