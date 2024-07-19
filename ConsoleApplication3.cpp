#include <iostream> //tik 1-4, ziauriai daug klaidu
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;
bool found_rule = false;
struct turkodas {
    string busena1, busena2;
    char simbolis1 = { 0 }, simbolis2 = { 0 }, judesys = { 0 };
};
//busena1 - pirmoji busena, busena2 - nauja busena, simbolis1 - dabartinis simbolis, simbolis 2- pakeistas simbolis, judesys - i desine ar kaire
void veiksmas(vector <turkodas> nzn, string& juosta, int& juostprad, string& busena, int& steps, string& galvutespozicija, int& eil);
bool kbhit() {
    DWORD numEvents;
    GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &numEvents);
    return numEvents > 0;
}
int main()
{
    int juostsk, juostprad, steps = 0, count = 0, eil; //juostu skaicius, judesiu kiekis ir galvutes pradine pozicija, juostprad taip pat seks galvutes pozicija
    string juosta, busena, failas;
    cout << "iveskite txt failo pavadinima (pvz 1.txt)\n\n";
    cin >> failas;
    ifstream baisu(failas);
    system("cls");
    turkodas laikinas;
    baisu >> juostsk;
    baisu >> juosta >> juostprad;
    busena = "0";
    string galvutespozicija(juosta.size(), ' ');
    vector<turkodas>nzn; //i si vektoriu surasomos visos turingo kodo taisykles
    while (!baisu.eof()) {
        baisu >> laikinas.busena1 >> laikinas.simbolis1 >> laikinas.simbolis2 >> laikinas.judesys >> laikinas.busena2;
        nzn.push_back(laikinas);
    }
    baisu.close();
    while (true) {
        int pozitemp = juostprad;
        galvutespozicija[pozitemp] = ' ';
        veiksmas(nzn, juosta, juostprad, busena, steps, galvutespozicija, eil);
        galvutespozicija[juostprad] = '^';
        cout << juosta << "    " << busena << endl << galvutespozicija << endl << "zingsniu kiekis: " << steps;
        if (kbhit()) {
            cout << endl << endl << "Halted: manually stopped";
            return 0;
        }
        for (int i = 0; i < nzn.size(); ++i) {
            if (busena == nzn[nzn.size() - 1].busena2 && nzn[nzn.size() - 1].busena2 != nzn[i].busena1 && i == nzn.size() - 1) {
                cout << endl << endl << "Halted: task complete";
                return 0;
            }
        }
        if (!found_rule) {
            cout << endl << endl << "Halted: no rule found for state '" << busena << "' and symbol '" << juosta[juostprad] << "'";
            return 0;
        }
        system("cls");
    }


}


void veiksmas(vector<turkodas> nzn, string& juosta, int& juostprad, string& busena, int& steps, string& galvutespozicija, int& eil) { //turingo taisykles

    for (int i = 0; i < nzn.size(); ++i) {
        if (juosta[juostprad] == nzn[i].simbolis1 && busena == nzn[i].busena1)
        {
            juosta[juostprad] = nzn[i].simbolis2;
            busena = nzn[i].busena2;
            ++steps;
            eil = i;

            if (nzn[i].judesys == 'R' && juostprad != nzn.size())
                ++juostprad;
            else if (nzn[i].judesys == 'R' && juostprad == nzn.size())
            {
                found_rule = false;
                juosta.push_back(' ');
                return;
            }
            if (nzn[i].judesys == 'L' && juostprad != 0)
                --juostprad;
            else if (nzn[i].judesys == 'L' && juostprad == 0)
            {

                found_rule = false;
                juosta.insert(juosta.begin(), ' ');
                return;
            }


            found_rule = true;
        }
    }
}