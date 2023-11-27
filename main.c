/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief Programa de cadastro de produto para um mercado
 * @version 0.1
 * @date 2023-11-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // Se tiver usando Linux/MAC -> Serve para pausar o programa por alguns segundos
// #include <windows.h> se tiver usando o windows

typedef struct Produto
{
    int codigo;
    char nome[30];
    float preco;
}Produto;

typedef struct Carrinho
{
    Produto produto;
    int quantidade;
}Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];

int main()
{
    menu();
    return 0;
}
void infoProduto(Produto prod)
{
    printf("Codigo: %d \nNome: %d \nPreço: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco); // Vamos usar o strtok para porder imprimir o string e tirar o \n que o programa grava junto com a string.
}
void menu()
{
    printf("=================================================\n");
    printf("=================== Bem-vindo(a) ================\n");
    printf("===================== Shop ======================\n");
    printf("=================================================\n");

    printf("Selecione uma opção abaixo: \n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produto(s)\n");
    printf("3 - Comprar Produto\n");
    printf("4 - Visualizar Carrinho\n");
    printf("5 - Fechar Pedido\n");
    printf("6 - Sair do sitema\n");

    int opcao;
    scanf("%d", &opcao);
    getchar(); // Serve para quando for informar um inteiro e depois uma string não pular a string

    switch (opcao)
    {
    case 1:
        cadastrarProduto();
        break;
    case 2:
        listarProdutos();
        break;
    case 3:
        comprarProduto();
        break;
    case 4:
        visualizarCarrinho();
        break;
    case 5:
        fecharPedido();
        break;
    case 6:
        printf("Volte sempre!\n");
        sleep(2); // Linux/Mac sleep, e no Windows Sleep. Em segundos
        exit(0);
    default:
        printf("Opção inválida.\n");
        sleep(2);
        menu();
        break;
    }
}
void cadastrarProduto()
{
    printf("Cadastro de produto\n");
    printf("====================\n");

    printf("Informe o nome do produto: \n");
    fgets(produtos[contador_produto].nome, 30, stdin); // Cadastrar o produto do array de até 30 caracteres com entrada standart, teclado.

    printf("Informe o preço do produto: \n");
    scanf("%f", &produtos[contador_produto].preco);

    printf("O produto %s foi cadastrado com sucesso.\n", strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++;
}
void listarProdutos()
{
    if (contador_produto > 0)
    {
        printf("Listagem de produtos: \n");
        printf("-----------------\n");
        for (int i = 0; i < contador_produto; i++)
        {
            infoProduto(produtos[i]);
            printf("--------------\n");
            sleep(1);
        }
        
    }
    else
    {
        printf("Não temos ainda produtos cadastrados.\n");
    }    
}
void comprarProduto()
{

}
void visualizarCarrinho()
{
    if (contador_carrinho > 0)
    {
        printf("Produtos do carrinho: \n");
        printf("-------------\n");
        for (int i = 0; i < contador_carrinho; i++)
        {
            infoProduto(carrinho[i].produto);
            printf("Qunatidade: %d\n", carrinho[i].quantidade);
            printf("-------------\n");
            sleep(1);
        }        
    }
    else
    {
        printf("Não existe produto no carrinho.\n");
    }    
}
Produto pegarProdutoPorCodigo(int codigo)
{
    Produto p;
    for (int i = 0; i < contador_produto; i++)
    {
        if (produtos[i].codigo == codigo)
        {
            p = produtos[i];
        }        
    }
    return p;    
}
int * temNoCarrinho(int codigo)
{
    int static retorno[] = {0, 0};
    for (int i = 0; i < contador_carrinho; i++)
    {
        if (carrinho[i].produto.codigo == codigo)
        {
            retorno[0] = 1; // Tem o produto com este código no carrinho
            retorno[1] = i; // O índice do produto no carrinho
        }        
    }
    return retorno;    
}
void fecharPedido()
{
    if (contador_carrinho > 0)
    {
        float valorTotal = 0.0;
        printf("Produtos do carrinho: \n");
        printf("----------------\n");
        for (int i = 0; i < contador_carrinho; i++)
        {
            Produto p = carrinho[i].produto;
            int qunatidade = carrinho[i].quantidade;
            valorTotal += p.preco * qunatidade;
            infoProduto(p);
            printf("Qunatidade: %d\n", qunatidade);
            printf("-------------------------\n");
            sleep(1);
        }
        printf("Sua fatura é: R$ %.2f\n", valorTotal);

        // Limpar carrinho
        contador_carrinho = 0;
        printf("Obrigado pela preferência.\n");
        sleep(5);
        menu();        
    }
    else
    {
        printf("Você não tem nenhum produto no carrinho.\n");
        sleep(3);
        menu();
    }   
}
