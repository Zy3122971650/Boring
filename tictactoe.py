def whoIsWiner(chess):
    if chess == 'O':
        print("玩家1胜利")
    elif chess == 'X':
        print('玩家2胜利')


def iSContinueGame(flag, chess_board):
    if flag == 0:
        print('游戏结束')
        input('任意键继续')
        return 1
    return 0


def judgeResult(chess_board):
    flag = 0  # 代表游戏是否还可以继续  0 代表不可以（赢了或者和棋了）1代表还未和棋或赢
    for m in range(3):
        if chess_board[m][0] == chess_board[m][1] == chess_board[m][2] and chess_board[m][2] != 0:
            whoIsWiner(chess_board[m][0])
            flag = 0
            break
        elif chess_board[0][m] == chess_board[1][m] == chess_board[2][m] and chess_board[m][2] != 0:
            whoIsWiner(chess_board[m][0])
            flag = 0
            break
        else:
            flag = 1
    if flag == 1:  # 在上一种赢法下游戏还没有结束可以继续 反之游戏结束
        if chess_board[0][0] == chess_board[1][1] == chess_board[2][2] and chess_board[m][2] != 0:
            whoIsWiner(chess_board[m][0])
            flag = 0
        elif chess_board[0][2] == chess_board[1][1] == chess_board[2][0] and chess_board[m][2] != 0:
            whoIsWiner(chess_board[m][0])
            flag = 0
    flag_init_chess_board = iSContinueGame(flag, chess_board)
    if flag == 1:  # 在得不到输赢的情况下检查是否已经和棋
        for row in chess_board:
            for chess in row:
                if chess == 0:
                    flag = 1
        flag_init_chess_board = iSContinueGame(flag, chess_board)
    return flag_init_chess_board


def isInputLegal(num):
    try:
        num = int(num)
    except:
        return 0
    if 0 < num <= 13:
        return 1
    elif 21 <= num <= 23:
        return 1
    elif 31 <= num <= 33:
        return 1
    return 0


def chess_board_print(chess_board):
    for row in chess_board:
        for chess in row:
            if chess != 0:
                print(chess, end=' ')
            else:
                print("？", end=" ")
        print('\n')


def set_chess_location(x, y, chess_board, user):
    if user == 0:
        chess_mark = 'O'
    elif user == 1:
        chess_mark = 'X'
    if chess_board[x][y] == 'X' or chess_board[x][y] == 'O':
        return 0
    chess_board[x][y] = chess_mark
    return 1


def get_chess_location(rawDate):
    temp = rawDate
    if temp <= 9:  # 顺数坐标
        if temp/3 <= 1:  # 第一行
            m = 0
            n = temp % 3
            n -= 1
        elif 1 < temp/3 <= 2:
            m = 1
            n = temp % 3
            n -= 1
        elif 2 < temp/3 <= 3:
            m = 2
            n = temp % 3
            n -= 1
    else:
        m, n = tuple(str(temp))
        m = int(m)-1  # 为数组做的处理
        n = int(n)-1
    return (m, n)


def main():
    chess_board = [[0]*3 for i in range(3)]
    user_flage = 0
    print("输入你要落字的位置可以是顺数位置也可以是坐标位置\n，横坐标\
            ，纵坐标\n例如第二行第三列表示为23", end='\r')

    while(True):
        chess_board_print(chess_board)
        temp = input('玩家{}位置是：'.format(user_flage+1))
        if isInputLegal(temp) == 0:
            print("请检查输入是否合法", end='\r')
            continue

        temp = int(temp)
        m, n = get_chess_location(temp)
        state = set_chess_location(m, n, chess_board, user_flage)#返回棋子安放信息，是否下在了同一位置
        if user_flage == 1 and state == 1:
            user_flage = 0
        elif user_flage == 0 and state == 1:
            user_flage = 1
        else:
            print('输入位置已存在棋子，重新落子', end='\r')
        if judgeResult(chess_board) == 1:
            chess_board = [[0]*3 for i in range(3)]


if __name__ == "__main__":
    main()
