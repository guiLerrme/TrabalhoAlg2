
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//OBS INICIAL: NOSSO SISTEMA DISPONIBILIZA QUE OS CLIENTES TENHAM VARIAS DIVIDAS PARA DIFERENTES EMPRESAS
//A STRUCT DIVIDA TEM COMO SUAS "CHAVES PRIMARIAS" O CPF_CLIENTE E CNPJ_EMPRESA (AMBAS JUNTAS).

/*FALTA [3] E [4] DO MENU, E AJUSTAR A CONSULTA DA DIVIDA CONFORME A INSTRUÇÃO 6, f)*/


/* ================= STRUCTS ================= */

typedef struct
{
    char cpf[12];
    char nome_cliente[50];
    int idade_cliente;
} Cliente;

typedef struct
{
    char cnpj[15];
    char nome_empresa[50];
    char produto[50];
} Empresa;

typedef struct
{
    char cpf_cliente[12];
    char cnpj_empresa[15];
    float valor;
} Divida;


int BuscaCliente(Cliente *cliente, int quantidade_cliente, char cpf[])
{
    for(int cont_c = 0; cont_c < quantidade_cliente; cont_c++)
    {
        if(strcmp(cliente[cont_c].cpf, cpf) == 0)
            return cont_c;
    }
    return -1;
}

int BuscaEmpresa(Empresa *empresa, int quantidade_empresa, char cnpj[])
{
    for(int cont_e = 0; cont_e < quantidade_empresa; cont_e++)
    {
        if(strcmp(empresa[cont_e].cnpj, cnpj) == 0)
            return cont_e;
    }
    return -1;
}

int BuscaDivida(Divida *divida, int quantidade_divida, char cpf_cliente[], char cnpj_empresa[])
{
    for(int cont_d = 0; cont_d < quantidade_divida; cont_d++)
    {
        if(strcmp(divida[cont_d].cpf_cliente, cpf_cliente) == 0 &&
                strcmp(divida[cont_d].cnpj_empresa, cnpj_empresa) == 0)
            return cont_d;
    }
    return -1;
}

int BuscaClienteEmpresa(Cliente *cliente, Empresa *empresa,
                        char cpf[], char cnpj[],
                        int quantidade_cliente, int quantidade_empresa)
{
    if(BuscaCliente(cliente, quantidade_cliente, cpf) != -1 &&
            BuscaEmpresa(empresa, quantidade_empresa, cnpj) != -1)
    {
        printf("\nCLIENTE: %s",
               cliente[BuscaCliente(cliente, quantidade_cliente, cpf)].nome_cliente);

        printf("\nEMPRESA: %s\n",
               empresa[BuscaEmpresa(empresa, quantidade_empresa, cnpj)].nome_empresa);

        return 1;
    }
    return -1;
}

void Menu()
{
    printf("\n _____________________________________________________\n");
    printf("\n ==            SGN ASSESSORIA FINANCEIRA            ==");
    printf("\n ==                  Cadastrar [1]                  ==");
    printf("\n ==                  Consultar [2]                  ==");
    printf("\n ==                  Atualizar [3]                  ==");
    printf("\n ==                   Excluir [4]                   ==");
    printf("\n ==               Sair do Programa [0]              ==");
    printf("\n _____________________________________________________\n");
    printf("\nDigite a opcao desejada: ");
}

void Qual_Struct()
{
    printf("\n _____________________________________________________\n");
    printf("\n ==     CLIENTE [1] / EMPRESA [2] / DIVIDA [3]       ==");
    printf("\n _____________________________________________________\n");
    printf("\nDigite a opcao desejada: ");
}

/* ================= FUNÇÕES DE CADASTRO ================= */

