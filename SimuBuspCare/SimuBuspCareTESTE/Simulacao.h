#ifndef SIMULACAO_H
#define SIMULACAO_H

class Simulador {
private:

    int* numeros;
    int quantidadeDeDados;
    static const int tamanhoBinario;
    int** dados;
public:

    Simulador();
    virtual ~Simulador();

    int getQuantidadeDeDados();
    int** getDados();

    int* binarioPadrao(int dado);
    void processar();
    void enviar();
    void computerReady();
    
    int* getNumeros();
    static const int getTamanhoBinario();
};

#endif

