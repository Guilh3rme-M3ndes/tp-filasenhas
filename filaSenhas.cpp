#include <iostream>
#include <locale.h>
#include <string>

#define TAM 6
using namespace std;

struct SenhasGeradas
{
	int senhas[TAM];
	int ini;
	int fim;
};

struct Senha
{
	int numero;
	Senha* prox;
};
struct SenhasAtendidas
{
	Senha* ini;
	Senha* fim;
};

SenhasGeradas* initGeradas()
{
	SenhasGeradas* s = new SenhasGeradas;
	s->ini = 0;
	s->fim = 0;
	return s;
}

SenhasAtendidas* initAtendidas()
{
	SenhasAtendidas* s = new SenhasAtendidas;
	s->ini = NULL;
	s->fim = NULL;
	return s;
}

bool isEmpty(SenhasGeradas* s)
{
	return (s->ini == s->fim);
}

bool isEmpty(SenhasAtendidas* s)
{
	return (s->ini == NULL);
}

int incrementa (int ii)
{
	return (ii+1)%TAM;
}

int count (SenhasGeradas* s)
{
	int qtd = 0;
	int ii = s->ini;
	while (ii != s->fim)
	{
		qtd++;
		ii = incrementa(ii);
	}
	return qtd;
}

int count (SenhasAtendidas* s)
{
	int qtd = 0;
	Senha* ii = s->ini;
	while(ii != NULL)
	{
		qtd++;
		ii = ii->prox;
	}
	return qtd;
}

bool geraSenha(SenhasGeradas* s, int ii) {
	bool podeGerar = incrementa(s->fim) != s->ini;
	if (podeGerar) {
		s->senhas[s->fim] = ii;
		s->fim = incrementa(s->fim);
	}
	return podeGerar;
}

int mataSenha(SenhasGeradas* s) {
	bool podeMatar = !isEmpty(s);
	int ret;
	if (podeMatar) {
		ret = s->senhas[s->ini];
		s->ini = incrementa(s->ini);
	}
	else {
		//cod de erro
		ret = -1;
	}
	return ret;
}

void geraSenha(SenhasAtendidas* s, int ii) {
	Senha* senha = new Senha;
	senha->numero = ii; 
	senha->prox = NULL;
	if (isEmpty(s)) {
		s->ini = senha;
	}
	else {
		s->fim->prox = senha;
	}
	s->fim = senha;
}

void atender(SenhasGeradas* g, SenhasAtendidas* s) {
	int atendido = mataSenha(g);
	if (atendido == -1) {
		cout << "Nenhum atendimento pendente!" << endl;
	}
	else {
		geraSenha(s, atendido);
		cout << "Senha: " << s->fim->numero << " atendida!"<<endl;;
	}
}

void relatorioDeAtendimentos(SenhasAtendidas* s) {
	Senha* aux = s->ini; 
	cout << string(50, '-') << endl;
	cout << "Senhas atendidas durante a execução: " << endl;
	
	while (aux != NULL) {
		cout << aux->numero << endl;
		aux = aux->prox;
	}
	cout << "Total de atendimentos: " << count(s);
	cout << string(50, '-') << endl;
}



int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	int prox = 1;
	SenhasGeradas* senhas = initGeradas();
	SenhasAtendidas* atendidos = initAtendidas();
	
	//numero qualquer para previnir que a variavel esteja localizada em um endereço cujo valor inteiro é 0
	int seletor = 1; 
	while(seletor != 0 || !isEmpty(senhas)) {
		
		//construção do menu
		cout << string(50, '-') << endl
		<< "Opções:" << endl 
		<< string(50, '-') << endl
		<< "0 - Sair." << endl
		<< "1 - Gerar senha." << endl
		<< "2 - Realizar atendimento." << endl;
		cout << string(50, '-') << endl
		<< "Aguardando atendimento: " << count(senhas) << endl
		<< string(50, '-') << endl;
		
		//inicio do atendimento
		cout << "Selecione uma opção" << endl;
		cin >> seletor;
		switch(seletor) {
			case 0: {
				if (!isEmpty(senhas)) {
					cout << "Finalize os atendimentos antes de sair! (restam " << count(senhas) << ")" << endl << endl;
				}
				else {
					cout << string(50, '-') << endl
					<< "Fim da execução, relatório de atendimentos abaixo:" <<  endl;
				}
				break;
			}
			case 1: {
				if (geraSenha(senhas, prox)) {
					cout << "Senha gerada! Aguarde o atendimento" << endl;
					cout << "N da senha: " << prox++ << endl << endl;
				} else {
					cout << "Quantidade máxima de senhas atingida" << endl << endl;
				}
				break;
			}
			case 2: {
				atender(senhas, atendidos);
				break;
			}
			default: {
				cout << "Informe uma opção válida!" << endl << endl;
				break;
			}
		}
		
	}
	relatorioDeAtendimentos(atendidos);
	return 0;
}
