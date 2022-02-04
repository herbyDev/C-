#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define ANO_ATUAL 2021
#define PI 3.14159265

/*
Nome: Herby Henrique de Castro santana
Email: herby.junior@gmail.com
*/

int main(int argc, char *argv[])
{

    system("date /t");
    system("time /t");

    setlocale(LC_ALL,"");
    char nome_[] = {'1','2','3','4','5','6','7','8','9','10'};
    char nome[50];
    char sobrenome[50];
    char nomeCompleto[100];
    char nascimento[11];
    int idade=0;
    float num1;
    float num2;
    float soma;
    float produto;
    float quadrado1;
    float quadrado2;
    float somaQUAD;
    float raizQ;
    float senDif;
    float diferenca;
    float modulo;
    float fahrenheit;
    float celsius;
    int n;
    int i;
    int fatorial=1;
    int hora=0;
    char num[10];
    int media;
    int adicao =0;
    int numConvert;

    int x;
    printf("Nome: Herby Henrique de Castro santana.\n");
    printf("Email: herby.junior@gmail.com\n");
    printf("Exercício realizado em 30 e 31 de agosto de 2021\n\n");

    printf("******  DIGITE A OPÇÃO DESEJADA: ****** \n\n");
    printf("1-CADASTRO DE DADOS\n");
    printf("2-REALIAR CÁLCULOS\n");
    printf("3-CALCULAR CONVERSÃO DE TEMPERATURA\n");
    printf("4-CALCULAR FATORIAL\n");
    printf("5-VERIFICAR A HORA\n");
    printf("6-CALCULAR MÉDIA\n");
    printf("7-IMPRIMIR TABUADA\n");
    printf("8-IMPRIMIR MATRIZ\n");
    printf("9-SAIR\n\n");
    scanf("%i", &x);

    switch(x)
    {
    case 1:

        printf("Digite seu nome:");
        scanf("%50s",nome);

        printf("Digite o sobrenome:");
        scanf("%50s", sobrenome);

        printf("Digite seu ano de nascimento:");
        scanf("%d", &idade);

        strcpy(nomeCompleto, nome);
        strcat (nomeCompleto," ");
        strcat (nomeCompleto, sobrenome);



        fflush(stdin);

        printf("Data do seu nascimento:(DD/MM)");
        gets(nascimento);

        printf("\nNome completo: %s\n", nomeCompleto);
        printf("Data de nascimento:");
        puts(nascimento);

        printf("Idade: %d\n",(int) ANO_ATUAL-idade);
        printf("Seu nome possui %d de caracteres\n\n",strlen(nomeCompleto));

        break;

    case 2:

        printf("Digite o primeiro número:");
        scanf("%f", &num1);
        printf("Digite o segundo número:");
        scanf("%f", &num2);

        soma = num1+num2;
        diferenca = num1-num2;
        produto = num1*num2;
        quadrado1 = num1*num1;
        quadrado2 = num2*num2;
        somaQUAD = quadrado1+quadrado2;
        raizQ = sqrt (somaQUAD);
        senDif = sin (diferenca*PI/180);
        modulo= num1/num2;



        printf("\n A soma dos números:%1.0f", soma);
        printf("\n O produto dos números:%1.0f", produto);
        printf("\n O quadrado do primeiro número:%1.0f", quadrado1);
        printf("\n A raiz quadrada da soma dos quadrados:%1.0f", raizQ);
        printf("\n O seno da diferença do primeiro número pelo segundo:%2f", senDif);
        printf("\n O módulo dos números:%1.0f", modulo);
        return 0;

    case 3:
        printf("\n Conversor de temperatura");
        printf("\n Digite a temperatura em fahrenheit:");
        scanf("%f", &fahrenheit);
        celsius = (fahrenheit - 32) * 5.0 / 9.0;

        printf("\n A temperatura em celsius é:%0.2f", celsius);
        return 0;

    case 4:
        printf("\n Cálculo de fatorial de um número");
        printf("\n Digite o número:");
        scanf("%f", &n);

        for(i=n; i>1; i--)
        {
            fatorial=fatorial*i;
        }

        printf("\n O valor do fatorial é: %d\n", n, fatorial);

        return 0;

    case 5:

        printf("ENTRE COM O HORÁRIO:");
        scanf("%i", &hora);

        if (hora >=0 && hora<=12)
        {
            printf("Bom dia.%h\n", hora);
        }
        else if (hora >=12 && hora <=18 )
        {
            printf("Boa tarde.");
        }
        else if (hora>=18 && hora <=23)
        {
            printf("Boa noite.");
        }
        else
        {
            printf("Horário Inválido!");
        }
        return 0;

    case 6:

        for(i=0; i<=9; i++)
        {
            printf("Digite o número:");
            scanf("%s", &num[i]);
            adicao = adicao + num[i];
        }

        printf("\n A soma dos valores dos vetores é %i", adicao);

        return 0;

    case 7:


    case 8:
        {

        }

    }

}




