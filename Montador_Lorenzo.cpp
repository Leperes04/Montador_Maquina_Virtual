//Montador --> Traduz código assembly para código de maquina
// ARRUMAR LER AREA DE DADOS --> SEGUNDA PALAVRA NAO É WORD
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_simbolos 100
#define max_linha 30 //chutei um valor para tamanho maximo da linha
#define max_token 5 

struct simbolo //struct para salvar o token e o endereço do token
{
    char simbolo[max_linha]; //tamanho maximo que um token pode ter é o tamanho maximo de uma linha
    int endereco;
};

struct opcode
{
    char opcode[20]; //NOME DO OPCODE
    int numero; //NUMERO QUE REPRESENTA O OPCODE
};

struct regs
{
    char reg[10]; //NOME DO REGISTRADOR
    int numero; //NUMERO QUE REPRESENTA O REGISTRADOR
};

struct simbolo TabelaVariaveis[max_simbolos];
struct simbolo TabelaSimbolos[max_simbolos]; //guardar as labels e seus endereços
struct simbolo instrucao[max_simbolos]; //guardar instrucoes e seus enderecos
int qtdlabels = 0;
int qtdinstrucao = 0;
int qtdWORDS = 0;




void passo1() //--------------- FEITO --------------------
{
    FILE *f ;
    char linha[100];
    f = fopen ("../NOME_ARQUIVO_ASSEMBLY.txt", "r") ; //Problema em ler o aquivo, tentar fazer em argc, argv
    if(f == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }
    int enderecoatual = 2;
    while (fgets(linha, sizeof(linha),f ) != NULL)
    {

        linha[strcspn(linha, "\r\n")] = 0; // tira o /n ou /r da leitura dos arquivos
        char *token = strtok(linha, " ,"); //procura o primeiro token dentro de linha e os separa de acordo com , ou espaço
        while (token != NULL) 
        {

            if(token[strlen(token) - 1] == ':')
            {
                token[strlen(token) - 1] = '\0'; 
                strcpy(TabelaSimbolos[qtdlabels].simbolo, token);
                TabelaSimbolos[qtdlabels].endereco = enderecoatual;
                qtdlabels++;
            }
            else
            {
                strcpy(instrucao[qtdinstrucao].simbolo, token);
                instrucao[qtdinstrucao].endereco = enderecoatual;
                qtdinstrucao++;
            }
            token = strtok(NULL, " ,\t"); //passa null pois a funcao guarda onde parou, e passar null significa falar isso
        }
        enderecoatual++;
    }
    fclose(f);
    printf("\nTabela de simbolos");
    int i;
    for(i = 0; i < qtdlabels; i++)
    {
        printf("\nLABELS: %s | Endereco: %d", TabelaSimbolos[i].simbolo, TabelaSimbolos[i].endereco);
    }
    printf("\n\nInstrucoes e enderecos:");
    for(i = 0; i < qtdinstrucao; i++)
    {
        printf("\nSimbolo: %s | Endereco: %d", instrucao[i].simbolo, instrucao[i].endereco);
    }
}

struct opcode TabelaOpcode[13] = //NOME DOS TOKENS E SEU CÓDIGO CORRESPONDENTE
{
    {"ADD", 0},
    {"SUB", 1},
    {"MUL", 2},
    {"DIV", 3},
    {"MV", 4},
    {"ST", 5},
    {"BR", 6},
    {"BEQ", 7},
    {"BGT", 8},
    {"BLT", 9},
    {"OUT", 10},
    {"IN", 11},
    {"STP", 12}
};

struct regs TabelaRegistradores[3]= //NOME DOS REGISTRADORES E SEU CÓDIGO CORRESPONDENTE
{
    {"R0", 1},
    {"R1", 2},
    {"R2", 3},
};

int buscaopcode(char *token)
{
    for(int i = 0; i <13; i++)
    {
        if(strcmp(TabelaOpcode[i].opcode, token) == 0) //verifica se o token passado coincide com um que esta na tabela de opcode
        {
            return TabelaOpcode[i].numero;
        }
    }
    return -1;
}

