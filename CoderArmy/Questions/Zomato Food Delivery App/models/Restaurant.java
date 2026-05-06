import java.util.List; // For List interface
import java.util.UUID;
import java.util.ArrayList; // For ArrayList implementation

class Restaurant {
        private String id;
        private String name;
        private String address;
        private List<MenuItem> menuItems;

        public Restaurant(String name, String address) {
            this.menuItems = new ArrayList<>();
        }

        // Getters and setters
}