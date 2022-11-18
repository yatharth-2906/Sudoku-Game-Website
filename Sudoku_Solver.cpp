#include<iostream>
#include<cmath>

using namespace std;

bool Sudoku_Solver(int board[9][9], int n, int i, int j);

bool Check_Validation(int board[9][9], int n, int i, int j, int num);

void Display_Board(int board[9][9], int n);

int main(void)
{
    int n = 9;
    // cout<<"Enter The Board Size: ";
    // cin>>n;
    int board[9][9] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0} };
    
    if(Sudoku_Solver(board,n,0,0) == false)
        cout<<"Sorry, the given Sudoku Puzzle can't be solved."<<endl;
    
    return 0;
}

bool Sudoku_Solver(int board[9][9], int n, int i, int j)
{
    if(i == n)
    {
        Display_Board(board,n);
        return true;
    }

    else if(j == n)
    {
        return Sudoku_Solver(board,n,i+1,0);
    }

    else if (board[i][j] > 0)
        return Sudoku_Solver(board,n,i,j+1);

    for(int num = 1; num <= 9; num++)
    {
        if(Check_Validation(board,n,i,j,num) == true)
        {
            board[i][j] = num;
            bool var = Sudoku_Solver(board,n,i,j+1);
            if(var == true)
                return true;
            else
                board[i][j] = 0;
        }
    }

    return false;
}

bool Check_Validation(int board[9][9], int n, int i, int j, int num)
{
    int row = 0, col = 0;

    // Column Check
    for(row = 0;  row < n; row++)
    {
        if(board[row][j] == num)
            return false;
    }

    // Row Check
    for(col = 0;  col < n; col++)
    {
        if(board[i][col] == num)
            return false;
    }

    // Sub-Matrix Check
    int sqn = sqrt(n);
    row = (i / (sqn)) * sqn;
    col = (j / (sqn)) * sqn;
    for(i=0; i<sqn; i++)
    {
        for(j=0; j<sqn; j++)
        {
            if(board[i+row][j+col] == num)
                return false;
        }
    }

    return true;
}

void Display_Board(int board[9][9], int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}