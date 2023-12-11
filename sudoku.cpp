# include <iostream>

int s[9][9][10];

const int z[9][9] = {
{9,0,0,0,6,3,0,5,0},
{0,0,2,0,0,1,0,9,0},
{0,0,4,9,0,0,7,0,1},
{0,0,6,0,1,0,0,8,0},
{0,0,0,3,0,6,0,0,0},
{0,1,0,0,8,0,9,0,0},
{7,0,9,0,0,5,8,0,0},
{0,4,0,8,0,0,2,0,0},
{0,3,0,1,4,0,0,0,9}
};

void read ()
{
    int i,j,k;
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            s[i][j][0] = z[i][j];

            for (k=1; k<10; k++) 
            {
                if (s[i][j][0] == 0)
                {
                    s[i][j][k] = k;
                }
                else 
                {
                    s[i][j][k] = 0;
                }
            }
        }
    }
}

void write (int st[9][9][10])
{
    int i,j,k;
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
    int i,j,l,m,n;
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

void check_third_dimension (int st[9][9][10])       // check if there is only one solution for s[i][j][0]
{
    int i,j,k,o;
    int winner;
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
            }
            if (o==1)
            {
                s[i][j][0] = winner;
            }
        }
    }
}

void check_rows_columns_square (int st[9][9][10])       // check if the number is present in row, column, square
{                                                   // dodelat
    int i,j,l,m,n;
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

rows_columns_square (s);
write (s);

check_third_dimension (s);
write (s);

std::cout << "**********************" << std::endl;
std::cout << std::endl;

for (int p=0; p<100; p++)
{
    rows_columns_square (s);
    check_third_dimension (s);
    write (s);
}


return 0;
}