#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct jogoDaGloria{
    string jogada = " ";
    bool ocupada = false;
};

jogoDaGloria tabuleiro[30];

int Dado(int &dado){
    dado = rand() % 6 + 1;
    cout << "Saiu-te isto boneco: " << dado << endl;
    return dado;
    }

void jogador(string &player){
    cout << endl;
    cout << "Mete o teu nome boneco: " << endl;
    cin >> player;
    cout << endl;
}

void casasEspeciais(){
    for(int i = 0; i < 30; i++){
        tabuleiro[i].jogada = ' ';  
        tabuleiro[i].ocupada = false;
    }
    int escolhidas[5];
    for(int i = 0; i < 5; i++) {
    int casa;
    do {
        casa = rand() % 28 + 1; 
    } 
    while(tabuleiro[casa].jogada != " ");
        escolhidas[i] = casa;
    }
    tabuleiro[escolhidas[0]].jogada = "P";
    tabuleiro[escolhidas[1]].jogada = "R";
    tabuleiro[escolhidas[2]].jogada = "A";
    tabuleiro[escolhidas[3]].jogada = "J";
    tabuleiro[escolhidas[4]].jogada = "E";
}

void Tabuleiro(int &pos1, int &pos2){
    for (int i = 0; i < 30; i++) {
        cout << "[" << i + 1 << ": ";
    if (i == pos1 && i == pos2) {
        cout << "P1P2";
    } else if (i == pos1) {
        cout << "P1";
    } else if (i == pos2) {
        cout << "P2";
    } else {
        cout << tabuleiro[i].jogada; 
    }
    cout << "] ";
    if ((i + 1) % 15 == 0) {
        cout << endl;
    }
    }
    
}

void efeitoCasaEspecial(int &pos, string &player, bool &podeJogar, int &dado){
    if(pos < 0 || pos > 29) return;
    if(tabuleiro[pos].jogada == " ")return;
    string casa = tabuleiro[pos].jogada;
    if(casa == "P") {
        cout << player << " perdeu a vez!" << endl;
        podeJogar = false;
    } 
    else if(casa == "R") {
        cout << player << " recua 3 casas!" << endl;
        pos -= 3;
        if(pos < 0) pos = 0;
    } 
    else if(casa == "A") {
        cout << player << " avança 3 casas!" << endl;
        pos += 3;
        if(pos > 29) pos = 29;
    } 
    else if(casa == "J") { 
        cout << player << " joga novamente!" << endl;
        podeJogar = true; 
    } 
    else if(casa == "E") {
        cout << player << " deve esperar pelos outros jogadores!" << endl;
        podeJogar = false;
        cout << endl << player << " gira o dado e é Enter boneco" << endl;
        cin.get();
        Dado(dado);
        pos += dado;
        if(pos > 29) pos = 29;
    }
}

void Jogo(int &dado){
    jogoDaGloria jogada;
    string player1;
    string player2;
    string jogada1 = "P1";
    string jogada2 = "P2";
    bool podeJogar1 = true;
    bool podeJogar2 = true;
    int pos1 = 0;
    int pos2 = 0;
    jogador(player1);
    jogador(player2);
    cin.ignore();
    bool jogoAtivo = true;
    casasEspeciais();
    while (jogoAtivo){
    if(podeJogar1){
        cout << endl << player1 << " gira o dado e é Enter boneco" << endl;
        cin.get();
        Dado(dado);
        pos1 += dado;
        if(pos1 > 29) pos1 = 29;
        efeitoCasaEspecial(pos1, player1, podeJogar1, dado);
    } else {
        cout << player1 << " perdeu a vez!" << endl;
        podeJogar1 = true; 
    }
    Tabuleiro(pos1, pos2);
    if(podeJogar2){
        cout << endl << player2 << " gira o dado e é Enter palhaco" << endl;
        cin.get();
        Dado(dado);
        pos2 += dado;
        if(pos2 > 29) pos2 = 29;
        efeitoCasaEspecial(pos2, player2, podeJogar2, dado);
    } else {
        cout << player2 << " perdeu a vez!" << endl;
        podeJogar2 = true;
    }
    Tabuleiro(pos1, pos2);
    if(pos1 >= 29){
        cout << player1 << " venceu" << endl;
        jogoAtivo = false;
    } else if(pos2 >= 29){
        cout << player2 << " venceu" << endl;
        jogoAtivo = false;
    }
}   
}

int main(){
    srand(time(0));
    int dado;
    Jogo(dado);
}
