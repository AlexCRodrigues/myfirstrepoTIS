#include <iostream>

using namespace std;

struct JogoDoGalo{
    char jogada;
    bool ocupada = false;
};

JogoDoGalo myMatriz[3][3];

void MostrarTabuleiro(JogoDoGalo matriz[3][3]){
    cout << "Tabuleiro: " << endl;
    cout << endl;
    for (int i = 0; i < 3; i++) {          
        for (int j = 0; j < 3; j++) {      
        if (myMatriz[i][j].ocupada){ 
        cout << " " << myMatriz[i][j].jogada << " ";
        }
        else{
        cout << " . ";
        }
        if (j < 2){
        cout << "|";
        }
        }
        cout << endl;
        if (i < 2){
        cout << "-----------" << endl;
        }
    }
}

char verificarWinCondition(JogoDoGalo matriz[3][3]) {
    
    for (int i = 0; i < 3; i++) {
        if (matriz[i][0].ocupada &&
        matriz[i][0].jogada == matriz[i][1].jogada &&
        matriz[i][1].jogada == matriz[i][2].jogada)
        return matriz[i][0].jogada;
    }

    for (int j = 0; j < 3; j++) {
        if (matriz[0][j].ocupada &&
        matriz[0][j].jogada == matriz[1][j].jogada &&
        matriz[1][j].jogada == matriz[2][j].jogada)
        return matriz[0][j].jogada;
    }

    if (matriz[0][0].ocupada &&
        matriz[0][0].jogada == matriz[1][1].jogada &&
        matriz[1][1].jogada == matriz[2][2].jogada)
        return matriz[0][0].jogada;

    if (matriz[0][2].ocupada &&
        matriz[0][2].jogada == matriz[1][1].jogada &&
        matriz[1][1].jogada == matriz[2][0].jogada)
        return matriz[0][2].jogada;

    return ' ';
}

void jogo(JogoDoGalo myMatriz[3][3]){
    char jogador1;
    char jogador2;
    string Player1, Player2;
    cout << "Player 1, nome: ";
    cin >> Player1;
    cout << "Player 1 escolhe o teu simbolo(X/O): ";
    cin >> jogador1;
    cout << endl;
    cout << "Player 2, nome: ";
    cin >> Player2;
    cout << "Player 2 escolhe o teu simbolo(X/O): ";
    cin >> jogador2;
    cout << endl;
    if(jogador1 == jogador2){
        cout << "Já foi escolhido, escolhe outro(X/O): " << Player2 << endl;
        cin >> jogador2;
    }
    cout << endl;

    int linha;
    int coluna;
    int jogadas= 0;
    int jogadasMax= 9;

    while(jogadas < jogadasMax){
    MostrarTabuleiro(myMatriz);
    cout << endl;
    cout << Player1 << " linha 1, 2, 3: ";
    cin >> linha;
    cout << endl;
    cout << Player1 << " coluna 1, 2, 3: ";
    cin >> coluna;
    linha--, coluna--;
    cout << endl;
 
    while (linha < 0 || coluna < 0 || linha > 2 || coluna > 2) {
    cout << "Só tens até 3 linhas e 3 colunas" << endl;
    MostrarTabuleiro(myMatriz);
    cout << endl;
    cout << Player1 << " linha 1, 2, 3: ";
    cin >> linha;
    cout << endl;
    cout << Player1 << " coluna 1, 2, 3: ";
    cin >> coluna;
    linha--, coluna--;
    cout << endl;
}

   while(myMatriz[linha][coluna].ocupada){
    cout << "Ocupado" << endl;
    cout << endl;
    cout << Player1 << " linha 1, 2, 3: ";
    cin >> linha;
    cout << endl;
    cout << Player1 << " coluna 1, 2, 3: ";
    cin >> coluna;
    linha--, coluna--;
    cout << endl;
}

    myMatriz[linha][coluna].jogada = jogador1;
    myMatriz[linha][coluna].ocupada = true;
    jogadas++;

    cout << Player1 << " jogou no quadrado (" << linha + 1 << ", " << coluna + 1 << ")" << endl;
    cout << endl;

    MostrarTabuleiro(myMatriz);
    cout << endl;

    char vencedor = verificarWinCondition(myMatriz);
    if (vencedor != ' ') {
        if (vencedor == jogador1){
        cout <<endl;
        cout << Player1 << " venceu o jogo!" << endl;
        break;
    }
        else if (vencedor == jogador2)
        cout << endl;
        cout << Player2 << " venceu o jogo!" << endl;
        break;
    }   

    if (jogadas >= jogadasMax){
    cout << "Tabuleiro cheio." << endl;
    break;
    }

    cout << Player2 << " linha 1, 2, 3: ";
    cin >> linha;
    cout << endl;
    cout << Player2 << " coluna 1, 2, 3: ";
    cin >> coluna;
    linha--, coluna--;
    cout << endl;

    while (linha < 0 || coluna < 0 || linha > 2 || coluna > 2) {
    cout << "Só tens até 3 linhas e 3 colunas" << endl;
    MostrarTabuleiro(myMatriz);
    cout << endl;
    cout << Player2 << " linha 1, 2, 3: ";
    cin >> linha;
    cout << endl;
    cout << Player2 << " coluna 1, 2, 3: ";
    cin >> coluna;
    linha--, coluna--;
    cout << endl;
    }
    
    while(myMatriz[linha][coluna].ocupada){
    cout << "Ocupado" << endl;
    cout << endl;
    cout << Player2 << " linha 1, 2, 3: ";
    cin >> linha;
    cout << endl;
    cout << Player2 << " coluna 1, 2, 3: ";
    cin >> coluna;
    linha--, coluna--;
    cout << endl;
    }
        
    myMatriz[linha][coluna].jogada = jogador2;
    myMatriz[linha][coluna].ocupada = true;
    jogadas++;

    cout << Player2 << " jogou no quadrado (" << linha + 1 << ", " << coluna + 1 << ")" << endl;
    cout << endl;

    MostrarTabuleiro(myMatriz);
    cout << endl;

    char vencedor2 = verificarWinCondition(myMatriz);
    
    if (vencedor2 != ' ') {
        if (vencedor2 == jogador1){
        cout << endl;
        cout << Player1 << " venceu o jogo!" << endl;
        break;
        }
        else if (vencedor2 == jogador2){
        cout << endl;
        cout << Player2 << " venceu o jogo!" << endl;
        break;
        }
    }   
    MostrarTabuleiro(myMatriz);
    }
}

int main(){
    system("clear");
    jogo(myMatriz);
    return 0;
}

