#include <stdio.h>
#include <stdlib.h>

int board[20];
int n;

int isSafe(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col ||
            abs(board[i] - col) == abs(i - row))
        {
            return 0;
        }
    }
    return 1;
}

int solve(int row)
{
    if (row == n)
    {
        // Print chessboard
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i] == j)
                    printf("Q ");
                else
                    printf(". ");
            }
            printf("\n");
        }

        // Print queen positions
        printf("\nQueen positions (row, column):\n");

        for (int i = 0; i < n; i++)
        {
            printf("Queen %d: (%d, %d)\n",
                   i + 1, i + 1, board[i] + 1);
        }

        return 1;
    } // Missing closing brace was needed here

    // Backtracking loop
    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col))
        {
            board[row] = col;

            if (solve(row + 1))
                return 1;

            board[row] = -1;
        }
    }

    return 0;
} // Missing closing brace for solve()

int main()
{
    printf("Enter N: ");
    scanf("%d", &n);

    if (n < 1 || n > 20)
    {
        printf("Enter N between 1 and 20.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        board[i] = -1;

    if (!solve(0))
        printf("No solution exists.\n");

    return 0;
}

