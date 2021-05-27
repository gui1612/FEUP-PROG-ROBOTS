// File Includes
#include "Player.h"
#include "constants.h"


Player::Player(char status, Point coordinates)
        : Entity(status, coordinates)
    {
        _score = 0;
        _win = false;
    }


Player::Player(std::string name, int score, char status, Point coordinates)
        : Entity(status, coordinates)
    {
        _name = name;
        _score = score;
        _win = false;
    }


Player::Player(): Entity() { _win = false; _score = 0; }


void Player::kill() {
    setStatus(PLAYER_DEAD_CHAR);
}


bool Player::isAlive() const {
    return getStatus() == PLAYER_ALIVE_CHAR;
}



void Player::getPlayerName() {
    // Variable to leave the do-while loop (should be at 0 to leave)
    short leave = 1;
    do{
        std::string playerName;                             // Initializes string to store the player username

        std::cout << "What's your name?" << std::endl;
        bool validInput = getInput(playerName);

        if (validInput) {                                   // Valid type
            clearBuffer();
            int nameLen = playerName.length();              // The size of the name

            if (0 < nameLen && nameLen <= 15) {             // Invalid name size
                setName(playerName);
                leave = 0;                                  // Leave the loop
            } else {
                warnUser("name");
            }
        } else if (!std::cin.eof()) {                        // Invalid type
            /**
             * Note: we need this condition for inputs like:
             * "ABCDEFGHJKLMNOPQRSTUV" where the name would exceed the 15
             * chars limit, but since only the string "ABCDEFGHJKLMNOP" would go to
             * the buffer, the scoreboard would be incorrectly updated
             */
            warnUser("name");
        }
    } while (!std::cin.eof() && leave != 0);
}