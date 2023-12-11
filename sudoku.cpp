# include <iostream>

int s[9][9][10];
int i,j,k,l,m,n;
const int z[9][9] = {
    {0,0,0,0,0,0,3,9,6},
    {3,0,0,0,0,8,2,0,0},
    {0,0,0,1,0,6,4,0,8},
    {5,9,0,0,0,1,0,0,0},
    {0,1,0,5,2,7,0,8,0},
    {0,0,0,4,0,0,0,3,1},
    {1,0,4,7,0,2,0,0,0},
    {0,0,7,8,0,0,0,0,3},
    {9,2,8,0,0,0,0,0,0}
};

void read ()
{
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            s[i][j][0] = z[i][j];

            for (k=1; k<10; k++) 
            {
                s[i][j][k] = k;
            }
        }
    }
}

void write (int st[9][9][10])
{
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            for (k=0; k<10; k++) 
            {
                std::cout << s[i][j][k];
                if (k==0) {std::cout << "*";}
            }
            std::cout << " ";
            if (j==2 || j==5) {std::cout << "  ";}
        }
        std::cout << std::endl;
        if (i==2 || i==5) {std::cout << std::endl;}
    }
    std::cout << std::endl << std::endl << std::endl;
}

void rows_columns_square (int st[9][9][10])
{
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            if (s[i][j][0] != 0)
            {
                for (l=0; l<9; l++)
                {
                    s[l][j][s[i][j][0]] = 0;     // delete the number in j column
                    s[i][l][s[i][j][0]] = 0;     // delete the number in i row
                }

                for (m=0; m<3; m++)
                {
                    for (n=0; n<3; n++)
                    {
                        s[(i/3)*3+m][(j/3)*3+n][s[i][j][0]] = 0;    // delete the number in square
                    }
                }
            }
        }
    }
}

int main () {

read ();
write (s);

rows_columns (s);
write (s);

return 0;
}