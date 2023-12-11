# include <iostream>

int s[9][9][10];
int i,j,k,l;
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
            std::cout << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void columns (int st[9][9][10])
{
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            if (s[i][j][0] != 0)
            {
                for (l=0; l<9; l++)
                {
                    s[i][l][s[i][j][0]] = 0;
                }
            }
        }
    }
}

int main () {

read ();
write (s);

columns (s);
write (s);

return 0;
}