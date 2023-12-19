#include "pch.h"
#include "Analisador.h"
#include <queue>
#include <iostream>
#include "Callback.h"

#include <string>


using namespace System;
using namespace System::IO::Ports;
using namespace std;

const std::string SERVER_ADDRESS = "lprot.pea.usp.br:7080"; // tcp://mqtt-broker-ip:1883
const std::string CLIENT_ID = "cpp-mqtt-receiver";
const std::string TOPIC = "/Intengele/Grupo_A_Tx";

Analisador::~Analisador() {
	delete dados;
    delete instantesDeManutencao;
    delete instantesDeReparoImperfeito;
}

Analisador::Analisador() {
    
    dados = new queue<int>();

}

void Analisador::receberDados() {
    }


int Analisador::processar() {
    double valor, soma = 0, media = 0, crescimento = 0.05, n = 1, EstadoDegradacao = 0, ContadorManu = 0, ContadorRepImperfeito = 0;
    int falha = 0, t = 0;

    instantesDeManutencao = new queue<int>();
    instantesDeReparoImperfeito = new queue<int>();
    queue<int>* sup = dados;

    while (!sup->empty()) {
        valor = sup->front();
        sup->pop();
        soma += valor;
        media = soma / (n++);
        t++;

        EstadoDegradacao = media + crescimento * valor;

        if (EstadoDegradacao > 150) {
            media = 100;
            ContadorManu++;
            instantesDeManutencao->push(t);
        }

        if (ContadorManu > 3) {
            media = 110;
            ContadorRepImperfeito++;
        }

        if (ContadorRepImperfeito > 2) {
            falha = 1;
            instantesDeReparoImperfeito->push(t);
            return 1;
        }
    }

    delete sup;

    if (ContadorManu == 0 && ContadorRepImperfeito == 0) return 0;
    else return 1;
}
queue<int>* Analisador::getSeq() {
    return dados;
}
queue<int>* Analisador::decimal(queue<int>* binario) {
    int aux;

    for (int i = 0; i < binario->size(); i++) {
        aux = binario->front();
        binario->pop();
        int dec = 0, k = 1;
        while (aux != 11) {
            dec += (aux / 10) * k;
            k *= 2;
            aux = aux / 10;
        }
        binario->push(dec);
    }
    return binario;
}

void Analisador::setSeq(queue<int>* dados) {
    this->dados = dados;
}

queue<int>* Analisador::getInstantesDeManutencao() {
    return instantesDeManutencao;
}
queue<int>* Analisador::getInstantesDeReparoImperfeito() {
    return instantesDeReparoImperfeito;
}