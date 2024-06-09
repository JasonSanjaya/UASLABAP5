#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class TicTacToe 
{
private:
    char papan[3][3];
    vector<pair<int, int>> gerakanTersedia;
    char winner;
    bool player1Turn;

public:
    TicTacToe() : player1Turn(true), winner(' ') 
    {
        inisialisasiPapan();
    }

    ~TicTacToe() {}

    void inisialisasiPapan() 
    {
        papan[0][0] = papan[0][1] = papan[0][2] = ' ';
        papan[1][0] = papan[1][1] = papan[1][2] = ' ';
        papan[2][0] = papan[2][1] = papan[2][2] = ' ';
        gerakanTersedia.clear();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                gerakanTersedia.push_back({i, j});
            }
        }
    }

    void tampilPapan() 
    {
        cout << "    1   2   3" << endl; 
        cout << "  -------------" << endl;
        for (int i = 0; i < 3; ++i) {
            cout << i + 1 << " | "; 
            for (int j = 0; j < 3; ++j) {
                cout << papan[i][j] << " | ";
            }
            cout << endl << "  -------------" << endl;
        }
    }

    bool gerakanValid(int baris, int kolom) {
        return baris >= 0 && baris < 3 && kolom >= 0 && kolom < 3 && papan[baris][kolom] == ' ';
    }

    void lakukanGerakan(int baris, int kolom, char pemain) {
        papan[baris][kolom] = pemain;
        gerakanTersedia.erase(remove(gerakanTersedia.begin(), gerakanTersedia.end(), make_pair(baris, kolom)), gerakanTersedia.end());
    }

    bool cekMenang(char pemain) {
        for (int i = 0; i < 3; ++i) {
            if ((papan[i][0] == pemain && papan[i][1] == pemain && papan[i][2] == pemain) ||
                (papan[0][i] == pemain && papan[1][i] == pemain && papan[2][i] == pemain)) {
                winner = pemain;
                return true;
            }
        }
        if ((papan[0][0] == pemain && papan[1][1] == pemain && papan[2][2] == pemain) ||
            (papan[0][2] == pemain && papan[1][1] == pemain && papan[2][0] == pemain)) {
            winner = pemain;
            return true;
        }
        return false;
    }

    bool penuhPapan(){
        return gerakanTersedia.empty();
    }

    void pembukaan(){
        int lebar_terminal = 60;
        string equal_line(lebar_terminal, '=');

        string baris1 = " X | O | X ";
        string pemisah = "---|---|---";
        string baris2 = " O | O | O ";
        string baris3 = " X | X | X ";

        int tab = (lebar_terminal - baris1.length()) / 2;
        string spaces(tab, ' ');

        cout << equal_line << endl;
        cout << spaces << baris1 << endl;
        cout << spaces << pemisah << endl;
        cout << spaces << baris2 << endl;
        cout << spaces << pemisah << endl;
        cout << spaces << baris3 << endl;
        cout << equal_line << endl;
        cout << "Selamat datang di Tic-Tac-Toe!" << endl;
    }

    void PlayGame()
    {
        while (true) {
            winner = ' ';
            player1Turn = true;
            inisialisasiPapan();

            tampilPapan();

            while (winner == ' ')
            {
                char symbol = (player1Turn) ? 'X' : 'O'; 

                int row, col;
                cout << "Giliran pemain " << symbol << ". Masukkan baris dan kolom (mis. 1 2): ";
                cin >> row >> col;

                if (row < 1 || row > 3 || col < 1 || col > 3 || !gerakanValid(row - 1, col - 1))
                {
                    cout << "Posisi tidak valid, coba lagi." << endl;
                    continue;
                }

                lakukanGerakan(row - 1, col - 1, symbol);

                if (cekMenang(symbol)) {
                    tampilPapan();
                    cout << "Pemenangnya adalah pemain " << winner << "!" << endl;
                    break;
                } else if (penuhPapan()) {
                    tampilPapan();
                    cout << "Permainan berakhir seri!" << endl;
                    break;
                }

                player1Turn = !player1Turn;

                system("cls");
                tampilPapan();
            }

            cout << "Terima kasih sudah bermain!" << endl;
            cout << "Apakah Anda ingin bermain lagi? (Y/N): ";
            char playAgain;
            cin >> playAgain;
            if (toupper(playAgain) != 'Y') break;
        }
    }
};

int main()
{
    TicTacToe *permainan = new TicTacToe();
    permainan->pembukaan();

    char mulai;
    cout << "Mulai Permainan (Y/N): ";
    cin >> mulai;

    if (toupper(mulai) == 'Y') {
        permainan->PlayGame();
    }

    delete permainan;
    cout << "Terima Kasih!!!" << endl;
    return 0;
}