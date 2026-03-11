#include <iostream>
#include <string>

using namespace std;

bool isEmpty = true;

struct Node {
    string data;
    Node *next;
};

Node* addNode(Node* head, string word){

    Node* newNode = new Node;
    newNode->data = word;
    newNode->next = NULL;

    if(head == NULL){

        return newNode;

    }

    Node* temp = head;

    while(temp->next != NULL){

        temp = temp->next;

    }

    temp->next = newNode;
    return head;
}

Node* deleteNode(Node* head) {

    if (head == NULL) {

        isEmpty = true;
        return NULL;
    }
    if (head->next == NULL) {

        delete head;
        isEmpty = true;
        return NULL;
    }

    Node* temp = head;
    while(temp->next->next != NULL) {

        temp = temp->next;
    }
    delete temp->next;
    temp->next = NULL;
    return head;
}

void displayNode(Node* head) {

    Node* temp = head;
    while (temp != nullptr) {
        cout << "[" << temp->data << "]";
        if (temp->next != NULL) {
            cout << "->";
        }
        temp = temp->next;
    }
    cout << endl;
}

int main() {

    Node* head = NULL;
    string input;
    while(true) {

        cout<<"\nDISPLAY -> Check out the list.\nUNDO -> Delete the last list object.\nEXIT -> Exit the program.";
        cout<<"\nEnter word to add to the list: ";
        cin>>input;

        if(input == "EXIT") {

            exit(0);
        }
        if (input == "UNDO") {

            if (isEmpty == true) {
                cout<<"\nThe list is empty.";

            }
            else if (isEmpty == false) {
                head =  deleteNode(head);

            }

        }
        else if (input == "DISPLAY") {

            displayNode(head);
        }
        else {

            head = addNode(head,input);
            isEmpty = false;
        }


    }
    return 0;

}