#include <stdio.h>
#include <string.h>

void main() {
    int chave[2][2];
    char mensagem[255];
    int msgcode[255];
    int msgcifrada[255];
    int determinante;
    int imm = 0;
    char alfabeto[26] = "zabcdefghijklmnopqrstuvwxy";

    puts("Informe a  mensagem que deseja encriptar: ");
    gets(mensagem);

    for(int i = 0; i < strlen(mensagem); i++) {
        for(int j = 0; j < strlen(alfabeto); j++) {
            if(mensagem[i] == alfabeto[j]) {
                msgcode[i] = j;
                break;
            }
        }
    }

    printf("Tamanho da mensagem: %d caracteres\n", strlen(mensagem));

    puts("Informe a matriz de encriptação 2x2: ");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("Informe o elemento a[%d,%d]: ", i+1, j+1);
            scanf("%d", &chave[i][j]);
        }
    }

    //Calcula o Determinante
    determinante = chave[0][0]*chave[1][1] - chave[0][1]*chave[1][0];
    printf("O determinante dessa matriz é: %d\n", determinante);

    //Calcula a matriz inversa
    printf("A Matriz inversa é: \n%d\t%d\n%d\t%d\n", 
    chave[1][1],-chave[0][1],-chave[1][0],chave[0][0]);

    //Calcula o inverso multiplicativo modular do determinante
    for(imm = 0; (imm*determinante)%strlen(alfabeto) != 1 ; imm++) {}
    printf("O inverso multiplicativo modular do determinante é: %d\n", imm);

    //Cifra a Mensagem
    for(int i = 0; i < strlen(mensagem); i++) {
        msgcifrada[i] = (chave[0][0]*msgcode[i] + (chave[0][1])*msgcode[i+1])%strlen(alfabeto);
        msgcifrada[i+1] = (chave[1][0]*msgcode[i] + (chave[1][1])*msgcode[i+1])%strlen(alfabeto);
        ++i;
    }

    printf("mensagem cifrada: ");
    for(int i = 0; i < strlen(mensagem); i++) {
        printf("%c",alfabeto[msgcifrada[i]]);
    }

    printf("\n");

}