/**
 *
 * DATE: 2024-05-16 - 2024-05-XX
 * PURPOSE: Generates the minesweeper game.
 *
 */



#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;



/**
 *
 * PURPOSE: Setup the game.
 * 
 */
class Game {
    public:
        unsigned int score;
        unsigned int difficulty;
        string username;
        vector<vector<char>> board;

        /**
         * PURPOSE: Generates the game.
         */
        Game(unsigned int size) : score(0), difficulty(0),
            username("null"), board(size) {

        }



        /**
         * PURPOSE: Generates the playing board.
         * @param board The board.
         * @return Nothing
         */
        void draw_board(vector<vector<char>> &board) {
            cout << " +===+===+===+===+===+===+===+===+===+" << endl;
            for (int i = 0; i < (int)board.size(); i++) {
                for (int j = 0; j < (int)board[i].size(); j++) {
                    cout << " | " << board[i][j]; 
                }
                cout << " |" << endl;
                cout << " +===+===+===+===+===+===+===+===+===+" << endl;
            }
        }
        


        /**
         * PURPOSE: Generates mines on the board.
         * @param board The playing board.
         * @return Nothing
         */
        void generate_mines(vector<vector<char>> &board,
                unsigned int &difficulty) {
            unsigned int mines_count = 0;
            unsigned int row_num;
            unsigned int col_num;
            unsigned int row_sel;
            unsigned int col_sel;

            switch(difficulty) {
                case 1:
                    mines_count = 10;
                    row_num = 16;
                    col_num = 16;
                    break;
                case 2:
                    mines_count = 99;
                    row_num = 16;
                    col_num = 30;
                    break;
                default:
                    mines_count = 10;
                    row_num = 9;
                    col_num = 9;
                    break;
            }

            for (int i = 0; i < (int)mines_count; i++) {
                row_sel = rand() % (row_num - 1);
                col_sel = rand() % (col_num - 1);
                board[row_sel][col_sel] = '*';
                
                cout << "A mine has been set at (" << row_sel << ","
                    << col_sel << ")." << endl;
            }
        }
};



/**
 * PURPOSE: Main function
 * @return 0 = success, 1 = failure
 */
int main() {
    vector<vector<char>> test = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};
    Game test_game(1);
//  test_game.board = test;
//  test_game.draw_board(test);

    vector<vector<char>> test_two(9, vector<char> (9, '1'));
    test_game.board = test_two;
    test_game.draw_board(test_game.board);
    test_game.generate_mines(test_game.board, test_game.difficulty);
    test_game.draw_board(test_game.board);
    cout << "Success" << endl;

    return 0;
}
