## |Interface| <- |Class|

## Interface code example
class PaymentGateway {
public:
    virtual ~PaymentGateway() {}  // Virtual destructor for proper cleanup
    virtual void initiatePayment(double amount) = 0;  // Pure virtual function
};

class StripePayment : public PaymentGateway {
public:
    void initiatePayment(double amount) override {
        cout << "Processing payment via Stripe: $" << amount << endl;
    }
};

- Use override keyword for overriding the function
    - it is not mandatory, but it is strongly recommended.
- Benefits of using override: Catches signature mismatches, Makes code clearer and self-documenting.

## Usage: Loose Coupling in Action
Now let’s say you have a CheckoutService that processes payments. Instead of hardcoding a specific payment gateway, you inject the interface:

class CheckoutService {
private:
    PaymentGateway* paymentGateway;

public:
    CheckoutService(PaymentGateway* gateway) : paymentGateway(gateway) {}
    
    void setPaymentGateway(PaymentGateway* gateway) {
        paymentGateway = gateway;
    }
    
    void checkout(double amount) {
        if (paymentGateway != nullptr) {
            paymentGateway->initiatePayment(amount);
        }
    }
};
Notice that CheckoutService depends only on the interface, not the implementation. This makes it easy to swap or extend payment providers without changing the checkout logic.

### NOTE: If a pointer variable is unassigned then it is nullptr

Now you can plug in any payment gateway at runtime:

int main() {
    StripePayment stripeGateway;
    CheckoutService service(&stripeGateway);
    service.checkout(120.50);  // Output: Processing payment via Stripe: $120.5
    
    // Switch to Razorpay
    RazorpayPayment razorpayGateway;
    service.setPaymentGateway(&razorpayGateway);
    service.checkout(150.50);  // Output: Processing payment via Razorpay: ₹150.5
  
    return 0;
}
Here’s the beauty of it:

CheckoutService doesn’t care which payment gateway is being used.
You can replace, extend, or test different gateways without touching its code.
