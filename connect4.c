// THIS CODE IS DONE BY GAURAV BUDHWANI - 22110085

// including the libraries

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// declaring a macro for a 4 * 5 grid having 4 rows and 5 columns.

#define ROWS 4
#define COLS 5
#define MAX_DEPTH 4

// declaring the global variables.

char board[ROWS][COLS], play, pc;

// function for initialising an empty board.
void initialise_board()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// function for prining the board.
void print_boards()
{
    printf("\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if(board[i][j] == 'X')
            printf("| %c ", play);
            else if(board[i][j] == 'O')
            printf("| %c ", pc);
            else
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("|---|---|---|---|---|\n");
    printf("| 1 | 2 | 3 | 4 | 5 |\n");
}

// function for checking whether the move made is valid or not.
bool is_an_valid_move(int col)
{
    return col >= 0 && col < COLS && board[0][col] == ' ';
}

// function to place the move on the board for computer and player
int drop_player_disc(int col, char player)
{
    for (int i = ROWS - 1; i >= 0; i--)
    {
        if (board[i][col] == ' ')
        {
            board[i][col] = player;
            return i;
        }
    }
    return -1; // Column is full
}

// function for checing the victory condition
// by checking horizontally, vertically, and diagonally.
bool has_won(int row, int col, char player)
{
    // Check horizontally
    int count = 0;
    for (int i = col - 3; i <= col + 3; i++)
    {
        if (i >= 0 && i < COLS && board[row][i] == player)
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            count = 0;
        }
    }

    // Check vertically
    count = 0;
    for (int i = row - 3; i <= row + 3; i++)
    {
        if (i >= 0 && i < ROWS && board[i][col] == player)
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            count = 0;
        }
    }

    // Check diagonally (top-left to bottom-right)
    count = 0;
    for (int i = -3; i <= 3; i++)
    {
        int r = row + i;
        int c = col + i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player)
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            count = 0;
        }
    }

    // Check diagonally (bottom-left to top-right)
    count = 0;
    for (int i = -3; i <= 3; i++)
    {
        int r = row - i;
        int c = col + i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player)
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            count = 0;
        }
    }

    return false;
}

// function to check if the board is full which will lead to draw condition
bool is_full()
{
    for (int i = 0; i < COLS; i++)
    {
        if (board[0][i] == ' ')
        {
            return false;
        }
    }
    return true;
}

// function for evaluatng the move made and calculating the appropriate score.
int evaluating_board(char player)
{
    int score = 0;

    // Check horizontally
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            int count_player = 0;
            int count_opponent = 0;
            for (int i = 0; i < 4; i++)
            {
                if (board[row][col + i] == player)
                {
                    count_player++;
                }
                else if (board[row][col + i] != ' ')
                {
                    count_opponent++;
                }
            }

            if (count_player == 4)
            {
                return 1000; // Player wins
            }
            else if (count_opponent == 4)
            {
                return -1000; // Opponent wins
            }
            else if (count_player == 3 && count_opponent == 0)
            {
                score += 100; // Potential win
            }
            else if (count_player == 2 && count_opponent == 0)
            {
                score += 10; // Potential win
            }
            else if (count_player == 1 && count_opponent == 0)
            {
                score += 1; // Potential win
            }
            else if (count_opponent == 3 && count_player == 0)
            {
                score -= 100; // Potential loss
            }
            else if (count_opponent == 2 && count_player == 0)
            {
                score -= 10; // Potential loss
            }
            else if (count_opponent == 1 && count_player == 0)
            {
                score -= 1; // Potential loss
            }
        }
    }

    // Check vertically
    for (int col = 0; col < COLS; col++)
    {
        for (int row = 0; row <= ROWS - 4; row++)
        {
            int count_player = 0;
            int count_opponent = 0;
            for (int i = 0; i < 4; i++)
            {
                if (board[row + i][col] == player)
                {
                    count_player++;
                }
                else if (board[row + i][col] != ' ')
                {
                    count_opponent++;
                }
            }

            if (count_player == 4)
            {
                return 500; // Player wins
            }
            else if (count_opponent == 4)
            {
                return -500; // Opponent wins
            }
            else if (count_player == 3 && count_opponent == 0)
            {
                score += 50; // Potential win
            }
            else if (count_player == 2 && count_opponent == 0)
            {
                score += 5; // Potential win
            }
            else if (count_player == 1 && count_opponent == 0)
            {
                score += 1; // Potential win
            }
            else if (count_opponent == 3 && count_player == 0)
            {
                score -= 50; // Potential loss
            }
            else if (count_opponent == 2 && count_player == 0)
            {
                score -= 5; // Potential loss
            }
            else if (count_opponent == 1 && count_player == 0)
            {
                score -= 1; // Potential loss
            }
        }
    }

    // Check diagonals  (upward)
    for (int row = 3; row < ROWS; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            int count_player = 0;
            int count_opponent = 0;
            for (int i = 0; i < 4; i++)
            {
                if (board[row - i][col + i] == player)
                {
                    count_player++;
                }
                else if (board[row - i][col + i] != ' ')
                {
                    count_opponent++;
                }
            }

            if (count_player == 4)
            {
                return 1000; // Player wins
            }
            else if (count_opponent == 4)
            {
                return -1000; // Opponent wins
            }
            else if (count_player == 3 && count_opponent == 0)
            {
                score += 100; // Potential win
            }
            else if (count_player == 2 && count_opponent == 0)
            {
                score += 10; // Potential win
            }
            else if (count_player == 1 && count_opponent == 0)
            {
                score += 1; // Potential win
            }
            else if (count_opponent == 3 && count_player == 0)
            {
                score -= 100; // Potential loss
            }
            else if (count_opponent == 2 && count_player == 0)
            {
                score -= 10; // Potential loss
            }
            else if (count_opponent == 1 && count_player == 0)
            {
                score -= 1; // Potential loss
            }
        }
    }

    // Check diagonals (downward)
    for (int row = 0; row <= ROWS - 4; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            int count_player = 0;
            int count_opponent = 0;
            for (int i = 0; i < 4; i++)
            {
                if (board[row + i][col + i] == player)
                {
                    count_player++;
                }
                else if (board[row + i][col + i] != ' ')
                {
                    count_opponent++;
                }
            }

            if (count_player == 4)
            {
                return 1000; // Player wins
            }
            else if (count_opponent == 4)
            {
                return -1000; // Opponent wins
            }
            else if (count_player == 3 && count_opponent == 0)
            {
                score += 100; // Potential win
            }
            else if (count_player == 2 && count_opponent == 0)
            {
                score += 10; // Potential win
            }
            else if (count_player == 1 && count_opponent == 0)
            {
                score += 1; // Potential win
            }
            else if (count_opponent == 3 && count_player == 0)
            {
                score -= 100; // Potential loss
            }
            else if (count_opponent == 2 && count_player == 0)
            {
                score -= 10; // Potential loss
            }
            else if (count_opponent == 1 && count_player == 0)
            {
                score -= 1; // Potential loss
            }
        }
    }

    return score;
}

