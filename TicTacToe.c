#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>

int board[10] = {2,2,2,2,2,2,2,2,2,2};
int turn = 1,flag = 0;
int player,comp;

void set(int n);
void start_game();
void check_draw();
void draw_board();
void player_first();
void put_X_O(char ch,int pos);
COORD coord= {0,0};

void console_position(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
    system("cls");
//    printf("\x1b[1;32m"); // Green
//    printf("\x1b[1;31m"); // Red
//    printf("\x1b[1;33m"); // Yellow
    printf("\x1b[1;34m"); // Blue
//    printf("\x1b[1;35m"); // Purple
//    printf("\x1b[1;36m"); // Cyan
//    printf("\x1b[0m");    // Reset color

    console_position(30,6);  printf("#################  Katagolla  ##################");
    console_position(30,7);  printf("#                                              #");
    console_position(30,8);  printf("#                                              #");
    console_position(30,9);  printf("#     Press X or O to choose your character    #");
    console_position(30,10); printf("#                                              #");
    console_position(30,11); printf("#     Press any other key to exit!             #");
    console_position(30,12); printf("#                                              #");
    console_position(30,13); printf("#                                              #");
    console_position(30,14); printf("#                                              #");
    console_position(30,15); printf("#                                              #");
    console_position(30,16); printf("#                                              #");
    console_position(30,17); printf("#################  Katagolla  ##################");
    console_position(30,14); printf("#");

    console_position(30,14); printf("# \x1b[1;31m          Enter your choice:> ");
    printf("\x1b[1;33m"); /// Green

    char choice;
    scanf("%c",&choice);
    turn = 1;
    if(choice=='X' || choice=='x')
    {
        system("cls");
        player = 1;
        comp = 0;
        player_first();
    }
    else if(choice=='O' || choice=='o')
    {
        system("cls");
        player = 0;
        comp = 1;
        start_game();
    }
    else exit(0);
}

int make2()
{
    if(board[5] == 2)
        return 5;
    if(board[2] == 2)
        return 2;
    if(board[4] == 2)
        return 4;
    if(board[6] == 2)
        return 6;
    if(board[8] == 2)
        return 8;
    return 0;
}

int make4()
{
    if(board[1] == 2)
        return 1;
    if(board[3] == 2)
        return 3;
    if(board[7] == 2)
        return 7;
    if(board[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{

    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;
    else
        check_val = 50;

    i = 1;
    while(i<=9)
    {
        if(board[i] * board[i+1] * board[i+2] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+1] == 2)
                return i+1;
            if(board[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)
    {
        if(board[i] * board[i+3] * board[i+6] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+3] == 2)
                return i+3;
            if(board[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(board[1] * board[5] * board[9] == check_val)
    {
        if(board[1] == 2)
            return 1;
        if(board[5] == 2)
            return 5;
        if(board[9] == 2)
            return 9;
    }

    if(board[3] * board[5] * board[7] == check_val)
    {
        if(board[3] == 2)
            return 3;
        if(board[5] == 2)
            return 5;
        if(board[7] == 2)
            return 7;
    }
    return 0;
}

void set(int n)
{
    if(turn % 2)
        board[n] = 3;
    else
        board[n] = 5;
    turn++;
}

void player_first()
{
    int pos;

    check_draw();
    draw_board();
    console_position(25,20);
    printf("Choose position to put your character :> ");
    scanf("%d",&pos);

    if(board[pos] != 2)
        player_first();

    if(pos == posswin(player))
    {
        system("cls");
        set(pos);
        draw_board();
        printf("\x1b[1;32m"); /// Green
        console_position(30,22);
        printf("*** You Wins ***");
        console_position(30,24);
        printf("Thank you for playing!!!");
        console_position(30,25);
        printf("Press any key to exit\n");
        getch();
        exit(0);
    }

    set(pos);
    draw_board();
    start_game();
}

void start_game()
{
    if(posswin(comp))
    {
        set(posswin(comp));
        flag = 1;
    }
    else if(posswin(player))
        set(posswin(player));
    else if(make2())
        set(make2());
    else
        set(make4());
    draw_board();

    if(flag)
    {
        system("cls");
        draw_board();
        printf("\x1b[1;31m"); ///Red
        console_position(30,22);
        printf("*** Computer Wins ***");
        console_position(30,24);
        printf("Thank you for playing!!!");
        console_position(30,25);
        printf("Press any key to exit\n");
        getch();
        exit(0);
    }
    else
        player_first();
}

void check_draw()
{
    if(turn > 9)
    {
        system("cls");
        draw_board();
        printf("\x1b[1;35m"); ///Purple
        console_position(30,22);
        printf("*** Game Drawn ***");
        console_position(30,24);
        printf("Thank you for playing!!!");
        console_position(30,25);
        printf("Press any key to exit\n");
        getch();
        exit(0);
    }
}

void draw_board()
{
    int j;

    for(j=9; j<17; j++)
    {
        console_position(35,j);
        printf("|       |");
    }
    console_position(28,11);
    printf("-----------------------");
    console_position(28,14);
    printf("-----------------------");

    for(j=1; j<10; j++)
    {
        if(board[j] == 3)
            put_X_O('X',j);
        else if(board[j] == 5)
            put_X_O('O',j);
    }
}

void put_X_O(char ch,int pos)
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    console_position(x,y);
    printf("%c",ch);
}

