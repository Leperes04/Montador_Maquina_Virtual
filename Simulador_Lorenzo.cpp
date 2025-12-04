#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>

//ARRUMAR AS OPERAÇÕES --> ASSEMBLY ESCRITO DE FORMA ERRADA
using namespace std;

int reg[3]; //R0 = 1, R1 = 2, R2 = 3;

struct Memoria {
    int op; 
    int r1;
    int r2;
    int r3;
};

struct Memoria mem[256];
int dados[256];

int qtd_dados = 0;
int linha_num;
void lerarquivo()
{
    FILE * f ;
    int i=0;
    char nomeArq [] = "../NOME_ARQUIVO_SAIDA.txt";

    f = fopen (nomeArq, "r") ;
    if(!f)
    {
        printf("ERRO AO ABRIR O ARQUIVO");
    }

    fscanf(f, "%d", &qtd_dados); //ler a primeira linha pra ver quantos dados terão
    printf("\nQuantidade de dados: %d\n", qtd_dados);

    for(i=1; i < qtd_dados + 1; i++) // salva os dados 
    {
        fscanf(f, "%d", &dados[i]);
        printf("\nVALOR DO DADO SALVO: %d\n", dados[i]);
    }

    linha_num = qtd_dados + 2;
    char linha[256];
    int ler_linha = linha_num;
    while (fgets(linha, sizeof(linha), f)) 
    {
        if (linha[0] == '\n' || linha[0] == '\r')
         {
            continue;
        }

        sscanf(linha, "%d %d %d %d",&mem[ler_linha].op, &mem[ler_linha].r1, &mem[ler_linha].r2, &mem[ler_linha].r3);
        printf("Linha %d -> ", ler_linha);
        printf("opcode: %d, r1:%d, r2:%d, r3;%d", mem[ler_linha].op, mem[ler_linha].r1, mem[ler_linha].r2, mem[ler_linha].r3);
        printf("\n");
        ler_linha ++;
    }
}

void simulador()
{
    int executa = 1;
    int pc = linha_num;
    int valor; 

    printf("\nO codigo comeca a rodar na linha: %d", linha_num);
    printf("\n O OPCODE DA PRIMEIRA INSTRUCAO E: %d", mem[linha_num].op);

    while(executa == 1 )
    {
        switch(mem[pc].op)
        {
            case 0:
                reg[mem[pc].r1] = reg[mem[pc].r2] + reg[mem[pc].r3];
                printf("\nVALOR DA SOMA = %d", reg[mem[pc].r1]);
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
                printf("\nCHEGOU NO STORE");
                dados[mem[pc].r1] = reg[mem[pc].r2];
                pc++;
                break;
            
            case 6:
                printf("\nCHEGOU NO BRANCH");
                pc = mem[pc].r1;
                printf("\nVALOR DO PC %d", pc);
                break;
            
            case 7:
                printf("\nCHEGOU NO BEQ");
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
                printf("\nCHEGOU NO BGT");
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
                printf("\nCHEGOU NO BLT");
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
                printf("\nFEZ O OUT");
                printf("\nVALOR DO DADO: %d", dados[mem[pc].r1]);
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
                printf("\nPrograma finalizado!!");
                break;
        }
    }
}

int main()
{
    lerarquivo();
    simulador();
}

