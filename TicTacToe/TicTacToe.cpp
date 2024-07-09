#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Board {
public:
    int size;
    vector<vector<char>> matrix;

    Board(int size, char defaultSymbol) : size(size), matrix(size, vector<char>(size, defaultSymbol)) {}

    void setDefaultSymbol(char symbol) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = symbol;
            }
        }
    }

    void printBoardConfig() const {
        for (const auto& row : matrix) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
};

class Player {
private:
    string name;
    char symbol;
    string address;
    string contactNumber;
    string emailId;
    int age;

public:
    void setPlayerDetails(const string& name, char symbol, const string& address, const string& contactNumber, const string& emailId, int age) {
        this->name = name;
        this->symbol = symbol;
        this->address = address;
        this->contactNumber = contactNumber;
        this->emailId = emailId;
        this->age = age;
    }

    void setPlayerNameAndAge(const string& name, int age) {
        this->name = name;
        this->age = age;
    }

    void setPlayerNameSymbolEmailIdAge(const string& name, char symbol, const string& emailId, int age) {
        this->name = name;
        this->symbol = symbol;
        this->emailId = emailId;
        this->age = age;
    }

    void changeSymbol(char symbol) {
        this->symbol = symbol;
    }

    void setPlayerNameAndSymbol(const string& name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }

    string getPlayerName() const {
        return name;
    }

    char getPlayerSymbol() const {
        return symbol;
    }

    void getPlayerNameAndSymbol() const {
        cout << "Player Name: " << name << endl;
        cout << "Player Symbol: " << symbol << endl;
    }

    void getPlayerNameAndAge() const {
        cout << "Player Name: " << name << endl;
        cout << "Player Age: " << age << endl;
    }

    void getPlayerDetails() const {
        cout << "Player Name: " << name << endl;
        cout << "Player Symbol: " << symbol << endl;
        cout << "Player EmailId: " << emailId << endl;
        cout << "Player Age: " << age << endl;
        cout << "Player Contact Number: " << contactNumber << endl;
        cout << "Player Address: " << address << endl;
    }
};

class Game {
public:
    vector<Player> players;
    Board board;
    int turn;
    int noOfMoves;
    bool gameOver;
    string zero;
    string cross;

    Game(const vector<Player>& players, Board& board)
        : players(players), board(board), turn(0), noOfMoves(0), gameOver(false) {
        zero = string(board.size, 'O');
        cross = string(board.size, 'X');
    }

    void printBoardConfig() {
        board.printBoardConfig();
    }

    void play() {
        printBoardConfig();
        int sz = board.size;

        while (!gameOver) {
            noOfMoves++;
            int idx = getIndex();

            int row = idx / sz;
            int col = idx % sz;

            board.matrix[row][col] = players[turn].getPlayerSymbol();

            if (noOfMoves >= sz * sz) {
                cout << "Game Draw" << endl;
                return;
            }

            if (noOfMoves >= 2 * sz - 1 && checkCombinations()) {
                gameOver = true;
                printBoardConfig();
                cout << "Winner is: " << players[turn].getPlayerName() << endl;
                return;
            }

            turn = (turn + 1) % 2;
            printBoardConfig();
        }
    }

    int getIndex() {
        while (true) {
            cout << "Player: " << players[turn].getPlayerName() << " give one position" << endl;
            int pos;
            cin >> pos;
            pos--;

            int sz = board.size;
            int row = pos / sz;
            int col = pos % sz;

            if (row < 0 || row >= sz || col < 0 || col >= sz) {
                cout << "Invalid position" << endl;
                continue;
            }

            if (board.matrix[row][col] != '-') {
                cout << "Position already occupied" << endl;
                continue;
            }

            return pos;
        }
    }

    bool checkCombinations() {
        int sz = board.size;

        for (int i = 0; i < sz; ++i) {
            string pattern;
            for (int j = 0; j < sz; ++j) {
                pattern += board.matrix[i][j];
            }
            if (pattern == zero || pattern == cross) {
                return true;
            }
        }

        for (int i = 0; i < sz; ++i) {
            string pattern;
            for (int j = 0; j < sz; ++j) {
                pattern += board.matrix[j][i];
            }
            if (pattern == zero || pattern == cross) {
                return true;
            }
        }

        string pattern;
        for (int i = 0; i < sz; ++i) {
            pattern += board.matrix[i][i];
        }
        if (pattern == zero || pattern == cross) {
            return true;
        }

        pattern.clear();
        for (int i = 0, j = sz - 1; i < sz; ++i, --j) {
            pattern += board.matrix[i][j];
        }
        if (pattern == zero || pattern == cross) {
            return true;
        }

        return false;
    }
};

int main() {
    cout << "First Project -> Tic Tac Toe" << endl;

    Board b(3, '-');

    Player p1;
    p1.setPlayerNameAndSymbol("Kamini", 'X');
    p1.getPlayerNameAndSymbol();

    Player p2;
    p2.setPlayerNameAndSymbol("Khushi", 'O');
    p2.getPlayerNameAndSymbol();

    vector<Player> players = { p1, p2 };
    Game game(players, b);
    game.play();

    return 0;
}
