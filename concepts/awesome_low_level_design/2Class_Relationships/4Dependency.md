Printer ----> (uses) Document

CODE - 
class Document {
private:
    string content;
public:
    Document(const string& content) : content(content) {}

    string getContent() const {
        return content;
    }
};

class Printer {
public:
    void print(const Document& document) const {
        cout << "Printing: " << document.getContent() << endl;
    }
};

int main() {
    Document doc("Hello, World!");
    Printer printer;

    printer.print(doc);

    // After print() returns, the printer has no reference to the document.
    // Both objects have completely independent lifecycles.

    return 0;
}

## Dependency Injection: a design technique where a class receives the objects it depends on rather than creating them itself.

class Sender {
public:
    virtual void send(const string& message) = 0;
    virtual ~Sender() = default;
};

class EmailSender : public Sender {
public:
    void send(const string& message) override {
        cout << "Email: " << message << endl;
    }
};

class SmsSender : public Sender {
public:
    void send(const string& message) override {
        cout << "SMS: " << message << endl;
    }
};

class NotificationService {
private:
    Sender* sender;
public:
    NotificationService(Sender* sender) : sender(sender) {} // Injected

    void notifyUser(const string& message) {
        sender->send(message);
    }
};