int buscareg(char *token)
{
    for(int i = 0; i < 3; i++)
    {
        if(strcmp(TabelaRegistradores[i].reg, token) == 0)
        {
            return TabelaRegistradores[i].numero;
        }
    }
    return -1;
}

int buscaLabel(char *token)
{
    for(int i = 0; i< qtdlabels; i++)
    {
        if(strcmp(TabelaSimbolos[i].simbolo, token) == 0)
        {
            return TabelaSimbolos[i].endereco;
        }
    }
    return -1;
}

int buscaVariavel(char *token)
{
    for(int i=0; i < qtdWORDS; i++)
    {
        if(strcmp(TabelaVariaveis[i].simbolo, token) == 0)
        {
            printf("\nENCONTRADO");
            return TabelaVariaveis[i].endereco;
        }
    }
    printf("\nNAO ENCONTRADO");
    return -1;
}


void passo2()
{
    FILE *saida = fopen("../NOME_ARQUIVO_SAIDA.txt", "w"); //abre o arquivo que sera escrito o código traduzido
    if(saida == NULL)
    {
        printf("NAO FOI POSSÍVEL ABRIR O ARQUIVO DE SAIDA");
        return;
    }
    else
    {
        int i = 0;
        while(i < qtdinstrucao && strcmp(instrucao[i+1].simbolo, "WORD"  ) == 0)
        {
            strcpy(TabelaVariaveis[qtdWORDS].simbolo, instrucao[i].simbolo);
            TabelaVariaveis[qtdWORDS].endereco = instrucao[i].endereco - 1;
            printf("\nNOME DA VARIAVEL: %s", TabelaVariaveis[qtdWORDS].simbolo);
            printf("Endereco da Variavel: %d", TabelaVariaveis[qtdWORDS].endereco);
            i = i+3;
            qtdWORDS  = qtdWORDS + 1;
        }
        printf("\nQUANTIDADE DE VARIAVEIS: %d", qtdWORDS );
        fprintf(saida, "%d\n", qtdWORDS);

        i=0;
        for(int k = 0; k < qtdWORDS; k++)
        {
            char *valor = instrucao[i + 2].simbolo;
            fprintf(saida, "%s\n", valor);
            i = i+3;
        }

        int inicio_codigo = i;
        int endereco_anterior = instrucao[inicio_codigo].endereco;
        for(int j = inicio_codigo; j < qtdinstrucao; j++) //i vai receber valor inicial de quantidade de lidas de 
        {
            if(instrucao[j].endereco != endereco_anterior) //separação por linhas
            {
                fprintf(saida, "\n");
                endereco_anterior = instrucao[j].endereco;
            }

            char *token = instrucao[j].simbolo;
            int codigo;

            codigo = buscaopcode(token);
            if(codigo != -1) 
            {
                fprintf(saida, "%02d ", codigo );
            }
            else
            {
                codigo = buscareg(token);
                if(codigo != -1)
                {
                    fprintf(saida, "%02d ", codigo);
                }
                else
                {
                    codigo = buscaLabel(token);
                    if(codigo != -1)
                    {
                        fprintf(saida, "%02d ", codigo);
                    }
                    else
                    {
                        codigo = buscaVariavel(token);
                        if(codigo != -1)
                        {
                            fprintf(saida, "%02d", codigo);
                        }
                        else
                        {
                            if(token != NULL && isdigit(*token))
                            {
                                fprintf(saida, "%02d ", atoi(token)); //converte um char de numero em um inteiro
                            }
                            else
                            {
                                fprintf(saida, "??"); //é um dado que nao existe
                            }
                        }  
                    }
                }
            }
        }
    }
    fclose(saida);
    printf("\nPasso 2 concluido com sucesso!!!!");
}


int main()
{
    passo1(); //Tabela de simbolos e opcode, lê o arquivo das instruções, identifica labels e salva o endereço
              //na tabela de simbolos e calcula o endereço de cada instrucao

    passo2(); //Usa a tabela de simbolos para gerar o código final em linguagem de máquina, substitui as labels pelos
              //enderecos da tabela, converte mnemonicos, registradores e constantes em binario
}