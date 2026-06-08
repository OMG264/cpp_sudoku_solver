#include<bits/stdc++.h>
using namespace std;

const int boardsize = 4;
const int cellsize = 2;
int board[boardsize][boardsize];
int takenrow[boardsize];
int takencol[boardsize];
int takengrid[cellsize][cellsize];
bool check(int ch, int row, int col)
{
    // check in row
    for(int i = 0; i < boardsize; i++)
    {
        if(i != col && board[row][i] == ch)
        {
            return false;
        }
    }
    
    // check in column
    for(int i = 0; i < boardsize; i++)
    {
        if(i != row && board[i][col] == ch)
        {
            return false;
        }
    }
    
    // check in square
    int str = (row / cellsize) * cellsize;
    int stc = (col / cellsize) * cellsize;
    
    for(int dx = 0; dx < cellsize; dx++)
    {
        for(int dy = 0; dy < cellsize; dy++)
        {
            int checkx = str + dx;
            int checky = stc + dy;

            
            if(checkx == row && checky == col) continue;
            if(board[checkx][checky] == ch) return false;
        }
    }
    return true;
}
int getchoices(int row,int col)
{
    int taken = (takenrow[row]|takencol[col]|takengrid[row/cellsize][col/cellsize]);
    int nottaken = ((1<<(boardsize+1))-1)^taken;
    if(nottaken&1)nottaken^=1;
    return nottaken;
}
int makemove(int ch,int row,int col)
{
    board[row][col]=ch;
    takenrow[row]^=(1<<ch);
    takencol[col]^=(1<<ch);
    takengrid[row/cellsize][col/cellsize]^=(1<<ch);
}
int revertmove(int ch,int row,int col)
{
    board[row][col]=0;
    takenrow[row]^=(1<<ch);
    takencol[col]^=(1<<ch);
    takengrid[row/cellsize][col/cellsize]^=(1<<ch);
}
void rec(int row, int col)
{
    if(col == boardsize)
    {
        rec(row + 1, 0);
        return;
    }
    if(row == boardsize)
    {
        // base case
        for(int i = 0; i < boardsize; i++)
        {
            for(int j = 0; j < boardsize; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }
    if(board[row][col] == 0)
    {
        int chmask = getchoices(row,col);
        for(int ch = 1; ch <= boardsize; ch++)
        {
            if(chmask&(1<<ch))
            {
                makemove(ch,row,col);
                rec(row, col + 1);
                makemove(0,row,col);
            }
        }
    }
    else
    {
        if(check(board[row][col], row, col))
        {
            rec(row, col + 1);
        }
    }
}

void solve()
{
    for(int i = 0; i < boardsize; i++)
    {
        for(int j = 0; j < boardsize; j++)
        {
            int ch;
            cin >> ch;
            makemove(ch,i,j);
        }
    }
    rec(0, 0);
}

signed main()
{
    solve();
    return 0;
}