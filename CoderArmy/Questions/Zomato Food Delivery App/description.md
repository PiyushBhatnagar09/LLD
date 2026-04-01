## Functional Requirement
- User can search for Restaurants based on location
- User can add items to Cart
- User can checkout by making Payment
- User should be notified once oredr is placed successfully

## Non-functional Requirement
- Each part of design should be scalable & Modifiable

## LLD Approach
- Bottom up approach: Make small objects first, identify relationships and then make bigger objects.
- Top dowm approach: Opposite of above.

## Objects
- Restaurant (id, name, addr, vector<MenuItem>) 
[Modal class because it only has getter setters, no special function]

- Menu item (code, name, price) 
[Modal class because it only has getter setters, no special function]

- Restaurant manager (vector<Restaurant>, CRUD ops, searchByLocation)
[Singleton Class because it should only has 1 instances. Because if multiple instances then every instance can have different set of restaurants]
- User (id, name, addr, Cart cart)
- Cart ()

## Relationship
- Restaurant has menu item (1..*)
- Menu item cannot exist without restaurant
- So, it's not association (basically both classes are independent), it's composition (one class owns another). [Filled Diamond icon]
- Restaurant can exist independently. But restaurants comes under restaurant manager. So, Aggregation (One class contains another class but doesn't fully own it like Team->Player). [Blank Diamond icon]
- User and Cart will have 1..1 relationship and Cart cannot exist independently without User. So, this is Composition.