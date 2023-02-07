// #define NDEBUG // disables assert()
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "forca.h"

void abertura(void){
	printf("*********************\n");
	printf("*   Jogo de Forca   *\n");
	printf("*********************\n\n");
}

void chuta(char chutes[26], int* tentativas){
	char chute;
	scanf(" %c", &chute);

	chutes[*tentativas] = chute;
	(*tentativas)++;
}

bool jachutou(char letra, char chutes[26], int tentativas){

	for (int j = 0; j < tentativas; ++j) {
		if (chutes[j] == letra) {
			return true;
		}

	}
	return false;
}
void desenhaForca(char palavraSecreta[20], char chutes[26], int tentativas){
	for (int i = 0; i < strlen(palavraSecreta); ++i) {

		// aqui esta o codigo
		bool achou = jachutou(palavraSecreta[i],chutes,tentativas);

		if(achou){
			printf("%c ", palavraSecreta[i]);
		}else{
			printf("_ ");
		}

	}
	printf("\n");
}
void escolhePalavra(char palavraSecreta[20]){
	FILE* f;
	f= fopen("palavras.txt","r");

	if(f == NULL){
		printf("Desculpe, banco de dados nao disponivel\n\n");
		exit(1);
	}
	int numPalavras;
	fscanf(f, "%d",&numPalavras);

	srand(time(0));
	int randomico = rand()% numPalavras; 

	for (size_t i = 0; i <= randomico; ++i) {
		fscanf(f, "%s",palavraSecreta);
	}
	fclose(f);
}
void adicionapalavra(){

	char quer;
	printf("Você deseja adicionar uma nova palavra no jogo(S/N)\n");

	scanf(" %c",&quer);
	if(quer == 'S'){
		char novaPalavra[20];
		printf("Qual é a nova palavra?\n");
		scanf("%s",novaPalavra);

		FILE* f;

		if(f == NULL){
			printf("Desculpe, banco de dados nao disponivel\n\n");
			exit(1);
		}
		f = fopen("palavras.txt", "r+");

		int qntd;
		fscanf(f, "%d",&qntd);
		qntd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d",qntd);
		
		fseek(f,0, SEEK_END);

		fprintf(f, "%s", novaPalavra);

		fclose(f);
	}
}

bool ganhou(int tentativas, char palavraSecreta[20], char chutes[26]){
	for (size_t i = 0; i < strlen(palavraSecreta); ++i) {
		if(!jachutou(palavraSecreta[i], chutes, tentativas)){
			return false;
		}
	}
	return true;

}

bool enforcou(int tentativas, char palavraSecreta[20],char chutes[26]){
	int erros = chutesErrados(tentativas,palavraSecreta,chutes);
	return erros>=5; 
}
int chutesErrados(int tentativas, char palavraSecreta[20],char chutes[26]){
	int erros = 0;
	for (size_t i = 0; i < tentativas; ++i) {
		bool existe = false;
		for (size_t j = 0; j < strlen(palavraSecreta); ++j) {
			
			if(chutes[i] == palavraSecreta[j]){
				existe = true;
				break;
			}
		}
		if(!existe) erros++;
		
	}
	return erros;
}

int main(int argc, char *argv[])
{

	char palavraSecreta[20] ;
	char chutes[26];
	int chutesDados = 0;

	escolhePalavra(palavraSecreta);
	abertura();

	do {
		desenhaForca(palavraSecreta,chutes,chutesDados);
		chuta(chutes, &chutesDados);
		int erros = chutesErrados(chutesDados,palavraSecreta,chutes);

		printf("  _______       \n");
		printf(" |/      |      \n");
		printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
				(erros>=1?'_':' '), (erros>=1?')':' '));
		printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
				(erros>=2?'|':' '), (erros>=3?'/': ' '));
		printf(" |       %c     \n", (erros>=2?'|':' '));
		printf(" |      %c %c   \n", (erros>=4?'/':' '), 
				(erros>=4?'\\':' '));
		printf(" |              \n");
		printf("_|___           \n");
		printf("\n\n");

	} while(!ganhou(chutesDados, palavraSecreta,chutes) && !(enforcou(chutesDados, palavraSecreta,chutes)));
	if(ganhou(chutesDados, palavraSecreta,chutes)) {
		printf("\nParabéns, você ganhou!\n\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");

	} else {
		printf("\nPuxa, você foi enforcado!\n");
		printf("A palavra era **%s**\n\n", palavraSecreta);

		printf("    _______________         \n");
		printf("   /               \\       \n"); 
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
	}
	adicionapalavra();
	return EXIT_SUCCESS;
}
