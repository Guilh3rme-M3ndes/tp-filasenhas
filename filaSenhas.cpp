#include <iostream>
#include <locale.h>
#include <string>

#define TAM 5

struct SenhasGeradas {
	
	int senhas[TAM];
	int ini;
	int fim;
};

struct Senha {
	int senha;
	Senha* prox;	
};
struct SenhasAtendidas {
	
	Senha* ini;
	Senha* fim;
	
};

SenhasGeradas* initGeradas() {
	SenhasGeradas* s = new SenhasGeradas;
	s->ini = 0;
	s->fim = 0;
	return s;
}

SenhasAtendidas* initAtendidas() {
	SenhasAtendidas* s = new SenhasAtendidas;
	s->ini = NULL;
	s->fim = NULL;
	return s;
}

int main(int argc, char** argv)
{
	
	return 0;
}