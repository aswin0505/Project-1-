#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_USERS 100
#define MAX_SEATS 50

typedef struct {
    int seatNumber;
    int isBooked;
} Seat;

typedef struct {
    char busNumber[20];
    char destination[50];
    Seat seats[MAX_SEATS];
    int totalSeats;
} Bus;

typedef struct {
    char username[20];
    char password[20];
} User;

Bus buses[MAX_BUSES];
User users[MAX_USERS];
int busCount = 0;
int userCount = 0;

void addBus(char *busNumber, char *destination, int totalSeats) {
    strcpy(buses[busCount].busNumber, busNumber);
    strcpy(buses[busCount].destination, destination);
    buses[busCount].totalSeats = totalSeats;
    for (int i = 0; i < totalSeats; i++) {
        buses[busCount].seats[i].seatNumber = i + 1;
        buses[busCount].seats[i].isBooked = 0;
    }
    busCount++;
}

int authenticateUser(char *username, char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void bookTicket(char *busNumber, int seatNumber) {
    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            if (buses[i].seats[seatNumber - 1].isBooked == 0) {
                buses[i].seats[seatNumber - 1].isBooked = 1;
                printf("Ticket booked successfully for seat %d on bus %s.\n", seatNumber, busNumber);
            } else {
                printf("Seat %d is already booked.\n", seatNumber);
            }
            return;
        }
    }
    printf("Bus not found.\n");
}

void cancelTicket(char *busNumber, int seatNumber) {
    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            if (buses[i].seats[seatNumber - 1].isBooked == 1) {
                buses[i].seats[seatNumber - 1].isBooked = 0;
                printf("Ticket cancelled successfully for seat %d on bus %s.\n", seatNumber, busNumber);
            } else {
                printf("Seat %d is not booked.\n", seatNumber);
            }
            return;
        }
    }
    printf("Bus not found.\n");
}

void checkBusStatus(char *busNumber) {
    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            printf("Bus Number: %s, Destination: %s\n", buses[i].busNumber, buses[i].destination);
            for (int j = 0; j < buses[i].totalSeats; j++) {
                printf("Seat %d: %s\n", buses[i].seats[j].seatNumber, buses[i].seats[j].isBooked ? "Booked" : "Available");
            }
            return;
        }
    }
    printf("Bus not found.\n");
}

void menu() {
    printf("1. Add Bus\n");
    printf("2. Book Ticket\n");
    printf("3. Cancel Ticket\n");
    printf("4. Check Bus Status\n");
    printf("5. Exit\n");
}

int main() {
    int choice;
    char busNumber[20], destination[50], username[20], password[20];
    int totalSeats, seatNumber;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Bus Number: ");
                scanf("%s", busNumber);
                printf("Enter Destination: ");
                scanf("%s", destination);
                printf("Enter Total Seats: ");
                scanf("%d", &totalSeats);
                addBus(busNumber, destination, totalSeats);
                break;
            case 2:
                printf("Enter Bus Number: ");
                scanf("%s", busNumber);
                printf("Enter Seat Number: ");
                scanf("%d", &seatNumber);
                bookTicket(busNumber, seatNumber);
                break;
            case 3:
                printf("Enter Bus Number: ");
                scanf("%s", busNumber);
                printf("Enter Seat Number: ");
                scanf("%d", &seatNumber);
                cancelTicket(busNumber, seatNumber);
                break;
            case 4:
                printf("Enter Bus Number: ");
                scanf("%s", busNumber);
                checkBusStatus(busNumber);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
