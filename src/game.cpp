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
 * PURPOSE: To fill board with cells.
 */
class Cell {
    public:
        char default_value;
        char hidden_value;
        vector<Cell> neighbors;
        vector<vector<int>> offsets;



        /*
         * PURPOSE: Generates a cell.
         */
        Cell() : default_value('-'), hidden_value('0') {
            offsets = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1},
                {1,0}, {1,1}};
        }

        ~Cell() {}
};



/**
 *
 * PURPOSE: Setup the game.
 * 
 */
class Game {
    public:
        unsigned int score;
        unsigned int difficulty;
        unsigned int row_num;
        unsigned int col_num;
        unsigned int mines_count;
        string username;
        vector<vector<Cell>> board;

        /**
         * PURPOSE: Generates the game.
         */
        Game() : score(0), difficulty(0), row_num(0),
            col_num(0), mines_count(0), username("null"), board() {

            switch(difficulty) {
                case 1:
                    row_num = 16;
                    col_num = 16;
                    mines_count = 10; 
                    break;
                case 2:
                    row_num = 16;
                    col_num = 30;
                    mines_count = 99;
                    break;
                case 7:
                    row_num = 5;
                    col_num = 5;
                    mines_count = 6;
                    break;
                default:
                    row_num = 9;
                    col_num = 9;
                    mines_count = 10;
                    break;
            }
        }

        ~Game() {}



        /**
         * PURPOSE: Finds and sets numbered cells.
         * @param board The playing board.
         * @return Nothing
         */
        void select_num_cells(vector<vector<Cell>> &board) {
            int x, y;
            for (int i = 0; i < (int)board.size(); i++) {
                for (int j = 0; j < (int)board[i].size(); j++) {
                    if (board[i][j].hidden_value == '*') {
                        for (int k = 0;
                                k < (int)board[i][j].offsets.size(); k++) {
                            x = i + board[i][j].offsets[k][0];
                            y = j + board[i][j].offsets[k][1];

                            if (x >= 0 && x < (int)board.size() && y >= 0
                                    && y < (int)board[i].size() &&
                                    board[x][y].hidden_value != '*') {
                                board[x][y].hidden_value++;
                            }
                        }
                    }   
                }

            }
        }



        /**
         * PURPOSE: Prints out the neighbors of a cell.
         * @return Nothing
         */
        void print_neighbors(vector<Cell> &neighbors) {
            for (int i = 0; i < (int)neighbors.size(); i++) {
                cout << neighbors[i].hidden_value << " "; 
            }
            cout << "\n" << endl;
        }



        /**
         * PURPOSE: Generates the playing board.
         * @return Nothing
         */
        void draw_board(vector<vector<Cell>> &board) {
            cout << " +===+===+===+===+===+===+===+===+===+" << endl;
            for (int i = 0; i < (int)board.size(); i++) {
                for (int j = 0; j < (int)board[i].size(); j++) {
                    cout << " | " << board[i][j].hidden_value; 
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
        void generate_mines() {
            unsigned int row_sel;
            unsigned int col_sel;

            for (int i = 0; i < (int)mines_count; i++) {
                row_sel = rand() % (row_num - 1);
                col_sel = rand() % (col_num - 1);
                board[row_sel][col_sel].hidden_value = '*';
                
                cout << "A mine has been set at (" << row_sel << ","
                    << col_sel << ")." << endl;
            }
            cout << "\n" << endl;
        }
};



/**
 * PURPOSE: Main function
 * @return 0 = success, 1 = failure
 */
int main() {
    vector<vector<char>> test = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};
    Game test_game;
//  test_game.board = test;
//  test_game.draw_board(test);

    vector<vector<Cell>> test_two(9, vector<Cell>(9));
    test_game.board = test_two;
    test_game.draw_board(test_game.board);
    test_game.generate_mines();
    test_game.draw_board(test_game.board);
    test_game.select_num_cells(test_game.board);
//    test_game.set_numbered_cells(test_game.board);
//    test_game.print_neighbors(test_game.board[1][1].neighbors);
    test_game.draw_board(test_game.board);
    cout << "Success" << endl;

    return 0;
}
