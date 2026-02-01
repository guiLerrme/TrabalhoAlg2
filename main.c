#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int cpf;
    char nome_cliente[50];
    int idade_cliente;
} Cliente;

typedef struct
{
    int cnpj;
    char nome_empresa[50];
    char produto[50];
}Empresa;

typedef struct
{
    int cpf_cliente;
    int cnpj_empresa;
    float valor;
    //int dias_atraso; opção caso fique dificil para geramos relatorios apenas com as 3 variaveis acima...
}Divida;

void Menu()
{
    printf("\n _____________________________________________________\n");
    printf("\n ==            SGN ASSESSORIA FINANCEIRA            ==");// Tirei esse nome das nossas iniciais, se quiserem mudar, à la vonte
    printf("\n ==                  Cadastrar (1)                  ==");
    printf("\n ==                  Consultar (2)                  ==");
    printf("\n ==                  Atualizar (3)                  ==");
    printf("\n ==                   Excluir (4)                   ==");
    printf("\n ==               Sair do Programa (0)              ==");
    printf("\n _____________________________________________________\n");
    printf("\nDigite a opcao desejada:");
}

void Qual_Struct()
{
    printf("\n _____________________________________________________\n");
    printf("\n ==                                                  ==");
    printf("\n ==     CLIENTE [1] / EMPRESA [2] / DIVIDA [3]       ==");
    printf("\n ==                                                  ==");
    printf("\n _____________________________________________________\n");
    printf("\nDigite a opcao desejada:");
}

int main()
{
    int flag; // Variavel que controla o while principal
    int flag_struct; // Variavel que controla qual das structs passará pelo CRUD

    int capacidade_cliente = 5;
    int capacidade_empresa = 5; // Iniciaremos com a capacidade 5 e aumentaremos conforme a necessidade nos reallocs
    int capacidade_divida = 5;

    int quantidade_cliente = 0;
    int quantidade_empresa = 0; // Variaveis que controlam a quantidade e ajudam na manipulação de reallocs
    int quantidade_divida = 0;

    Cliente *cliente_lista;
    cliente_lista = malloc(capacidade_cliente * sizeof(Cliente)); //alocando espaço de 5 Clientes na memoria para iniciar o programa

    Empresa *empresa_lista;
    empresa_lista = malloc(capacidade_empresa * sizeof(Empresa)); //alocando espaço de 5 Empresas na memoria para iniciar o programa

    Divida *divida_lista;
    divida_lista = malloc(capacidade_divida * sizeof(Divida)); //alocando espaço de 5 Dividas na memoria para iniciar o programa

    do
    {
        Menu();
        scanf("%d", &flag);

        if (flag == 1)  // Cadastro
        {
            Qual_Struct();// Pergunta oq deseja cadastrar
            scanf("%d", &flag_struct);
            if (flag_struct == 1)
            {
                if (capacidade_cliente == quantidade_cliente)  // Verifica a capacidade atual de clientes
                {
                    capacidade_cliente += 5;// Se necessario aumenta a capacidade em 5
                    cliente_lista = realloc(cliente_lista, capacidade_cliente * sizeof(Cliente));
                }
                printf("\nDigite o CPF do Cliente (apenas numeros): ");
                scanf("%d", &cliente_lista[quantidade_cliente].cpf);// Como CPF será o ID precisaremos fazer outro if para checar se já existe alguem com esse cpf
                                                                    // Checar caracteres fora do formato
                printf("\nDigite o nome do Cliente: ");
                scanf("%s", &cliente_lista[quantidade_cliente].nome_cliente); // Checar caracteres fora do formato

                printf("\nDigite a idade do Cliente: ");
                scanf("%d", &cliente_lista[quantidade_cliente].idade_cliente); // Checar caracteres fora do formato

                quantidade_cliente ++;
            }
            else if(flag_struct == 2)
            {
                if (capacidade_empresa == quantidade_empresa)  // Verifica a capacidade atual de empresas
                {
                    capacidade_empresa += 5;// Se necessario aumenta a capacidade em 5
                    empresa_lista =  realloc(empresa_lista, capacidade_empresa * sizeof(Empresa));
                }
                printf("\nDigite o CPNJ da empresa (apenas numeros): ");
                scanf("%d", empresa_lista[quantidade_empresa].cnpj);// Como CNPJ será o ID precisaremos fazer outro if para checar se já existe alguem com esse cpf
                                                                    // Checar caracteres fora do formato
                printf("\nDigite o nome da empresa: ");
                scanf("%s", empresa_lista[quantidade_empresa].nome_empresa); // Checar caracteres fora do formato

                printf("\nDigite o nome do produto: ");
                scanf("%s", empresa_lista[quantidade_empresa].produto); // Checar caracteres fora do formato

                quantidade_empresa++;
            }
            else if(flag_struct == 3)
            {
                if (capacidade_divida == quantidade_divida) // Verifica a capacidade atual de empresas
                {
                    capacidade_divida += 5;// Se necessario aumenta a capacidade em 5
                    divida_lista = realloc(divida_lista, capacidade_divida * sizeof(Divida));
                }
                printf("Digite o CPF do Cliente que detem essa divida (apenas numeros): ");
                scanf("%d", divida_lista[quantidade_divida].cpf_cliente);

                printf("Digite o CPNJ do credor em questao (apenas numeros): ");
                scanf("%d", divida_lista[quantidade_divida].cnpj_empresa);

                printf("Digite o valor dessa Divida: ");
                scanf("%f", divida_lista[quantidade_divida].valor);
            }
        }

        else if (flag == 2)  // Cadastro
        {
            Qual_Struct();// Pergunta oq deseja cadastrar
            scanf("%d", &flag_struct);
            // criar outros IFs para cliente/empresa/ divida
        }

        else if (flag == 3)  // Cadastro
        {
            Qual_Struct();// Pergunta oq deseja cadastrar
            scanf("%d", &flag_struct);
            // criar outros IFs para cliente/empresa/ divida
        }

        else if (flag == 4)  // Cadastro
        {
            Qual_Struct();// Pergunta oq deseja cadastrar
            scanf("%d", &flag_struct);
            // criar outros IFs para cliente/empresa/ divida
        }
        else if (flag == 0)
        {
            printf("\n==               PROGRAMA FINALIZADO               ==\n");
        }
        else
            printf("\n==             Digite uma opcao valida!             ==\n");

    }
    while (flag != 0);
    return 0;
}
