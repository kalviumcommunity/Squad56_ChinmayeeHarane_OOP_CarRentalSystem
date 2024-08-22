#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
// #include <unistd.h>
// #include <ctime>
// #include <fstream>
#include <iomanip>

using namespace std;

// Class Car
class Car {
public:
    public:
    string model;
    string brand;
    double basePrice;

    static int totalCars;

    // constructer fir class Car
    Car(string brand = "", string model = "", double basePrice = 0.0){
        this->brand = brand;
        this->model = model;
        this->basePrice = basePrice;

        totalCars++;
    }

    // Decrement totalCars when a car object is deleted
    ~Car() {
        totalCars--; 
    }

    // Funtion to calculate rental price per hour
    double getRentalPricePerHour() {
        return this->basePrice + 300.0;
    }

    // Funtion to Display the details of the cars
    void displayCarDetails() {
        cout << "Brand: " << this->brand << "\nModel: " << this->model << "\nBase Price: ₹" << this->basePrice 
             << "\nRental Price per Hour: ₹" << this->getRentalPricePerHour() << endl;
    }

    // Static function to display the total number of cars
    static void displayTotalCars() {
        cout << "Total cars in the system: " << totalCars << endl;
    }
};

int Car::totalCars = 0;

// Class Customer
class Customer {
public:
    string name;
    int hours;

    // Funtion to Display invoice
    void rentCar(Car* car) {
        cout << "Customer: " << this->name << " has rented " << car->brand << " " << car->model 
             << " for " << this->hours << " hours." << endl;
        cout << "Total Rental Cost: ₹" << car->getRentalPricePerHour() * this->hours << endl;
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

// Function to add a new car in the list
void addCar(Car** &cars, int &numberOfCars, int &capacity) {
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


//authentication function to idenfiy admin
bool authenticateAdmin() {
    string adminPassword = "admin123"; // Set a simple password for demonstration
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
    cin.ignore(); 

    cout << "\nEnter customer name: ";
    getline(cin, customer1.name);

    // User's option to choose the car
    int choice;
    cout << "\nChoose a car by entering the corresponding number: ";
    cin >> choice;

    if (choice < 1 || choice > numberOfCars) {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }
    
    cout << "Enter number of rental hours: ";
    cin >> customer1.hours;

    // invoice
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