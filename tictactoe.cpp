#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *translateLocation(int rawLocation)
{
    int m, n;
    float temp;
    static int x_y[2];
    temp = (float)rawLocation/3;
    /*这里所作的减1操作均是把习惯上1为下标表达转化成数组上0为下标的表达*/
    if (rawLocation <= 9)
    {
        if (temp <= 1)
        {
            m = 0;
        }
        else if ((1 < temp) && (temp <= 2))
        {
            m = 1;
        }
        else if ((2 < temp) && (temp <= 3))
        {
            m = 2;
        };
        n = rawLocation % 3;
        if (n == 0){
            n = 2;
        }
        else
        {
            n -= 1;
        }

    }
    else
    {
        n = rawLocation % 10;
        m = (rawLocation - n) / 10;
        n -= 1;
        m -= 1;
    };
    x_y[0] = m;
    x_y[1] = n;
    return x_y;
};
int set_chess_localtion(int rawLocation, int user_flage, int chess_board[][3])
{
    int x, y, *x_y;
    int chess_mark;
    x_y = translateLocation(rawLocation);
    x = *(x_y + 0);
    y = *(x_y + 1);
    if (user_flage == 0)
    {
        chess_mark = 'O';
    }
    else if (user_flage == 1)
    {
        chess_mark = 'X';
    };
    if (chess_board[x][y] == 'X' || chess_board[x][y] == 'O')
    {
        return 0;
    }
    printf("玩家%d已落子在行%d列%d\n",user_flage+1,x+1,y+1);
    chess_board[x][y] = chess_mark;

    return 1;
};
void whoIsWiner(int chess)
{
    if (chess == 'O')
    {
        printf("玩家1胜利\n");
    }
    else if (chess == 'X')
    {
        printf("玩家2胜利\n");
    }
};

int judgeResult(int chess_board[][3])
{
    int go_ahead_flag, isGameOver;
    for (int i = 0; i < 3; i++)
    {
        if ((chess_board[i][0] == chess_board[i][1]) && (chess_board[i][1] == chess_board[i][2]) && chess_board[i][1] != '?')
        {
            whoIsWiner(chess_board[i][0]);
            go_ahead_flag = 0;
            break;
        }
        else if ((chess_board[0][i] == chess_board[1][i]) && (chess_board[1][i] == chess_board[2][i]) && chess_board[1][i] != '?')
        {
            whoIsWiner(chess_board[0][i]);
            go_ahead_flag = 0;
            break;
        }
        else
        {
            go_ahead_flag = 1;
        }
    }
    if (go_ahead_flag == 1)
    {
        if ((chess_board[0][0] == chess_board[1][1]) && (chess_board[1][1] == chess_board[2][2]) && chess_board[1][1] != '?')
        {
            whoIsWiner(chess_board[1][1]);
            go_ahead_flag = 0;
        }
        else if ((chess_board[0][2] == chess_board[1][1]) && (chess_board[1][1] == chess_board[2][0]) && chess_board[1][1] != '?')
        {
            whoIsWiner(chess_board[1][1]);
            go_ahead_flag = 0;
        }
    }
    if (go_ahead_flag == 1)
    {
        go_ahead_flag = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (chess_board[i][j] == '?')
                {
                    go_ahead_flag = 1;
                    break;
                }
            }
            if (go_ahead_flag == 1)
            {
                break;
            }
        }
    };
    isGameOver = !(go_ahead_flag);
    return isGameOver;
};

int isInputLegal(int input)
{
    if (0 < input && input <= 13)
    {
        return 1;
    }
    else if (21 <= input && input <= 23)
    {
        return 1;
    }
    else if (31 <= input && input <= 33)
    {
        return 1;
    }
    return 0;
}

void chess_board_print(int chess_board[3][3]) /*让棋盘显示出来，好看*/
{
    printf("%c|%c|%c\n%c|%c|%c\n%c|%c|%c\n",
           chess_board[0][0],
           chess_board[0][1],
           chess_board[0][2],
           chess_board[1][0],
           chess_board[1][1],
           chess_board[1][2],
           chess_board[2][0],
           chess_board[2][1],
           chess_board[2][2]);
}

int *get_how_to_game()
{
    int robot_flag, isRobotFlagLegal, isDiffcultFlagLegal, diffcult_flag;
    static int temp[2];
    while (1)
    {
        printf("输入1选择玩家对战，输入2选择人机对战\n");
        isRobotFlagLegal = scanf("%d", &robot_flag);
        if (isRobotFlagLegal == 0)
        {
            continue;
        }
        else
        {
            robot_flag -= 1; /*处理一下使得1为人机对战，0为玩家对战*/
            if (robot_flag == 1)
            {
                printf("输入1选择简单模式，2为困难模式");
                isDiffcultFlagLegal = scanf("%d", &diffcult_flag);
                if (isDiffcultFlagLegal != 0)
                {
                    if (diffcult_flag == 1 || diffcult_flag == 2)
                    {
                        break;
                    }
                }
            }
            else if (robot_flag == 0)
            {
                break;
            }
        }
    };
    temp[0] = robot_flag;
    temp[1] = diffcult_flag;
    return temp;
}

int get_where_to_go(int robot_flag, int user_flage)
{
    int where_to_go, isOneOr2;
    int x, y,temp1,temp2;
    while (1)
    {
        if ((robot_flag == 1 && user_flage == 0) || (robot_flag == 0))
        {
            printf("玩家%d,使用%c，你选择的位置是:\n",
                   user_flage + 1,
                   user_flage == 0 ? 'O' : 'X');
            isOneOr2 = scanf("%d", &where_to_go);
            if (isInputLegal(where_to_go) == 1)
            {
                break;
            }
            printf("请检查输入是否合法\n");
        }
        else
        {
            /*Easy机器人下棋*/
            srand((unsigned)time(NULL));
            temp1 = rand() % 3;
            temp2 = rand() % 3;
            temp1 == 0?x = 3:(x = temp1);
            temp2 == 0?y = 3:(y = temp2);
            where_to_go = (x * 10) + y; /*对数据进行统一处理*/
            break;
        }
    };
    return where_to_go;
}

void game(int *game_model, int chess_board[][3])
{
    int user_flage = 0;
    int robot_flag, diffcult_flag, isOneOr2, set_chess_state;
    int where_to_go;
    int black_hole;
    robot_flag = *(game_model + 0);
    diffcult_flag = *(game_model + 1);
    while (1)
    {
        where_to_go = get_where_to_go(robot_flag, user_flage);
        set_chess_state = set_chess_localtion(where_to_go, user_flage, chess_board);
        if (set_chess_state == 1)
        {
            user_flage = !(user_flage);
            chess_board_print(chess_board);
        }
        else
        {   
            if (robot_flag == 1 && user_flage == 1){
                continue;
            }
            printf("该位置已经存在落子，请重新选取位置");
        };
        if (judgeResult(chess_board) == 1)
        {
            printf("游戏结束\n任意字符回车\n开始下一局");
            scanf("%d",&black_hole);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    chess_board[i][j] = '?';
                }
            };
            chess_board_print(chess_board);
        }
    }
};
int main()
{
    int chess_board[3][3] = {
        '?',
        '?',
        '?',
        '?',
        '?',
        '?',
        '?',
        '?',
        '?',
    };
    int *game_model;
    game_model = get_how_to_game();
    /*    printf("%d,%d",*(game_model+0),*(game_model+1));  */
    chess_board_print(chess_board);
    printf("输入你要落字的位置可以是顺数位置也可以是坐标位置\n，行\
            ，列\n例如第二行第三列表示为23\n");
    game(game_model, chess_board);
}