// function for getting the minimum or maximum evaluated score
int score_mini_max(int depth, int alpha, int beta, bool score_is_maximizing, char player)
{
    if (depth == 0 || has_won(0, 0, 'X') || has_won(0, 0, 'O') || is_full())
    {
        return evaluating_board(player);
    }

    char opponent = (player == 'X') ? 'O' : 'X';

    if (score_is_maximizing)
    {
        int max_eval = INT_MIN;
        for (int col = 0; col < COLS; col++)
        {
            if (is_an_valid_move(col))
            {
                int row = drop_player_disc(col, player);
                int eval = score_mini_max(depth - 1, alpha, beta, !score_is_maximizing, opponent);  // Use opponent here
                max_eval = (eval > max_eval) ? eval : max_eval;
                alpha = (alpha > eval) ? alpha : eval;
                board[row][col] = ' ';
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return max_eval;
    }
    else
    {
        int min_eval = INT_MAX;
        for (int col = 0; col < COLS; col++)
        {
            if (is_an_valid_move(col))
            {
                int row = drop_player_disc(col, opponent);
                int eval = score_mini_max(depth - 1, alpha, beta, !score_is_maximizing, player);  // Use player here
                min_eval = (eval < min_eval) ? eval : min_eval;
                beta = (beta < eval) ? beta : eval;
                board[row][col] = ' ';
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return min_eval;
    }
}

// function for making the best move by pc realted to the move made by player
int best_move(char player)
{
    int best_column = -1;
    int best_evaluation = INT_MIN;

    for (int col = 0; col < COLS; col++)
    {
        if (is_an_valid_move(col))
        {
            int row = drop_player_disc(col, player);
            int evaluation = score_mini_max(MAX_DEPTH, INT_MIN, INT_MAX, false, player);
            board[row][col] = ' ';
            if (evaluation >= best_evaluation)
            {
                best_evaluation = evaluation;
                best_column = col;
            }
        }
    }

    return best_column;
}

// main function.
int main()
{
    initialise_board();
    printf("Enter the choice of player: R/B\n");
    char player = 'X';
    scanf("%c", &play);
    int moves = 0;
    if(play == 'R')
    {
        pc = 'B';
    }
    else
    {
        pc = 'R';
    }
    while (true)
    {
        print_boards();

        if (player == 'X')
        {
            printf("Player %c, enter your move (1-5): ", play);
            int col;
            scanf("%d", &col);
            col--;

            if (is_an_valid_move(col))
            {
                int row = drop_player_disc(col, player);
                if (has_won(row, col, player))
                {
                    print_boards();
                    printf("Player %c wins!\n", play);
                    break;
                }
                else if (is_full())
                {
                    print_boards();
                    printf("It's a draw!\n");
                    break;
                }
                player = 'O';
            }
            else
            {
                printf("Invalid move. Try again.\n");
            }
        }
        else
        { // Computer's turn
            printf("Computer's move...\n");
            int col;
            do
            {
                col = best_move(player);
                ;
            } while (!is_an_valid_move(col));

            int row = drop_player_disc(col, player);
            if (has_won(row, col, player))
            {
                print_boards();
                printf("Computer wins!\n");
                break;
            }
            else if (is_full())
            {
                print_boards();
                printf("It's a draw!\n");
                break;
            }
            player = 'X';
        }
    }

    return 0;
}
