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
    Car(string b, string m, double price) : brand(b), model(m), basePrice(price) {}

    // Funtion to calculate rental price per hour
    double getRentalPricePerHour() {
        return basePrice + 300.0;
    }

    // Funtion to Display the details of the cars
    void displayCarDetails() {
        cout << "Brand: " << brand << "\nModel: " << model << "\nBase Price: ₹" << basePrice 
             << "\nRental Price per Hour: ₹" << getRentalPricePerHour() << endl;
    }
};

// Class Customer
class Customer {
public:
    string name;
    int hours;

    // Funtion to Display invoice
    void rentCar(Car car) {
        cout << "Customer: " << name << " has rented " << car.brand << " " << car.model 
             << " for " << hours << " hours." << endl;
        cout << "Total Rental Cost: ₹" << car.getRentalPricePerHour() * hours << endl;
    }
};

int main() {

    // Multiple objects of Car class
    Car cars[] = {
        Car("Toyota", "Corolla", 1500),
        Car("Honda", "Civic", 1600),
        Car("Ford", "Focus", 1700),
        Car("Citroen", "Basalt", 1400),
        Car("Tata", "Curvv EV", 1300),
        Car("Mahindra", "XUV 3XO", 1600),
        Car("Maruti", "Fronx", 1300),
        Car("Tata", "Punch", 1400)
    };
    
    int numberOfCars = sizeof(cars) / sizeof(cars[0]);

    // Displaying the available cars
    cout << "Available cars:\n";
    for (int i = 0; i < numberOfCars; i++) {
        cout << i + 1 << ". ";
        cars[i].displayCarDetails();
        cout << "----------------------" << endl;
    }

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