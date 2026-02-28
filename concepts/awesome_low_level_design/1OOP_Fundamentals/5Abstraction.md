How Abstraction Is Achieved - 
1. Abstract classes
2. Interface
3. Public apis

## Abstraction vs Encapsulation
Abstraction focuses on hiding complexity. It's about simplifying what the user sees. Think of the accelerate() pedal in a car. You press it and the car speeds up. You don't need to know about fuel injection, throttle body mechanics, or engine control unit signals. The pedal is the abstraction.

EX: Exposing only deposit() and withdraw() without showing how they work

Encapsulation focuses on hiding data. It's about bundling data and methods together to protect an object's internal state. Think of the engine itself as a self-contained unit. Its internal components (pistons, valves, sensors) are sealed inside a housing. You can't reach in and manually adjust the fuel mixture. The engine protects its own internals.

EX: Private balance field in BankAccount