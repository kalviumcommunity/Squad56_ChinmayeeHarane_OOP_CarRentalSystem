#include <iostream>
#include <string>
#include <iomanip>

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

class Car: public Vehicle {
private:
    static int totalCars;

public:
    Car(string brand = "", string model = "", double basePrice = 0.0) : Vehicle(brand, model, basePrice) {
        totalCars++;
    }

    ~Car() {
        totalCars--;
    }

    double getRentalPricePerHour() const override{
        return basePrice + 300.0;
    }

    void displayCarDetails() const {
        cout << "Car Brand: " << brand << "\nModel: " << model
             << "\nBase Price: ₹" << basePrice 
             << "\nRental Price per Hour: ₹" << getRentalPricePerHour() << endl;
    }

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

class Bike : public Vehicle {
public:
    Bike(string brand = "", string model = "", double basePrice = 0.0) 
        : Vehicle(brand, model, basePrice) {}

    double getRentalPricePerHour() const override {
        return basePrice + 150.0;
    }

    void displayBikeDetails() const {
        cout << "Bike Brand: " << brand << "\nModel: " << model
             << "\nBase Price: ₹" << basePrice 
             << "\nRental Price per Hour: ₹" << getRentalPricePerHour() << endl;
    }
};

class Customer {
private:
    string name;
    int hours;

public:
    Customer(string name = "", int hours = 0) : name(name), hours(hours) {}

    string getName() const {
        return name;
    }

    int getHours() const {
        return hours;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setHours(int newHours) {
        hours = newHours;
    }
};

class Invoice {
public:
    void generateInvoice(const Customer& customer, const Vehicle* vehicle) const {
        cout << "Customer: " << customer.getName() << " has rented " 
             << vehicle->getBrand() << " " << vehicle->getModel() 
             << " for " << customer.getHours() << " hours." << endl;
        cout << "Total Rental Cost: ₹" << vehicle->getRentalPricePerHour() * customer.getHours() << endl;
    }
};

void displayAllCars(RentalVehicle** cars, int numberOfCars) {
    cout << "Available cars:\n";
    for (int i = 0; i < numberOfCars; i++) {
        cout << i + 1 << ". ";
        cars[i]->displayCarDetails();
        cout << "----------------------" << endl;
    }
}

void displayAllBikes(Bike** bikes, int numberOfBikes) {
    cout << "Available bikes:\n";
    for (int i = 0; i < numberOfBikes; i++) {
        cout << i + 1 << ". ";
        bikes[i]->displayBikeDetails();
        cout << "----------------------" << endl;
    }
}

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

void addBike(Bike**& bikes, int& numberOfBikes, int& capacity) {
    if (numberOfBikes == capacity) {
        capacity *= 2;
        Bike** temp = new Bike*[capacity];
        for (int i = 0; i < numberOfBikes; i++) {
            temp[i] = bikes[i];
        }
        delete[] bikes;
        bikes = temp;
    }

    string brand, model;
    double price;
    cout << "Enter bike brand: ";
    cin >> brand;
    cout << "Enter bike model: ";
    cin >> model;
    cout << "Enter base price: ";
    cin >> price;

    bikes[numberOfBikes] = new Bike(brand, model, price);
    numberOfBikes++;
}

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

    int numberOfBikes = 0;
    int bikeCapacity = 5;
    Bike** bikes = new Bike*[bikeCapacity];

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

            char addMoreBikes;
            cout << "Do you want to add bikes to the list? (y/n): ";
            cin >> addMoreBikes;
            while (addMoreBikes == 'y' || addMoreBikes == 'Y') {
                addBike(bikes, numberOfBikes, bikeCapacity);
                cout << "Do you want to add another bike? (y/n): ";
                cin >> addMoreBikes;
            }
        }
    }

    displayAllCars(cars, numberOfCars);
    displayAllBikes(bikes, numberOfBikes);

    Car::displayTotalCars();

    Customer customer1;
    cin.ignore();

    string customerName;
    cout << "\nEnter customer name: ";
    getline(cin, customerName);
    customer1.setName(customerName);

    int vehicleTypeChoice;
    cout << "\nChoose vehicle type:\n1. Car\n2. Bike\n";
    cin >> vehicleTypeChoice;

    int choice;
    if (vehicleTypeChoice == 1) {
        cout << "\nChoose a car by entering the corresponding number: ";
        cin >> choice;
        if (choice < 1 || choice > numberOfCars) {
            cout << "Invalid choice. Exiting program." << endl;
            return 1;
        }
    } else if (vehicleTypeChoice == 2) {
        cout << "\nChoose a bike by entering the corresponding number: ";
        cin >> choice;
        if (choice < 1 || choice > numberOfBikes) {
            cout << "Invalid choice. Exiting program." << endl;
            return 1;
        }
    }

    int rentalHours;
    cout << "Enter the number of hours for rental: ";
    cin >> rentalHours;
    customer1.setHours(rentalHours);

    Invoice invoice;
    if (vehicleTypeChoice == 1) {
        invoice.generateInvoice(customer1, cars[choice - 1]);
    } else if (vehicleTypeChoice == 2) {
        invoice.generateInvoice(customer1, bikes[choice - 1]);
    }

    // Clean up memory
    for (int i = 0; i < numberOfCars; i++) {
        delete cars[i];
    }
    delete[] cars;

    for (int i = 0; i < numberOfBikes; i++) {
        delete bikes[i];
    }
    delete[] bikes;

    return 0;
}
