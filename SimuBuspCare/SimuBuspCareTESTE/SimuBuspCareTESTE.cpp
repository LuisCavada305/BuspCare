#include "pch.h"
#include "Simulacao.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <queue>
#include <vector>
#include "Analisador.h"
#include "Callback.h"

#include <string>
#include <sstream>

using namespace System;
using namespace System::IO::Ports;
using namespace std;

const std::string SERVER_ADDRESS = "lprot.pea.usp.br:7080"; // tcp://mqtt-broker-ip:1883
const std::string CLIENT_ID = "cpp-mqtt-receiver";
const std::string TOPIC = "/Intengele/Grupo_A_Tx";





int main() {
    Simulador* simu = new Simulador();
    simu->processar();
    simu->enviar();

    Analisador* analisador = new Analisador();

    int* aux = simu->getNumeros();
    queue<int>* fila = new queue<int>();
    for (int i = 0; i < simu->getQuantidadeDeDados(); i++) fila->push(aux[i]);
    

    analisador->setSeq(fila);

    analisador->processar();

    queue<int>* instantes;
    

    instantes = analisador->getInstantesDeManutencao();
    cout << "Instantes de Manutencao: " << endl;
    if (instantes->empty())
        cout << "N/A" << endl;
    else
    while (!instantes->empty()) {
        cout << "- " << instantes->front() << endl;
        instantes->pop();
    }

    instantes = analisador->getInstantesDeReparoImperfeito();
    cout << "Instantes de Reparo Imperfeito: " << endl;
    if (instantes->empty())
        cout << "N/A" << endl;
    else
    while (!instantes->empty()) {
        cout << "- " << instantes->front() << endl;
        instantes->pop();
    }
    
   
    
    delete simu;
    return 0;
}
