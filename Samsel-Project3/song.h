#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <queue>

class SongClass {
private:
    std::string songTitle;
    std::string artistName;
    int songDuration;

public:
    // Constructors
    SongClass();
    SongClass(int time, std::string title, std::string name);

    // Getters and Setters
    std::string getTitle() const { return songTitle; }
    std::string getArtist() const { return artistName; }
    int getDuration() const { return songDuration; }

    void setTitle(const std::string& title) { songTitle = title; }
    void setArtist(const std::string& artist) { artistName = artist; }
    void setDuration(int duration) { songDuration = duration; }

    // Pointer to the next song
    SongClass* next;
};

class Node {
public:
    SongClass song;
    Node* next;
    Node* prev;

    // Constructor
    Node(SongClass s);
};

class Playlist {
private:
    Node* head;
    Node* archiveHead;
    Node* current;
    std::unordered_map<std::string, Node*> songHashTable;
    std::queue<Node*> requestQueue;

public:
    Playlist();
    ~Playlist();

    // Methods for managing the playlist
    void songAdd(int time, std::string title, std::string name);
    void songAddBefore(int time, std::string title, std::string name);
    void removeNArchive(std::string title);
    void playSong(std::string title);
    void requestSong(std::string title);
    void playRequestSongs();
    void displayPlaylist();
    void displayArchive();
    void songSearch(std::string title); //Search in hash table
    void nextSong();
    void prevSong();
};


