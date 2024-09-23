#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Class Car
class Car {
private:
    string model;
    string brand;
    double basePrice;

    static int totalCars;

public:
    // Constructor for class Car
    Car(string brand = "", string model = "", double basePrice = 0.0) {
        this->brand = brand;
        this->model = model;
        this->basePrice = basePrice;
        totalCars++;
    }

    // Destructor to decrement totalCars when a car object is deleted
    ~Car() {
        totalCars--;
    }

    // Getter for rental price per hour
    double getRentalPricePerHour() const {
        return basePrice + 300.0;
    }

    // Getter for brand (marked as const)
    string getBrand() const {
        return brand;
    }

    // Getter for model (marked as const)
    string getModel() const {
        return model;
    }

    // Getter for base price
    double getBasePrice() const {
        return basePrice;
    }

    // Setter for brand
    void setBrand(const string& newBrand) {
        brand = newBrand;
    }

    // Setter for model
    void setModel(const string& newModel) {
        model = newModel;
    }

    // Setter for base price
    void setBasePrice(double newBasePrice) {
        basePrice = newBasePrice;
    }

    // Function to display car details
    void displayCarDetails() const {
        cout << "Brand: " << brand << "\nModel: " << model
             << "\nBase Price: ₹" << basePrice 
             << "\nRental Price per Hour: ₹" << getRentalPricePerHour() << endl;
    }

    // Static function to display the total number of cars
    static void displayTotalCars() {
        cout << "Total cars in the system: " << totalCars << endl;
    }
};

int Car::totalCars = 0;

// Class Customer
class Customer {
private:
    string name;
    int hours;

public:
    // Constructor for class Customer
    Customer(string name = "", int hours = 0) {
        this->name = name;
        this->hours = hours;
    }

    // Getter for name
    string getName() const {
        return name;
    }

    // Getter for rental hours
    int getHours() const {
        return hours;
    }

    // Setter for name
    void setName(const string& newName) {
        name = newName;
    }

    // Setter for hours
    void setHours(int newHours) {
        hours = newHours;
    }

    // Function to display the rental invoice
    void rentCar(const Car* car) const {
        cout << "Customer: " << name << " has rented " << car->getBrand() << " "
             << car->getModel() << " for " << hours << " hours." << endl;
        cout << "Total Rental Cost: ₹" << car->getRentalPricePerHour() * hours << endl;
    }
};

// Function to display all available cars
void displayAllCars(Car** cars, int numberOfCars) {
    cout << "Available cars:\n";
    for (int i = 0; i < numberOfCars; i++) {
        cout << i + 1 << ". ";
        cars[i]->displayCarDetails();
        cout << "----------------------" << endl;
    }
}

// Function to add a new car to the list
void addCar(Car**& cars, int& numberOfCars, int& capacity) {
    if (numberOfCars == capacity) {
        capacity *= 2;
        Car** temp = new Car*[capacity];
        for (int i = 0; i < numberOfCars; i++) {
            temp[i] = cars[i];
        }
        delete[] cars;
        cars = temp;
    }

    string brand, model;
    double price;
    cout << "Enter car brand: ";
    cin >> brand;
    cout << "Enter car model: ";
    cin >> model;
    cout << "Enter base price: ";
    cin >> price;

    cars[numberOfCars] = new Car(brand, model, price);
    numberOfCars++;
}

// Authentication function to identify admin
bool authenticateAdmin() {
    string adminPassword = "admin123"; 
    string inputPassword;

    cout << "Enter admin password to access admin features: ";
    cin >> inputPassword;

    if (inputPassword == adminPassword) {
        return true;
    } else {
        cout << "Incorrect password. Access denied." << endl;
        return false;
    }
}

int main() {
    int numberOfCars = 8;
    int capacity = 20;

    // Dynamically allocating memory for an array of Car objects
    Car** cars = new Car*[capacity];
    cars[0] = new Car("Tata", "Curvv EV", 1300);
    cars[1] = new Car("Maruti", "Fronx", 1300);
    cars[2] = new Car("Tata", "Punch", 1400);
    cars[3] = new Car("Citroen", "Basalt", 1400);
    cars[4] = new Car("Toyota", "Corolla", 1500);
    cars[5] = new Car("Honda", "Civic", 1600);
    cars[6] = new Car("Mahindra", "XUV 3XO", 1600);
    cars[7] = new Car("Ford", "Focus", 1700);

    Car::displayTotalCars();

    // Check for admin
    char isAdmin;
    cout << "Are you an admin? (y/n): ";
    cin >> isAdmin;

    if (isAdmin == 'y' || isAdmin == 'Y') {
        if (authenticateAdmin()) {
            char addMoreCars;
            cout << "Do you want to add more cars to the list? (y/n): ";
            cin >> addMoreCars;
            while (addMoreCars == 'y' || addMoreCars == 'Y') {
                addCar(cars, numberOfCars, capacity);
                cout << "Do you want to add another car? (y/n): ";
                cin >> addMoreCars;
            }
        }
    }

    // Displaying the available cars
    displayAllCars(cars, numberOfCars);

    // Display the updated total number of cars
    Car::displayTotalCars();

    // Object of Customer class
    Customer customer1;
    cin.ignore(); // To clear the input buffer after the previous input

    string customerName;
    cout << "\nEnter customer name: ";
    getline(cin, customerName);
    customer1.setName(customerName); 

    // User's option to choose the car
    int choice;
    cout << "\nChoose a car by entering the corresponding number: ";
    cin >> choice;

    if (choice < 1 || choice > numberOfCars) {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    int rentalHours;
    cout << "Enter number of rental hours: ";
    cin >> rentalHours;
    customer1.setHours(rentalHours); 

    // Invoice
    Car* chosenCar = cars[choice - 1];
    cout << "\nRental Information:\n";
    customer1.rentCar(chosenCar);

    // Freeing the dynamically allocated memory
    for (int i = 0; i < numberOfCars; i++) {
        delete cars[i];
    }
    delete[] cars;

    return 0;
}