/**
 * DATE: 2024-05-16 - 2024-05-19
 * PURPOSE: Generates the minesweeper game.
 */



#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
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
        unsigned int flagged; // 0 if not flagged, 1 otherwise.
        vector<Cell> neighbors;
        vector<vector<int>> offsets;



        /*
         * PURPOSE: Generates a cell.
         */
        Cell() : default_value(' '), hidden_value('0'), flagged(0) {
            offsets = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1},
                {1,0}, {1,1}};
        }

        ~Cell() {}
        


        /**
         * NOTE: For DEBUGGING purposes only.
         * PURPOSE: Prints out the neighbors of a cell.
         * @return Nothing.
         */
        void print_neighbors() {
            for (int i = 0; i < (int)neighbors.size(); i++) {
                cout << neighbors[i].hidden_value << " "; 
            }
            cout << "\n" << endl;
        }
};



/**
 *
 * PURPOSE: Setup the game.
 * 
 */
class Game {
    public:
        unsigned int score;
        unsigned int status; // 0 = lose, 1 = win
        unsigned int difficulty;
        unsigned int row_num;
        unsigned int col_num;
        unsigned int mines_count;
        unsigned int flags_count;
        unsigned int flag_enable; // 0 unflag, 1 flag
        string move;
        set<string> track_moves;
        set<pair<int,int>> visited_cells;
        string username;
        vector<vector<Cell>> board;



