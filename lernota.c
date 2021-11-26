#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <windows.h>



void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

int checkIfFileExists(const char *filename);
int menuOptions();
void getStudentsAndNotes();
void getLinesFromTxt();

int main(int argc, char *argv[]) {
	int option = -1;
	
    while (option != 0)
    {
    	option = menuOption();
    	
    	if (option == 1){
    		// Obter o número de alunos
    		getStudentsAndNotes();
		}
    	
    	if (option == 2){
    		if(!checkIfFileExists("Pauta.txt"))
    			printf("\n\nArquivo de notas salvas inexistente!\n");
			else
				getLinesFromTxt();
   			system("pause");
		}
	}
}

int checkIfFileExists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else  
        return 0;
}

int menuOption(){
	int op = 0;
	
	system("cls");
	gotoxy(1,1); printf("--- LER NOTAS ---");
	gotoxy(1,2); printf("1 - Criar arquivo de notas");
	gotoxy(1,3); printf("2 - Carregar notas salvas ");
	gotoxy(1,4); printf("3 - Resultados (Media Aritimetica)");
	gotoxy(1,5); printf("4 - Resultados (Media Ponderada=> pesos 3,3, 4)");
	gotoxy(1,6); printf("5-  Resultados (Media geometrica)");
	gotoxy(1,8); printf("0 - SAIR");
	
	gotoxy(1,10); printf("Executar tarefa: "); scanf("%i", &op);
	
	return op;
}

void getStudentsAndNotes(){
	int linhas = 0;
	int c, l, conta;
	
	gotoxy(1,11); printf("Informe a quantidade de alunos:"); scanf("%i", &linhas);
	
	if (linhas-1 > 0){
		
		char alunos [linhas][40];
			char notas[linhas*4][3];

		conta = 0;
		
		for (l=0; l<linhas; l++){
			system("cls"); 
			gotoxy(1,1); printf("--- MATRIZ DE ALUNOS E NOTAS POR BIMESTRE ---");	
			gotoxy(1,2); printf ("Nome do %io. aluno: ", l+1); scanf("%s", alunos[l]);
			
			for (c=0; c<4; c++){
				gotoxy(1,3+c); printf("Nota do %i bimestre: ", c+1); scanf("%s", notas[conta]);
				conta++;
			}
		}
		
		/*Grava os dados da matriz num arquivo texto
		 criando a variável ponteiro para o arquivo
		*/
  		FILE *pont_arq;
  		
  		//abrindo o arquivo com tipo de abertura w
  		pont_arq = fopen("Pauta.txt", "w");
  		
  		conta = 0;
  		for (l=0; l<linhas; l++){
  			fprintf(pont_arq, "%s", alunos[l]);
  			fprintf(pont_arq, "\n");
  			for (c=0; c<4; c++){
  				fprintf(pont_arq, "%s", notas[conta]);
  				if (c+1 < 4)
  					fprintf(pont_arq, "%c", ';');
  				conta++;
			  }
			  
			fprintf(pont_arq,"\n");
		  }
  
  		// Fechar o arquivo
  		fclose(pont_arq);
	}
}

void getLinesFromTxt(){
	FILE *in_file = fopen("Pauta.txt", "r");
	int conta=0;
	
    struct stat sb;
    stat("Pauta.txt", &sb);

    char *file_contents = malloc(sb.st_size);

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        printf("> %s\n", file_contents);
        conta++;
    }

    fclose(in_file);	
}

