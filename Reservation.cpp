#include <iostream>
#include<string>
#include<stdio.h>
#include<conio.h>
using namespace std;

class MBus;

class User {
public:
    string name, route, email, address;
    int phone, busNo, seatNo, userId;
    User* next;

    User(string n, string r, string e, string a, int p, int bN, int sN, int uI) {
        name = n;
        route = r;
        email = e;
        address = a;
        phone = p;
        busNo = bN;
        seatNo = sN;
        userId = uI;
        next = NULL;
    }

    // USER INFORMATION
    void UserInfo() {
        cout << "Name: " << name << endl;
        cout << "Route: " << route << endl;
        cout << "Email: " << email << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        cout << "Bus Number: " << busNo << endl;
        cout << "Seat Number: " << seatNo << endl;
    }

    // REGISTER USER
    static void registration(User* &head, string n, string r, string e, string a, int p, int bN, int sN, int uI) {
        static int userIdcounter = 0;

        User* temp = new User(n, r, e, a, p, bN, sN, uI);
        temp->userId = ++userIdcounter;
        temp->next = head;
        head = temp;

        //cout << "User ID is: " << temp->userId << endl;
    }

    // DISPLAY ALL USER
    static void displayAll(User* head) {
        User* temp = head;
        while (temp != NULL) {
            cout << "User Information: " << endl;
            temp->UserInfo();
            temp = temp->next;
        }
        cout << endl;
    }

