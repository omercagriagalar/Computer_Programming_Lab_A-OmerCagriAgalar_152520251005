#include <iostream>
#include <string>
using namespace std;

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3];
};

struct PNode {
    Package data;
    PNode* next;
};

PNode* topPackage = NULL;

void pushPackage(string id, string city, int l, int w, int h) {

    PNode* newNode = new PNode;

    newNode->data.packageID = id;
    newNode->data.destinationCity = city;

    newNode->data.dimensions[0] = l;
    newNode->data.dimensions[1] = w;
    newNode->data.dimensions[2] = h;

    newNode->next = topPackage;
    topPackage = newNode;
}

bool popPackage(Package &p) {

    if (topPackage == NULL) return false;

    PNode* temp = topPackage;
    p = temp->data;

    topPackage = topPackage->next;
    delete temp;

    return true;
}

void displayPackages() {

    if (topPackage == NULL) {
        cout << "There is no package to display\n";
        return;
    }

    PNode* temp = topPackage;

    cout << "\n= = = = = PACKAGES = = = = =\n";

    while (temp != NULL) {

        cout << temp->data.packageID << " | "
             << temp->data.destinationCity << " | ";

        for (int i = 0; i < 3; i++) {
            cout << temp->data.dimensions[i];
            if (i < 2) cout << ",";
        }

        cout << endl;
        temp = temp->next;
    }
}

#define SIZE 5

struct Courier {
    string courierName;
    string vehicleType;
};

Courier queueArr[SIZE];

int front = -1;
int rear = -1;

bool isFull() {
    return (front == (rear + 1) % SIZE);
}

bool isEmpty() {
    return (front == -1);
}

void enqueueCourier(string name, string vehicle) {

    if (isFull()) {
        cout << "Queue is FULL\n";
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    }
    else {
        rear = (rear + 1) % SIZE;
    }

    queueArr[rear].courierName = name;
    queueArr[rear].vehicleType = vehicle;
}

bool dequeueCourier(Courier &c) {

    if (isEmpty()) return false;

    c = queueArr[front];

    if (front == rear) {
        front = rear = -1;
    }
    else {
        front = (front + 1) % SIZE;
    }

    return true;
}

void displayCouriers() {

    if (isEmpty()) {
        cout << "\nThere is no couriers\n";
        return;
    }

    cout << "\n= = = = = COURIERS = = = = =\n";

    int i = front;

    while (true) {

        cout << queueArr[i].courierName << " | "
             << queueArr[i].vehicleType << endl;

        if (i == rear) break;

        i = (i + 1) % SIZE;
    }
}

void dispatch() {

    Package p;
    Courier c;

    if (!popPackage(p)) {
        cout << "No package to dispatch\n";
        return;
    }

    if (!dequeueCourier(c)) {
        cout << "No courier available\n";
        pushPackage(p.packageID, p.destinationCity,
                    p.dimensions[0], p.dimensions[1], p.dimensions[2]);
        return;
    }

    cout << "\nDISPATCHED:\n";
    cout << c.courierName << " (" << c.vehicleType << ") -> "
         << p.packageID << " to " << p.destinationCity << endl;
}

int main() {

    string cmd;

    while (true) {

        displayPackages();
        displayCouriers();

        cout << "\nCommands:\nPUSH (Add a new package to the top of the stack.)\nENQUEUE (Add a new courier to the end of the circular queue.)\nDISPATCH (the first courier in the queue takes the top package from the stack.)\nEXIT(Show all packages in the stack and all couriers waiting in the queue.)\n";
        cout << "Enter your command: ";
        cin >> cmd;

        if (cmd == "PUSH") {

            string id, city;
            int l, w, h;

            cout << "Package ID (Only NUMBERS): ";
            cin >> id;

            cout << "City: ";
            cin >> city;

            cout << "Dimensions (Lenght, Width, Height, enter this 3 option in order): ";
            cin >> l >> w >> h;

            pushPackage(id, city, l, w, h);
        }

        else if (cmd == "ENQUEUE") {

            string name, vehicle;

            cout << "Courier Name: ";
            cin >> name;

            cout << "Vehicle: ";
            cin >> vehicle;

            enqueueCourier(name, vehicle);
        }

        else if (cmd == "DISPATCH") {
            dispatch();
        }

        else if (cmd == "EXIT") {
            break;
        }
    }

    return 0;
}