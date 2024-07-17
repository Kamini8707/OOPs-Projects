#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Triple.h
class Triple {
public:
    int row;
    int col;
    int val;

    Triple(int row, int col, int val) : row(row), col(col), val(val) {}
};

// Player.h
class Player {
private:
    string name;
    int age;

public:
    Player(const string& name, int age) : name(name), age(age) {}

    string getPlayerName() const {
        return name;
    }

    int getPlayerAge() const {
        return age;
    }
};

// Board.h
class Board {
public:
    int size;
    vector<vector<int>> matrix;

    Board(int size) : size(size), matrix(size, vector<int>(size, 0)) {}

    void printBoard() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void setUpBoardConfig(int row, int col, int val) {
        matrix[row][col] = val;
    }

    void setUpColumnwise(int row, const vector<int>& col, const vector<int>& val) {
        for (size_t i = 0; i < col.size(); ++i) {
            matrix[row][col[i]] = val[i];
        }
    }

    void setUpBoard(const vector<Triple>& triples) {
        for (const auto& triple : triples) {
            matrix[triple.row][triple.col] = triple.val;
        }
    }
};

// QueenBoard.h
class QueenBoard {
public:
    int size;
    vector<vector<char>> board;

    QueenBoard(int size) : size(size), board(size, vector<char>(size, '-')) {}

    void printBoard() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Game.h
class Game {
public:
    Board board;
    Player player;

    Game(Board board, Player player) : board(board), player(player) {}

    void play() {
        solveSudoku(0, 0);
    }

private:
    void solveSudoku(int row, int col) {
        if (row == board.size) {
            cout << "Sudoku Solved!!!!! by " << player.getPlayerName() << endl;
            board.printBoard();
            return;
        }

        int nrow = 0, ncol = 0;

        if (col == board.size - 1) {
            nrow = row + 1;
            ncol = 0;
        } else {
            nrow = row;
            ncol = col + 1;
        }

        if (board.matrix[row][col] != 0) {
            solveSudoku(nrow, ncol);
        } else {
            for (int i = 1; i <= 9; ++i) {
                if (validPos(board.matrix, row, col, i)) {
                    board.matrix[row][col] = i;
                    solveSudoku(nrow, ncol);
                    board.matrix[row][col] = 0;
                }
            }
        }
    }

    bool validPos(const vector<vector<int>>& matrix, int row, int col, int val) {
        for (int i = 0; i < matrix.size(); ++i) {
            if (matrix[row][i] == val) {
                return false;
            }
        }

        for (int i = 0; i < matrix.size(); ++i) {
            if (matrix[i][col] == val) {
                return false;
            }
        }

        int tempRow = (row / 3) * 3;
        int tempCol = (col / 3) * 3;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (matrix[tempRow + i][tempCol + j] == val) {
                    return false;
                }
            }
        }

        return true;
    }
};

// NQueenGame.h
class NQueenGame {
public:
    QueenBoard q;

    NQueenGame(QueenBoard q) : q(q) {}

    void play() {
        if (q.size < 4) {
            cout << "No configuration possible" << endl;
            return;
        }

        nqueen_helper(q.board, 0);
    }

private:
    void nqueen_helper(vector<vector<char>>& board, int row) {
        if (row == board.size()) {
            printBoard(board);
            return;
        }

        for (int col = 0; col < board.size(); ++col) {
            if (isSafeQueen(board, row, col)) {
                board[row][col] = 'Q';
                nqueen_helper(board, row + 1);
                board[row][col] = '-';
            }
        }
    }

    bool isSafeQueen(const vector<vector<char>>& board, int row, int col) {
        for (int i = row - 1, j = col - 1; j >= 0 && i >= 0; --i, --j) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        for (int i = row - 1, j = col + 1; j < board.size() && i >= 0; --i, ++j) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        for (int i = row - 1; i >= 0; --i) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }

        return true;
    }

    void printBoard(const vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// App.cpp
int main() {
    QueenBoard b(4);
    NQueenGame game(b);

    game.play();

    return 0;
}
