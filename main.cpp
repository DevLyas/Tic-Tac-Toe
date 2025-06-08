#include <iostream>
#include <vector>

constexpr int GRID_SIZE = 3;

// Function declarations
void mainMenu();
void startGame();
bool getValidInput(int &);
bool getValidInput(int &, int &);
void displayGrid(const std::vector<std::vector<char>> &);
bool checkWinner(const std::vector<std::vector<char>> &, char);
bool checkDraw(const std::vector<std::vector<char>> &);

int main()
{
    std::cout << "Tic Tac Toe v1.0.0\n\n\n";
    mainMenu();
    return 0;
}

void mainMenu()
{
    while (true)
    {
        // Display menu options
        std::cout << "[1]. Start\n"
                  << "[2]. Quit\n";

        int input;

        // Validate numeric input
        if (!getValidInput(input))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
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
                if (c != 'Y' && c != 'y') break;
            }
            break;
        case 2:
            return;  // Exit the program
        default:
            std::cout << "Invalid input!\n";
        }
    }
}

void startGame()
{
    // Initialize empty 3x3 grid with '?'
    std::vector<std::vector<char>> grid =
    {
        {'?', '?', '?'},
        {'?', '?', '?'},
        {'?', '?', '?'}
    };

    bool isPlayerOneTurn = true;
    displayGrid(grid);

    while (true)
    {
        char symbol = isPlayerOneTurn ? 'X' : 'O';
        int row, col;

        std::cout << "Player " << symbol << "'s Turn (" << symbol << ")\n";

        // Validate input values
        if (!getValidInput(row, col))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter numbers only.\n";
            continue;
        }

        // Check input is within valid range
        if (row < 1 || row > GRID_SIZE || col < 1 || col > GRID_SIZE)
        {
            std::cout << "Invalid move! Row and Column must be between 1 and 3.\n";
            continue;
        }

        // Check if the selected cell is already taken
        if (grid[row - 1][col - 1] != '?')
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
    return static_cast<bool>(std::cin >> input);
}

// Prompts the user for row and column input; returns true if both are valid integers
bool getValidInput(int &row, int &col)
{
    std::cout << "Row (1-3): ";
    if (!(std::cin >> row)) return false;

    std::cout << "Column (1-3): ";
    if (!(std::cin >> col)) return false;

    return true;
}

void displayGrid(const std::vector<std::vector<char>> &grid)
{
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
    std::cout << "'-----------'\n";
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
            if (grid[i][j] == '?')
                return false;
        }
    }
    return true;
}