void CadastrarCliente(Cliente **cliente_lista, int *quantidade_cliente, int *capacidade_cliente)
{
    if(*capacidade_cliente == *quantidade_cliente)
    {
        *capacidade_cliente += 5;
        *cliente_lista = realloc(*cliente_lista, (*capacidade_cliente) * sizeof(Cliente));
    }

    char cpf_temp[12];

    printf("\nDigite o CPF do Cliente (11 numeros): ");
    scanf("%11s", cpf_temp);

    if(BuscaCliente(*cliente_lista, *quantidade_cliente, cpf_temp) != -1)
    {
        printf("\n== ESSE CPF JA CONSTA NO SISTEMA ==\n");
        return;
    }

    strcpy((*cliente_lista)[*quantidade_cliente].cpf, cpf_temp);

    getchar();

    printf("\nDigite o nome do Cliente: ");
    fgets((*cliente_lista)[*quantidade_cliente].nome_cliente, 50, stdin);
    (*cliente_lista)[*quantidade_cliente].nome_cliente[strcspn(
                (*cliente_lista)[*quantidade_cliente].nome_cliente, "\n")] = '\0';

    printf("\nDigite a idade do Cliente: ");
    scanf("%d", &(*cliente_lista)[*quantidade_cliente].idade_cliente);

    printf("\n== CLIENTE CADASTRADO COM SUCESSO! ==\n");

    (*quantidade_cliente)++;
}

void CadastrarEmpresa(Empresa **empresa_lista, int *quantidade_empresa, int *capacidade_empresa)
{
    if(*capacidade_empresa == *quantidade_empresa)
    {
        *capacidade_empresa += 5;
        *empresa_lista = realloc(*empresa_lista, (*capacidade_empresa) * sizeof(Empresa));
    }

    char cnpj_temp[15];

    printf("\nDigite o CNPJ da empresa (14 numeros): ");
    scanf("%14s", cnpj_temp);

    if(BuscaEmpresa(*empresa_lista, *quantidade_empresa, cnpj_temp) != -1)
    {
        printf("\n== ESSE CNPJ JA CONSTA NO SISTEMA ==\n");
        return;
    }

    strcpy((*empresa_lista)[*quantidade_empresa].cnpj, cnpj_temp);

    getchar();

    printf("\nDigite o nome da empresa: ");
    fgets((*empresa_lista)[*quantidade_empresa].nome_empresa, 50, stdin);
    (*empresa_lista)[*quantidade_empresa].nome_empresa[strcspn(
                (*empresa_lista)[*quantidade_empresa].nome_empresa, "\n")] = '\0';

    printf("\nDigite o nome do produto: ");
    fgets((*empresa_lista)[*quantidade_empresa].produto, 50, stdin);
    (*empresa_lista)[*quantidade_empresa].produto[strcspn(
                (*empresa_lista)[*quantidade_empresa].produto, "\n")] = '\0';

    printf("\n== EMPRESA CADASTRADA COM SUCESSO! ==\n");

    (*quantidade_empresa)++;
}

void CadastrarDivida(Divida **divida_lista, int *quantidade_divida, int *capacidade_divida,
                     Cliente *cliente_lista, int quantidade_cliente,
                     Empresa *empresa_lista, int quantidade_empresa)
{
    if(*capacidade_divida == *quantidade_divida)
    {
        *capacidade_divida += 5;
        *divida_lista = realloc(*divida_lista, (*capacidade_divida) * sizeof(Divida));
    }

    char cpf_temp[12];
    char cnpj_temp[15];

    printf("Digite o CPF do Cliente: ");
    scanf("%11s", cpf_temp);

    printf("Digite o CNPJ do credor: ");
    scanf("%14s", cnpj_temp);

    if(BuscaClienteEmpresa(cliente_lista, empresa_lista,
                           cpf_temp, cnpj_temp,
                           quantidade_cliente, quantidade_empresa) != -1)
    {
        if(BuscaDivida(*divida_lista, *quantidade_divida,
                       cpf_temp, cnpj_temp) != -1)
        {
            printf("\n== DIVIDA JA CADASTRADA ==\n");
            return;
        }

        strcpy((*divida_lista)[*quantidade_divida].cpf_cliente, cpf_temp);
        strcpy((*divida_lista)[*quantidade_divida].cnpj_empresa, cnpj_temp);

        printf("Digite o valor da Divida: ");
        scanf("%f", &(*divida_lista)[*quantidade_divida].valor);

        printf("\n== DIVIDA CADASTRADA COM SUCESSO! ==\n");

        (*quantidade_divida)++;
    }
    else
        printf("\n== CLIENTE OU EMPRESA NAO CADASTRADOS ==\n");
}

