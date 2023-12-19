#ifndef ANALISADOR_H
#define ANALISADOR_H

#include "Simulacao.h"
#include <queue>


using namespace std;

class Analisador {
private:
	queue<int>* dados;
	queue<int>* instantesDeManutencao;
	queue<int>* instantesDeReparoImperfeito;
	
public:
	void receberDados();
	int processar();
	queue<int>* Analisador::decimal(queue<int>* binario);
	
	virtual ~Analisador();
	Analisador(); 

	queue<int>* getSeq();
	void setSeq(queue<int>* dados);
	queue<int>* getInstantesDeManutencao();
	queue<int>* getInstantesDeReparoImperfeito();
};

#endif 

