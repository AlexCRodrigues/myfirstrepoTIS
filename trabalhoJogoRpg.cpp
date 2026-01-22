#include <iostream>
#include <string>
using namespace std;

class Personagem {
protected:
    string nome;
    int vida;
    int vidaMaxima;

public:

    Personagem(string n, int v) : nome(n), vida(v), vidaMaxima(v) {}

    string getNome() const { return nome; }
    int getVida() const { return vida; }

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) vida = 0;
        cout << nome << " sofreu " << dano << " de dano! Vida restante: " << vida << endl;
    }
    bool estaVivo() const{
        if(vida <=0){
            cout << "Está morto" << endl; return false;
        }
        else{ return true;}
    }

    virtual void atacar() {
        cout << nome << " fez um ataque basico." << endl;
    }
};

class Guerreiro : public Personagem {
    private:
        int forca; 
    
    public:
        Guerreiro(string n, int v, int f) : Personagem(n, v), forca(f) {}
    
        void atacar(Personagem &alvo) {
            cout << nome << " brande a sua espada com forca " << forca << "!" << endl;
            alvo.receberDano(this->forca);
        }
    
        void gritoDeGuerra() {
            cout << nome << " grita: POR SPARTA!!" << endl;
        }
    };
    
    class Mago : public Personagem {
    private:
        int magia;
    
    public:
        Mago(string n, int v, int m) : Personagem(n, v), magia(m) {}
    
        void atacar(Personagem &alvo) {
            cout << nome << " lanca uma bola de fogo com poder " << magia << "!" << endl;
            alvo.receberDano(magia);
        }
    
        void curar() {
            vida += 10;
            if (vida > vidaMaxima) vida = vidaMaxima;
            cout << nome << " curou-se. Vida atual: " << vida << endl;
        }
    };
    class Ladino : public Personagem{
        private:
        int furtividade;

        public:
        Ladino(string nome, int vida, int furtividade)
        : Personagem(nome, vida) {
        this->furtividade = furtividade;
        }
        void atacar(Personagem &alvo){
            int confirmacao;
            cout << "Queres que o " << nome
            << " ataque das sombras? (1 = sim, 0 = nao): ";
            cin >> confirmacao;
    
            if (confirmacao == 1) {
                cout << "O " << nome << " atacou das sombras com furtividade "
                     << furtividade << "!" << endl;
            } else {
                cout << nome << " decidiu nao atacar." << endl;
            }
        }
    };
    int main() {
        cout << "--- INICIO DA BATALHA ---" << endl;
    
        Guerreiro g1("Thor", 100, 20);
        Mago m1("Gandalf", 60, 35);
        Ladino l1("Alex",30, 20);
        
        cout << "O guerreiro " << g1.getNome() << " entrou na arena." << endl;
        cout << "O mago " << m1.getNome() << " entrou na arena." << endl;
    
        cout << "\n--- COMBATE ---" << endl;
        while(g1.estaVivo() && m1.estaVivo()){

        if (g1.estaVivo()) { g1.atacar(m1); }
        else if(!g1.estaVivo()){
            cout << "morreu" << endl;
            break;}

        cout << endl;
        g1.gritoDeGuerra(); 

        if (m1.estaVivo()) { m1.atacar(g1); }
        else if(!m1.estaVivo()){
            cout <<"morreu"<< endl;
            break;
        }
        cout << endl;
        m1.curar();
        Ladino l1("Ezio",30,20);    
        if(l1.estaVivo()) l1.atacar(g1);
    }
        return 0;
    }