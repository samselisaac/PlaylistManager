/*Homework: Program 3 - Playlist Manager Second Interpretation
* Author : Isaac Samsel
* Date : 12/4/2024
*
*Description :
	* This program is a simulated playlist manager. With a second round of implemenations.
	* It allows the user to manage the software like a playlist within a music app.
	* Allowing songs to be added, inserted before songs, removed and archived, the playlist and archive to be displayed, etc.
	* Usage :
	* To run the program, the user is prompted to make a choice on what they would like to do.
	* Follow the prompts to edit and manage the playlist however the user would like according to the given prompts.*/

#include <iostream>
#include "song.h"


int main(void) {
	Playlist myPlaylist;
	std::string title, artist;
	int choice = 0;
	int duration = 0;

	do {
		std::cout << " " << std::endl;
		std::cout << "Playlist Manager" << std::endl;
		std::cout << "1. Add a song" << std::endl;
		std::cout << "2. Insert a song before another" << std::endl;
		std::cout << "3. Remove a song and archive it" << std::endl;
		std::cout << "4. Display the playlist" << std::endl;
		std::cout << "5. Request a song to be played" << std::endl; //New addition
		std::cout << "6. Play requested songs" << std::endl; //New addition
		std::cout << "7. Play a song" << std::endl;
		std::cout << "8. Search for a song" << std::endl;	//New addition
		std::cout << "9. Move to next song" << std::endl; //New addition
		std::cout << "10. Move to previous song" << std::endl; //New addition
		std::cout << "0. Exit" << std::endl;
		std::cout << "Choose an option or exit: ";
		std::cin >> choice;
		std::cout << " " << std::endl;


		switch (choice) {
		case 1:
			std::cout << "Enter a song title: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			std::cout << "Enter artist name: ";
			std::getline(std::cin, artist);
			std::cout << "Enter song duration (in seconds): ";
			std::cin >> duration;
			myPlaylist.songAdd(duration, title, artist);
			std::cout << " " << std::endl;
			std::cout << "Song added to playlist." << std::endl;
			break;

		case 2:
			std::cout << "Enter new song title: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			std::cout << "Enter artist name: ";
			std::getline(std::cin, artist);
			std::cout << "Enter song duration (in seconds): ";
			std::cin >> duration;
			myPlaylist.songAddBefore(duration, title, artist);
			std::cout << " " << std::endl;
			std::cout << "Song added to playlist." << std::endl;
			break;

		case 3:
			std::cout << "Enter the title of a song to remove and archive: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			myPlaylist.removeNArchive(title);
			break;

		case 4:
			myPlaylist.displayPlaylist();
			break;

		case 5:
			std::cout << "Enter the title of the song to request: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			myPlaylist.requestSong(title);
			break;

		case 6:
			myPlaylist.playRequestSongs();
			break;

		case 7:
			std::cout << "Enter a song title to play: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			myPlaylist.playSong(title);
			break;

		case 8:
			std::cout << "Enter a song title to search for: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			myPlaylist.songSearch(title);
			break;

		case 9:
			std::cout << "Move to the next song:";
			std::cin.ignore();
			myPlaylist.nextSong();
			break;

		case 10:
			std::cout << "Move to the previous song:";
			std::cin.ignore();
			myPlaylist.prevSong();
			break;

		case 0:
			std::cout << " " << std::endl;
			std::cout << "Exiting the program." << std::endl;
			break;

		default:
			std::cout << " " << std::endl;
			std::cout << "Invalid choice. Please try again." << std::endl;
			break;
		}

	} while (choice != 0);

	return 0;
}

