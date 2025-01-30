#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* pBuffer = NULL;

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarPessoas();
void menu();
void buscaNome();
void buscaEmail();


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
	void* menu = (int)pBuffer + 1;


	


	printf("\nDigite o nome completo da pessoa: (max 100 caracteres) ");
	fgets(nomeTemp, 100, stdin);
	nomeTemp[strcspn(nomeTemp, "\n")] = 0;

	printf("\nDigite a idade da pessoa: ");
	scanf_s("%d", idadeTemp);
	while (getchar() != '\n');

	printf("\nDigite o email da pessoa: ");
	fgets(emailTemp, 100, stdin);
	emailTemp[strcspn(emailTemp, "\n")] = 0;

	printf("\nNome %s\n", nomeTemp);
	printf("\nEmail %s\n", emailTemp);
	printf("\nIdade %d\n", *idadeTemp);

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
	escrever = (char*)pBuffer + 3 * sizeof(int) + (*numPessoas * (sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char)));
	memcpy(escrever, nomeTemp, 100 * sizeof(char));
	escrever = (char*)pBuffer + 3 * sizeof(int) + *numPessoas * (sizeof(int) + 100 * sizeof(char) + 100 * sizeof(char)) + 100 * sizeof(char);
	memcpy(escrever, emailTemp, 100 * sizeof(char));





}
void removerPessoa() {
	printf("remover pessoa");
}
void buscarPessoa() {


	if (*((int*)pBuffer) == 0) {
		printf("\nPrimeiro voce precisa adicionar um nome na lista\n");
	}
	else {


		printf("\nEscolha o modo de busca:\n");
		printf("1 - Por nome\n");
		printf("2 - Por email\n");


		int* menu;
		menu = ((int*)pBuffer + 1);

		if (scanf_s("%d", menu) != 1) {
			printf("Erro ao ler a opcao\n");
			free(pBuffer);
			exit(1);
		}

		while (getchar() != '\n');

		switch (*menu)
		{
		case 1:
			buscaNome();
			break;

		case 2:

			buscaEmail();
			break;

		default:
			printf("\nOpcao invalida\n");
			break;
		}


	}
}
void listarPessoas() {
	int* numPessoas = (int*)pBuffer;
	int* contador = (int*)pBuffer + 1;
	int* idade;
	char* idadeEndereco;
	char* nome;
	char* email;

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
void buscaNome() {

	int* numPessoas = (int*)pBuffer;
	int* contador = (int*)pBuffer + 1;
	char* nomeGuardado;
	int* posicao = (int*)pBuffer + 2;
	

	int* idade;
	char* idadeEndereco;
	char* nome;
	char* email;

	*posicao = -1;

	char* nomeTemp = (char*)pBuffer + 3 * sizeof(int);
	printf("\nDigite o nome completo da pessoa: (max 100 caracteres) ");
	fgets(nomeTemp, 100, stdin);
	nomeTemp[strcspn(nomeTemp, "\n")] = 0;

	for (*contador = 0; *contador < *numPessoas; (*contador)++) {
		nomeGuardado = (char*)pBuffer + 3 * sizeof(int) + *contador * (sizeof(int) + 2 * (100 * sizeof(char)));
		if (strcmp(nomeTemp, nomeGuardado) == 0) {
			*posicao = *contador;
			break;
		}

	}

	if (*posicao != -1) {
		nome = (char*)pBuffer + 3 * sizeof(int) + *posicao * (sizeof(int) + 2 * (100 * sizeof(char)));
		idadeEndereco = (char*)pBuffer + 2 * sizeof(int) + (*posicao * (sizeof(int) + 2 * (100 * sizeof(char))));
		idade = (int*)idadeEndereco;
		email = (char*)pBuffer + 3 * sizeof(int) + *posicao * (sizeof(int) + 2 * (100 * sizeof(char))) + 100 * sizeof(char);

		printf("[%d] Nome = %s | Idade = %d | Email = %s\n", *contador + 1, nome, *idade, email);
	}
	else {
		printf("\nNome nao encontrado\n");
	}


}
void buscaEmail() {

	int* numPessoas = (int*)pBuffer;
	int* contador = (int*)pBuffer + 1;
	char* emailGuardado;
	int* posicao = (int*)pBuffer + 2;
	int* idade;
	char* idadeEndereco;
	char* nome;
	char* email;

	*posicao = -1;

	char* emailTemp = (char*)pBuffer + 3 * sizeof(int) + 100;

	printf("\nDigite o email da pessoa: ");
	fgets(emailTemp, 100, stdin);
	emailTemp[strcspn(emailTemp, "\n")] = 0;

	for (*contador = 0; *contador < *numPessoas; (*contador)++) {
		emailGuardado = (char*)pBuffer + 3 * sizeof(int) + (*contador * (sizeof(int) + 2 * (100 * sizeof(char)))) + 100 * sizeof(char);
		if (strcmp(emailTemp, emailGuardado) == 0) {
			*posicao = *contador;
			break;
		}

	}

	if (*posicao != -1) {
		nome = (char*)pBuffer + 3 * sizeof(int) + *posicao * (sizeof(int) + 2 * (100 * sizeof(char)));
		idadeEndereco = (char*)pBuffer + 2 * sizeof(int) + (*posicao * (sizeof(int) + 2 * (100 * sizeof(char))));
		idade = (int*)idadeEndereco;
		email = (char*)pBuffer + 3 * sizeof(int) + *posicao * (sizeof(int) + 2 * (100 * sizeof(char))) + 100 * sizeof(char);

		printf("[%d] Nome = %s | Idade = %d | Email = %s\n", *contador + 1, nome, *idade, email);
	}
	else {
		printf("\nEmail nao encontrado\n");
	}


}
