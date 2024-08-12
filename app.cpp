#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

// Class Car
class Car {
public:
    public:
    string model;
    string brand;
    double basePrice;

    // constructer fir class Car
    Car(string brand, string model, double basePrice){
        this->brand = brand;
        this->model = model;
        this->basePrice = basePrice;
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
};

// Class Customer
class Customer {
public:
    string name;
    int hours;

    // Funtion to Display invoice
    void rentCar(Car car) {
        cout << "Customer: " << this->name << " has rented " << car.brand << " " << car.model 
             << " for " << this->hours << " hours." << endl;
        cout << "Total Rental Cost: ₹" << car.getRentalPricePerHour() * this->hours << endl;
    }
};

void displayAllCars(Car cars[], int numberOfCars) {
    cout << "Available cars:\n";
    for (int i = 0; i < numberOfCars; i++) {
        cout << i + 1 << ". ";
        cars[i].displayCarDetails();
        cout << "----------------------" << endl;
    }
}

int main() {

    // Array of objects
    Car cars[] = {
        Car("Tata", "Curvv EV", 1300),
        Car("Maruti", "Fronx", 1300),
        Car("Tata", "Punch", 1400),
        Car("Citroen", "Basalt", 1400),
        Car("Toyota", "Corolla", 1500),
        Car("Honda", "Civic", 1600),
        Car("Mahindra", "XUV 3XO", 1600),
        Car("Ford", "Focus", 1700)
    };
    
    int numberOfCars = sizeof(cars) / sizeof(cars[0]);

    // Displaying the available cars
    displayAllCars(cars, numberOfCars);

    // User's option to choose the car
    int choice;
    cout << "\nChoose a car by entering the corresponding number: ";
    cin >> choice;

    if (choice < 1 || choice > numberOfCars) {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    // Object of Customer class
    Customer customer1;
    cin.ignore(); 

    cout << "\nEnter customer name: ";
    getline(cin, customer1.name);
    
    cout << "Enter number of rental hours: ";
    cin >> customer1.hours;

    // invoice
    Car chosenCar = cars[choice - 1];
    cout << "\nRental Information:\n";
    customer1.rentCar(chosenCar);

  return 0;
}