    // UPDATE USER
    static void update(User* head, const string& email) {
        User* temp = head;
        while (temp != NULL) {
            if (temp->email == email) {
                cout << "\nEnter updated information for user with email " << email << ":" << endl;
                cout << "Name: ";
                cin >> temp->name;
                cout << "Route: ";
                cin >> temp->route;
                cout << "Email: ";
                cin >> temp->email;
                cout << "Address: ";
                cin >> temp->address;
                cout << "Phone: ";
                cin >> temp->phone;
                cout << "Bus Number: ";
                cin >> temp->busNo;
                cout << "Seat Number: ";
                cin >> temp->seatNo;
                cout << "\nUser information updated successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\n\tUser with email " << email << " not found." << endl;
    }

    // DELETE USER
    static void deleteUser(User* &head, const string& email) {
        User* temp = head;
        User* prev = NULL;

        while (temp != NULL) {
            if (temp->email == email) {
                if (prev == NULL) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                cout << "\n\tUser with email " << email << " deleted successfully." << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "\n\tUser with email " << email << " not found." << endl;
    }
};


class Driver {
public:
    string name;
    string busNumber;
    string address;
    string cnic;
    string driverId;
    Driver* next;

    Driver(const string& n, const string& bus, const string& addr, const string& id, const string& c) :
        name(n), busNumber(bus), address(addr), driverId(id), cnic(c), next(NULL) {}
     
    static void insertDriver(Driver* &driverHead, const string& name, const string& bus, const string& address, const string& driverId, const string& cnic) {
        Driver* newDriver = new Driver(name, bus, address, driverId, cnic);

        if (!driverHead) {
            newDriver->next = newDriver;
            driverHead = newDriver;
        } else {
            Driver* temp = driverHead;
            while (temp->next != driverHead) {
                temp = temp->next;
            }
            temp->next = newDriver;
            newDriver->next = driverHead;
        }
        cout<<"\nDriver added successfully";
    }  
    
    static void displayDrivers(Driver* driverHead) {
        if (!driverHead) {
            cout << " Driver Circular linked list is empty." << endl;
            return;
        }

        Driver* current = driverHead;
        do {
            cout << endl;
            cout << " \n\t----------------------------------------------------" << endl;
            cout << " \tDriver Information:" << endl;
            cout << " \t----------------------------------------------------" << endl;
            cout << endl;
            cout << " Name: " << current->name << endl;
            cout << " Bus Number: " << current->busNumber << endl;
            cout << " Address: " << current->address << endl;
            cout << " CNIC: " << current->cnic << endl;
            cout << " Driver ID: " << current->driverId << endl;

            current = current->next;
        } while (current != driverHead);
    } 
    
    static void updateDriver(Driver* &driverHead, const string& driverId, const string& newName, const string& newBus, const string& newAddress, const string& newCnic) {
        if (!driverHead) {
            cout << "Driver list is empty." << endl;
            return;
        }

        Driver* current = driverHead;
        do {
            if (current->driverId == driverId) {
                current->name = newName;
                current->busNumber = newBus;
                current->address = newAddress;
                current->cnic = newCnic;
                cout << "Driver information updated successfully." << endl;
                return;
            }
            current = current->next;
        } while (current != driverHead);

        cout << "Driver with ID " << driverId << " not found." << endl;
    }

    static void deleteDriver(Driver* &driverHead, const string& driverId) {
        if (!driverHead) {
            cout << "Driver list is empty." << endl;
            return;
        }

        Driver* current = driverHead;
        Driver* prev = NULL;

        do {
            if (current->driverId == driverId) {
                if (prev) {
                    prev->next = current->next;
                    delete current;
                } else {
                    // If the driver to be deleted is the head
                    if (driverHead->next == driverHead) {
                        // Only one driver in the list
                        delete driverHead;
                        driverHead = NULL;
                    } else {
                        Driver* temp = driverHead;
                        while (temp->next != driverHead) {
                            temp = temp->next;
                        }
                        temp->next = driverHead->next;
                        delete driverHead;
                        driverHead = temp->next;
                    }
                }
                cout << "Driver with ID " << driverId << " deleted successfully." << endl;
                return;
            }

            prev = current;
            current = current->next;

        } while (current != driverHead);

        cout << "Driver with ID " << driverId << " not found." << endl;
    }
     static void updateOrDeleteDriver(Driver* &driverHead) {
       
            cout << "Enter 'U' to update or 'D' to delete a Driver: ";
            char driverAction;
            cin >> driverAction;

            if (driverAction == 'U' || driverAction == 'u') {
                // Update driver
                string driverId, newName, newBus, newAddress, newCnic;
                cout << "Enter Driver ID to update: ";
                cin >> driverId;
                cout << "Enter new name: ";
                getline(cin, newName);
                cout << "Enter new bus number: ";
                getline(cin, newBus);
                cout << "Enter new address: ";
                getline(cin, newAddress);
                cout << "Enter new CNIC: ";
                getline(cin, newCnic);
                updateDriver(driverHead, driverId, newName, newBus, newAddress, newCnic);
            } else if (driverAction == 'D' || driverAction == 'd') {
                // Delete driver
                string driverId;
                cout << "Enter Driver ID to delete: ";
                cin >> driverId;
                deleteDriver(driverHead, driverId);
            } else {
                cout << "Invalid choice for Driver. Exiting." << endl;
            }
    }
};


class Bus {
public:
    string busNumber;
    int busSeats;
    string busDriver;
    string route;
    string arrivalTime;
    string departureTime;
    int passengers;
    int payment;
    Bus* next;

    Bus(const string& number, int seats, const string& driver, string route, const string& arrival, const string& departure, int passngr, int pay) :
        busNumber(number), busSeats(seats), busDriver(driver), route(route), arrivalTime(arrival), departureTime(departure), passengers(passngr), payment(pay), next(NULL) {}

    static void insertBus(Bus* &busHead, const string& number, int seats, const string& driver, string route, const string& arrival, const string& departure, int passngr, int pay) {
        Bus* newBus = new Bus(number, seats, driver, route, arrival, departure, passngr, pay);

        if (!busHead) {
            newBus->next = newBus;
            busHead = newBus;
        } else {
            Bus* temp = busHead;
            while (temp->next != busHead) {
                temp = temp->next;
            }
            temp->next = newBus;
            newBus->next = busHead;
        }
    }

    static void displayBuses(Bus* busHead) {
        if (!busHead) {
            cout << " Bus Circular linked list is empty." << endl;
            return;
        }

        Bus* current = busHead;
        do {
            cout << " ----------------------------------------------------" << endl;
            cout << " Bus Information:" << endl;
            cout << " ----------------------------------------------------" << endl;
            cout << endl;

            cout << " Bus Number: " << current->busNumber << endl;
            cout << " Bus Seats: " << current->busSeats << endl;
            cout << " Bus Driver: " << current->busDriver << endl;
            cout << " Route Number: " << current->route << endl;
            cout << " Arrival Time: " << current->arrivalTime << endl;
            cout << " Departure Time: " << current->departureTime << endl;
            cout << " passengers: " << current->passengers << endl;
            cout << " payment: " << current->payment << endl;
            cout << " Total bus's Bill: " << (current->payment * current->passengers) << endl;

            current = current->next;
        } while (current != busHead);
    }

    static void updateBus(Bus* &busHead, const string& busNumber, int newSeats, const string& newDriver, const string& newRoute,
                   const string& newArrival, const string& newDeparture, int newPassengers, int newPayment) {
        if (!busHead) {
            cout << "Bus list is empty." << endl;
            return;
        }

        Bus* current = busHead;
        do {
            if (current->busNumber == busNumber) {
                current->busSeats = newSeats;
                current->busDriver = newDriver;
                current->route = newRoute;
                current->arrivalTime = newArrival;
                current->departureTime = newDeparture;
                current->passengers = newPassengers;
                current->payment = newPayment;
                cout << "Bus information updated successfully." << endl;
                return;
            }
            current = current->next;
        } while (current != busHead);

        cout << "Bus with Number " << busNumber << " not found." << endl;
    }

    static void deleteBus(Bus* &busHead, const string& busNumber) {
        if (!busHead) {
            cout << "Bus list is empty." << endl;
            return;
        }

        Bus* current = busHead;
        Bus* prev = NULL;

        do {
            if (current->busNumber == busNumber) {
                if (prev) {
                    prev->next = current->next;
                    delete current;
                } else {
                    // If the bus to be deleted is the head
                    if (busHead->next == busHead) {
                        // Only one bus in the list
                        delete busHead;
                        busHead = NULL;
                    } else {
                        Bus* temp = busHead;
                        while (temp->next != busHead) {
                            temp = temp->next;
                        }
                        temp->next = busHead->next;
                        delete busHead;
                        busHead = temp->next;
                    }
                }
                cout << "Bus with Number " << busNumber << " deleted successfully." << endl;
                return;
            }

            prev = current;
            current = current->next;

        } while (current != busHead);

        cout << "Bus with Number " << busNumber << " not found." << endl;
    }

    static void updateOrDeleteBus(Bus* &busHead) {
        cout << "Enter 'U' to update or 'D' to delete a Bus: ";
        char busAction;
        cin >> busAction;

        if (busAction == 'U' || busAction == 'u') {
            string busNumber;
            cout << "Enter Bus Number to update: ";
            cin >> busNumber;
            int newSeats, newPassengers, newPayment;
            string newDriver, newRoute, newArrival, newDeparture;
            
            cout << "Enter new number of seats: ";
            cin >> newSeats;
            cout << "Enter new bus driver: ";
            cin >> newDriver;
            cout << "Enter new route: ";
            cin >> newRoute;
            cout << "Enter new arrival time: ";
            cin >> newArrival;
            cout << "Enter new departure time: ";
            cin >> newDeparture;
            cout << "Enter new total passengers: ";
            cin >> newPassengers;
            cout << "Enter new payment per seat: ";
            cin >> newPayment;
            
            updateBus(busHead, busNumber, newSeats, newDriver, newRoute, newArrival, newDeparture, newPassengers, newPayment);
        } else if (busAction == 'D' || busAction == 'd') {
            string busNumber;
            cout << "Enter Bus Number to delete: ";
            cin >> busNumber;
            deleteBus(busHead, busNumber);
        } else {
            cout << "Invalid choice for Bus. Exiting." << endl;
        }
    } 
};


class Seat{
	public:
    int seatNumber;
    Seat* next;

    Seat(int number) : seatNumber(number), next(NULL) {}

    // Create (Reserve) operation
    static void reserveSeat(Seat* &seatHead, int seatNumber) {
        if (isSeatValid(seatNumber) && !isSeatReserved(seatHead, seatNumber)) {
            Seat* newNode = new Seat(seatNumber);
            newNode->next = seatHead;
            seatHead = newNode;

            cout << "Seat " << seatNumber << " reserved successfully." << endl;
        } else {
            cout << "Invalid seat number or seat is already reserved." << endl;
        }
    }

    // Read (Display) operation
    static void displaySeats(Seat* &seatHead) {
        cout << "Reserved Seats: ";
        Seat* current = seatHead;
        while (current != NULL) {
            cout << current->seatNumber << " ";
            current = current->next;
        }
        cout << endl;
    }

static void updateSeat(Seat* &seatHead, int oldSeatNumber, int newSeatNumber) {
        cancelSeat(seatHead, oldSeatNumber);
        reserveSeat(seatHead, newSeatNumber);
    }
    
    // Delete (Cancel) operation
    static void cancelSeat(Seat* &seatHead, int seatNumber) {
        if (isSeatValid(seatNumber) && isSeatReserved(seatHead, seatNumber)) {
            Seat* current = seatHead;
            Seat* prev = NULL;

            while (current->seatNumber != seatNumber) {
                prev = current;
                current = current->next;
            }

            if (prev != NULL) {
                prev->next = current->next;
            } else {
                seatHead = current->next;
            }

            delete current;
            cout << "Seat " << seatNumber << " cancelled successfully." << endl;
        } else {
            cout << "Invalid seat number or seat is not reserved." << endl;
        }
    }

private:
    static bool isSeatValid(int seatNumber) {
        return seatNumber > 0;
    }

    static bool isSeatReserved(Seat* seatHead, int seatNumber) {
        Seat* current = seatHead;
        while (current != NULL) {
            if (current->seatNumber == seatNumber) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

class Route{
	public:
 int id;
    string routeName;
    Route* next;

    Route(int _id, const string& _routeName, Route* _next) : id(_id), routeName(_routeName), next(_next) {}

    // Function to insert a route at the end of the list
    static void insertRoute(Route* &routeHead, int id, const string& routeName) {
        Route* newNode = new Route(id, routeName, NULL);
        if (!routeHead) {
            routeHead = newNode;
        } else {
            Route* current = routeHead;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        cout << "Route added successfully." << endl;
    }

    // Function to display all routes in the list
    static void displayRoutes(Route* routeHead) {
        if (!routeHead) {
            cout << "No routes added yet." << endl;
        } else {
            Route* current = routeHead;
            cout << "Routes in the list:" << endl;
            while (current) {
                cout << "ID: " << current->id << ", Name: " << current->routeName << endl;
                current = current->next;
            }
        }
    }

    // Function to update a route
    static void updateRoute(Route* routeHead, int id, const string& newRouteName) {
        Route* current = routeHead;
        while (current && current->id != id) {
            current = current->next;
        }

        if (current) {
            current->routeName = newRouteName;
            cout << "Route updated successfully." << endl;
        } else {
            cout << "Route not found." << endl;
        }
    }

    // Function to delete a route at an arbitrary position
    static void deleteRoute(Route* &routeHead, int id) {
        if (!routeHead) {
            cout << "No routes to delete." << endl;
        } else {
            Route* current = routeHead;
            Route* prev = NULL;

            // Search for the node to delete
            while (current && current->id != id) {
                prev = current;
                current = current->next;
            }

            // If the node is found, delete it
            if (current) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    routeHead = current->next;
                }
                delete current;
                cout << "Route deleted successfully." << endl;
            } else {
                cout << "Route not found." << endl;
            }
        }
    }
};

class Reservation{

public:
    string personName;
    int busId;
    string time;
    Reservation* next;

    Reservation(const string& name, int id, const string& t)
        : personName(name), busId(id), time(t), next(NULL) {}

    static void insertAtEnd(Reservation* &reserveHead, const string& name, int id, const string& time) {
        Reservation* newNode = new Reservation(name, id, time);
        if (!reserveHead) {
            reserveHead = newNode;
        } else {
            Reservation* temp = reserveHead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Reservation added successfully.\n";
    }

    static void displayList(Reservation* &reserveHead) {
        const Reservation* temp = reserveHead;
        if (!temp) {
            cout << "No reservations added yet.\n";
        } else {
            cout << "Reservations:\n";
            while (temp) {
                cout << "Name: " << temp->personName << ", Bus ID: " << temp->busId << ", Time: " << temp->time << "\n";
                temp = temp->next;
            }
        }
    }

    static void deleteReservation(Reservation* &reserveHead, const string& name) {
        if (!reserveHead) {
            cout << "No reservation to delete.\n";
            return;
        }

        Reservation* current = reserveHead;
        Reservation* previous = NULL;

        while (current && current->personName != name) {
            previous = current;
            current = current->next;
        }

        if (!current) {
            cout << "No reservation found with the given name.\n";
            return;
        }

        if (!previous) {
            // If the first node is the one to be deleted
            reserveHead = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Reservation deleted successfully.\n";
    }

    static void updateReservation(Reservation* &reserveHead, const string& name, int newBusId, const string& newTime) {
        Reservation* current = reserveHead;
        while (current && current->personName != name) {
            current = current->next;
        }

        if (current) {
            current->busId = newBusId;
            current->time = newTime;
            cout << "Reservation updated successfully.\n";
        } else {
            cout << "Reservation not found.\n";
        }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MBus {
public:
    void menu() {
        User* head = NULL;
        Bus* busHead = NULL;
        Driver* driverHead = NULL;
        Seat* seatHead= NULL;
        Route* routeHead= NULL;
        Reservation* reserveHead= NULL;
        
        string updateEmail, deleteEmail;
    p:
        system("cls"); // to clear screen
        int choice;

		cout<<"\n"<<endl;
		cout<<"\t%%      %% %%%%%%% %%      %%%%%% %%%%%% %%%%  %%%% %%%%%%%"<<endl;
		cout<<"\t%%      %% %%      %%      %%     %%  %% %%  %%  %% %%"<<endl;
		cout<<"\t%%  %%  %% %%%%    %%      %%     %%  %% %%  %%  %% %%%%"<<endl;
		cout<<"\t%%  %%  %% %%      %%      %%     %%  %% %%      %% %%"<<endl;
		cout<<"\t%%%%%%%%%% %%%%%%% %%%%%%% %%%%%% %%%%%% %%      %% %%%%%%%"<<endl;
		cout<<"\n";
		cout<<"\t                      $$$$$$$$$   $$$$$$                  "<<endl;
		cout<<"\t                          $$      $$  $$"<<endl;
		cout<<"\t                          $$      $$  $$"<<endl;
		cout<<"\t                          $$      $$  $$"<<endl;
		cout<<"\t                          $$      $$$$$$"<<endl;
		cout<<"\n";
		cout<<"\t      ####################[DSA PROJECT]#################"<<endl;
    	cout<<"\n\t                             ON";
    	cout<<"\n\t     ===================================================="<<endl;
    	cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    	cout<<"\n\t                             BY:            "<<endl;
    	cout<<"\n\t                    WAFI, JAWERIYA, MARIA           "<<endl;
    	cout<<"\n\t                    RAHAT, SABAHAT, ESHA           "<<endl;
    	cout<<"\t            ======================================"<<endl;
    	cout<<"\t                              ^";
        cout << "\n\t                        ::MAIN MENU::" << endl;
        cout << "\n\t[1]. Admin Dasboard" << endl;
        cout << "\n\t[2]. User Registration" << endl;
        cout << "\n\t[3]. Route Management" << endl;
        cout << "\n\t[4]. Bus Information" << endl;
        cout << "\n\t[5]. Driver Information" << endl;
        cout << "\n\t[6]. Reservation" << endl;
        cout << "\n\t[7]. Seat cancellation" << endl;
        cout << "\n\t[8]. Exit" << endl;
        cout << "\n\tSelet your choice(1-8):";
        cin >> choice;

        switch (choice) {
        case 1:
             Admin_menu(head, busHead, driverHead, routeHead);
            break;
        case 2:
            User_menu(head);
            break;
        case 3:
             Route_menu(routeHead);
            break;
        case 4:
             Bus_menu(busHead);
            break;
        case 5:
             Driver_menu(driverHead);
            break;
        case 6:
            Reservation_menu(reserveHead);
            break;
        case 7:
             Seat_menu(seatHead);
            break;
        case 8:
            exit(0);
            break;
        default:
            cout << "\n\nInvalid Choice.......................Please Try Again";
        }
        getch();
       goto p;
    }

    void User_menu(User* &head) {
        string updateEmail, deleteEmail;
        string name, route, email, address;
            int phone, busNo, seatNo, userId;
    p:
        system("cls"); // to clear screen
        int choice;

        cout << "\n"
             << endl;
        cout << "\t                     BUS RESERVATION SYSTEM              " << endl;
        cout << "\t                              ^";
        cout << "\n\t                        ::User Registration::" << endl;
        cout << "\n\t[1]. Create Profile" << endl;
        cout << "\n\t[2]. Update Profile" << endl;
        cout << "\n\t[3]. Delete Profile" << endl;
        cout <<"\n\t[4]. View Profile"<<endl;
        cout << "\n\t[5]. Back to main menu" << endl;
        cout << "\n\tSelet your choice(1-5):";
        cin >> choice;

        switch (choice) {
        case 1:
            char registerAnother;
            do {
                cout << "Enter your information:" << endl;

                cout << "name : ";
                cin >> name;
                cout << "route: ";
                cin >> route;
                cout << "Email: ";
                cin >> email;
                cout << "Address: ";
                cin >> address;
                cout << "Phone: ";
                cin >> phone;
                cout << "Bus Number: ";
                cin >> busNo;
                cout << "Seat Number: ";
                cin >> seatNo;
                User::registration(head, name, route, email, address, phone, busNo, seatNo, userId);
                cout << "User registered successfully." << endl;
                cout << "Do you want to register another user? (y/n): ";
                cin >> registerAnother;
            } while (registerAnother == 'y' || registerAnother == 'Y');
            break;
        case 2:
            cout << "Enter the email of the user you want to update: ";
            cin >> updateEmail;
            User::update(head, updateEmail);
            break;
        case 3:
            cout << "Enter the email of the user you want to delete: ";
            cin >> deleteEmail;
            User::deleteUser(head, deleteEmail);
            break;
        case 4:
            User::displayAll(head);
            break;
            
        case 5:
            menu();
            break;
        default:
            cout << "\n\nInvalid Choice.......................Please Try Again";
        }
        getch();
        goto p;
    }
    
    	void Admin_menu(User* &head, Bus* &busHead, Driver* &driverHead, Route* &routeHead){
    		string updateEmail, deleteEmail;
        string name, route, email, address;
            int phone, busNo, seatNo, userId;
            string busNumber, busDriver, arrivalTime, departureTime;
                int busSeats, passengers, payment;
                string bus, driverId, cnic;
                	int id;
        
        string newName;
	p:
	system("cls");                                //to clear screen
	int choice;

	cout<<"\n"<<endl;
    cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    cout<<"\t                              ^";
	cout<<"\n\t                        ::Admin Dashboard::"<<endl;
	cout<<"\n\t[1]. add User"<<endl;
	cout<<"\n\t[2]. add Bus"<<endl;
	cout<<"\n\t[3]. Add driver"<<endl;
	cout<<"\n\t[4]. add route"<<endl;
	cout<<"\n\t[5]. View all users"<<endl;
	cout<<"\n\t[6]. view all buses"<<endl;
	cout<<"\n\t[7]. view all drivers"<<endl;
	cout<<"\n\t[8]. view all route"<<endl;
	cout<<"\n\t[9]. Back to main menu"<<endl;
	cout<<"\n\tSelet your choice(1-9):";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		       char registerAnother;
            do {
                cout << "Enter your information:" << endl;

                cout << "name : ";
                cin >> name;
                cout << "route: ";
                cin >> route;
                cout << "Email: ";
                cin >> email;
                cout << "Address: ";
                cin >> address;
                cout << "Phone: ";
                cin >> phone;
                cout << "Bus Number: ";
                cin >> busNo;
                cout << "Seat Number: ";
                cin >> seatNo;
                User::registration(head, name, route, email, address, phone, busNo, seatNo, userId);
                cout << "User registered successfully." << endl;
                cout << "Do you want to register another user? (y/n): ";
                cin >> registerAnother;
            } while (registerAnother == 'y' || registerAnother == 'Y');
            break;
		case 2:
		       cout << "Enter Bus information:\n";
                cout << "Enter bus number: ";
                cin >> busNumber;
                cout << "Enter bus seats: ";
                cin >> busSeats;
                cout << "Enter bus driver: ";
                cin >> busDriver;
                cout << "Enter route: ";
                cin >> route;
                cout << "Enter arrival time: ";
                cin >> arrivalTime;
                cout << "Enter departure time: ";
                cin >> departureTime;
                cout << "Enter total passengers in bus: ";
                cin >> passengers;
                cout << "Enter payment per seat: ";
                cin >> payment;

                Bus::insertBus(busHead, busNumber, busSeats, busDriver, route, arrivalTime, departureTime, passengers, payment);
		       break;
		case 3: 
		      cout << "Enter Driver information:\n";
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter bus number: ";
                cin >> bus;
                cout << "Enter address: ";
                cin >> address;
                cout << "Enter driver ID: ";
                cin >> driverId;
                cout << "Enter CNIC: ";
                cin >> cnic;

                Driver::insertDriver(driverHead, name, bus, address, driverId, cnic);
	       	   break;
		case 4:
			  cout << "Enter route ID: ";
                cin >> id;
                cout << "Enter route name: ";
                cin >> name;
                Route::insertRoute(routeHead, id, name);
		      break;
		case 5:
		     User::displayAll(head);
		      break;
		case 6:
		        Bus::displayBuses(busHead);
		       break;
		case 7: 
		        Driver::displayDrivers(driverHead);
	       	   break;
		case 8:
			  Route::displayRoutes(routeHead);
		      break;
		case 9:
		      menu();
		      break;	
		default:
			cout<<"\n\nInvalid Choice.......................Please Try Again";
	}
	getch();
	goto p;
	}
	
		void Bus_menu(Bus* &busHead){
		string busNumber, busDriver, arrivalTime, departureTime, route;
                int busSeats, passengers, payment;
				p:
	system("cls");                                //to clear screen
	int choice;

	cout<<"\n"<<endl;
    cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    cout<<"\t                              ^";
	cout<<"\n\t                        ::Bus Information::"<<endl;
	cout<<"\n\t[1]. Add Bus Information"<<endl;
	cout<<"\n\t[2]. Update"<<endl;
	cout<<"\n\t[3]. Delete"<<endl;
	cout<<"\n\t[4]. Display Bus Information"<<endl;
	cout<<"\n\t[5]. Back to main menu"<<endl;
	cout<<"\n\tSelet your choice(1-5):";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
                cout << "Enter Bus information:\n";
                cout << "Enter bus number: ";
                cin >> busNumber;
                cout << "Enter bus seats: ";
                cin >> busSeats;
                cout << "Enter bus driver: ";
                cin >> busDriver;
                cout << "Enter route: ";
                cin >> route;
                cout << "Enter arrival time: ";
                cin >> arrivalTime;
                cout << "Enter departure time: ";
                cin >> departureTime;
                cout << "Enter total passengers in bus: ";
                cin >> passengers;
                cout << "Enter payment per seat: ";
                cin >> payment;

                Bus::insertBus(busHead, busNumber, busSeats, busDriver, route, arrivalTime, departureTime, passengers, payment);
                break;
    
		case 2:
		       Bus::updateOrDeleteBus(busHead);
		       break;
		case 3: 
		      Bus::updateOrDeleteBus(busHead);
	       	   break;
		case 4:
			  Bus::displayBuses(busHead);
		      break;
		case 5:
		      menu();
		      break;	
		default:
			cout<<"\n\nInvalid Choice.......................Please Try Again";
	}
	getch();
	goto p;
	}
	
	
	void Driver_menu(Driver* &driverHead){
		 string name, bus, address, driverId, cnic;
				p:
	system("cls");                                //to clear screen
	int choice;

	cout<<"\n"<<endl;
    cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    cout<<"\t                              ^";
	cout<<"\n\t                        ::Driver Information::"<<endl;
	cout<<"\n\t[1]. Add Driver Information"<<endl;
	cout<<"\n\t[2]. Update"<<endl;
	cout<<"\n\t[3]. Delete"<<endl;
	cout<<"\n\t[4]. Display Driver Information"<<endl;
	cout<<"\n\t[5]. Back to main menu"<<endl;
	cout<<"\n\tSelet your choice(1-5):";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		       cout << "Enter Driver information:\n";
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter bus number: ";
                cin >> bus;
                cout << "Enter address: ";
                cin >> address;
                cout << "Enter driver ID: ";
                cin >> driverId;
                cout << "Enter CNIC: ";
                cin >> cnic;

                Driver::insertDriver(driverHead, name, bus, address, driverId, cnic);
		       break;
		case 2:
		       Driver::updateOrDeleteDriver(driverHead);
		       break;
		case 3: 
		      Driver::updateOrDeleteDriver(driverHead);
	       	   break;
		case 4:
			  Driver::displayDrivers(driverHead);
		      break;
		case 5:
		      menu();
		      break;	
		default:
			cout<<"\n\nInvalid Choice.......................Please Try Again";
	}
	getch();
goto p;
	}
	
		void Seat_menu(Seat* &seatHead){
			int seatNumber,newSeatNumber;
				p:
	system("cls");                                //to clear screen
	int choice;

	cout<<"\n"<<endl;
    cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    cout<<"\t                              ^";
	cout<<"\n\t                        ::Seat Cancellation::"<<endl;
	cout<<"\n\t[1]. Reserve Seat"<<endl;
	cout<<"\n\t[2]. Update"<<endl;
	cout<<"\n\t[3]. Cancel Reservation"<<endl;
	cout<<"\n\t[4]. Display all Reservations"<<endl;
	cout<<"\n\t[5]. Back to main menu"<<endl;
	cout<<"\n\tSelet your choice(1-5):";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		       cout << "Enter the seat number to reserve: ";
                cin >> seatNumber;
                Seat::reserveSeat(seatHead, seatNumber);
		       break;
		case 2:
		        cout << "Enter the old seat number to update: ";
                cin >> seatNumber;
                cout << "Enter the new seat number: ";
                cin >> newSeatNumber;
                Seat::updateSeat(seatHead, seatNumber, newSeatNumber);
		       break;
		case 3: 
		      cout << "Enter the seat number to cancel: ";
                cin >> seatNumber;
                Seat::cancelSeat(seatHead, seatNumber);
	       	   break;
		case 4:
			  
                Seat::displaySeats(seatHead);
                break;
		      break;
		case 5:
		      menu();
		      break;	
		default:
			cout<<"\n\nInvalid Choice.......................Please Try Again";
	}
	getch();
	goto p;
	}
	
	void Route_menu(Route* &routeHead){
		int id;
        string name;
        string newName;
				p:
	system("cls");                                //to clear screen
	int choice;

	cout<<"\n"<<endl;
    cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    cout<<"\t                              ^";
	cout<<"\n\t                        ::Route Management::"<<endl;
	cout<<"\n\t[1]. Create Route"<<endl;
	cout<<"\n\t[2]. Update Route"<<endl;
	cout<<"\n\t[3]. Delete Route"<<endl;
	cout<<"\n\t[4]. View Route"<<endl;
	cout<<"\n\t[5]. Back to main menu"<<endl;
	cout<<"\n\tSelet your choice(1-5):";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
                cout << "Enter route ID: ";
                cin >> id;
                cout << "Enter route name: ";
                cin >> name;
                Route::insertRoute(routeHead, id, name);
		       break;
		case 2:
		       cout << "Enter route ID to update: ";
                cin >> id;
                cout << "Enter new route name: ";
                cin >> newName;
                Route::updateRoute(routeHead, id, newName);
		       break;
		case 3: 
                cout << "Enter route ID to delete: ";
                cin >> id;
                Route::deleteRoute(routeHead, id);
                break;
	       	   break;
		case 4:
			  Route::displayRoutes(routeHead);
		      break;
		case 5:
		      menu();
		      break;	
		default:
			cout<<"\n\nInvalid Choice.......................Please Try Again";
	}
	getch();
	goto p;
	}
	
	
	void Reservation_menu(Reservation* &reserveHead){
		string name, time, newtime;
   		int id;
				p:
	system("cls");                                //to clear screen
	int choice;

	cout<<"\n"<<endl;
    cout<<"\t                     BUS RESERVATION SYSTEM              "<<endl;
    cout<<"\t                              ^";
	cout<<"\n\t                        ::Reservation::"<<endl;
	cout<<"\n\t[1]. Create"<<endl;
	cout<<"\n\t[2]. Update"<<endl;
	cout<<"\n\t[3]. Delete"<<endl;
	cout<<"\n\t[4]. View"<<endl;
	cout<<"\n\t[5]. Back to main menu"<<endl;
	cout<<"\n\tSelet your choice(1-5):";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
    	cout << "Enter person name: ";
        cin >> name;
        cout << "Enter bus ID: ";
        cin >> id;
        cout << "Enter time: ";
        cin >> time;

        Reservation::insertAtEnd(reserveHead, name, id, time);
        break;
		case 2:
    cout << "Enter person name to update reservation: ";
    cin >> name;
    cout << "Enter new bus ID: ";
    cin >> id;
    cout << "Enter new time: ";
    cin >> newtime;

    Reservation::updateReservation(reserveHead, name, id, newtime);
		       break;
		case 3: 
		     
    cout << "Enter person name to delete reservation: ";
    cin >> name;
   Reservation::deleteReservation(reserveHead, name);
	       	   break;
		case 4:
	 Reservation::displayList(reserveHead);
		      break;
		case 5:
		      menu();
		      break;	
		default:
			cout<<"\n\nInvalid Choice.......................Please Try Again";
	}
	getch();
	goto p;
	}
};


int main() {
    MBus mb;
    mb.menu();
    return 0;
}

