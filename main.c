#include <stdio.h>
#include <stdlib.h>
#include <String.h>

void* pBuffer;

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarPessoas();
void menu();


void main() {

	pBuffer = malloc(sizeof(int));
	if (!pBuffer) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}
	// Aqui sera o contador de pessoas
	*((int*)pBuffer) = 0;
	for (;;) {
		menu();
	}



}


void menu() {

    int* menu;

    menu = malloc(sizeof(int));
    if (!menu) {
        printf("Erro ao alocar memoria (menu)");
        exit(1);
    }
	
	printf("\nEscolha uma opcao:\n");
	printf("1 - Adicionar pessoa\n");
	printf("2 - Remover Pessoa\n");
	printf("3 - Buscar Pessoa\n");
	printf("4 - Listar Pessoas\n");
	printf("5 - Sair\n\n");


	if (scanf_s("%d", (int*)menu) != 1) {
		printf("Erro ao ler a opcao\n");
		free(pBuffer);
        free(menu);
		exit(1);
	}

	while (getchar() != '\n');

	switch (*((int*)menu))
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
        free(menu);
		exit(0);

	default:
		printf("Opcao Invalida");
		break;

    free(menu);

	}

}
void adicionarPessoa() {
	
	int* numPessoas = (int*)pBuffer;
	int* idade = malloc(sizeof(int));
	char* nome = malloc(sizeof(char) * 100);
	char* email = malloc(sizeof(char) * 320);
	

	if (!numPessoas || !idade || !nome || !email) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}
	
	printf("\nDigite o nome completo da pessoa: (max 100 caracteres) ");
	fgets(nome, 100, stdin);
	nome[strcspn(nome, "\n")] = 0;

	printf("\nDigite a idade da pessoa: ");
	scanf_s("%d", idade);
	while (getchar() != '\n');

	printf("\nDigite o email da pessoa: ");
	fgets(email, 320, stdin);
	
	printf("Nome %s\n",nome);
	printf("Email %s\n",email);
	printf("Idade %d\n", *idade);


	printf("\n num pessoas %d\n", *numPessoas);
	*numPessoas++;
	*((int*)pBuffer) = *numPessoas;
	
    printf("num pos incremento %d", *((int*)pBuffer));
	
	pBuffer = realloc(pBuffer, 2*sizeof(int) + *numPessoas * (sizeof(int) + 100 * sizeof(char) + 320 * sizeof(char)));
	if (!pBuffer) {
		printf("Erro ao realocar memoria\n");
		exit(1);
	}



	free(nome);
	free(email);
	free(idade);
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