#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Вывод текущего состояния доски на экран.
string board_now(vector<int>& bo, int& r)
{
    string board_row = "";
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < bo.at(i); ++j)
            board_row += "* ";
        board_row += "\n";
    }
    return board_row;
}

int main()
{
    //Приветствие пользователя, настройки игры.
    int rows = 0, row, num, empty_rows = 0, str_1 = 0, str_2 = 0, str = 0;
    vector<int> board;
    cout << "Hello! Welcome to NIM-game! Let's play!" << endl;
    cout << "How many rows will we have?" << endl;
    cin >> rows;
    cout << "Nice! Then, please, enter the number of coins in each row." << endl;
    for (int i = 0; i < rows; i++)
    {
        int number;
        cin >> number;
        board.push_back(number);
    }
    cout << "Here's your beginning board." << endl;
    cout << board_now(board, rows);
    cout << "Very good. Here's the short list of rules:" << endl;
    cout << "When it's your turn, first enter the number of row you want to take coins from.\n"
        << "Then enter how many coins you want to take.\n"
        << "Please, remember: if you want to exit the game, enter '0 0'.\n"
        << "If you want to return to game settings, enter -1 0." << endl;
    cout << "Now it's time to play! Let's begin!" << endl;
    //Определение очередности.
    cout << "Who will move first? (Type 'H' for 'human' and 'C' for computer)." << endl;
    char turn;
    cin >> turn;

    //Начало игры.
    bool game = true;
    while (game)
    {
        //Выбор, кто ходит.
        switch (turn) {
        case 'H':
            //Ход пользователя.
            cout << "Your move." << endl;
            cin >> row >> num;
            //При вводе 0 0 выход из игры.
            if (row == 0 && num == 0){
                cout << "See ya later!" << endl;
                game = false;
                break;
            }
            //Некорректный ввод.
            if (row <= 0 || num <= 0){
                cout << "Sorry, incorrect enter." << endl;
                game = false;
                break;
            }
            cout << "You took " << num << " coins from " << row << " row." << endl;
            //Забираем больше, чем можем.
            if (board.at(row - 1) - num < 0){
                cout << "Sorry, you want to take more than you can." << endl;
                game = false;
                break;
            }
            board.at(row - 1) -= num;
            if (board.at(row - 1) == 0){
                empty_rows += 1;
            }
            if (empty_rows == rows){
                cout << "Congrats, you win!" << endl;
                game = false;
                break;
            }
            cout << board_now(board, rows);
            turn = 'C';
            break;
        case 'C':
            //Ход компьютера.
            //Если осталось больше двух непустых строк, забираем все монетки из одной из них.
            if ((rows - empty_rows) > 2){
                for (int i = 0; i < rows; i++)
                    if (board.at(i) > 0){
                        row = i + 1;
                        num = board.at(i);
                        break;
                    }
            }
            //Если осталось только две непустые строки, каждым ходом стараемся сделать так, чтобы они стали равны.
            else if ((rows - empty_rows) == 2){
                //Если мы не знаем номера этих строк, определяем их.
                if (str_1 == 0 && str_2 == 0){
                    for (int i = 0; i < rows; ++i)
                    if (board.at(i) > 0){
                        if (str_1 == 0){
                            str_1 = i + 1;
                        }
                        else str_2 = i + 1;
                    }
                }
                //Если знаем номера этих строк, сравниваем их длины.
                //Из большей строки вычитаем разницу между длинами строк.
                if (board.at(str_1 - 1) < board.at(str_2 - 1)){
                    row = str_2;
                    num = board.at(str_2 - 1) - board.at(str_1 - 1);
                }
                else if (board.at(str_1 - 1) > board.at(str_2 - 1)){
                    row = str_1;
                    num = board.at(str_1 - 1) - board.at(str_2 - 1);
                }
                //Если строки одинаковы по длине,
                //возьмем из первой строки 1 монетку, потому что что-то нужно взять).
                else{
                    row = str_1;
                    num = 1;
                }
            }
            else {
                if (str == 0)
                    for (int i = 0; i < rows; ++i)
                        if (board.at(i) > 0)
                            str = i + 1;
                row = str;
                num = board.at(str - 1);
            }
            cout << "I took " << num << " coins from " << row << " row." << endl;
            board.at(row - 1) -= num;
            if (board.at(row - 1) == 0){
                empty_rows += 1;
            }
            if (empty_rows == rows){
                cout << "You lose!" << endl;
                game = false;
                break;
            }
            cout << board_now(board, rows);
            turn = 'H';
            break;
        default:
            cout << "Sorry, try again." << endl;
            game = false;
            break;
        }
    }
}