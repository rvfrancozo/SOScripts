#include <stdio.h>
#include <string.h>

    int chave[2][2];
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

void cifra(char mensagem[255]) {
    char mensagemcifrada[strlen(mensagem)];
    //Cifra a Mensagem
    for(int i = 0; i < strlen(mensagem); i++) {
        for(int j = 0; j < strlen(alfabeto); j++) {
            if(mensagem[i] == alfabeto[j]) {
                msgcode[i] = j;
                break;
            }
        }
    }

    for(int i = 0; i < strlen(mensagem); i++) {
        msgcifrada[i] = (chave[0][0]*msgcode[i] + (chave[0][1])*msgcode[i+1])%strlen(alfabeto);
        msgcifrada[i+1] = (chave[1][0]*msgcode[i] + (chave[1][1])*msgcode[i+1])%strlen(alfabeto);
        ++i;
    }

    printf("mensagem cifrada: ");
    for(int i = 0; i < strlen(mensagem); i++) {
        printf("%c",alfabeto[msgcifrada[i]]);
    }
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
    printf("A Matriz decodificadora é: \n%d\t%d\n%d\t%d\n", 
    chave[1][1]*getImm()%x > 0 ? chave[1][1]*getImm()%x : chave[1][1]*getImm()%x + x,
    -chave[0][1]*getImm()%x > 0 ? -chave[0][1]*getImm()%x : -chave[0][1]*getImm()%x + x,
    -chave[1][0]*getImm()%x > 0 ?-chave[1][0]*getImm()%x : -chave[1][0]*getImm()%x + x,
    chave[0][0]*getImm()%x > 0 ? -chave[1][0]*getImm()%x : -chave[1][0]*getImm()%x + x
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

void main() {
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

    cifra(mensagem);

    printf("\n");
}