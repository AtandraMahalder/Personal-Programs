//Atandra Mahalder
//10/05/2020
//Sudoku Solver using backtracking

#include<bits/stdc++.h>
using namespace std;

int grid[9][9];
bool checkR[9][9];
bool checkC[9][9];
bool checkS[9][9];

bool solve(int r, int c){

 if(c==9){
    r++;
    c = 0;
 }

 if(r==9) return true;

 if(grid[r][c]) return solve(r, c+1);

 for(int i=1;i<10;++i){
    if(checkR[i-1][r] && checkC[i-1][c] && checkS[i-1][3*(r/3)+c/3]){
        grid[r][c] = i;
        checkR[i-1][r] = false;
        checkC[i-1][c] = false;
        checkS[i-1][3*(r/3)+c/3] = false;
        if(solve(r, c+1))
            return true;
        checkR[i-1][r] = true;
        checkC[i-1][c] = true;
        checkS[i-1][3*(r/3)+c/3] = true;
   }
 }
 grid[r][c] = 0;

 return false;
}

int main(){
 cout<<"Enter your puzzle (enter 0 for empty spot):\n\n";
 for(int i=0;i<9;++i)
    for(int j=0;j<9;++j)
        cin>>grid[i][j];

 for(int i=0;i<9;++i)
    for(int j=0;j<9;++j){
        checkR[i][j] = true;
        checkC[i][j] = true;
        checkS[i][j] = true;
    }

 for(int i=0;i<9;++i)
    for(int j=0;j<9;++j)
        if(grid[i][j]){
            checkR[grid[i][j]-1][i] = false;
            checkC[grid[i][j]-1][j] = false;
            checkS[grid[i][j]-1][3*(i/3)+j/3] = false;
        }

 solve(0,0);

 cout<<"\nThe solution to the given sudoku is:\n\n";

 for(int i=0;i<9;++i){
    for(int j=0;j<9;++j)
        cout<<grid[i][j]<<" ";
    cout<<"\n";
 }

 return 0;
}
