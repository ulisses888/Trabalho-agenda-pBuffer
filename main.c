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
	int* idadeTemp = (int*)pBuffer + 2;
	char* nomeTemp = (char*)pBuffer + 3 * sizeof(int);
	char* emailTemp = (char*)pBuffer + 3 * sizeof(int) + 100 * sizeof(char);
	void* escrever = NULL;




	printf("\nDigite o nome completo da pessoa: (max 100 caracteres) ");
	fgets(nomeTemp, 100, stdin);
	nomeTemp[strcspn(nomeTemp, "\n")] = 0;

	printf("\nDigite a idade da pessoa: ");
	scanf_s("%d", idadeTemp);
	while (getchar() != '\n');

	printf("\nDigite o email da pessoa: ");
	fgets(emailTemp, 100, stdin);
	emailTemp[strcspn(emailTemp, "\n")] = 0;

	printf("Nome %s\n", nomeTemp);
	printf("Email %s\n", emailTemp);
	printf("Idade %d\n", *idadeTemp);

	pBuffer = realloc(pBuffer, 3 * sizeof(int) + 2 * (100 * sizeof(char)) + ((*numPessoas + 1) * (sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char))));
	if (!pBuffer) {
		printf("Erro ao realocar memoria\n");
		free(pBuffer);
		exit(1);
	}

	numPessoas = (int*)pBuffer;
	idadeTemp = (int*)pBuffer + 2;
	nomeTemp = (char*)pBuffer + 3 * sizeof(int);
	emailTemp = (char*)pBuffer + 3 * sizeof(int) + 100 * sizeof(char);

	(*numPessoas)++;

	escrever = (char*)pBuffer + 2 * sizeof(int) + (*numPessoas * (sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char)));
	memcpy(escrever, idadeTemp, sizeof(int));
	escrever = (char*)pBuffer + 3 * sizeof(int) + (*numPessoas * (sizeof(int) + 100 * sizeof(char)+ 100 * sizeof(char)));
	memcpy(escrever, nomeTemp, 100 * sizeof(char));
	escrever = (char*)pBuffer + 3 * sizeof(int) + *numPessoas * (sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char)) + 100 * sizeof(char);
	memcpy(escrever, emailTemp, 100 * sizeof(char));





}
void removerPessoa() {
	printf("remover pessoa");
}
void buscarPessoa() {
	printf("buscar pessoa");
}
void listarPessoas() {
	int* numPessoas = (int*)pBuffer;
	int* contador = (int*)pBuffer + 1;
	int* idade;
	char* idadeEndereco;
	char* nome;
	char* email;

	printf("valor pBuffer %d\n", (*(int*)pBuffer));
	printf("num pessoas %d\n", *numPessoas);
	if (*numPessoas == 0) {
		printf("----------------");
		printf("\n\nLISTA VAZIA\n\n");
		printf("----------------");
	}
	else {
		printf("----------------");
		printf("\n\nLISTA DE PESSOAS:\n\n");

		for (*contador = 0; *contador < *numPessoas; (*contador)++) {
			nome = (char*)pBuffer + 3 * sizeof(int) + *contador * (sizeof(int) + 2 * (100 * sizeof(char)));
			idadeEndereco = (char*)pBuffer + 2 * sizeof(int) + (*contador * (sizeof(int) + 2 * (100 * sizeof(char))));
			idade = (int*)idadeEndereco;
			email = (char*)pBuffer + 3 * sizeof(int) + *contador * (sizeof(int) + 2 * (100 * sizeof(char))) + 100 * sizeof(char);

			printf("[%d] Nome = %s | Idade = %d | Email = %s\n", *contador + 1, nome, *idade, email);

		}
		printf("----------------");
	}
}
