#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

int reg[3];

struct Memoria {
    int op; 
    int r1;
    int r2;
    int r3;
};

struct Memoria mem[32];
int dados[32];
void lerarquivo()
{
    FILE * f ;
    int i = 0;
    char nomeArq [] = "../instrucoes.txt";

    f = fopen (nomeArq, "r") ;
    if(!f)
    {
        printf("ERRO AO ABRIR O ARQUIVO");
    }
    while (!feof(f))
    {
        fscanf (f, "%d%d%d%d", &mem[i].op, &mem[i].r1,&mem[i].r2,&mem[i].r3) ;
        printf(" op= %d r1= %d r2=%d r3=%d\n", mem[i].op, mem[i].r1,mem[i].r2,mem[i].r3) ;
        i = i+1;
    }
}

void simulador()
{
    int executa = 1;
    int pc = 0;
    int valor;

    while(executa == 1 )
    {
        switch(mem[pc].op)
        {
            case 0:
                reg[mem[pc].r1] = reg[mem[pc].r2] + reg[mem[pc].r3];
                printf("\nVALOR DA SOMA  = %d", reg[mem[pc].r1]);
                pc++;
                break;
            
            case 1:
                reg[mem[pc].r1] = reg[mem[pc].r2] - reg[mem[pc].r3];
                printf("\nVALOR DA SUBTRAÇÃO%d", reg[mem[pc].r1]);
                pc++;
                break;

            case 2:
                reg[mem[pc].r1] = reg[mem[pc].r2] * reg[mem[pc].r3];
                printf("\nVALOR DA MULTIPLICACAO%d", reg[mem[pc].r1]);
                pc++;
                break;
            
            case 3:
                if(reg[mem[pc].r3] != 0)
                    reg[mem[pc].r1] = reg[mem[pc].r2] / reg[mem[pc].r3];
                else
                    printf("Erro: divisao por zero!\n");
                printf("\nVALOR DA DIVISAO %d", reg[mem[pc].r1]);
                pc++;
                break;

            case 4:
                reg[mem[pc].r1] = dados[mem[pc].r2];
                printf("\nVALOR MOVIDO %d", reg[mem[pc].r1]);    
                pc++;
                break;

            case 5:
                dados[mem[pc].r1] = reg[mem[pc].r2];
                pc++;
                break;
            
            case 6:
                pc = mem[pc].r1;
                printf("\nVALOR DO PC %d", pc);
                break;
            
            case 7:
                if(reg[mem[pc].r1] == reg[mem[pc].r2] )
                {
                    pc = mem[pc].r3;
                    printf("\nVALOR DO PC%d", pc);
                    break;
                }
                pc++;
                printf("\nVALOR DO PC%d",pc);
                break;

            case 8:
                if(reg[mem[pc].r1] > 0)
                {
                    pc = mem[pc].r3;
                    printf("\nVALOR DO PC %d", pc);
                    break;
                }
                pc++;
                printf("\nVALOR DO PC%d", pc);
                break;
                
            case 9:
                if(reg[mem[pc].r1] < 0)
                {
                    pc = mem[pc].r3;
                    printf("\nVALOR DO PC%d",pc);
                    break;
                }
                pc++;
                printf("\nVALOR DO PC%d",pc);
                break;

            case 10:
                printf("\nVALOR DO DADO%d", dados[mem[pc].r1]);
                pc++;
                break;
            
            case 11:
                printf("\nDigite o valor para ser adicionado: ");
                scanf("%d", &valor);
                dados[mem[pc].r1] = valor;
                pc++;
                break;
            
            case 12:
                executa = 0;
                break;
        }
    }
}

int main()
{
    lerarquivo();
    simulador();
}