        /**
         * PURPOSE: Generates the game.
         */
        Game() : score(0), difficulty(0), row_num(0),
            col_num(0), mines_count(0), flags_count(10), flag_enable(-1),
            move(), username("null"), board(9, vector<Cell>(9)) {

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
         * PURPOSE: Asks and verifies user input of a cell.
         * @return True, if valid move. Otherwise, false. 
         */
        bool request_move() {
            cout << "[SYSTEM]: Please enter a move from below.\n" <<
                "{<letter><number>}\nflag\nquit/q/exit to terminate\n:";
            cin >> move;

            set<string> valid_moves = {
                "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9",
                "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9",
                "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9",
                "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9",
                "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9",
                "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9",
                "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9",
                "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9",
                "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9",
                "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9",
            };

            if (move == "quit" || move == "q" || move == "exit") {
                cout << "[SYSTEM]: The game has been shut down." << endl;
                exit(0);
            }

            if (move == "flag") {
                cout << "[SYSTEM]: Enter a cell coordinate " <<
                    "{<letter><number>} to flag/unflag: ";
                cin >> move;
                flag_enable = 1;
            }

            move[0] = tolower(move[0]);
            move[1] = tolower(move[1]);

            if (valid_moves.find(move) != valid_moves.end() &&
                    track_moves.find(move) == track_moves.end()) {
                if (flag_enable == 0) {
                    track_moves.insert(move);
                }
                cout <<
                    "[SYSTEM]: Your requested move has been accepted.\n" <<
                    endl;
                return true;
            }
            cout << "[SYSTEM]: Your requested move is either INVALID "
                << "or has been already CALLED!\n" << endl;

            flag_enable = 0;
            return false;
        }
        


        /**
         * PURPOSE: Checks and reveals the contents of a cell.
         * @return True, if cell is a mine. Otherwise, false.
         */
        bool check_cell() {
            int x, y;
            x = move[0] - 'a';
            y = move[1] - '1';

            if (flag_enable == 1 && flags_count != 0 &&
                    board[x][y].flagged == 0 &&
                    board[x][y].default_value == ' ') {
                cout << "[SYSTEM]: This cell is now flagged.\n" << endl;
                board[x][y].default_value = '>';
                board[x][y].flagged = 1;
                flag_enable = 0;
                --flags_count;
                return false;
            } 

            if (flag_enable == 1 && board[x][y].flagged == 1 &&
                    board[x][y].default_value == '>') {
                board[x][y].default_value = ' ';
                board[x][y].flagged = 0;
                flag_enable = 0;
                ++flags_count;
                cout << "[SYSTEM]: This cell is now unflagged.\n" << endl;
                return false;
            }

            if (flag_enable == 1 && flags_count == 0) {
                cout << "[SYSTEM]: No flags remaining. " << 
                    "Please unflag(s) cell(s).\n" << endl;
                return false;
            }

            if (board[x][y].hidden_value == '*') {
                if (score > 0) {
                    board[x][y].hidden_value = '!';
                    status = 0;
                    return true;
                }

                board[x][y].hidden_value = '0';
                remap_first_mine_cell();
            }

            if (score == 0) {
                select_num_cells();
            }

            if (board[x][y].hidden_value == '0') {
                traverse_zero_cells(x, y);
            } else {
                board[x][y].default_value = board[x][y].hidden_value;
                ++score;
            }
            return false;
        }



        /**
         * PURPOSE: Traverses through blank spaces.
         * @param x The row coordinate of a cell.
         * @param y The column coordinate of a cell.
         * @return Nothing.
         */
        void traverse_zero_cells(int x, int y) {
            if (x < 0 || x >= (int)row_num || y < 0 || y >= (int)col_num ||
                    visited_cells.find(make_pair(x,y)) !=
                    visited_cells.end()) { 
                return;
            }

            if (board[x][y].hidden_value != '0') {
                board[x][y].default_value = board[x][y].hidden_value;
                ++score;
                visited_cells.insert(make_pair(x,y));
                return;
            }

            board[x][y].default_value = board[x][y].hidden_value;
            ++score;
            visited_cells.insert(make_pair(x,y));

            traverse_zero_cells(x, y-1);
            traverse_zero_cells(x, y+1);
            traverse_zero_cells(x-1, y);
            traverse_zero_cells(x+1, y);
            traverse_zero_cells(x-1, y-1);
            traverse_zero_cells(x-1, y+1);
            traverse_zero_cells(x+1, y-1);
            traverse_zero_cells(x+1, y+1);
       }



        /**
         * PURPOSE: Checks if user as won using score.
         * @param score The final score.
         * @return True, if all safe cells were revealed. Otherwise, false.
         */
        bool check_score() {
            if (score == 71) {
                status = 1;
                return true;
            }

            return false;
        }



        /**
         * PURPOSE: Finds and sets numbered cells.
         * @param board The playing board.
         * @return Nothing.
         */
        void select_num_cells() {
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
                                ++board[x][y].hidden_value;
                            }
                        }
                    }   
                }

            }
        }



        /**
         * PURPOSE: Generates the playing board.
         * @param type (0)Hide or (1)reveal cells.
         * @return Nothing.
         */
        void draw_board(int type) {
            char row_val = 'A';
            cout << "    1   2   3   4   5   6   7   8   9" << endl;
            cout << "  +===+===+===+===+===+===+===+===+===+" << endl;
            for (int i = 0; i < (int)board.size(); i++) {
                cout << row_val;
                for (int j = 0; j < (int)board[i].size(); j++) {
                    if (type == 0) {
                        cout << " | " << board[i][j].default_value;
                    } else {
                        cout << " | " << board[i][j].hidden_value;
                    }   
                }
                cout << " |" << endl;
                cout << "  +===+===+===+===+===+===+===+===+===+" << endl;
                ++row_val;
            }
            cout << "\n                                           " << 
                "FLAGS REMAINING: " << flags_count << endl;
            cout << "\n                                           " << 
                "SCORE: " << score << "\n\n" << endl;
        }
        


        /**
         * PURPOSE: Generates mines on the board.
         * @param board The playing board.
         * @return Nothing.
         */
        void generate_mines() {
            unsigned int row_sel;
            unsigned int col_sel;

            for (int i = 0; i < (int)mines_count; i++) {
                row_sel = rand() % (row_num - 1);
                col_sel = rand() % (col_num - 1);
                board[row_sel][col_sel].hidden_value = '*';
                
                //cout << "[SYSTEM]: A mine has been set at ("
                    //<< row_sel << "," << col_sel << ")." << endl;
            }
            cout << "\n\n" << endl;
        }



        /**
         * PURPOSE: Remap first mine cell if chosen.
         * @return Nothing.
         */
        void remap_first_mine_cell() {
            bool found = false;
            int x,y;
            while (found == false) {
                x = rand() % (row_num - 1);
                y = rand() % (col_num - 1);
                if (board[x][y].hidden_value != '*') {
                    board[x][y].hidden_value = '*';
                    found = true;
                    //cout << 
                        //"[SYSTEM]: The selected mine has been remapped to: "
                        //<< x << "," << y << ".\n" << endl;
                    return;
                }
            }
        }
};



/**
 * PURPOSE: Main function.
 * @return 0 = success, 1 = failure
 */
int main() {
    Game game;
    srand(time(NULL));
    cout << "[SYSTEM]: LOADING Minesweeper..." << endl;
    cout << "[SYSTEM]: Welcome to Minesweeper!" << endl;
    game.generate_mines();

    while (game.check_score() != true) {
        // game.draw_board(1);
        game.draw_board(0);
        if (game.request_move() && game.check_cell() == true) {;
            break;
        }
    }

    game.draw_board(1);

    if (game.status == 0) {
        cout << "[SYSTEM]: You have lost..." << endl;
    } else {
        cout << "[SYSTEM]: You have won!" << endl;
    }

    cout << "[SYSTEM]: This program has ended.\n" << 
        "[SYSTEM]: Please rerun to play again!" << endl;
    return 0;
}
