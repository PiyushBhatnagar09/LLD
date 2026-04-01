## Based on Direction

1. Unidirectional
EX: Order uses Payment Gateway

Order class has Payment gateway object.

Code - 
```
class PaymentGateway {
public:
    void processPayment(double amount) {
        cout << "Processing payment of $" << amount << endl;
    }
};

class Order {
private:
    PaymentGateway* gateway;

public:
    Order(PaymentGateway* gateway) {
        this->gateway = gateway;
    }

    void checkout() {
        gateway->processPayment(100.0);
    }
};
```

2. Bidirectional
EX: Team --- Developer

Code - 
```
class Developer {
private:
    Team* team;
public:
    void setTeam(Team* team) {
        this->team = team;
    }
};

class Team {
private:
    vector<Developer*> developers;
public:
    void addDeveloper(Developer* dev) {
        developers.push_back(dev);
        dev->setTeam(this);
    }
};
```

## Based on Multiplicity

1..1, 1..*, *..1, *..*

Code - IMP
class Group; // Forward declaration

class User {
private:
    string name;
    vector<Group*> groups;
public:
    User(const string& name) : name(name) {}

    void joinGroup(Group* group);

    string getName() const { return name; }
    vector<Group*> getGroups() const { return groups; }
};

class Group {
private:
    string name;
    vector<User*> users;
public:
    Group(const string& name) : name(name) {}

    void addUser(User* user) {
        for (auto u : users) if (u == user) return;
        users.push_back(user);
        user->joinGroup(this);
    }

    string getName() const { return name; }
    vector<User*> getUsers() const { return users; }
};

void User::joinGroup(Group* group) {
    for (auto g : groups) if (g == group) return;
    groups.push_back(group);
    group->addUser(this);
}

// Usage
User alice("Alice");
User bob("Bob");

Group backend("Backend");
Group devOps("DevOps");

alice.joinGroup(&backend);
alice.joinGroup(&devOps);
bob.joinGroup(&backend);