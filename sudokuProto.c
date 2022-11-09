#include <stdio.h>
#include <conio.h> // _getch() and _kbhit()
#include <windows.h> // Sleep()

int numberValidityCheck();

int main()
{
    printf("Hello World!\n");

    //numbers for testing
    int numberGrid[4][4] = { 
        {1,3,2,4},
        {4,2,3,1},
        {3,4,1,2},
        {2,1,0,3} };

    //works
    //numberValidityCheck(numberGrid);

    /*
    //test print the numbers
    for (int i = 0; i < 4; ++i) {
        for (int x = 0; x < 4; ++x) {
            printf("%d ", numberGrid[i][x]);
        }
        printf("...\n");
    }
    */

    /*
    //test print the subgrid numbers
    for (int i = 0; i < 4; ++i) {
        for (int x = 0; x < 4; ++x) {
            printf("%d ", subgridNums[i][x]);
        }
        printf("...\n");
    }
    */

    //numberGrid testing position start
    int gridY = 1; //row
    int gridX = 2; //col

    int pointerNum = -1;
    int blinkCounter = 0;

    char pointerDir = '0';

    int running = 1;
    while (running == 1) {

        //test print the numbers
        for (int i = 0; i < 4; ++i) {
            printf("... ");
            for (int x = 0; x < 4; ++x) {
                printf("%d ", numberGrid[i][x]);
            }
            printf("...\n");
        }

        //so that you aren't overwriting anything on the first run
        if (pointerNum != -1)numberGrid[gridY][gridX] = pointerNum;

        pointerNum = numberGrid[gridY][gridX];

        //changes pointed number to 0 and back to original on alternating loops
        if (blinkCounter == 0) {
            numberGrid[gridY][gridX] = 0;
            blinkCounter++;
        }
        else {
            numberGrid[gridY][gridX] = pointerNum;
            blinkCounter--;
        }

        //check for directional inputs
        if (_kbhit()) {
            pointerDir = _getch();
            printf("%c\n", pointerDir);

            //have to return number to array so it doesn't leave a zero in its place
            if (blinkCounter == 1) {
                printf("blinkCounter was 1...\n");
                numberGrid[gridY][gridX] = pointerNum;
            }


            //wasd for directional inputs, e for selection
            int inputCleared = 0;
            switch (pointerDir) {
            case 'w':
                if (gridY != 0) {
                    printf("moving up...\n");
                    gridY--;
                }
                else {
                    printf("moving up, overflow...\n");
                    gridY = 3;
                }
                break;
            case 'd':
                if (gridX != 3) {
                    printf("moving right...\n");
                    gridX++;
                }
                else {
                    printf("moving right, overflow...\n");
                    gridX = 0;
                }
                break;
            case 's':
                if (gridY != 3) {
                    printf("moving down...\n");
                    gridY++;
                }
                else {
                    printf("moving down, overflow...\n");
                    gridY = 0;
                }
                break;
            case 'a':
                if (gridX != 0) {
                    printf("moving left...\n");
                    gridX--;
                }
                else {
                    printf("moving left, overflow...\n");
                    gridX = 3;
                }
                break;
            case 'e':
                //code for inputting numbers goes here
                while (inputCleared == 0) {
                    if (_kbhit()) {
                        pointerDir = _getch();
                        printf("%c\n", pointerDir);

                        //let's implement up right down left as 1 2 3 4 for now
                        switch (pointerDir) {
                        case 'w':
                            numberGrid[gridY][gridX] = 1;
                            break;
                        case 'd':
                            numberGrid[gridY][gridX] = 2;
                            break;
                        case 's':
                            numberGrid[gridY][gridX] = 3;
                            break;
                        case 'a':
                            numberGrid[gridY][gridX] = 4;
                            break;
                        case 'e':

                            break;
                        default:
                            break;
                        }
                        inputCleared = 1;
                    }
                }
                //after input, check if the game is won
                if (numberValidityCheck(numberGrid) == 0) {
                    printf("YOU WON!!!!!!!!!!!!!!!!!!!!!!\n");
                }
                break;
            default:
                break;
            }
            pointerNum = numberGrid[gridY][gridX]; //store pointed number at new location
        }


        printf("... ------- ...\n");
        Sleep(1000);
    }

    return 0;
}



int numberValidityCheck(int gridNums[4][4]) {
    int numVal = 0; //set to 1 on fail

    //make subgrids easier to manage for my peabrain
    int subgridNums[4][4] = { 
        {gridNums[0][0],gridNums[0][1],gridNums[1][0],gridNums[1][1]},
        {gridNums[0][2],gridNums[0][3],gridNums[1][2],gridNums[1][3]},
        {gridNums[2][0],gridNums[2][1],gridNums[3][0],gridNums[3][1]},
        {gridNums[2][2],gridNums[2][3],gridNums[3][2],gridNums[3][3]} };

    //compare numbers in rows
    //i=row, y=current number, x=number to compare against
    for (int i = 0; i < 4; ++i) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {

                if (gridNums[i][y] == gridNums[i][x] && y != x) {
                    printf("on row %d: %d.num = %d.num\n", i + 1, y + 1, x + 1);
                    numVal = 1;
                }
            }
        }
    }

    //compare numbers in columns
    //i=column, y=current number, x=number to compare against
    for (int i = 0; i < 4; ++i) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {

                if (gridNums[y][i] == gridNums[x][i] && y != x) {
                    printf("on column %d: %d.num = %d.num\n", i + 1, y + 1, x + 1);
                    numVal = 1;
                }
            }
        }
    }

    //compare numbers in subgrids
    //since subgrids were converted into easy form we can reuse this easy code
    //i=subgrid, y=current number, x=number to compare against
    for (int i = 0; i < 4; ++i) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {

                if (subgridNums[i][y] == subgridNums[i][x] && y != x) {
                    printf("on subgrid %d: %d.num = %d.num\n", i + 1, y + 1, x + 1);
                    numVal = 1;
                }
            }
        }
    }

    //sum up the numbers and see if the grid is full (1+2+3+4)*4=40
    int sum = 0;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            sum += gridNums[y][x];
        }
    }
    //printf("%d\n", sum); //for debugging
    if (sum != 40)numVal = 1;

    return numVal;
}
