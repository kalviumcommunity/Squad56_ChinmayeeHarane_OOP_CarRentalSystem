#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Vehicle {
protected:
    string model;
    string brand;
    double basePrice;

public:
    Vehicle(string brand = "", string model = "", double basePrice = 0.0) 
        : brand(brand), model(model), basePrice(basePrice) {}

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    double getBasePrice() const { return basePrice; }

    virtual double getRentalPricePerHour() const = 0;
};

// Class Car
class Car: public Vehicle  {
private:
    static int totalCars;

public:
    // Constructor for class Car
    Car(string brand = "", string model = "", double basePrice = 0.0) : Vehicle(brand, model, basePrice) {
        totalCars++;
    }

    // Destructor to decrement totalCars when a car object is deleted
    ~Car() {
        totalCars--;
    }

    // Getter for rental price per hour
    double getRentalPricePerHour() const override{
        return basePrice + 300.0;
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

class RentalVehicle : public Car {
public:
    RentalVehicle(string brand = "", string model = "", double basePrice = 0.0) 
        : Car(brand, model, basePrice) {}

    double calculateRentalCost(int hours) const {
        return getRentalPricePerHour() * hours;
    }
};

// Class Customer
class Customer {
private:
    string name;
    int hours;

public:
    // Constructor for class Customer
    Customer(string name = "", int hours = 0) : name(name), hours(hours) {}

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
};

// class Invoice {
// public:
//     // Function to display the rental invoice
//     void rentCar(const Vehicle* car) const {
//         cout << "Customer: " << name << " has rented " << car->getBrand() << " "
//              << car->getModel() << " for " << hours << " hours." << endl;
//         cout << "Total Rental Cost: ₹" << car->getRentalPricePerHour() * hours << endl;
//     }

//     void rentCar(const string& brand, const string& model) const {
//         cout << "Customer: " << name << " has rented a " << brand << " "
//              << model << " for " << hours << " hours." << endl;
//     }
// };

class Invoice {
public:
    void generateInvoice(const Customer& customer, const Vehicle* car) const {
        cout << "Customer: " << customer.getName() << " has rented " 
             << car->getBrand() << " " << car->getModel() 
             << " for " << customer.getHours() << " hours." << endl;
        cout << "Total Rental Cost: ₹" << car->getRentalPricePerHour() * customer.getHours() << endl;
    }
};

// Function to display all available cars
void displayAllCars(RentalVehicle** cars, int numberOfCars) {
    cout << "Available cars:\n";
    for (int i = 0; i < numberOfCars; i++) {
        cout << i + 1 << ". ";
        cars[i]->displayCarDetails();
        cout << "----------------------" << endl;
    }
}

// Function to add a new car to the list
void addCar(RentalVehicle**& cars, int& numberOfCars, int& capacity) {
    if (numberOfCars == capacity) {
        capacity *= 2;
        RentalVehicle** temp = new RentalVehicle*[capacity];
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

    cars[numberOfCars] = new RentalVehicle(brand, model, price);
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
    RentalVehicle** cars = new RentalVehicle*[capacity];
    cars[0] = new RentalVehicle("Tata", "Curvv EV", 1300);
    cars[1] = new RentalVehicle("Maruti", "Fronx", 1300);
    cars[2] = new RentalVehicle("Tata", "Punch", 1400);
    cars[3] = new RentalVehicle("Citroen", "Basalt", 1400);
    cars[4] = new RentalVehicle("Toyota", "Corolla", 1500);
    cars[5] = new RentalVehicle("Honda", "Civic", 1600);
    cars[6] = new RentalVehicle("Mahindra", "XUV 3XO", 1600);
    cars[7] = new RentalVehicle("Ford", "Focus", 1700);

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
    cin.ignore(); 

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
    Invoice invoice;
    RentalVehicle* chosenCar = cars[choice - 1];
    cout << "\nRental Information:\n";
    invoice.generateInvoice(customer1 ,chosenCar);

    // Freeing the dynamically allocated memory
    for (int i = 0; i < numberOfCars; i++) {
        delete cars[i];
    }
    delete[] cars;

    return 0;
}
