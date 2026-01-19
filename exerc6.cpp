#include <iostream>
#include <string>
using namespace std;

class Veiculo {
    private:
        string marca;
        string modelo;
        double combustivel; 
        double capacidadeTanque;
    public:
    Veiculo(string marc, string nomeDoModelo, double capacidade)
    : marca(marc), modelo(nomeDoModelo), combustivel(0), capacidadeTanque(capacidade) {}
    
    string getMarcaAndModelo() const {
        return marca + modelo;
        }
        
    void abastecer(double litros) {
        if (litros <= 0) {
            cout << "Erro: Quantidade inválida.\n";
            return;
        }
        if (combustivel + litros > capacidadeTanque) {
            combustivel = capacidadeTanque;
            cout << "Tanque cheio! (Excesso descartado)\n";
        } else {
            combustivel += litros;
        }
            cout << "Abastecido. Nivel atual: " << combustivel << "L\n";
        }
    
    void mostrarDetalhes() {
        cout << "Veiculo: " << getMarcaAndModelo()
        << " | Combustivel: " << combustivel << "L\n";
    }
    
    protected:
    double getCombustivel() const {
        return combustivel;
    }
    
    void gastarCombustivel(double valor) {
        combustivel -= valor;
        if (combustivel < 0) combustivel = 0;
    }
    };

class Carro : public Veiculo{
    private: 
    int numPassageiros;

    public:
    Carro(string marca, string modelo, double capacidadeTanque, int passageiros)
    : Veiculo(marca, modelo, capacidadeTanque), numPassageiros(passageiros) {}
    double calcularPortagem() const {
        return 1.5;
    }
    void mostrarDetalhes() const{
        cout << "Carro: " << getMarcaAndModelo() << endl;
        cout << " | Combustivel: " << getCombustivel() << "L" << endl;
        cout << " | Portagem: " << calcularPortagem() << "€" << endl;
        cout << " | Passageiros: " << numPassageiros << "." << endl;
    }
};

class Camiao : public Veiculo {
    private:
        double cargaMaxima;

    public:
    Camiao(string marca, string modelo, double capacidadeTanque, double carga)
        : Veiculo(marca, modelo, capacidadeTanque), cargaMaxima(carga) {}
    void viajar(float km) {
    double consumo = km * 0.5;
        if (getCombustivel() < consumo) {
            cout << "Combustivel insuficiente para viajar " << km << " km.\n";
            return;
        }
        gastarCombustivel(consumo);
        cout << "Viagem de " << km << " km realizada. Combustivel restante: "
        << getCombustivel() << "L\n";
        }
    double calcularPortagem() const{
            return 5.0;
    }
    double getCargaMaxima() const{
        return cargaMaxima;
    }
    void mostrarDetalhes() const{
        cout << "Camiao: " << getMarcaAndModelo()
        << " | Combustivel: " << getCombustivel() << "L"
        << " | Carga maxima: " << cargaMaxima << "kg"
        << " | Portagem: " << calcularPortagem() << "€\n";
    }
    };

int main(){
    Carro meuCarro("Toyota", "Corolla", 50, 5);
    Camiao meuCamiao("Volvo", "FH", 300, 20);
    //meuCarro.combustivel = 100; //dá erro pq n é acessivel e tá em comentario para o programa compilar e executar.
    meuCarro.abastecer(30);
    meuCarro.abastecer(-10);   
    meuCarro.abastecer(5000);  
    meuCamiao.abastecer(150);
    meuCamiao.abastecer(-50);
    meuCamiao.abastecer(5000);
    meuCarro.mostrarDetalhes();
    meuCamiao.mostrarDetalhes();
    meuCamiao.viajar(100);
    meuCamiao.viajar(500); //faz a viagem sem erro mas o tanque fica vazio como deveria.
    meuCamiao.viajar(501); //nao tera combustivel para fazer 501kms considerando a capacidade maxima de 300 litros e 1 litro faz 2kms.

    return 0;
}