#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TamanhoNome 100
#define TamanhoEmail 100
#define TamanhoPessoa (sizeof(int) + TamanhoNome + TamanhoEmail)
#define Base (sizeof(int) * 3)
#define EspacoTemporario (sizeof(int) + TamanhoNome + TamanhoEmail)
#define Realocar (Base + EspacoTemporario + TamanhoPessoa * (*contadorPessoas))

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarTodos();
void menu();
void limparAgenda();
void buscarNome();
void buscarEmail();
void* pBuffer;
int* contadorPessoas;

int main() {


	// 3 Inteiros - 1.Contador Pessoas 2.Menu 3.Coringa | 1 Inteiro Idade Temporaria , 2 String 1. NomeTemp 2. EmailTemp
	pBuffer = malloc(Base + EspacoTemporario);

	if (!pBuffer) {
		printf("Erro ao alocar memória\n");
		free(pBuffer);
		exit(1);
	}


	contadorPessoas = (int*)pBuffer;
	*contadorPessoas = 0;

	for (;;) {
		menu();
	}

	return 0;
}
void menu() {

	int* menu;
	menu = (int*)pBuffer + 1;


	printf("\n1 - Adicionar Pessoa\n");
	printf("2 - Remover Pessoa\n");
	printf("3 - Listar todos\n");
	printf("4 - Buscar pessoa\n");
	printf("5 - Limpar agenda\n");
	printf("6 - Sair da agenda\n");
	printf("\nEscolha uma Opcao: ");

	if (scanf_s("%d", menu) != 1) {
		printf("Erro ao ler a opcao\n");
		free(pBuffer);
		exit(1);
	}//if
	while (getchar() != '\n');


	switch (*menu) {
	case 1:
		adicionarPessoa();
		break;
	case 2:
		removerPessoa();
		break;
	case 3:
		listarTodos();
		break;
	case 4:
		buscarPessoa();
		break;
	case 5:
		limparAgenda();
		break;
	case 6:
		printf("\nEncerrando o Porgrama\n");
		free(pBuffer);
		exit(0);
	default:
		printf("\nOpcao Invalida\n");
	}//switch


}//menu
void adicionarPessoa() {

	(*contadorPessoas)++;

	void* bufferTemp = realloc(pBuffer, Realocar);
	if (!bufferTemp) {
		printf("Erro ao alocar memória\n");
		free(pBuffer);
		exit(1);
	}
	pBuffer = bufferTemp;

	int* idadeTemp = (int*)((char*)pBuffer + Base);
	char* nomeTemp = (char*)idadeTemp + sizeof(int);
	char* emailTemp = nomeTemp + TamanhoNome;

	printf("\nDigite o nome completo da pessoa com no maximo 100 caracteres: ");
	fgets(nomeTemp, TamanhoNome, stdin);
	nomeTemp[strcspn(nomeTemp, "\n")] = '\0';

	printf("\nDigite a idade da pessoa: ");
	if (scanf_s("%d", idadeTemp) != 1) {
		printf("\nValor de idade incorreto\n");
		free(pBuffer);
		exit(1);
	}
	while (getchar() != '\n');

	printf("\nDigite o email da pessoa: ");
	fgets(emailTemp, TamanhoEmail, stdin);
	emailTemp[strcspn(emailTemp, "\n")] = '\0';

	contadorPessoas = (int*)pBuffer;
	void* enderecoFinal = (char*)pBuffer + Base + EspacoTemporario + ((*contadorPessoas - 1) * TamanhoPessoa);
	int* idade = (int*)enderecoFinal;
	char* nome = (char*)(idade + 1);
	char* email = nome + TamanhoNome;

	*idade = *idadeTemp;
	strcpy_s(nome, TamanhoNome , nomeTemp);
	strcpy_s(email, TamanhoEmail , emailTemp);

	printf("\nPessoa adicionada com sucesso!\n");
}
void removerPessoa() {
	listarTodos();
	if (*contadorPessoas > 0) {
		int* opcao;
		opcao = (int*)pBuffer + 2;

		printf("\n-----------------------------------------");
		printf("\nDigite o numero do contato que deseja remover:");
		if (scanf_s("%d", opcao) != 1) {
			printf("Erro ao ler a opcao\n");
			free(pBuffer);
			exit(1);
		}
		while (getchar() != '\n');

		if (*opcao < 1 || *opcao > *contadorPessoas) {
			printf("\n\nContato invalido\n");
			return;
		}
		(*opcao)--;

		for (; *opcao < (*contadorPessoas) - 1; (*opcao)++) {
			void* proximaPessoa = (char*)pBuffer + Base + EspacoTemporario + ((*opcao + 1) * TamanhoPessoa);
			void* pessoaAtual = (char*)pBuffer + Base + EspacoTemporario + (*opcao * TamanhoPessoa);
			memmove(pessoaAtual, proximaPessoa, TamanhoPessoa);

		}

		(*contadorPessoas)--;

		void* bufferTemp = realloc(pBuffer, Realocar);
		if (!bufferTemp) {
			printf("Erro ao alocar memória\n");
			free(pBuffer);
			exit(1);
		}
		pBuffer = bufferTemp;

		contadorPessoas = (int*)pBuffer;

	}
	else {
		return;
	}







}
void listarTodos() {
	if (*contadorPessoas == 0) {
		printf("-----------------\n");
		printf("Lista esta vazia\n");
		printf("-----------------\n");
	}
	else {
		printf("-----------------\n");
		printf("Lista de contatos\n");
		printf("-----------------\n");

		int* contador = (int*)((char*)pBuffer + 2 * sizeof(int));
		*contador = 0;

		while (*contador < *contadorPessoas) {
			void* pessoaAtual = (char*)pBuffer + Base + EspacoTemporario + (*contador * TamanhoPessoa);
			int* idade = (int*)pessoaAtual;
			char* nome = (char*)(idade + 1);
			char* email = nome + TamanhoNome;

			printf("[%d] Nome = %s | Idade = %d | Email = %s\n", *contador + 1, nome, *idade, email);

			(*contador)++;
		}
	}
}
void limparAgenda() {

	if (*contadorPessoas == 0) {
		printf("-----------------");
		printf("\nA agenda ja esta limpa!\n");
		printf("-----------------\n");
	}
	else {

		printf("Tem certeza que deseja excluir todos contatos?\n");
		printf("1 - Sim | 2 - Nao\n");

		int* menu;
		menu = (int*)pBuffer + 1;

		if (scanf_s("%d", menu) != 1) {
			printf("Erro ao ler a opcao\n");
			free(pBuffer);
			exit(1);
		}
		while (getchar() != '\n');


		switch (*menu) {
		case 1:
			free(pBuffer);
			pBuffer = malloc(Base + TamanhoPessoa);

			if (!pBuffer) {
				printf("Erro ao alocar memória\n");
				exit(1);
			}


			contadorPessoas = (int*)pBuffer;
			*contadorPessoas = 0;
			printf("-----------------");
			printf("\nAgenda limpa com sucesso\n");
			printf("-----------------\n");
			break;
		case 2:
			break;

		default:
			printf("Opcao invalida\n");
			break;


		}
	}
}
void buscarPessoa() {
	int* menu;
	menu = (int*)pBuffer + 1;

	if (0 == *contadorPessoas) {
		printf("\nAgenda vazia\n");
	}
	else {

		printf("\n\n 1 - Buscar por nome | 2 - Buscar por email\n");

		if (scanf_s("%d", menu) != 1) {
			printf("Erro ao ler a opcao");
			free(pBuffer);
			exit(1);
		}
		while (getchar() != '\n');



		switch (*menu) {
		case 1:
			buscarNome();
			break;
		case 2:
			buscarEmail();
			break;
		default:
			printf("\nOpcao Invalida\n");
			break;
		}
	}


}
void buscarNome() {

	int* contador = (int*)((char*)pBuffer + 2 * sizeof(int));
	*contador = 0;

	char* nomeLido = (char*)pBuffer + Base + sizeof(int);

	printf("\nDigite o nome completo da pessoa que deseja buscar na agenda:");
	fgets(nomeLido, TamanhoNome, stdin);
	nomeLido[strcspn(nomeLido, "\n")] = '\0';

	while (*contador < *contadorPessoas) {
		void* pessoaAtual = (char*)pBuffer + Base + EspacoTemporario + (*contador * TamanhoPessoa);
		int* idade = (int*)pessoaAtual;
		char* nome = (char*)(idade + 1);
		char* email = nome + TamanhoNome;

		if (strcmp(nomeLido, nome) == 0) {
			printf("Nome = %s | Idade = %d | Email = %s\n",nome, *idade, email);
			return;
		}

		(*contador)++;
	}
	printf("\nPessoa nao encontrada\n\n");
}
void buscarEmail() {

	int* contador = (int*)((char*)pBuffer + 2 * sizeof(int));
	*contador = 0;

	char* emailLido = (char*)pBuffer + Base + sizeof(int) + TamanhoNome;

	printf("\nDigite o nome completo da pessoa que deseja buscar na agenda:");
	fgets(emailLido, TamanhoEmail, stdin);
	emailLido[strcspn(emailLido, "\n")] = '\0';

	while (*contador < *contadorPessoas) {
		void* pessoaAtual = (char*)pBuffer + Base + EspacoTemporario + (*contador * TamanhoPessoa);
		int* idade = (int*)pessoaAtual;
		char* nome = (char*)(idade + 1);
		char* email = nome + TamanhoNome;

		if (strcmp(emailLido, email) == 0) {
			printf("Nome = %s | Idade = %d | Email = %s\n", nome, *idade, email);
			return;
		}

		(*contador)++;
	}
	printf("\nEmail nao encontrado\n\n");

}

