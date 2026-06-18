#include <iostream>

using namespace std;

int boardsize;
int cellsize;

const int MAX_SIZE = 25; 
int board[MAX_SIZE][MAX_SIZE];
int takenrow[MAX_SIZE];
int takencol[MAX_SIZE];
int takengrid[MAX_SIZE][MAX_SIZE];

bool check(int ch, int row, int col) {
    for(int i = 0; i < boardsize; i++) {
        if(i != col && board[row][i] == ch) return false;
    }
    
    for(int i = 0; i < boardsize; i++) {
        if(i != row && board[i][col] == ch) return false;
    }
    
    int str = (row / cellsize) * cellsize;
    int stc = (col / cellsize) * cellsize;
    
    for(int dx = 0; dx < cellsize; dx++) {
        for(int dy = 0; dy < cellsize; dy++) {
            int checkx = str + dx;
            int checky = stc + dy;
            
            if(checkx == row && checky == col) continue;
            if(board[checkx][checky] == ch) return false;
        }
    }
    return true;
}

int getchoices(int row, int col) {
    int taken = (takenrow[row] | takencol[col] | takengrid[row / cellsize][col / cellsize]);
    int nottaken = ((1 << (boardsize + 1)) - 1) ^ taken;
    if(nottaken & 1) nottaken ^= 1; // Clear the 0th bit
    return nottaken;
}

void makemove(int ch, int row, int col) {
    board[row][col] = ch;
    takenrow[row] ^= (1 << ch);
    takencol[col] ^= (1 << ch);
    takengrid[row / cellsize][col / cellsize] ^= (1 << ch);
}

void revertmove(int ch, int row, int col) {
    board[row][col] = 0;
    takenrow[row] ^= (1 << ch);
    takencol[col] ^= (1 << ch);
    takengrid[row / cellsize][col / cellsize] ^= (1 << ch);
}

void rec(int row, int col) {
    if(col == boardsize) {
        rec(row + 1, 0);
        return;
    }
    if(row == boardsize) {
        for(int i = 0; i < boardsize; i++) {
            for(int j = 0; j < boardsize; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return; 
    }
    
    if(board[row][col] == 0) {
        int chmask = getchoices(row, col);
        for(int ch = 1; ch <= boardsize; ch++) {
            if(chmask & (1 << ch)) {
                makemove(ch, row, col);
                rec(row, col + 1);
                revertmove(ch, row, col);
            }
        }
    } else {
        if(check(board[row][col], row, col)) {
            rec(row, col + 1);
        }
    }
}

void solve() {
    cin >> boardsize >> cellsize; 
    
    for(int i = 0; i < boardsize; i++) {
        for(int j = 0; j < boardsize; j++) {
            int ch;
            cin >> ch;
            if (ch != 0) {
                makemove(ch, i, j);
            } else {
                board[i][j] = 0;
            }
        }
    }
    rec(0, 0);
}

signed main() {
    // Opt-in for faster I/O
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    solve();
    return 0;
}
