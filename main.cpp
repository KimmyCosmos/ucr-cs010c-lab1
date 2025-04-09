#include <iostream>
#include <string>
#include "Playlist.h"

void PrintMenu(const std::string& title) {
    std::cout << title << " PLAYLIST MENU" << std::endl;
    std::cout << "a - Add song" << std::endl;
    std::cout << "d - Remove song" << std::endl;
    std::cout << "c - Change position of song" << std::endl;
    std::cout << "s - Output songs by specific artist" << std::endl;
    std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
    std::cout << "o - Output full playlist" << std::endl;
    std::cout << "q - Quit" << std::endl;
    std::cout << "\nChoose an option:" << std::endl;
}

int main() {
    std::string playlistTitle;

    std::cout << "Enter playlist's title:" << std::endl;
    std::getline(std::cin, playlistTitle);
    std::cout << std::endl;

    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr;

    char choice;

    do {
        PrintMenu(playlistTitle);
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {

            case 'a': {
                std::string id, name, artist;
                int length;

                std::cout << "ADD SONG" << std::endl;

                std::cout << "Enter song's unique ID:" << std::endl;
                std::getline(std::cin, id);

                std::cout << "Enter song's name:" << std::endl;
                std::getline(std::cin, name);

                std::cout << "Enter artist's name:" << std::endl;
                std::getline(std::cin, artist);

                std::cout << "Enter song's length (in seconds):" << std::endl;
                std::cin >> length;
                std::cin.ignore();

                PlaylistNode* newNode = new PlaylistNode(id, name, artist, length);

                if (head == nullptr) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->SetNext(newNode);
                    tail = newNode;
                }

                std::cout << std::endl;
                break;
            }

            case 'd': {
                std::string idToDelete;
                std::cout << "REMOVE SONG" << std::endl;
                std::cout << "Enter song's unique ID:" << std::endl;
                std::getline(std::cin, idToDelete);

                PlaylistNode* current = head;
                PlaylistNode* previous = nullptr;

                while (current != nullptr && current->GetID() != idToDelete) {
                    previous = current;
                    current = current->GetNext();
                }

                if (current == nullptr) {
                    std::cout << "Song with ID " << idToDelete << " not found." << std::endl;
                } else {
                    if (previous == nullptr) {
                        head = current->GetNext();
                    } else {
                        previous->SetNext(current->GetNext());
                    }

                    if (current == tail) {
                        tail = previous;
                    }

                    std::cout << "\"" << current->GetSongName() << "\" removed" << std::endl;
                    delete current;
                }

                std::cout << std::endl;
                break;
            }

            case 'o': {
                std::cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << std::endl;

                if (head == nullptr) {
                    std::cout << "Playlist is empty" << std::endl;
                } else {
                    int position = 1;
                    PlaylistNode* current = head;

                    while (current != nullptr) {
                        std::cout << position << "." << std::endl;
                        current->PrintPlaylistNode();
                        std::cout << std::endl;

                        current = current->GetNext();
                        ++position;
                    }
                }

                break;
            }

            case 't': {
                std::cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << std::endl;
            
                int totalTime = 0;
                PlaylistNode* current = head;
            
                while (current != nullptr) {
                    totalTime += current->GetSongLength();
                    current = current->GetNext();
                }
            
                std::cout << "Total time: " << totalTime << " seconds" << std::endl;
                std::cout << std::endl;
                break;
            }

            case 's': {
                std::string artistName;
                std::cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << std::endl;
                std::cout << "Enter artist's name:" << std::endl;
                std::getline(std::cin, artistName);
            
                PlaylistNode* current = head;
                int position = 1;
                while (current != nullptr) {
                    if (current->GetArtistName() == artistName) {
                        std::cout << position << "." << std::endl;
                        current->PrintPlaylistNode();
                        std::cout << std::endl;
                    }
                    current = current->GetNext();
                    ++position;
                }
            
                break;
            }
            
            case 'c': {
                std::cout << "CHANGE POSITION OF SONG" << std::endl;
            
                int oldPos, newPos;
                std::cout << "Enter song's current position:" << std::endl;
                std::cin >> oldPos;
                std::cout << "Enter new position for song:" << std::endl;
                std::cin >> newPos;
                std::cin.ignore();
            
                if (head == nullptr || head->GetNext() == nullptr || oldPos == newPos) {
                    break;
                }
            
                // Finding and removing the node at oldPos
                PlaylistNode* current = head;
                PlaylistNode* previous = nullptr;
                int position = 1;
            
                while (current != nullptr && position < oldPos) {
                    previous = current;
                    current = current->GetNext();
                    ++position;
                }
            
                if (current == nullptr) {
                    break; // Invalid position
                }
            
                // Removing node from current position
                if (previous == nullptr) {
                    head = current->GetNext();
                } else {
                    previous->SetNext(current->GetNext());
                }
            
                if (current == tail) {
                    tail = previous;
                }
            
                current->SetNext(nullptr); // 🔥 prevent dangling pointer
            
                // Reinserting at newPos
                PlaylistNode* insertPrev = nullptr;
                PlaylistNode* insertCurr = head;
                int insertPos = 1;
            
                if (newPos <= 1 || head == nullptr) {
                    current->SetNext(head);
                    head = current;
                    if (tail == nullptr) {
                        tail = current;
                    }
                } else {
                    while (insertCurr != nullptr && insertPos < newPos) {
                        insertPrev = insertCurr;
                        insertCurr = insertCurr->GetNext();
                        ++insertPos;
                    }
            
                    if (insertPrev != nullptr) {
                        insertPrev->SetNext(current);
                        current->SetNext(insertCurr);
                    }
            
                    if (insertCurr == nullptr) {
                        tail = current;
                    }
                }
            
                std::cout << "\"" << current->GetSongName() << "\" moved to position " << newPos << std::endl;
                std::cout << std::endl;
                break;
            }            
            

            case 'q':
                break;

            default:
                break;
        }

    } while (choice != 'q');

    // Clean up memory
    PlaylistNode* current = head;
    while (current != nullptr) {
        PlaylistNode* temp = current;
        current = current->GetNext();
        delete temp;
    }

    return 0;
}