/* ================= FUNÇÕES DE LISTAGEM ================= */

void ListarClientes(Cliente *cliente_lista, int quantidade_cliente)
{
    if(quantidade_cliente == 0)
    {
        printf("\n== NENHUM CLIENTE CADASTRADO! ==\n");
        return;
    }

    for(int i = 0; i < quantidade_cliente; i++)
    {
        printf("\nCPF: %s", cliente_lista[i].cpf);
        printf("\nNOME: %s", cliente_lista[i].nome_cliente);
        printf("\nIDADE: %d\n", cliente_lista[i].idade_cliente);
    }
}

void ListarEmpresas(Empresa *empresa_lista, int quantidade_empresa)
{
    if(quantidade_empresa == 0)
    {
        printf("\n== NENHUMA EMPRESA CADASTRADA! ==\n");
        return;
    }

    for(int i = 0; i < quantidade_empresa; i++)
    {
        printf("\nCNPJ: %s", empresa_lista[i].cnpj);
        printf("\nNOME: %s", empresa_lista[i].nome_empresa);
        printf("\nPRODUTO: %s\n", empresa_lista[i].produto);
    }
}

void ListarDividas(Divida *divida_lista, int quantidade_divida)
{
    if(quantidade_divida == 0)
    {
        printf("\n== NENHUMA DIVIDA CADASTRADA! ==\n");
        return;
    }

    for(int i = 0; i < quantidade_divida; i++)
    {
        printf("\nCPF DO CLIENTE: %s", divida_lista[i].cpf_cliente);
        printf("\nCNPJ DO CREDOR: %s", divida_lista[i].cnpj_empresa);
        printf("\nVALOR DA DIVIDA: R$%.2f\n", divida_lista[i].valor);
    }
}

/* ================= MAIN ================= */

int main()
{
    int flag, flag_struct;

    int capacidade_cliente = 5, quantidade_cliente = 0;
    int capacidade_empresa = 5, quantidade_empresa = 0;
    int capacidade_divida = 5, quantidade_divida = 0;

    Cliente *cliente_lista = malloc(capacidade_cliente * sizeof(Cliente));
    Empresa *empresa_lista = malloc(capacidade_empresa * sizeof(Empresa));
    Divida *divida_lista = malloc(capacidade_divida * sizeof(Divida));

    do
    {
        Menu();
        scanf("%d", &flag);

        if(flag == 1)
        {
            Qual_Struct();
            scanf("%d", &flag_struct);

            if(flag_struct == 1)
                CadastrarCliente(&cliente_lista, &quantidade_cliente, &capacidade_cliente);
            else if(flag_struct == 2)
                CadastrarEmpresa(&empresa_lista, &quantidade_empresa, &capacidade_empresa);
            else if(flag_struct == 3)
                CadastrarDivida(&divida_lista, &quantidade_divida, &capacidade_divida,
                                cliente_lista, quantidade_cliente,
                                empresa_lista, quantidade_empresa);
        }
        else if(flag == 2)
        {
            Qual_Struct();
            scanf("%d", &flag_struct);

            if(flag_struct == 1)
                ListarClientes(cliente_lista, quantidade_cliente);
            else if(flag_struct == 2)
                ListarEmpresas(empresa_lista, quantidade_empresa);
            else if(flag_struct == 3)
                ListarDividas(divida_lista, quantidade_divida);
        }

    }
    while(flag != 0);

    free(cliente_lista);
    free(empresa_lista);
    free(divida_lista);

    return 0;
}
