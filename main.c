#include <stdio.h>
#include <stdlib.h>

//OBS INICIAL: NOSSO SISTEMA DISPONIBILIZA QUE OS CLIENTES TENHAM VARIAS DIVIDAS, PARA DIFERENTES EMPRESAS
//A STRUCT DIVIDA TEM COMO SUAS "CHAVES PRIMARIAS" O CPF_CLIENTE E CNPJ_EMPRESA (AMBAS JUNTAS).

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
} Empresa;

typedef struct
{
    int cpf_cliente;
    int cnpj_empresa;
    float valor;
    //int dias_atraso; opção caso fique dificil para geramos relatorios apenas com as 3 variaveis acima...
} Divida;

int BuscaCliente(Cliente *cliente, int quantidade_cliente,int cpf) // Essa função é essencial em todos os itens do Menu
{
    // Se já existir ele vai retornar o indice com o cpf, se nao, vai retornar -1
    for(int cont_c = 0; cont_c < quantidade_cliente; cont_c++)
    {
        if (cliente[cont_c].cpf == cpf)
        {
            return cont_c;
        }
    }
    return -1;
}

int BuscaEmpresa(Empresa *empresa, int quantidade_empresa, int cnpj)// Essa função é essencial em todos os itens do Menu
{
    // Se já existir ele vai retornar o indice com o cnpj, se nao, vai retornar -1
    for(int cont_e = 0; cont_e < quantidade_empresa; cont_e++)
    {
        if(empresa[cont_e].cnpj == cnpj)
        {
            return cont_e;
        }
    }
    return -1;
}

int BuscaDivida(Divida *divida, int quantidade_divida, int cpf_cliente, int cnpj_empresa)//Aqui verifico se a divida já existe
{
    for(int cont_d = 0; cont_d < quantidade_divida; cont_d++)
    {
        if(divida[cont_d].cpf_cliente == cpf_cliente && divida[cont_d].cnpj_empresa == cnpj_empresa)
        {
            return cont_d;
        }
    }
    return -1;
}

//PRECISO DE OUTRA FUNÇÃO QUE VERIFICA SE O CPF E O CNPJ JA ESTAO CADASRTRADOS


void Menu()
{
    printf("\n _____________________________________________________\n");
    printf("\n ==            SGN ASSESSORIA FINANCEIRA            ==");// Tirei esse nome das nossas iniciais, se quiserem mudar, à la vonte
    printf("\n ==                  Cadastrar [1]                  ==");
    printf("\n ==                  Consultar [2]                  ==");
    printf("\n ==                  Atualizar [3]                  ==");
    printf("\n ==                   Excluir [4]                   ==");
    printf("\n ==               Sair do Programa [0]              ==");
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

    int cpf_temp;
    int cnpj_temp; //Variaveis temporarias para validar se os IDs já constam
    int cpf_divida_temp;
    int cnpj_divida_temp;

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
                scanf("%d", &cpf_temp);

                if(BuscaCliente(cliente_lista, quantidade_cliente, cpf_temp) != -1)// Valida se já existe
                {
                    printf("\n==          ESSE CPF JA CONSTA NO SISTEMA           ==\n");
                }
                else
                {
                    cliente_lista[quantidade_cliente].cpf = cpf_temp;
                    printf("\nDigite o nome do Cliente: ");
                    scanf("%49s", cliente_lista[quantidade_cliente].nome_cliente); // Checar caracteres fora do formato

                    printf("\nDigite a idade do Cliente: ");
                    scanf("%d", &cliente_lista[quantidade_cliente].idade_cliente); // Checar caracteres fora do formato
                    printf("\n==          CLIENTE CADASTRADO COM SUCESSO!         ==\n");
                    quantidade_cliente ++;
                }
            }
            else if(flag_struct == 2)
            {
                if (capacidade_empresa == quantidade_empresa)  // Verifica a capacidade atual de empresas
                {
                    capacidade_empresa += 5;// Se necessario aumenta a capacidade em 5
                    empresa_lista =  realloc(empresa_lista, capacidade_empresa * sizeof(Empresa));
                }
                printf("\nDigite o CPNJ da empresa (apenas numeros): ");
                scanf("%d", &cnpj_temp);
                // Checar caracteres fora do formato
                if(BuscaEmpresa(empresa_lista, quantidade_empresa, cnpj_temp) != -1)
                {
                    printf("\n==          ESSE CNPJ JA CONSTA NO SISTEMA          ==\n");
                }
                else
                {
                    empresa_lista[quantidade_empresa].cnpj = cnpj_temp;
                    printf("\nDigite o nome da empresa: ");
                    scanf("%s", empresa_lista[quantidade_empresa].nome_empresa); // Checar caracteres fora do formato

                    printf("\nDigite o nome do produto: ");
                    scanf("%s", empresa_lista[quantidade_empresa].produto); // Checar caracteres fora do formato
                    printf("\n==          EMPRESA CADASTRADA COM SUCESSO!         ==\n");
                    quantidade_empresa++;
                }
            }
            else if(flag_struct == 3)
            {
                if (capacidade_divida == quantidade_divida) // Verifica a capacidade atual de empresas
                {
                    capacidade_divida += 5;// Se necessario aumenta a capacidade em 5
                    divida_lista = realloc(divida_lista, capacidade_divida * sizeof(Divida));
                }

                printf("Digite o CPF do Cliente que detem essa divida (apenas numeros): ");
                scanf("%d", &cpf_divida_temp);

                printf("Digite o CPNJ do credor em questao (apenas numeros): ");
                scanf("%d", &cnpj_divida_temp);

                //LINHA 67

                if (BuscaDivida(divida_lista, quantidade_divida, cpf_divida_temp, cnpj_divida_temp) != -1)
                {
                    printf("\n==         DIVIDA JA CADASTRADA NO SISTEMA         ==\n");
                }


                else
                {
                    divida_lista[quantidade_divida].cpf_cliente = cpf_divida_temp;
                    divida_lista[quantidade_divida].cnpj_empresa = cnpj_divida_temp;

                    printf("Digite o valor dessa Divida: ");
                    scanf("%f", &divida_lista[quantidade_divida].valor);
                    printf("\n==          DIVIDA CADASTRADA COM SUCESSO!          ==\n");
                    quantidade_divida++;
                }
            }
            else
            {
                printf("\n==             Digite uma opcao valida!             ==\n");//Valida se está digitando 1,2 ou 3
            }
        }

        else if (flag == 2)  // Consulta
        {
            Qual_Struct();// Pergunta oq deseja Consultar
            scanf("%d", &flag_struct);
            // criar outros IFs para cliente/empresa/ divida
        }

        else if (flag == 3)  // Atualiza
        {
            Qual_Struct();// Pergunta oq deseja atualizar
            scanf("%d", &flag_struct);
            // criar outros IFs para cliente/empresa/ divida
        }

        else if (flag == 4)  // Exclui
        {
            Qual_Struct();// Pergunta oq deseja excluir
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
