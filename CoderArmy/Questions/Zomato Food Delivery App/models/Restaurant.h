#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
using namespace std;
class Restaurant {
        private:
        static int nextRestaurantId;
        int id;
        string name;
        string address;
        vector<MenuItem> menuItems;


        public:
        Restaurant(const string& name, const string& address) {
            this->id = ++nextRestaurantId;
            this->name = name;
            this->address = address;
        }

        ~Restaurant() {
                cout<<"Restaurant with ID " << id << " is being destroyed." << endl;
                menuItems.clear();
        }
};

#endif // RESTAURANT_H