# include <iostream>

int s[9][9][10];
int error_row = 888;
int error_column = 888;
int error_square_row = 888;
int error_square_column = 888;

// const int z[9][9] = {
// {9,0,0,0,6,3,0,5,0},
// {0,0,2,0,0,1,0,9,0},
// {0,0,4,9,0,0,7,0,1},
// {0,0,6,0,1,0,0,8,0},
// {0,0,0,3,0,6,0,0,0},
// {0,1,0,0,8,0,9,0,0},
// {7,0,9,0,0,5,8,0,0},
// {0,4,0,8,0,0,2,0,0},
// {0,3,0,1,4,0,0,0,9}
// };

const int z[9][9] = {
{0,1,0,6,0,0,9,0,0},
{0,0,0,0,3,0,0,0,1},
{9,0,8,1,7,4,5,0,0},
{0,0,1,8,0,0,0,7,4},
{0,0,0,0,0,0,0,0,0},
{5,6,0,0,0,7,1,0,0},
{0,0,9,7,4,6,8,0,5},
{6,0,0,0,9,0,0,0,0},
{0,0,7,0,0,2,0,3,0},
};

void read ()
{
    int row_index,col_index,up_index;
    for (row_index=0; row_index<9; row_index++) 
    {
        for (col_index=0; col_index<9; col_index++) 
        {
            s[row_index][col_index][0] = z[row_index][col_index];

            for (up_index=1; up_index<10; up_index++) 
            {
                if (s[row_index][col_index][0] == 0)
                {
                    s[row_index][col_index][up_index] = up_index;
                }
                else 
                {
                    s[row_index][col_index][up_index] = 0;
                }
            }
        }
    }
}

void write (int st[9][9][10])
{
    int row_index,col_index,up_index;
    for (row_index=0; row_index<9; row_index++) 
    {
        for (col_index=0; col_index<9; col_index++) 
        {
            for (up_index=0; up_index<10; up_index++) 
            {
                std::cout << s[row_index][col_index][up_index];
                if (up_index==0) {std::cout << "*";}
            }
            std::cout << " ";
            if (col_index==2 || col_index==5) {std::cout << "  ";}
        }
        std::cout << std::endl;
        if (row_index==2 || row_index==5) {std::cout << std::endl;}
    }
    std::cout << std::endl << std::endl << std::endl;
}

void rows_columns_square (int st[9][9][10])
{
    int row_index,col_index,l,m,n;
    for (row_index=0; row_index<9; row_index++) 
    {
        for (col_index=0; col_index<9; col_index++) 
        {
            if (s[row_index][col_index][0] != 0)            // if solution exists
            {
                for (l=0; l<9; l++)
                {
                    s[l][col_index][s[row_index][col_index][0]] = 0;     // delete the number in j column
                    s[row_index][l][s[row_index][col_index][0]] = 0;     // delete the number in i row
                }

                for (m=0; m<3; m++)
                {
                    for (n=0; n<3; n++)
                    {
                        s[(row_index/3)*3+m][(col_index/3)*3+n][s[row_index][col_index][0]] = 0;    // delete the number in square
                    }
                }
            }
        }
    }
}

void check_third_dimension (int st[9][9][10])       // check if there is only one solution for s[i][j][0]
{
    int i,j,k,o,winner;
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            o=0;
            for (k=1; k<10; k++) 
            {
                if ((s[i][j][k] != 0) && (s[i][j][0]==0))
                {
                    o++;
                    winner = s[i][j][k];
                }
                if (s[i][j][0] != 0)
                {
                    s[i][j][k] = 0;     // if the sulution exists s[i][j][0] != 0, erase all other posible solutions 
                }
            }
            if (o==1)
            {
                s[i][j][0] = winner;
            }
        }
    }
}

// check if the number is present in row, column or square.
// If the number is present in the row, column or square only onece, it is the solution.
// Even if there are more possibilities for given field.
void check_rows_columns_square (int st[9][9][10])
{
    int i,j,k,l,m,n,n_in_row,n_in_column,n_in_square;
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            for (k=1; k<10; k++) 
            {
                if ((s[i][j][k] != 0) && (s[i][j][0] == 0))
                {
                    n_in_row = 0;
                    n_in_column = 0;
                    n_in_square = 0;
                    for (l=0; l<9; l++)
                    {
                        if (s[i][l][k] !=0)
                        {
                            n_in_row++;
                        }
                        if (s[l][j][k] !=0)
                        {
                            n_in_column++;
                        }                     
                    }
                    for (m=0; m<3; m++)
                    {
                        for (n=0; n<3; n++)
                        {
                            if (s[(i/3)*3+m][(j/3)*3+n][k] != 0)
                            {
                                n_in_square++;
                            }
                        }
                    }

                    if (n_in_row == 1 || n_in_column == 1 || n_in_square == 1 )
                    {
                        s[i][j][0] = s[i][j][k];
                    }
                }
            }
        }
    }
}

// check if the solution comply with sudoku rules
void check_one_to_nine (int st[9][9][10])
{
    int i,j,k,l,m,n,sum_row,sum_column,sum_square;
    for (i=0; i<9; i++) 
    {
        sum_row = 0;
        sum_column = 0;
        for (j=0; j<9; j++) 
        {
            sum_row = sum_row + s[i][j][0];
            sum_column = sum_column + s[j][i][0];       
        }

        if (sum_row != 45)
        {
            error_row = i;
        }
        if (sum_column != 45)
        {
            error_column = i;
        }
    }
    
    for (k=0; k<3; k++)
    {
        for (l=0; l<3; l++)
        {
            sum_square = 0;
            for (m=0; m<3; m++)
            {
                for (n=0; n<3; n++)
                    {
                        sum_square = sum_square + s[m+3*k][n+3*l][0];    // delete the number in square
                    }
            }
            if (sum_square != 45)
            {
                error_square_row = k;
                error_square_column = l;
            }
        }    
    }    
    
}

int main () {

read ();
write (s);



// s[0][1][0] = 7;

std::cout << "**********************" << std::endl;
std::cout << std::endl;

std::cout << s[2][0][0] << std::endl;

for (int p=0; p<20; p++)
{
    rows_columns_square (s);
    check_rows_columns_square (s);
    check_third_dimension (s);
    write (s);
}



check_one_to_nine (s);
std::cout << "888 no error, error_row = " << error_row << std::endl;
std::cout << "888 no error, error_column = " << error_column << std::endl;
std::cout << "888 no error, error_square_row = " << error_square_row << std::endl;
std::cout << "888 no error, error_square_column = " << error_square_column << std::endl;

return 0;
}