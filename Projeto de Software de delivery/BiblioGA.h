#ifndef BIBLIOGA_H
#define BIBLIOGA_H

//===================================================================
/*
BIBLIOTECAS UTILIZADAS
*/
//===================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <cstdio>
#include <clocale>
#include <cstdlib>
#include <windows.h>

using namespace std;

#define TAM3 17
#define BIG 9999

void Dijkstra(int **G,int n,int inicial, int fim);
int  **AlocaMDist(int n);
void ImprimeMatriz(int **M,int n);
int **LerMatriz(int **M, int n);
void MostrarResultado(int n, int ini, float dist[TAM3], float pred[TAM3], int fim);

// ==================================================================
/*
ESTRUTURA DOS DADOS - CADASTRO CLIENTE
*/
// ==================================================================

struct Cliente
{
	int CPF;
	char NomeCliente[10];
	int LoginCliente;
	int SenhaCliente;
};

// ==================================================================
/*
ESTRUTURA DOS DADOS - CADASTRO ITENS
*/
// ==================================================================

struct Itens
{
	char NomeItem[25];
	float Preco;
	int Codigo;
	int Quantidade;
};

// ==================================================================
/*
ESTRUTURA DOS DADOS - Pedidos
*/
// ==================================================================

struct Pedido
{
	int CPF;
	int Codigo;
	int Quantidade;
	int Control;
	float Valor;
	int Bairro;
};

// ==================================================================
/*
ESTRUTURA DOS DADOS - CADASTRO EMPRESA
*/
// ==================================================================

struct Empresa
{
	int CNPJ;
	int LoginEmp;
	int SenhaEmp;
	char NomeDaEmpresa[25];
};

// ==================================================================
/*
PROTOTIAÇÃO DOS DADOS - CADASTRO CLIENTE
*/
// ==================================================================

void CadastrarCliente(FILE* Arquivo, Cliente C[100], int pos);
int LoginCliente(FILE* Arquivo, Cliente CL[100], int login_cliente, int senha_cliente);
int IniciarCliente(FILE* Arquivo, Cliente C[100]);

// ==================================================================
/*
PROTOTIAÇÃO DOS DADOS - CADASTRO EMPRESA
*/
// ==================================================================

int IniciarEmpresa(FILE* Arquivo, Empresa EM[100]);
int IniciarItens(FILE* Arquivo, Itens IT[100]);
int IniciarPedidos(FILE* Arquivo, Pedido PD[100]);

int VisualizarRota(FILE* Arquivo, int TAM,int Achou);
int Atualizar(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100]);
int SAVED(FILE* Arquivo, int pos, Pedido PD[100], int Cod, float real, int Achou);
int SAVED2(FILE* Arquivo, int pos, Pedido PD[100], int C);
int SAVED3(int Cod, int qt, int Achou);
int SAVED4(int Achou);
int FecharMovimento(Pedido PD[100]);
int CadastroItens(FILE* Arquivo, Itens IT[100], int pos);
int Caixa(FILE* Arquivo, Itens IT[100], int pos,Pedido PD[100]);
int Pedidos(FILE* Arquivo, int pos2, Pedido PD[100]);
int Entregas(FILE* Arquivo, int pos, Pedido PD[100]);
int Consulta(FILE* Arquivo, Itens IT[100], int pos);
int LoginEmpresa(FILE* Arquivo, Empresa EM[100], int login_empresa, int senha_empresa);
void CadastrarEmpresa(FILE* Arquivo, Empresa EM[100], int pos);

// ==================================================================
/*
 MENUS
*/
// ==================================================================

int main();
void criaMenuLinhaSuperior();
void criaMenuLinhaRodape(int tamX);
void criaMenuItem(int tamX, char str[]);
void criaMenuLinhaHorizontal(int tamX);
void arrow (int position, int arrowPosition);
void imprimirArcoIris(string x);
void imprimirArcoIrisLC(string x);

int MenuPrincipal();
int MenuPrincipalCliente();
int MenuPrincipalEmpresa();
void MenuCliente(FILE* Arquivo,int pos, Pedido PD[100], int Achou);
void MenuEmpresa(FILE* Arquivo, Itens IT[100], int pos,Pedido PD[100]);

// ===================
/*
	Funções e menus de compras
*/

int Compra(FILE* Arquivo,int pos, Pedido PD[100], int Achou);
int FecharPedido();
int Bebidas(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Drinks(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Sucos(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Cervejas(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Vinhos(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
int Pizzas(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Pizza1(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Pizza2(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Pizza3(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Pizza4(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
int Combos(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Combo1(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Combo2(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Combo3(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Combo4(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
int PromocaoDoDia(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Promo1(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Promo2(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Promo3(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
string Promo4(FILE* Arquivo, int pos, Pedido PD[100], int Achou);
int Saida();

#endif
