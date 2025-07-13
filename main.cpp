#include <iostream>
#include <vector>

// Constants
constexpr const char *VERSION = "v1.1.0";
constexpr int GRID_SIZE = 3;
constexpr char EMPTY_CELL = ' ';
constexpr char PLAYER_ONE = 'X';
constexpr char PLAYER_TWO = 'O';

// Type alias
using Grid = std::vector<std::vector<char>>;

// Function declarations
void runMenu();
void startGame();
void displayGrid(const Grid &);
bool checkWinner(const Grid &, char);
bool checkDraw(const Grid &);
bool getInput(const std::string &prompt, int &result);

// Main Function
int main()
{
    runMenu();
    return 0;
}

// Main Menu Loop
void runMenu()
{
    system("cls");

    while (true)
    {
        std::cout << "Tic Tac Toe - " << VERSION << "\n\n"
                  << "[1]. Start\n"
                  << "[2]. Quit\n";

        char input;
        std::cin >> input;

        if (!isdigit(input))
        {
            system("cls");
            std::cout << "Invalid input! Please enter numbers only.\n\n";
            continue;
        }

        switch (input)
        {
        case '1':
            while (true)
            {
                startGame();
                std::cout << "Play again? (Y/N): ";
                char c;
                std::cin >> c;
                if (c != 'Y' && c != 'y')
                    break;
            }
            system("cls");
            break;
        case '2':
            return;
        default:
            system("cls");
            std::cout << "Invalid input!\n\n";
        }
    }
}

// Game Loop
void startGame()
{
    Grid grid(GRID_SIZE, std::vector<char>(GRID_SIZE, EMPTY_CELL));
    bool isPlayerOneTurn = true;

    displayGrid(grid);

    while (true)
    {
        char symbol = isPlayerOneTurn ? PLAYER_ONE : PLAYER_TWO;
        int row, col;

        std::cout << "Player " << symbol << "'s Turn.\n";

        if (!getInput("Row (1-3): ", row) || !getInput("Column (1-3): ", col))
        {
            displayGrid(grid);
            std::cout << "Invalid input! Please enter a number between 1 and 3.\n\n";
            continue;
        }

        if (grid[row][col] != EMPTY_CELL)
        {
            displayGrid(grid);
            std::cout << "Invalid move! The cell is already occupied.\n\n";
            continue;
        }

        grid[row][col] = symbol;
        displayGrid(grid);

        if (checkWinner(grid, symbol))
        {
            std::cout << "Player " << symbol << " won!!!\n";
            break;
        }

        if (checkDraw(grid))
        {
            std::cout << "It's a draw!\n";
            break;
        }

        isPlayerOneTurn = !isPlayerOneTurn;
    }
}

// Display Grid
void displayGrid(const Grid &grid)
{
    system("cls");
    std::cout << ".-----------.\n";

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        std::cout << "|";
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            std::cout << " " << grid[i][j] << " |";
        }
        std::cout << "\n";
        if (i < GRID_SIZE - 1)
            std::cout << ":---+---+---:\n";
    }

    std::cout << "'-----------'\n\n";
}

// Win Checker
bool checkWinner(const Grid &grid, char symbol)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
            (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol))
        {
            return true;
        }
    }

    if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
        (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol))
    {
        return true;
    }

    return false;
}

// Draw Checker
bool checkDraw(const Grid &grid)
{
    for (int i = 0; i < GRID_SIZE; ++i)
        for (int j = 0; j < GRID_SIZE; ++j)
            if (grid[i][j] == EMPTY_CELL)
                return false;
    return true;
}

// Input with validation
bool getInput(const std::string &prompt, int &result)
{
    std::cout << prompt;
    std::cin >> result;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    
        return false;
    }

    --result;
    return result >= 0 && result < GRID_SIZE;
}
