It is the practice of grouping data (variables) and behavior (methods) that operate on that data into a single unit (typically a class) and restricting direct access to the internal details of that class.

In simple terms:

Encapsulation = Data hiding + Controlled access

The below text you can confuse it with Abstraction
But, Abstraction = Hiding Complexity + Showing Essentials

For my understanding of Encapsulation (may need changes below)
[
Basically giving only getter & setter to user and separating the other business logic for security.
We can handle the get, set as well.
Like for setting balance, the amt should be > 0, cannot be -ve, etc.
For setting card number, we can mask the card number while creating the object, so that actual card number never gets saved.
]