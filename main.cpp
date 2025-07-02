#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

// Constants
constexpr const char *VERSION = "v1.1.0";
constexpr int GRID_SIZE = 3;
constexpr char EMPTY_CELL = ' ';

// Function declarations
bool isRunning();
void startGame();
bool getValidInput(int &);
bool getValidInput(int &, int &);
void enableAnsiEscape();
void clearScreen();
void displayGrid(const std::vector<std::vector<char>> &);
bool checkWinner(const std::vector<std::vector<char>> &, char);
bool checkDraw(const std::vector<std::vector<char>> &);

int main()
{
    isRunning();
    return 0;
}

bool isRunning()
{
    enableAnsiEscape();
    clearScreen();

    while (true)
    {
        // Display menu options
        std::cout << "Tic Tac Toe - "
                  << VERSION
                  << "\n\n\n"
                  << "[1]. Start\n"
                  << "[2]. Quit\n";

        int input = 0;

        // Validate numeric input
        if (!getValidInput(input))
        {
            std::cout << "Invalid input! Please enter numbers only.\n";
            continue;
        }

        // Handle user input
        switch (input)
        {
        case 1:
            // Game loop for multiple rounds
            while (true)
            {
                startGame();
                std::cout << "Play again? (Y/N): ";
                char c;
                std::cin >> c;
                if (c != 'Y' && c != 'y')
                    break;
            }
            clearScreen();
            break;
        case 2:
            return 0; // Exit the program
        default:
            std::cout << "Invalid input!\n";
        }
    }
}

void startGame()
{
    clearScreen();

    // Initialize empty 3x3 grid with '?'
    std::vector<std::vector<char>> grid(GRID_SIZE, std::vector<char>(GRID_SIZE, EMPTY_CELL));

    bool isPlayerOneTurn = true;
    displayGrid(grid);

    while (true)
    {
        char symbol = isPlayerOneTurn ? 'X' : 'O';
        int row = 0, col = 0;

        std::cout << "Player " << symbol << "'s Turn.\n";

        // Validate input values
        if (!getValidInput(row, col))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter numbers only.\n";
            continue;
        }

        // Check input is within valid range [1;3]
        if (row < 1 || row > GRID_SIZE || col < 1 || col > GRID_SIZE)
        {
            std::cout << "Invalid move! Row and Column must be between 1 and 3.\n";
            continue;
        }

        // Check if the selected cell is already taken
        if (grid[row - 1][col - 1] != EMPTY_CELL)
        {
            std::cout << "Invalid move! The cell is already occupied.\n";
            continue;
        }

        // Place the player's symbol
        grid[row - 1][col - 1] = symbol;

        // Display updated grid
        displayGrid(grid);

        // Check for win condition
        if (checkWinner(grid, symbol))
        {
            std::cout << "Player " << symbol << " won!!!\n";
            break;
        }

        // Check for draw condition
        if (checkDraw(grid))
        {
            std::cout << "It's a draw!\n";
            break;
        }

        // Switch to the other player
        isPlayerOneTurn = !isPlayerOneTurn;
    }
}

// Attempts to read an integer from input; returns true on success
bool getValidInput(int &input)
{
    if (std::cin >> input)
        return true;

    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return false;
}

// Prompts the user for row and column input; returns true if both are valid integers
bool getValidInput(int &row, int &col)
{
    std::cout << "Row (1-3): ";
    if (!(std::cin >> row))
        return false;

    std::cout << "Column (1-3): ";
    if (!(std::cin >> col))
        return false;

    return true;
}

void enableAnsiEscape()
{
    // Enable ANSI escape codes for Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode))
    {
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}

void clearScreen()
{
    std::cout << "\033[2J\033[H"; // ANSI escape to clear screen and move cursor to top-left
}

void displayGrid(const std::vector<std::vector<char>> &grid)
{
    clearScreen();

    std::cout << ".-----------.\n";

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        std::cout << "|";
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            std::cout << " " << grid[i][j] << " |";
        }
        std::cout << '\n';

        if (i < GRID_SIZE - 1)
            std::cout << ":---+---+---:\n";
    }

    std::cout << "'-----------'\n\n";
}

bool checkWinner(const std::vector<std::vector<char>> &grid, char symbol)
{
    // Check all rows and columns
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
            (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol))
        {
            return true;
        }
    }

    // Check both diagonals
    if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
        (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol))
    {
        return true;
    }

    return false;
}

bool checkDraw(const std::vector<std::vector<char>> &grid)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] == EMPTY_CELL)
                return false;
        }
    }
    return true;
}
