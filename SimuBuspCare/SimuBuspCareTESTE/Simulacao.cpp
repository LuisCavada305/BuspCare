#include "pch.h"
#include "Simulacao.h"
#include <iostream>
#include <chrono>
#include <thread>

#include <fstream>
#include <string>

using namespace System;
using namespace System::IO::Ports;

using namespace std;

const int Simulador::tamanhoBinario = 8;

Simulador::Simulador() {

    dados = new int* [Simulador::tamanhoBinario + 2];
    std::cout << "Insira o numero de dados: ";
    
    cin >> quantidadeDeDados; std::cout  << endl;

    
    

    numeros = new int[quantidadeDeDados];
    cout << "Insira os dados um a um separados por <enter>: " << endl;

    for (int i = 0; i < quantidadeDeDados; i++) {
        cin >> numeros[i];
        cout << endl; 
    }

    std::cout << "Simulador com " << quantidadeDeDados << " dados criado com sucesso." << endl;
    
}

Simulador::~Simulador() {
    delete[] numeros;  

    for (int i = 0; i < quantidadeDeDados; i++) {
        delete[] dados[i];
    }

    delete[] dados; 
}

int* Simulador::binarioPadrao(int dado) {
    int *binario = new int[Simulador::tamanhoBinario + 2];
    int i = 0;
    int k;
    
    while (dado > 0 && i < 10) {
        binario[i] = dado % 2;
        i = i + 1;
        dado = dado / 2;
    }

    for (k = i; k < Simulador::tamanhoBinario + 2; k++)
        binario[k] = 0;

    binario[Simulador::tamanhoBinario] = binario[Simulador::tamanhoBinario+1] = 1;

    int h = 0;
    for (int j = Simulador::tamanhoBinario + 1; j > 4; j--) {
        int aux;
        aux = binario[j];
        binario[j] = binario[h];
        binario[h] = aux;
        h++;
    }


    return binario;
}

void Simulador::processar() {
    for (int i = 0; i < quantidadeDeDados; i++) {
        dados[i] = binarioPadrao(numeros[i]);
    }
}



int Simulador::getQuantidadeDeDados() {
    return quantidadeDeDados;
}

int** Simulador::getDados() {
    return dados;
}

const int Simulador::getTamanhoBinario() {
    return tamanhoBinario;
}

void Simulador::enviar() {
    SerialPort port("COM4", 9600);
    port.Open();

    
    for (int i = 0; i < getQuantidadeDeDados(); i++) {
        for (int j = 0; j < Simulador::getTamanhoBinario() + 2; j++) {
            if (getDados()[i][j] == 1) {
                port.Write("1"); 
            }
            else
                port.Write("0");
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        port.Write(";\n");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    port.Write(",");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Simulacao completa." << endl;
    port.Close();
}

void Simulador::computerReady() {

    SerialPort port("COM4", 9600);
    port.Open();
    string a;

    
    cout << a;
        
    port.Close();

}

int* Simulador::getNumeros() {
    return numeros;
}