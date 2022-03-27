#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <fstream>      
#include <vector>
#include <algorithm>    /* std::sort */

using namespace std;
struct vertical{
    string Line1, Line2, Line3, Line4;
};

struct cell{
    string UpperHori;
    string BottomHori;
    vertical VerLine;
    char figure;
};



/* Đây là khung sườn đại khái (chưa đầy đủ) của Product, căn theo khung này và thêm mắm dặm muối
--Tách nhánh(branche) để lấy bản sao của master rồi code, chỉnh sửa.
Khi nào code ok, chạy tốt thì merge từ branche lên master.
--Trong lúc code, dĩ nhiên cần thêm function, thấy thiếu function nào thì bổ sung thêm vào
--Tự thêm parameter phù hợp vào prototype của function
--Nhớ comment dòng code để tui hiểu nhe
*/


//void SignUp_LogIn(); // dùng lúc mới vào game, hàm này có thể gồm 2 hàm nhỏ: đăng kí, đăng nhập
void generateBoard(cell Board[][8]);

void print_UpperHorizontalLine(cell Board[][8], int Row);
void print_BottomHorizontalLine(cell Board[][8], int Row);
void print_VerticalLine(cell Board[][8], int Row);
void printBoard(cell Board[][8]);



//void checkValidMatching(); // gọi hàm này để kiểm tra ghép cặp có được không
//void check_I_Matching(); // hàm này nằm trong hàm checkValidMatching
//void check_L_Matching(); // hàm này nằm trong hàm checkValidMatching
//void check_U_Matching(); // hàm này nằm trong hàm checkValidMatching
//void check_Z_Matching(); // hàm này nằm trong hàm checkValidMatching

//void checkEndGame(); // kiểm tra có còn cặp nào không

//void countTime(); // đếm thời gian hoàn thành bàn chơi
//check valid name


bool isValidName(string name) {
    if (name.length() < 3) {
        return false;
    }
    for (int i = 0; i < name.length(); i++) {
        if (name[i] < 'A' || name[i] > 'Z') {
            return false;
        }
    }
    return true;
}




void makeLeaderboard(string maze_name, string formated_time) {
    string winner_name, filename = maze_name.substr(0,7) + "_WINNERS.txt";

    while(true) {
        
        if(ifstream(filename)) {   // If MAZE_XX_WINNERS.txt file exists
            fstream leaderboard(filename, fstream :: app);
            cout << "Enter your name (max 15 characters): ";
            if(isValidName(winner_name) && winner_name.length() <= 15) {  // If name is valid
                string line;
                vector<string> lb_entries;
                int n_line = 0;
                leaderboard << formated_time << " - " << winner_name << endl; // Append to the end of the file
                // Store all leaderboard entries in a vector
                while(!leaderboard.eof()) {  
                    if(n_line >= 2) {
                        getline(leaderboard, line);
                        lb_entries.push_back(line);
                    }
                    n_line++;
                }
                leaderboard.close();
                sort(lb_entries.begin(), lb_entries.end());//sort the leaderboard entries first by name, then by time
                // Check if leaderboard has more than 10 entries to delete those past the limit
                if(lb_entries.size() > 10) {  
                    lb_entries.erase(lb_entries.begin() + 9, lb_entries.end()); // Truncates the vector from the 10th position forward
                }
                leaderboard.open(filename, fstream :: trunc);   // Reopens the file in truncation mode to delete pre-existing leaderboard
                leaderboard << "|    TIME    -    NAME   |" << endl;
                leaderboard << "--------------------------" << endl;
                // Updates leaderboard
                for(string entry : lb_entries) { 
                    leaderboard << entry << endl;
                }
                leaderboard.close();
                break;
            }
            // If name not valid
            else if (isValidName(winner_name) && winner_name.length() > 15) {
                cerr << endl << "Name has more than 15 characters! Please retry." << endl;
            }
            else {
                cerr << endl << "Not a valid name input!" << endl << endl;
            }
    }
    // If file doesn't exist
    else {
        cout << "Creating leaderboard ..." << endl;
        ofstream leaderboard(filename);
        if (!leaderboard) {
            cerr << "File could not be created!" << endl;
        }
        else {
            leaderboard << "|    TIME    -    NAME   |" << endl;
            leaderboard << "--------------------------" << endl;
            leaderboard.close();
        }
    }
    }
}

int main()
{
    cell Board[8][8];
    int Row = 0;

    printBoard(Board);

}
void print_UpperHorizontalLine(cell Board[][8], int Row)
{
    for (int Col = 0; Col < 8; Col++)
    {
        Board[Row][Col].UpperHori = " ------- ";
        cout << Board[Row][Col].UpperHori;
    }
    cout << "\n";
}
void print_BottomHorizontalLine(cell Board[][8], int Row)
{
    for (int Col = 0; Col < 8; Col++)
    {
        Board[Row][Col].BottomHori = " ------- ";
        cout << Board[Row][Col].BottomHori;
    }
    cout << "\n";
}
void print_VerticalLine(cell Board[][8], int Row)
{
    int Col;
    for(Col = 0; Col < 8; Col++)
    {
        Board[Row][Col].VerLine.Line1 = "|       |";
        cout << Board[Row][Col].VerLine.Line1;
    }
    cout << "\n";
    //
    for(Col = 0; Col < 8; Col++)
    {
        Board[Row][Col].VerLine.Line2 = "|   ";
        Board[Row][Col].VerLine.Line3 = "   |";
        cout << Board[Row][Col].VerLine.Line2 << Board[Row][Col].figure << Board[Row][Col].VerLine.Line3;
    }
    cout << "\n";
    //
    for(Col = 0; Col < 8; Col++)
    {
        Board[Row][Col].VerLine.Line4 = "|       |";
        cout << Board[Row][Col].VerLine.Line4;
    }    
    cout << "\n";

}
void printBoard(cell Board[][8])
{
    generateBoard(Board);
    for (int Row = 0; Row < 8; Row++)
    {
        print_UpperHorizontalLine(Board, Row);
        print_VerticalLine(Board, Row);
        print_BottomHorizontalLine(Board, Row);   
    }
}
void generateBoard(cell Board[][8])
{
    int count[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int index, number;
    srand(time(NULL));
    for (int Row = 0; Row < 8; Row++){
        for (int Col = 0; Col < 8; Col++)
        {
            while(true){
                index = rand()%8; // [0-->7]
                number = 65 + index;
                if (count[index] < 8)
                {
                    count[index]++;
                    Board[Row][Col].figure = number;
                    break;
                }
            }
        }
    }
}