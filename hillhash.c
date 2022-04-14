#include <stdio.h>
#include <string.h>

    int chave[2][2];
    int chavedecod[2][2];
    int msgcode[255];
    int msgcifrada[255];
    int determinante;
    int imm = 0;
    char alfabeto[26] = "zabcdefghijklmnopqrstuvwxy";

void getChave() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("Informe o elemento a[%d,%d]: ", i+1, j+1);
            scanf("%d", &chave[i][j]);
        }
    }
}

const char* cifra(char mensagem[255]) {
    char mensagemcifrada[strlen(mensagem)];
    //Cifra a Mensagem
    for(int i = 0; i < strlen(mensagem); i++) {
        for(int j = 0; j < strlen(alfabeto); j++) {
            if(mensagem[i] == alfabeto[j]) {
                msgcode[i] = j;
                printf(" %d ",j);
                break;
            }
        }
    }

    for(int i = 0; i < strlen(mensagem); i++) {
        msgcifrada[i] = (chave[0][0]*msgcode[i] + (chave[0][1])*msgcode[i+1])%strlen(alfabeto);
        msgcifrada[i+1] = (chave[1][0]*msgcode[i] + (chave[1][1])*msgcode[i+1])%strlen(alfabeto);
        ++i;
    }

    //printf("mensagem cifrada: ");
    char result[strlen(mensagem)];
    for(int i = 0; i < strlen(mensagem); i++) {
        //printf("%c",alfabeto[msgcifrada[i]]);
        printf(" %d-",msgcifrada[i]);
        result[i] = alfabeto[msgcifrada[i]];
    }
    char *saida;

    saida = malloc(sizeof(char) * (strlen(result) + 1));
    strncpy(saida,result,strlen(mensagem));

    return saida;
}

void showMatrix() {
    printf("A Matriz é: \n%d\t%d\n%d\t%d\n", 
    chave[0][0],chave[0][1],chave[1][0],chave[1][1]);
}

void showInversa() {
    printf("A Matriz inversa é: \n%d\t%d\n%d\t%d\n", 
    chave[1][1],-chave[0][1],-chave[1][0],chave[0][0]);
}

void showDecodificadora() {
    int x = strlen(alfabeto);
    chavedecod[0][0] = chave[1][1]*getImm()%x > 0 ? chave[1][1]*getImm()%x : chave[1][1]*getImm()%x + x;
    chavedecod[0][1] = -chave[0][1]*getImm()%x > 0 ? -chave[0][1]*getImm()%x : -chave[0][1]*getImm()%x + x;
    chavedecod[1][0] = -chave[1][0]*getImm()%x > 0 ?-chave[1][0]*getImm()%x : -chave[1][0]*getImm()%x + x;
    chavedecod[1][1] = chave[0][0]*getImm()%x > 0 ? chave[0][0]*getImm()%x : chave[0][0]*getImm()%x + x;
    printf("A Matriz decodificadora é: \n%d\t%d\n%d\t%d\n", 
    chavedecod[0][0],
    chavedecod[0][1],
    chavedecod[1][0],
    chavedecod[1][1]
    );
}

int getDeterminante() {
    return chave[0][0]*chave[1][1] - chave[0][1]*chave[1][0];
}

int getImm() {
    int imm;
    for(imm = 0; (imm*getDeterminante())%strlen(alfabeto) != 1 ; imm++) {}
    return imm;
}

const char* decifra(char mensagem[255]) {

    for(int i = 0; i < strlen(mensagem); i++) {
        for(int j = 0; j < strlen(alfabeto); j++) {
            if(mensagem[i] == alfabeto[j]) {
                msgcode[i] = j;
                break;
            }
        }
    }

    for(int i = 0; i < strlen(mensagem); i++) {
        msgcifrada[i] = (chavedecod[0][0]*msgcode[i] + (chavedecod[0][1])*msgcode[i+1])%strlen(alfabeto);
        msgcifrada[i+1] = (chavedecod[1][0]*msgcode[i] + (chavedecod[1][1])*msgcode[i+1])%strlen(alfabeto);
        ++i;
    }

    //printf("\nmensagem Decifrada: ");
    char result[strlen(mensagem)];
    for(int i = 0; i < strlen(mensagem); i++) {
        //printf("%c",alfabeto[msgcifrada[i]]);
        result[i] = alfabeto[msgcifrada[i]];
    }

    char *saida;

    saida = malloc(sizeof(char) * (strlen(result) + 1));
    strncpy(saida,result,strlen(mensagem));

    return saida;
}

int main() {
    printf("%d", 554%26);
    char mensagem[255];

    puts("Informe a  mensagem que deseja encriptar: ");
    gets(mensagem);

    puts("Informe a matriz de encriptação 2x2: ");
    
    getChave();

    showMatrix();
    showInversa();
    showDecodificadora();

    printf("O determinante é: %d\n", getDeterminante());
    printf("O Inverso Multiplicativo Modular é: %d\n", getImm());

    printf("\nA mensagem cifrada é: %s \n",cifra(mensagem));
    printf("\nA mensagem Decifrada é: %s \n", decifra(cifra(mensagem)));

    printf("\n");

    return 0;
}