#include "song.h"


// Default constructor for SongClass
SongClass::SongClass() {
    songTitle = "NULL";
    artistName = "NULL";
    songDuration = 0;
    next = NULL;
}

// Constructor for SongClass
SongClass::SongClass(int time, std::string title, std::string name) {
    songDuration = time;
    songTitle = title;
    artistName = name;
    next = NULL;
}

// Node class constructor
Node::Node(SongClass s) {
    song = s;
    next = NULL;
    prev = NULL;
}

// Playlist class constructor
Playlist::Playlist() {
    head = NULL;
    archiveHead = NULL;
    current = NULL;
}

// Destructor to free memory
Playlist::~Playlist() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Add a song to the end of the playlist
void Playlist::songAdd(int time, std::string title, std::string name) {
    SongClass newSong(time, title, name);
    Node* newNode = new Node(newSong);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp; //Link to previous node
    }

    songHashTable[title] = newNode;
}

// Add a song before another specified song in the playlist
void Playlist::songAddBefore(int time, std::string title, std::string name) {
    if (head == nullptr) {
        std::cout << "Playlist is empty. Adding song to head." << std::endl;
        songAdd(time, title, name);
        return;
    }

    std::string targetSong;
    std::cout << "Enter the target song title: ";
    std::cin.ignore();
    std::getline(std::cin, targetSong);

    SongClass newSong(time, title, name);
    Node* newNode = new Node(newSong);

    if (head->song.getTitle() == targetSong) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;

    while (current != NULL && current->song.getTitle() != targetSong) {
        current = current->next;
    }

    if (current == NULL) {
        std::cout << "Song: " << targetSong << " not found in the playlist." << std::endl;
        delete newNode;
        return;
    }

    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev != NULL) {
        current->prev->next = newNode;
    }
    else {
        head = newNode;
    }
    current->prev = newNode;

    songHashTable[title] = newNode;
}

// Remove a song and archive it
void Playlist::removeNArchive(std::string title) {
    if (head == NULL) {
        std::cout << "The playlist is empty." << std::endl;
        return;
    }

    Node* current = head;

    while (current != NULL && current->song.getTitle() != title) {
        current = current->next;
    }

    if (current == NULL) {
        std::cout << "Song: '" << title << "' not found in the playlist" << std::endl;
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    else {
        head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    songHashTable.erase(title);

    // Archive logic
    Node* archiveCurrent = archiveHead;
    Node* archivePrevious = NULL;

    while (archiveCurrent != NULL && archiveCurrent->song.getTitle() < current->song.getTitle()) {
        archivePrevious = archiveCurrent;
        archiveCurrent = archiveCurrent->next;
    }

    if (archivePrevious == NULL) {
        current->next = archiveHead;
        archiveHead = current;
    }
    else {
        archivePrevious->next = current;
        current->next = archiveCurrent;
    }

    std::cout << "Song: '" << title << "' has been removed and archived." << std::endl;
}

// Play a song by title
void Playlist::playSong(std::string title) {
    if (head == NULL) {
        std::cout << "The playlist is empty." << std::endl;
        return;
    }

    Node* current = head;

    while (current != NULL) {
        if (current->song.getTitle() == title) {
            std::cout << "Now playing: '" << current->song.getTitle() << "' by " << current->song.getArtist() << std::endl;
            return;
        }
        current = current->next;
    }

    std::cout << "Song: '" << title << "' was not found in the playlist." << std::endl;
}

// Display the playlist
void Playlist::displayPlaylist() {
    if (head == NULL) {
        std::cout << "The playlist is empty." << std::endl;
        return;
    }

    Node* current = head;
    int number = 1;

    std::cout << " " << std::endl;
    std::cout << "Playlist:" << std::endl;
    while (current != NULL) {
        std::cout << number << ". " << current->song.getTitle() << " - " << current->song.getArtist() << " (" << current->song.getDuration() << " seconds)" << std::endl;
        number++;
        current = current->next;
    }
}

// Display the archive
void Playlist::displayArchive() {
    if (archiveHead == NULL) {
        std::cout << "No archived songs." << std::endl;
        return;
    }

    Node* current = archiveHead;
    int number = 1;

    std::cout << " " << std::endl;
    std::cout << "Archived Songs:" << std::endl;

    while (current != NULL) {
        std::cout << number << ". " << current->song.getTitle() << " - " << current->song.getArtist() << " (" << current->song.getDuration() << " seconds)" << std::endl;
        number++;
        current = current->next;
    }
}

// Search for a song by title
void Playlist::songSearch(std::string title) {
        auto it = songHashTable.find(title);
        if (it != songHashTable.end()) {
            Node* foundSong = it->second;
            std::cout << "Song found: '" << foundSong->song.getTitle()
                << "' by " << foundSong->song.getArtist()
                << " (" << foundSong->song.getDuration() << " seconds)" << std::endl;
        }
        else {
            std::cout << "No song with title: '" << title << "' was found in the playlist." << std::endl;
        }

}

void Playlist::nextSong() {
    if (current == nullptr) {
        current = head;
    }
    else if (current->next != nullptr) {
        current = current->next;
    }
    else {
        std::cout << "You are at the end of the playlist." << std::endl;
        return;
    }

    std::cout << "Now playing: '" << current->song.getTitle()
        << "' by " << current->song.getArtist() << std::endl;
}

void Playlist::prevSong() {
    if (current == nullptr) {
        current = head;
        std::cout << " You are at the beginning of the playlist." << std::endl;
        return;
    }
    else if (current->prev != nullptr) {
        current = current->prev;
    }
    else {
        std::cout << " You are at the beginning of the playlist." << std::endl;
        return;
    }

    std::cout << "Now playing: '" << current->song.getTitle()
        << "' by " << current->song.getArtist() << std::endl;
}

void Playlist::requestSong(std::string title) {
    auto it = songHashTable.find(title);
    if (it != songHashTable.end()) {
        Node* requestedSong = it->second;
        requestQueue.push(requestedSong);
        std::cout << "Song: '" << requestedSong->song.getTitle()
            << "' has been added to the request queue." << std::endl;
    }
    else {
        std::cout << "Song: '" << title << "' not found in the playlist." << std::endl;
    }
}

void Playlist::playRequestSongs() {
    if (requestQueue.empty()) {
        std::cout << "No songs in the request queue." << std::endl;
        return;
    }

    while (!requestQueue.empty()) {
        Node* song = requestQueue.front();
        std::cout << "Now playing requested song: '" << song->song.getTitle()
            << "' by " << song->song.getArtist()
            << " (" << song->song.getDuration() << " seconds)" << std::endl;
        requestQueue.pop();
    }

    std::cout << "Finished playing requested songs. Resuming playlist." << std::endl;
}
