#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* pBuffer = NULL;

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarPessoas();
void menu();


void main() {

	// 1 Int para armazenar n pessoas 2 int para menu 3 int idade temp 100 char nome e 100 char email temporario tbm
	pBuffer = malloc(3 * sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char));
	if (!pBuffer) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}
	// Contador de Pessoas
	*((int*)pBuffer) = 0;
	for (;;) {
		menu();
	}



}


void menu() {

	int* menu;

	menu = ((int*)pBuffer + 1);

	printf("\nEscolha uma opcao:\n");
	printf("1 - Adicionar pessoa\n");
	printf("2 - Remover Pessoa\n");
	printf("3 - Buscar Pessoa\n");
	printf("4 - Listar Pessoas\n");
	printf("5 - Sair\n\n");


	if (scanf_s("%d", menu) != 1) {
		printf("Erro ao ler a opcao\n");
		free(pBuffer);
		exit(1);
	}

	while (getchar() != '\n');

	switch (*menu)
	{
	case 1:
		adicionarPessoa();
		break;
	case 2:

		removerPessoa();
		break;

	case 3:
		buscarPessoa();
		break;

	case 4:
		listarPessoas();
		break;
	case 5:
		printf("\n\nFechando a Agenda\n\n");
		free(pBuffer);
		exit(0);

	default:
		printf("Opcao Invalida");
		break;



	}

}
void adicionarPessoa() {

	int* numPessoas = (int*)pBuffer;
	int* idade = (int*)pBuffer + 2;
	char* nome = (char*)pBuffer + 3 * sizeof(int);
	char* email = (char*)pBuffer + 3 * sizeof(int) + 100 * sizeof(char);
	void* escrever;




	printf("\nDigite o nome completo da pessoa: (max 100 caracteres) ");
	fgets(nome, 100, stdin);
	nome[strcspn(nome, "\n")] = 0;

	printf("\nDigite a idade da pessoa: ");
	scanf_s("%d", idade);
	while (getchar() != '\n');

	printf("\nDigite o email da pessoa: ");
	fgets(email, 100, stdin);

	printf("Nome %s\n", nome);
	printf("Email %s\n", email);
	printf("Idade %d\n", *idade);

	printf("\n num pessoas %d\n", *numPessoas);


	

	pBuffer = realloc(pBuffer, (3 * sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char)) + (*numPessoas * 1 * sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char)));
	if (!pBuffer) {
		printf("Erro ao realocar memoria\n");
		exit(1);
	}

	(*(int*)pBuffer)++;
	numPessoas = (int*)pBuffer;
	printf("num pos incremento %d", *numPessoas);

	(int*)escrever = (int*)pBuffer + 2 + (*numPessoas * (sizeof(int) + 200 * sizeof(char)));
	memcpy(escrever, idade, sizeof(int));
	(char*)escrever = (char*)pBuffer + 3 * sizeof(int) + *numPessoas * (sizeof(int) + 200 * sizeof(char));
	memcpy(escrever, nome, 100 * sizeof(char));
	(char)escrever = (char*)pBuffer + 3 * sizeof(int) + *numPessoas * (sizeof(int) + 200 * sizeof(char)) + 100 * sizeof(char);
	memcpy(escrever, email, 100 * sizeof(char));

	

}
void removerPessoa() {
	printf("remover pessoa");
}
void buscarPessoa() {
	printf("buscar pessoa");
}
void listarPessoas() {



	printf("listar pessoa");
}
