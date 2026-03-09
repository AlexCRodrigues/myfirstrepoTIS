#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

void inserir(string &nome, int &idade, int &CC){
    ofstream ficheiro("registos.txt", ios::app);
    cin.ignore();
    cout << "Insira o seu nome" << endl;
    cin >> nome;
    cout << "Insira o seu número de cartão de cidadão" << endl;
    cin >> CC;
    cout << "Insira sua idade" << endl;
    cin >> idade;
    ficheiro << nome << ";" << CC << ";" << idade << endl;
    ficheiro.close();
    cout << "Registo guardado" << endl;
}
void consultar(int &CC, string &nome, int &idade) {
    ifstream ficheiro("registos.txt");
    if (!ficheiro.is_open()) {
        cout << "Ficheiro nao encontrado!" << endl;
        return;
    }

    string linha;
    bool encontrado = false;
    cout << "Numero de CC a procurar: ";
    cin >> CC;
    cin.ignore();

    while (getline(ficheiro, linha)) {

    if (linha.empty()) continue;
    stringstream ss(linha);
    string nome_ficheiro, cc, idade_str;
    if (!getline(ss, nome_ficheiro, ';')) continue;

    if (!getline(ss, cc, ';')) continue;

    if (!getline(ss, idade_str, ';')) continue;

    try{
        int cc_ficheiro = stoi(cc);
        int idade_ficheiro = stoi(idade_str);

    if (cc_ficheiro == CC) {
        nome = nome_ficheiro;
        idade = idade_ficheiro;
        cout << "Nome: " << nome << endl;
        cout << "CC: " << cc_ficheiro << endl;
        cout << "Idade: " << idade << endl;
        encontrado = true;
        break;
    }
    } catch (...) {
    continue;
    }
}
    if (!encontrado) {
    cout << "Registo nao encontrado." << endl;
}
    ficheiro.close();
}
void listar() {
    ifstream ficheiro("registos.txt");

    if (!ficheiro.is_open()) {
    cout << "Ficheiro nao encontrado!" << endl;
    return;
    }

    string linha;
    string ultimo = "";

    while (true){
        ficheiro.clear();
        ficheiro.seekg(0);
        string menor_nome = "";
        int menor_cc = 0;
        int menor_idade = 0;
        bool encontrado = false;

    while (getline(ficheiro, linha)) {
        stringstream ss(linha);
        string nome, cc, idade;
        getline(ss, nome, ';');
        getline(ss, cc, ';');
        getline(ss, idade, ';');
    if (nome > ultimo) {
    if (!encontrado || nome < menor_nome){
        menor_nome = nome;
        menor_cc = stoi(cc);
        menor_idade = stoi(idade);
        encontrado = true;
    }
    }
}
    if (!encontrado)
    break;
    cout << "Nome: " << menor_nome << endl;
    cout << "CC: " << menor_cc << endl;
    cout << "Idade: " << menor_idade << endl;
    ultimo = menor_nome;
}
    ficheiro.close();
}

int main(){

string nome = "";
int idade = 0;
int CC = 0;
int escolha = 0;

do{
cout << endl;
cout << "Menu de registros de cartão de cidadão" << endl;
cout << "1- inserir" << endl;
cout << "2- consultar" << endl;
cout << "3- listar" << endl;
cout << "0- sair" << endl;
cout << "Qual opção deseja escolher" << endl;
cin >> escolha;

if(escolha == 1){
    system("clear");
    inserir(nome, idade, CC);
}

if(escolha == 2){
    system("clear");
    consultar(CC, nome, idade);
}

if(escolha == 3){
    system("clear");
    listar();
}
}

while(escolha != 0);

return 0;
}


