The main concept is whenever I make a new instance of a singleton class then it should always point to same instance.
This can happend when 'new ClassName()' is not possible. So, we have to make constructor private.

# Best ways to implement
## java - 
### Enum Singleton [Can be used if your class doesn't require or extend any base class because singleton class extens Enum class only]
enum EnumSingleton {
        INSTANCE;

        public void func()
        {

        }
}

### Bill Pugh implementation
class Singleton {
        //private constructor
        private Singleton() {}

        private static class Holder {
                private static final Singleton INSTANCE = new Singleton();
        }

        public getInstance() {
                return Holder.INSTANCE;
        }
}

### Double checked locking
class Singleton {

    private static volatile Singleton instance;

    private Singleton() {}

    public static Singleton getInstance() {
        if (instance == null) {
            synchronized (Singleton.class) {
                if (instance == null) {
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
}