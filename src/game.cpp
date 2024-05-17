/**
 *
 * DATE: 2024-05-16 - 2024-05-XX
 * PURPOSE: Generates the minesweeper game.
 *
 */



#include <iostream>
#include <string>
#include <vector>
using namespace std;



/**
 *
 * PURPOSE: Setup the game.
 * 
 */
class Game {
    public:
        unsigned int score;
        string username;
        vector<vector<char>> board;

        /**
         * PURPOSE: Generates the game.
         */
        Game(unsigned int size) : score(0), username("null"), board(size) {

        }

        /**
         * PURPOSE: Generates the playing board.
         * @param board The board.
         * @return Nothing
         */
        void draw_board(vector<vector<char>> &board) {
            cout << "==============================" << endl;
            for (int i = 0; i < (int)board.size(); i++) {
                cout << "|| "; 
                for (int j = 0; j < (int)board[i].size(); j++) {
                    cout << "[" << board[i][j] << "]"; 
                }
                cout << " ||" << endl;
            }
            cout << "==============================" << endl;
        }
};



/**
 * Main function
 * @return 0 = success, 1 = failure
 */
int main() {
    vector<vector<char>> test = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};
    Game test_game(1);
    test_game.board = test;
    test_game.draw_board(test);
    cout << "Success" << endl;

    return 0;
}
