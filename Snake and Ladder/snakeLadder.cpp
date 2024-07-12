#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

class Coordinates {
public:
    int x;
    int y;
    Coordinates() : x(0), y(0) {} // Default constructor
    Coordinates(int x, int y) : x(x), y(y) {}
};

class Jumper {
public:
    Coordinates start;
    Coordinates end;
    Jumper() : start(Coordinates()), end(Coordinates()) {} // Default constructor
    Jumper(Coordinates start, Coordinates end) : start(start), end(end) {}
};

class Player {
public:
    string name;
    Coordinates position;
    Player(string name, Coordinates position) : name(name), position(position) {}
};
class Dice {
private:
    static const int MIN = 1;
    static const int MAX = 6;

public:
    Dice() {
        srand(static_cast<unsigned int>(time(0)));
    }

    int diceRoll() const {
        return rand() % MAX + MIN;
    }
};

class GameBoard {
private:
    vector<vector<int>> board;
    int size;
    unordered_map<string, Jumper> ladders;
    unordered_map<string, Jumper> snakes;

public:
    GameBoard(int size) : size(size) {
        board.resize(size, vector<int>(size, 0));
    }

    void addLadder(string name, Jumper ladder) {
        ladders[name] = ladder;
    }

    void addSnake(string name, Jumper snake) {
        snakes[name] = snake;
    }

    Coordinates getNewPosition(Coordinates pos, int roll) {
        int newX = pos.x;
        int newY = pos.y + roll;

        while (newY >= size) {
            newX += 1;
            newY -= size;
        }

        Coordinates newPos(newX, newY);

        for (const auto& ladder : ladders) {
            if (ladder.second.start.x == newPos.x && ladder.second.start.y == newPos.y) {
                return ladder.second.end;
            }
        }

        for (const auto& snake : snakes) {
            if (snake.second.start.x == newPos.x && snake.second.start.y == newPos.y) {
                return snake.second.end;
            }
        }

        return newPos;
    }

    bool isWinningPosition(Coordinates pos) {
        return pos.x == size - 1 && pos.y == size - 1;
    }
};

class Game {
private:
    GameBoard board;
    vector<Player> players;
    int currentPlayerIndex;

public:
    Game(int boardSize) : board(boardSize), currentPlayerIndex(0) {
        players.push_back(Player("Player 1", Coordinates(0, 0)));
        players.push_back(Player("Player 2", Coordinates(0, 0)));
    }

    void addLadder(string name, Jumper ladder) {
        board.addLadder(name, ladder);
    }

    void addSnake(string name, Jumper snake) {
        board.addSnake(name, snake);
    }

    void playTurn() {
        Player& currentPlayer = players[currentPlayerIndex];
        int roll = (rand() % 6) + 1;
        Coordinates newPosition = board.getNewPosition(currentPlayer.position, roll);
        currentPlayer.position = newPosition;
        cout << currentPlayer.name << " rolled a " << roll << " and moved to (" << newPosition.x << ", " << newPosition.y << ")" << endl;

        if (board.isWinningPosition(newPosition)) {
            cout << currentPlayer.name << " wins!" << endl;
            exit(0);
        }

        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    void startGame() {
        while (true) {
            playTurn();
        }
    }
};

int main() {
    srand(time(0));
    Game game(10);

    game.addLadder("Ladder 1", Jumper(Coordinates(0, 1), Coordinates(4, 1)));
    game.addLadder("Ladder 2", Jumper(Coordinates(2, 3), Coordinates(5, 3)));
    game.addSnake("Snake 1", Jumper(Coordinates(3, 5), Coordinates(1, 5)));
    game.addSnake("Snake 2", Jumper(Coordinates(6, 7), Coordinates(2, 7)));

    game.startGame();

    return 0;
}
