#include <iostream>

using namespace std;

bool usadas[256] = {false};

int main() {

    char b;
    bool acertou = false;
    string frase;
    cout << "insira a frase: " << endl;
    getline(cin, frase);

    while (!acertou) {
        acertou = true;
        for (char a : frase) {
            if (a == ' ' || usadas[a]) {
                cout << a;
            } else {
                cout << "_ "; 
                acertou = false;
            }
        }

        if (acertou == true) 
        break;

        cout << endl;

        cout << "Insira a letra que penses que esta presente na frase escondida" << endl;
        cin >> b;
        usadas[b] = true;
    }
    cout << endl;
    cout << "Acertaste a frase escondida." << endl;
    return 0;
}