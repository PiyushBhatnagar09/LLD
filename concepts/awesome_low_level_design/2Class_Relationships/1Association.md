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