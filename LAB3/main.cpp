#include <iostream>
#include <string>

using namespace std;

struct rating {
    int r[3];
};
struct song {
    string songName;
    string artistName;
    rating rating;
};
struct Node {
    song data;
    Node* next;
    Node* prev;
};

Node* createSong(string songName, string artistName, int r1, int r2, int r3) {

    Node* newNode = new Node;

    newNode->data.songName = songName;
    newNode->data.artistName = artistName;
    newNode->data.rating.r[0] = r1;
    newNode->data.rating.r[1] = r2;
    newNode->data.rating.r[2] = r3;

    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}
Node* addSongtoList(Node* head, string songName, string artistName, int r1, int r2, int r3) {

    Node* newNode = createSong(songName, artistName, r1, r2, r3);

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }
    Node* tail = head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
    return head;
}
Node* nextSong(Node* current) {
    if (current == NULL)return NULL;
    return current->next;
}
Node* prevSong(Node* current) {
    if (current == NULL)return NULL;
    return current->prev;
}
Node* deleteCurrentSong(Node* head, Node*& current) {
    if (current == NULL)return NULL;
    if (current->next == current) {
        delete current;
        current = NULL;
        return NULL;
    }
    Node* nextNode = current->next;
    current->prev->next = current->next;
    current->next->prev = current->prev;

    if (current==head) {
        head = nextNode;
    }
    delete current;
    current = nextNode;

    return head;
}
void displaySong(Node* head,Node* current) {
    if (head == NULL) {
        cout << "Your list is empty.\n";
        return;
    }
    Node* temp = head;
    do {
        if (temp==current) {
            cout << "## ";
        }
        else {
            cout << "   ";
        }
        cout << temp->data.songName << " - " << temp->data.artistName << " | Ratings: ";
        for (int i = 0; i<3; i++) {
            cout << temp->data.rating.r[i];
            if (i<2)cout<<",";
        }
        cout << endl;
        temp=temp->next;

    }while (temp!=head);
}

int main() {
    Node* head = NULL;
    Node* current = NULL;

    string input;
    while (true) {
        displaySong(head,current);
        cout << "\nADD | NEXT | PREV | DELETE | EXIT\n";
        cin >> input;

        if (input=="ADD") {
            string songName;
            string artistName;
            int r1, r2, r3;
            cout << "Enter song name: ";
            cin >> songName;
            cout << "Enter artist name: ";
            cin >> artistName;
            cout << "Enter rating (3): ";
            cin >> r1 >>r2 >> r3;
            head = addSongtoList(head, songName ,artistName, r1, r2, r3);
            if (current==NULL) {
                current = head;
            }
        }
        else if (input=="NEXT") {
            current = nextSong(current);
        }
        else if (input=="PREV") {
            current = prevSong(current);
        }
        else if (input=="DELETE") {
            current = deleteCurrentSong(head,current);
        }
        else if (input=="EXIT") {
            break;
        }
    }

    return 0;
}