#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include "BiblioGA.h"

using namespace std;
#define STRTAM 40

Pedido PD[100];
int Qt = 0;
float Balance = 0;

int IniciarCliente(FILE* Arquivo, Cliente C[100])
{
	int cont = 0;
	Arquivo = fopen ("DadosCliente.bin", "rb");
	if(Arquivo != NULL)
		while(fread(&C[cont], sizeof(Cliente), 1, Arquivo) != 0) cont++;
	else
	{
		Arquivo = fopen("DadosCliente.bin", "wb");
		printf("Arquivo Criado com sucesso!");
	}
	return cont;
}

int IniciarEmpresa(FILE* Arquivo, Empresa EM[100])
{
	int cont = 0;
	Arquivo = fopen ("DadosEmpresa.bin", "rb");
	if(Arquivo != NULL)
		while(fread(&EM[cont], sizeof(Empresa), 1, Arquivo) != 0) cont++;
	else
	{
		Arquivo = fopen("DadosEmpresa.bin", "Wb");
		printf("Arquivo criado com sucesso!\n");
	}
	return cont;
}

int IniciarItens(FILE* Arquivo, Itens IT[100])
{
	int cont = 0;
	Arquivo = fopen ("DadosIT.bin", "rb");
	if(Arquivo != NULL)
		while(fread(&IT[cont], sizeof(Itens), 1, Arquivo) != 0) cont++;
	else
	{
		Arquivo = fopen("DadosIT.bin", "Wb");
		printf("Arquivo criado com sucesso!\n");
	}
	return cont;
}

int IniciarPedidos(FILE* Arquivo, Pedido PD[100])
{
	int cont = 0;
	Arquivo = fopen ("Pedidos.bin", "rb");
	if(Arquivo != NULL)
		while(fread(&PD[cont], sizeof(Pedido), 1, Arquivo) != 0) cont++;
	else
	{
		Arquivo = fopen("Pedidos.bin", "Wb");
		printf("Arquivo criado com sucesso!\n");
	}
	return cont;
}

int LoginCliente(FILE* Arquivo, Cliente CL[100], int login_cliente, int senha_cliente)
{
	int Tam;
	int Achou = -1, TT = 0;

	Tam = IniciarCliente(Arquivo, CL);
	int login, senha;

	cout << "DIGITE SEU LOGIN: ";
	cin >> login;
	cout << "DIGITE SUA SENHA: ";
	cin >> senha;

	for(int i = 0; i < Tam; i++)
		if(CL[i].LoginCliente == login)TT = i;

	login_cliente = CL[TT].LoginCliente;
	for(int i = 0; i < Tam; i++)
		if(CL[i].SenhaCliente == senha)TT = i;

	senha_cliente = CL[TT].SenhaCliente;

	system("cls");
	if(login_cliente == login)
	{
		if(senha_cliente == senha)
		{
			return Achou = CL[TT].CPF;
		}
	}
	else
	{
		printf("ACESSO NEGADO!!!");
		return 0;
	}

	fclose(Arquivo);
}

void CadastrarCliente(FILE* Arquivo, Cliente C[100], int pos)
{
	cout << "\n Insira seu CPF (xxx.xxx.xxx-xx): ";
	cin >> C[pos + 1].CPF;
	cout << " LOGIN: ";
	cin >> C[pos + 1].LoginCliente;
	cout << " SENHA: ";
	cin >> C[pos + 1].SenhaCliente;
	cout << " NOME: ";
	cin.ignore();
	cin.getline(C[pos + 1].NomeCliente, 10);
	fwrite(&C[pos + 1], sizeof(Cliente), 1, Arquivo);
	fclose(Arquivo);
	main();
}

void CadastrarEmpresa(FILE* Arquivo, Empresa EM[100], int pos)
{

	cout << "\n Insira o CNPJ da empresa (XX. XXX. XXX/0001-XX): ";
	cin >> EM[pos + 1].CNPJ;
	cout << " Insira o nome da empresa: ";
	cin.ignore();
	cin.getline(EM[pos + 1].NomeDaEmpresa, 25);
	cout << " Insira o login: ";
	cin >> EM[pos + 1].LoginEmp;
	cout << " Insira a senha: ";
	cin >> EM[pos + 1].SenhaEmp;
	system("cls");
	fwrite(&EM[pos + 1], sizeof(Empresa), 1, Arquivo);
	fclose(Arquivo);
	main();
}

int LoginEmpresa(FILE* Arquivo, Empresa EM[100], int login_empresa, int senha_empresa)
{
	int Tam;
	int Achou = -1, TT = 0;

	Tam = IniciarEmpresa(Arquivo, EM);
	int login, senha;


	cout << "DIGITE SEU LOGIN: ";
	cin >> login;
	cout << "DIGITE SUA SENHA: ";
	cin >> senha;

	for(int i = 0; i < Tam; i++)
		if(EM[i].LoginEmp == login)TT = i;
	login_empresa = EM[TT].LoginEmp;

	for(int i = 0; i < Tam; i++)
		if(EM[i].SenhaEmp == senha)TT = i;
	senha_empresa = EM[TT].SenhaEmp;

	if(login_empresa == login)
	{
		if(senha_empresa == senha)
		{
			return Achou = 1;
		}
	}
	else
	{
		printf("ACESSO NEGADO!!!");
		return 0;
	}
	fclose(Arquivo);
};
//-----------------------------------------------------------------------------
//     FUNÇÃO PARA EXIBIR DADOS DA STRUCT
//-----------------------------------------------------------------------------
void Listagem(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100])
{
	int TAM, i;

	Arquivo = fopen ("DadosIT.bin", "rb");
	TAM = IniciarItens(Arquivo, IT);

	for(i = 0; i < TAM; i++)
	{
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		cout << "Código do produto: " << IT[i].Codigo << endl;
		cout << "Nome do produto: " << IT[i].NomeItem << endl;
		cout << "Preço do produto: " << IT[i].Preco << endl;
		cout << "Quantidade em estoque: " << IT[i].Quantidade << endl;
		criaMenuLinhaRodape(STRTAM);
	}
	system("pause");
	Atualizar(Arquivo, IT, pos, PD);
}

void Editar(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100])
{
#define ED_MAX 4
#define ED_MIN 1
	int i, TAM, Codigo, TT = -1;
	TAM = IniciarItens(Arquivo, IT);
	cout << " Informe o Codigo: ";
	cin >> Codigo;
	Arquivo = fopen("DadosIT.bin", "rb");
	for(i = 0; i < TAM; i++)
	{
		if(IT[i].Codigo == Codigo)
		{
			TT = i;
			cout << "      Nome: " << IT[TT].NomeItem << endl;
			cout << "     Preço: " << IT[TT].Preco << endl;
			cout << "Quantidade: " << IT[TT].Quantidade << endl;
			Sleep(1500);
		}
	}
	if(TT != -1)
	{
		int position1 = 1, arrowPress1;
		do
		{
			do
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 14);
				criaMenuLinhaSuperior();
				criaMenuLinhaHorizontal(STRTAM);
				criaMenuItem(STRTAM, " Edições ");
				arrow(1, position1);
				criaMenuItem(STRTAM, "[1] Nome");
				arrow(2, position1);
				criaMenuItem(STRTAM, "[2] Preço");
				arrow(3, position1);
				criaMenuItem(STRTAM, "[3] Estoque");
				arrow(4, position1);
				criaMenuItem(STRTAM, "[4] VOLTAR");
				criaMenuLinhaRodape(STRTAM);
				cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
				arrowPress1 = getch();
				system("CLS");
				fflush(stdin);

				if (arrowPress1 == 80 && position1 != ED_MAX)
					position1++;
				else if (arrowPress1 == 72 && position1 != ED_MIN)
					position1--;
				else
					position1 = position1;
			}
			while (arrowPress1 != 13);

			switch(position1)
			{
			case 1:
				IniciarItens(Arquivo, IT);
				cout << " Insira o novo Nome: ";
				cin.getline(IT[TT].NomeItem, 25);
				Arquivo = fopen("DadosIT.bin", "wb");
				fwrite(&IT[TT], sizeof(Itens), 1, Arquivo);

				fclose(Arquivo);
				break;
			case 2:
				IniciarItens(Arquivo, IT);
				cout << " Insira o novo Preco: ";
				cin >> IT[TT].Preco;
				Arquivo = fopen("DadosIT.bin", "wb");
				fwrite(&IT[TT], sizeof(Itens), 1, Arquivo);

				fclose(Arquivo);
				break;
			case 3:
				IniciarItens(Arquivo, IT);
				cout << " Insira o novo Estoque: ";
				cin >> IT[TT].Quantidade;
				Arquivo = fopen("DadosIT.bin", "wb");
				fwrite(&IT[TT], sizeof(Itens), 1, Arquivo);

				fclose(Arquivo);
				break;
			case 4:
				Atualizar(Arquivo, IT, pos, PD);
				break;
			default:
				break;
			}
		}
		while(position1 != 4);
	}
}
void Excluir(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100])
{
	int i, TAM, Codigo, TT;
	cout << "Insira o Codigo: ";
	cin >> Codigo;

	TAM = IniciarItens(Arquivo, IT);
	for(i = 0; i < TAM; i++)
	{
		if(IT[i].Codigo == Codigo)
		{
			TT = i;
		}
	}
	if(TT != -1)
	{
		cout << "       Nome: " << IT[TT].NomeItem << endl;
		cout << "      Preco: " << IT[TT].Preco << endl;
		cout << "     Codigo: " << IT[TT].Codigo << endl;
		cout << " Quantidade: " << IT[TT].Quantidade << endl;
		Sleep(1300);

		if(TT == 0)
			for(i = 1; i < TAM; i++)
				IT[i - 1] = IT[i];
		else
			for(i = 0; i < TAM; i++)
				if(i >= TT)
					IT[i] = IT[i + 1];

		Arquivo = fopen ("DadosIT.bin", "wb");
		for(i = 0; i < TAM - 1; i++)
			fwrite(&IT[i], sizeof(Itens), 1, Arquivo);
		fclose(Arquivo);
	}


}

// ALTERAÇÕES ;;;

void imprimirArcoIris(string x)
{
	cout << "|";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int k = 10, tam = x.length();

	for(int i = 0; i < tam; i++)
	{
		SetConsoleTextAttribute(hConsole, k);
		if (k > 14)
		{
			k = 10;
		}

		((i + 1) % 2 != 0) ? cout << char(toupper(x[i])) : cout << x[i];
		Sleep(70);
		k++;
	}
	SetConsoleTextAttribute(hConsole, 0);
}

void imprimirArcoIrisLC(string x)
{
	string login_cliente, senha_cliente;
	cout << "|";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int k = 10, tam = x.length();

	for(int i = 0; i < tam; i++)
	{
		SetConsoleTextAttribute(hConsole, k);
		if (k > 14)
		{
			k = 10;
		}

		((i + 1) % 2 != 0) ? cout << char(toupper(x[i])) : cout << x[i];
		Sleep(70);
		// k++; CASO QUEIRA QUE FIQUE COLORIDO ;
	}
}
int MenuPrincipal()
{
#define MENU_MAX 3
#define MENU_MIN 1

	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Prototipo de Aplicativo ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] CLIENTE");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] EMPRESA");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] SAIR DO PROGRAMA");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != MENU_MAX)
			position++;
		else if (arrowPress == 72 && position != MENU_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);

	return position;
}

int MenuPrincipalCliente()
{
#define MENUCliente_MAX 3
#define MENUCliente_MIN 1

	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " CLIENTE ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] LOGIN");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] REGISTRO");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] SAIR DO PROGRAMA");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != MENUCliente_MAX)
			position++;
		else if (arrowPress == 72 && position != MENUCliente_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	return position;
}

int MenuPrincipalEmpresa()
{
#define MENUEmpresa_MAX 3
#define MENUEmpresa_MIN 1

	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " EMPRESA ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] LOGIN");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] REGISTRO");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] SAIR DO PROGRAMA");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != MENUEmpresa_MAX)
			position++;
		else if (arrowPress == 72 && position != MENUEmpresa_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);

	return position;
}

void MenuCliente(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Cliente_MAX 3
#define Cliente_MIN 1
	system("cls");
	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " USUÁRIO: CLIENTE ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] REALIZAR COMPRA");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] VIZUALIZAR SUA ROTA");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] SAIR DO PROGRAMA");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Cliente_MAX)
			position++;
		else if (arrowPress == 72 && position != Cliente_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);

	switch (position)
	{
	case 1:
		Compra(Arquivo, pos, PD, Achou);
		break;
	case 2:
		VisualizarRota(Arquivo, pos, Achou);
		break;
	case 3:
		Saida();
		break;
	}
}

void MenuEmpresa(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100])
{
#define Empresa_MAX 4
#define Empresa_MIN 1
	system("cls");
	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " USUÁRIO: EMPRESA ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] CADASTRO DE ITENS");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] CAIXA");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] CONSULTA DE ITENS");
		arrow(4, position);
		criaMenuItem(STRTAM, "[4] SAIR DO PROGRAMA");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Empresa_MAX)
			position++;
		else if (arrowPress == 72 && position != Empresa_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);

	switch (position)
	{
	case 1:
		CadastroItens(Arquivo, IT, pos);
		break;
	case 2:
		Caixa(Arquivo, IT, pos, PD);
		break;
	case 3:
		Consulta(Arquivo, IT, pos);
		break;
	case 4:
		Saida();
		break;
	}
}

int VisualizarRota(FILE* Arquivo, int TAM, int Achou)
{
	int i, TT;
	TAM = IniciarPedidos(Arquivo, PD);
	Arquivo = fopen ("Pedidos.bin", "rb");
	for(i = 0; i < TAM; i++)
	{
		if(PD[i].CPF == Achou)
			TT = i;
	}
	if(PD[TT].Control == 0)
	{
		cout << " Aguarde... Seu Pedido está em analise !!!";
	}
	if(PD[TT].Control == 1)
	{
		cout << " Seu Pedido foi Aceito ";
	}
	else if(PD[TT].Control == 2)
	{
		cout << " Seu Pedido saiu para entrega ";
	}
}

string Promo1(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define First1_MAX 5
#define First1_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Pizza Grande + Refri 1 Litro ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Frango com Catupiry");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Portuguesa");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza 4 Queijos");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != First1_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != First1_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 111, 38.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 112, 44.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 113, 48.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 114, 48.00, Achou);
		break;
	case 5:
		PromocaoDoDia(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Promo2(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Second1_MAX 5
#define Second1_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Combos Feliz 2 Pizza G + Refri 2 Litros ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa e/ou Chocolate Branco");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Frango com Catupiry e/ou Banana com Chocolate");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Portuguesa e/ou Pizza Brigadeiro");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza 4 Queijos e/ou Pizza de Chocolate");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Second1_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Second1_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 121, 58.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 122, 65.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 123, 67.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 124, 67.00, Achou);
		break;
	case 5:
		PromocaoDoDia(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Promo3(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Third1_MAX 5
#define Third1_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Combo 1 Pizza P + Refri 1 Litro ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Frango com Catupiry");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Portuguesa");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza 4 Queijos");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Third1_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Third1_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 131, 20.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 132, 24.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 133, 28.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 134, 28.00, Achou);
		break;
	case 5:
		PromocaoDoDia(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Promo4(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Fourth1_MAX 5
#define Fourth1_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Combo 1 Pizza M + Refri 1 Litro ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Frango com Catupiry");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Portuguesa");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza 4 Queijos");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Fourth1_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Fourth1_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 141, 30.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 142, 34.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 143, 38.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 144, 38.00, Achou);
		break;
	case 5:
		PromocaoDoDia(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Combo1(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define First2_MAX 5
#define First2_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Pizza Familia + Refri 2 Litros ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Chocolate Branco");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Banana com Chocolate");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != First2_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != First2_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 211, 52.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 212, 62.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 213, 55.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 214, 56.00, Achou);
		break;
	case 5:
		Combos(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Combo2(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Second2_MAX 5
#define Second2_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Duas Pizzas Grande + Refri 2 Litros ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa e Mussarela ");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa + Bacon");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza 4 Queijos + Chocolate Branco");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Frango com Catupiry + Banana com Chocolate");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Second2_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Second2_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 221, 66.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 222, 76.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 223, 76.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 224, 70.00, Achou);
		break;
	case 5:
		Combos(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Combo3(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Third2_MAX 5
#define Third2_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Pizza Grande + Refri 1 Litro ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Chocolate Branco");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Banana com Chocolate");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Third2_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Third2_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 231, 46.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 232, 56.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 233, 49.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 234, 49.00, Achou);
		break;
	case 5:
		Combos(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Combo4(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Fourth2_MAX 5
#define Fourth2_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Pizza Média + Refri 1 Litro ");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Calabresa");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza Chocolate Branco");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Banana com Chocolate");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Fourth2_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Fourth2_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 241, 38.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 242, 48.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 243, 41.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 244, 41.00, Achou);
		break;
	case 5:
		Combos(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Pizza1(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define First3_MAX 5
#define First3_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "        Pizza Familia");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Bacon");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza 4 Queijos");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Frango com Catupiry");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != First3_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != First3_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 311, 56.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 312, 64.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 313, 64.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 314, 60.00, Achou);
		break;
	case 5:
		Pizzas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Pizza2(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Second3_MAX 5
#define Second3_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "        Pizza Grande");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Bacon");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza 4 Queijos");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Frango com Catupiry");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Second3_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Second3_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 321, 48.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 322, 58.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 323, 58.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 324, 52.00, Achou);
		break;
	case 5:
		Pizzas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Pizza3(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Third3_MAX 5
#define Third3_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "        Pizza Media");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Bacon");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza 4 Queijos");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Frango com Catupiry");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Third3_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Third3_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 331, 40.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 332, 50.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 333, 50.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 334, 46.00, Achou);
		break;
	case 5:
		Pizzas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Pizza4(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Fourth3_MAX 5
#define Fourth3_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "        Pizza Pequena");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Pizza Bacon");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Pizza Portuguesa");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Pizza 4 Queijos");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Pizza Frango com Catupiry");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Fourth3_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Fourth3_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 341, 26.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 342, 36.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 343, 36.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 344, 32.00, Achou);
		break;
	case 5:
		Pizzas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Drinks(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define First4_MAX 5
#define First4_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "          Refri/Drinks");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Refrigerante Coca Cola 2L");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Refrigerante Coca Cola 1L");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Caipirinha (300 ml)");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Whisky Teachers Importado 1L");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != First4_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != First4_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 411, 10.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 412, 6.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 413, 12.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 414, 70.00, Achou);
		break;
	case 5:
		Bebidas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Sucos(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Second4_MAX 5
#define Second4_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "     Sucos Naturais 900ml");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Uva");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Laranja");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Maracuja");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Morango");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Second4_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Second4_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 421, 11.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 422, 11.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 423, 11.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 424, 11.00, Achou);
		break;
	case 5:
		Bebidas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Cervejas(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Third4_MAX 5
#define Third4_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "           Cerveja");
		criaMenuItem(STRTAM, "           Sabores");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Chopp (200 ml)");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Chopp (300 ml)");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Cerveja Lata Skol (350ml)");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Cerveja Lata Antarctica (350ml)");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Third4_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Third4_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 431, 8.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 432, 10.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 433, 4.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 434, 4.00, Achou);
		break;
	case 5:
		Bebidas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

string Vinhos(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Fourth4_MAX 5
#define Fourth4_MIN 1
	string Codigo;
	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "            Vinhos");
		criaMenuItem(STRTAM, "           Escolhas");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Jarra Pequena");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Jarra Grande");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Sangria Pequena");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Sangria Grande");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Fourth4_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Fourth4_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);
	switch(position1)
	{
	case 1:
		SAVED(Arquivo, pos, PD, 441, 20.00, Achou);
		break;
	case 2:
		SAVED(Arquivo, pos, PD, 442, 30.00, Achou);
		break;
	case 3:
		SAVED(Arquivo, pos, PD, 443, 30.00, Achou);
		break;
	case 4:
		SAVED(Arquivo, pos, PD, 444, 40.00, Achou);
		break;
	case 5:
		Bebidas(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

int SAVED(FILE* Arquivo, int pos, Pedido PD[100], int Cod, float real, int Achou)
{
	int QT;
	pos = IniciarPedidos(Arquivo, PD);
	cout << " Informe a quantidade: ";
	cin >> PD[pos + 1].Quantidade;
	PD[pos + 1].Codigo = Cod;
	PD[pos + 1].Control = 0;
	PD[pos + 1].Valor = real;
	PD[pos + 1].CPF = Achou;
	fwrite(&PD[pos + 1], sizeof(Pedido), 1, Arquivo);
	fclose(Arquivo);
	QT = PD[pos + 1].Quantidade;
	SAVED3(Cod, QT, Achou);
}

int SAVED2(FILE* Arquivo, int pos, Pedido PD[100], int C)
{
	PD[pos].Control = C;
	Arquivo = fopen ("Pedidos.bin", "wb");
	fwrite(&PD[pos], sizeof(Pedido), 1, Arquivo);

	fclose(Arquivo);
}

int SAVED3(int Cod, int qt, int Achou)
{
	int TAM, i;
	FILE* Arquivo;
	Itens IT[100];
	TAM = IniciarItens(Arquivo, IT);

	for(i = 0; i <= TAM; i++)
	{
		if(IT[i].Codigo == Cod)
		{
			IT[i].Quantidade -= qt;
		}
	}
	Arquivo = fopen("DadosIT.bin", "wb");
	for(i = 0; i < TAM; i++)
		fwrite(&IT[i], sizeof(Itens), 1, Arquivo);

	fclose(Arquivo);
	SAVED4(Achou);
}

int SAVED4(int Achou)
{
#define Bairros_MAX 17
#define Bairros_MIN 1
	int TAM, i, TT = -1;
	FILE* Arquivo;
	Pedido PD[100];
	TAM = IniciarPedidos(Arquivo, PD);
	for(i = 0; i < TAM; i++)
	{
		if(PD[i].CPF == Achou)TT = i;
	}

	int position1 = 1, arrowPress1;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "  Mossoro RN ");
		criaMenuItem(STRTAM, "    Bairros  ");
		arrow(1, position1);
		criaMenuItem(STRTAM, "[1] Belo Horizonte");
		arrow(2, position1);
		criaMenuItem(STRTAM, "[2] Boa Vista");
		arrow(3, position1);
		criaMenuItem(STRTAM, "[3] Alagados");
		arrow(4, position1);
		criaMenuItem(STRTAM, "[4] Itapetinga");
		arrow(5, position1);
		criaMenuItem(STRTAM, "[5] Alto de São Manoel ");
		arrow(6, position1);
		criaMenuItem(STRTAM, "[6] Ilha de Santa Luzia");
		arrow(7, position1);
		criaMenuItem(STRTAM, "[7] Liberdade I");
		arrow(8, position1);
		criaMenuItem(STRTAM, "[8] Liberdade II");
		arrow(9, position1);
		criaMenuItem(STRTAM, "[9] Costa e Silva");
		arrow(10, position1);
		criaMenuItem(STRTAM, "[10] Sumaré");
		arrow(11, position1);
		criaMenuItem(STRTAM, "[11] Santa Delmira");
		arrow(12, position1);
		criaMenuItem(STRTAM, "[12] Abolição ");
		arrow(13, position1);
		criaMenuItem(STRTAM, "[13] Redenção");
		arrow(14, position1);
		criaMenuItem(STRTAM, "[14] Paredões");
		arrow(15, position1);
		criaMenuItem(STRTAM, "[15] Doze Anos ");
		arrow(16, position1);
		criaMenuItem(STRTAM, "[16] Independência");
		arrow(17, position1);
		criaMenuItem(STRTAM, "[17] Santa Helena");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress1 = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress1 == 80 && position1 != Bairros_MAX)
			position1++;
		else if (arrowPress1 == 72 && position1 != Bairros_MIN)
			position1--;
		else
			position1 = position1;
	}
	while (arrowPress1 != 13);

	switch(position1)
	{
	case 1:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 1;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 2:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 2;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 3:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 3;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 4:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 4;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 5:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 5;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 6:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 6;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 7:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 7;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 8:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 8;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 9:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 9;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 10:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 10;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 11:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 11;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 12:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 12;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 13:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 13;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 14:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 14;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 15:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 15;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 16:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 16;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	case 17:
		IniciarPedidos(Arquivo, PD);
		PD[TT].Bairro = 17;
		Arquivo = fopen("Pedidos.bin", "wb");
		fwrite(&PD[TT], sizeof(Pedido), 1, Arquivo);

		fclose(Arquivo);
		break;
	default:
		break;
	}
}
int PromocaoDoDia(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Promocao_MAX 5
#define Promocao_MIN 1
	int position = 1, arrowPress;
	do
	{

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " PROMOÇÃO DO DIA ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] Pizza Grande + Refri 1 Litro");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] Combos Feliz 2 Pizza G + Refri 2 Litros");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] Combo 1 Pizza P + Refri 1 Litro");
		arrow(4, position);
		criaMenuItem(STRTAM, "[4] Combo 1 Pizza M + Refri 1 Litro");
		arrow(5, position);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Promocao_MAX)
			position++;
		else if (arrowPress == 72 && position != Promocao_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	switch(position)
	{
	case 1:
		Promo1(Arquivo, pos, PD, Achou);
		break;
	case 2:
		Promo2(Arquivo, pos, PD, Achou);
		break;
	case 3:
		Promo3(Arquivo, pos, PD, Achou);
		break;
	case 4:
		Promo4(Arquivo, pos, PD, Achou);
		break;
	case 5:
		Compra(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

int Combos(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Combo_MAX 5
#define Combo_MIN 1
	int position = 1, arrowPress;
	do
	{

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " COMBOS ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] Combo Familia + Refri 2 Litros");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] Combo Duas Grandes + Refri 2 Litros");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] Combo Grande + Refri 1 Litro");
		arrow(4, position);
		criaMenuItem(STRTAM, "[4] Combo Media + Refri 1 Litro");
		arrow(5, position);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Combo_MAX)
			position++;
		else if (arrowPress == 72 && position != Combo_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	switch(position)
	{
	case 1:
		Combo1(Arquivo, pos, PD, Achou);
		break;
	case 2:
		Combo2(Arquivo, pos, PD, Achou);
		break;
	case 3:
		Combo3(Arquivo, pos, PD, Achou);
		break;
	case 4:
		Combo4(Arquivo, pos, PD, Achou);
		break;
	case 5:
		Compra(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

int Pizzas(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Pizza_MAX 5
#define Pizza_MIN 1
	int position = 1, arrowPress;
	do
	{

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " PIZZAS ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] Pizza Tamanho Familia");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] Pizza Tamanho Grande");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] Pizza Tamanho Media");
		arrow(4, position);
		criaMenuItem(STRTAM, "[4] Pizza Tamanho Pequena");
		arrow(5, position);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Pizza_MAX)
			position++;
		else if (arrowPress == 72 && position != Pizza_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	switch(position)
	{
	case 1:
		Pizza1(Arquivo, pos, PD, Achou);
		break;
	case 2:
		Pizza2(Arquivo, pos, PD, Achou);
		break;
	case 3:
		Pizza3(Arquivo, pos, PD, Achou);
		break;
	case 4:
		Pizza4(Arquivo, pos, PD, Achou);
		break;
	case 5:
		Compra(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

int Bebidas(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Bebida_MAX 5
#define Bebida_MIN 1
	int position = 1, arrowPress;
	do
	{

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " BEBIDAS ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] Refri/Drinks");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] Suco");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] Cerveja");
		arrow(4, position);
		criaMenuItem(STRTAM, "[4] Vinho");
		arrow(5, position);
		criaMenuItem(STRTAM, "[5] VOLTAR");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Bebida_MAX)
			position++;
		else if (arrowPress == 72 && position != Bebida_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	switch(position)
	{
	case 1:
		Drinks(Arquivo, pos, PD, Achou);
		break;
	case 2:
		Sucos(Arquivo, pos, PD, Achou);
		break;
	case 3:
		Cervejas(Arquivo, pos, PD, Achou);
		break;
	case 4:
		Vinhos(Arquivo, pos, PD, Achou);
		break;
	case 5:
		Compra(Arquivo, pos, PD, Achou);
		break;
	default:
		break;
	}
}

int Cancelar()
{
// 	Essa função deve receber como parametro, a quantidade de itens inserios;
// 	Para isso basta criar uma variavel para cada tipo usando codigo de sabores
// 	o codigo de sabores está la no topo desse arquivo;
}

int Compra(FILE* Arquivo, int pos, Pedido PD[100], int Achou)
{
#define Compra_MAX 5
#define Compra_MIN 1

	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " CARDAPIO ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] PROMOÇÃO DO DIA");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] COMBOS");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] PIZZAS");
		arrow(4, position);
		criaMenuItem(STRTAM, "[4] BEBIDAS");
		arrow(5, position);
		criaMenuItem(STRTAM, "[5] Sair");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Compra_MAX)
			position++;
		else if (arrowPress == 72 && position != Compra_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	switch(position)
	{
	case 1:
		PromocaoDoDia(Arquivo, pos, PD, Achou);
		break;
	case 2:
		Combos(Arquivo, pos, PD, Achou);
		break;
	case 3:
		Pizzas(Arquivo, pos, PD, Achou);
		break;
	case 4:
		Bebidas(Arquivo, pos, PD, Achou);
		break;
	case 5:
		Saida();
		break;
	default:
		break;
	}
}

int Consulta(FILE* Arquivo, Itens IT[100], int pos)
{
	IniciarItens(Arquivo, IT);
	int COD, i;
	int TT = -2;
	cout << " Insira o Codigo: ";
	cin >> COD;

	for(i = 0; i <= pos; i++)
	{
		if(IT[i].Codigo == COD)TT = i;
	}

	if(TT != -2)
	{
		cout << "   Codigo: " << IT[TT].Codigo << endl;
		cout << "     Nome: " << IT[TT].NomeItem << endl;
		cout << "    Preço: " << IT[TT].Preco << endl;
		cout << "Quantiade: " << IT[TT].Quantidade << endl;
		fclose(Arquivo);
		system("pause");
		MenuEmpresa(Arquivo, IT, pos, PD);
	}
	else
	{
		cout << " Produto não encontrado !!! ";
		fclose(Arquivo);
		Sleep(2000);
		MenuEmpresa(Arquivo, IT, pos, PD);
	}
}

int CadastroItens(FILE* Arquivo, Itens IT[100], int pos)
{

	cout << " Nome do Produto: ";
	cin.getline(IT[pos + 1].NomeItem, 25);
	cout << " Preço: ";
	cin >> IT[pos + 1].Preco;
	cout << " Codigo: ";
	cin >> IT[pos + 1].Codigo;
	cout << " Quantidade: ";
	cin >> IT[pos + 1].Quantidade;
	fwrite(&IT[pos + 1], sizeof(Itens), 1, Arquivo);
	fclose(Arquivo);
	MenuEmpresa(Arquivo, IT, pos, PD);
}

int Caixa(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100])
{
#define Caixa_MAX 3
#define Caixa_MIN 1
	system("cls");
	int TAM;
	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Caixa ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] Atualizar estoque");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] Fechar Movimento do dia");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] Voltar");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != Caixa_MAX)
			position++;
		else if (arrowPress == 72 && position != Caixa_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);

	switch(position)
	{
	case 1:
		Atualizar(Arquivo, IT, pos, PD);
		break;
	case 2:
		FecharMovimento(PD);
		break;
	case 3:
		MenuEmpresa(Arquivo, IT, pos, PD);
		break;
	default:
		break;
	}
}
int Atualizar(FILE* Arquivo, Itens IT[100], int pos, Pedido PD[100])
{
#define ATT_MAX 4
#define ATT_MIN 1
	system("cls");
	int TAM;
	int position = 1, arrowPress;
	do
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		criaMenuLinhaSuperior();
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, " Atualizar ");
		arrow(1, position);
		criaMenuItem(STRTAM, "[1] Editar Estoque");
		arrow(2, position);
		criaMenuItem(STRTAM, "[2] Listagem de Itens");
		arrow(3, position);
		criaMenuItem(STRTAM, "[3] Exclusão");
		arrow(4, position);
		criaMenuItem(STRTAM, "[3] Voltar");
		criaMenuLinhaRodape(STRTAM);
		cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
		arrowPress = getch();
		system("CLS");
		fflush(stdin);

		if (arrowPress == 80 && position != ATT_MAX)
			position++;
		else if (arrowPress == 72 && position != ATT_MIN)
			position--;
		else
			position = position;
	}
	while (arrowPress != 13);
	switch(position)
	{
	case 1:
		Editar(Arquivo, IT, pos, PD);
		break;
	case 2:
		Listagem(Arquivo, IT, pos, PD);
		break;
	case 3:
		Excluir(Arquivo, IT, pos, PD);
		break;
	case 4:
		Caixa(Arquivo, IT, pos, PD);
		break;
	default:
		break;
	}
}
int FecharMovimento(Pedido PD[100])
{
	int TAM, i;
	FILE* Arquivo;
	TAM = IniciarPedidos(Arquivo, PD);
	Arquivo = fopen ("Pedidos.bin", "rb");
	for(i = 0; i < TAM; i++)
	{
		if(PD[i].Control == 2)
		{
			Balance += PD[i].Quantidade * PD[i].Valor;
			Qt += 1;
		}
	}

	cout << " VALOR TOTAL DE VENDAS: " << Balance << endl;
	cout << " QUANTIDADE TOTAL DE VENDAS: " << Qt << endl;

	for(i = 0; i < TAM; i++)
	{
		if(PD[i].Control == 2)
		{
			PD[i].Control = 3;
		}
	}
	Arquivo = fopen("Pedidos.bin", "wb");
	for(i = 0; i < TAM; i++)
		fwrite(&PD[i], sizeof(Pedido), 1, Arquivo);
	fclose(Arquivo);

	Balance = 0;
	Qt = 0;
}
int Entregas(FILE* Arquivo, int pos, Pedido PD[100])
{
#define ENT_MAX 2
#define ENT_MIN 1
	IniciarPedidos(Arquivo, PD);
	int i = 0;
	for(i = 0; i <= pos; i++)
	{
		system("cls");
		if(PD[i].Control == 0 && PD[i].Quantidade == 0) cout << endl << "Não possui entregas";
		if(PD[i].Codigo != 0 && PD[i].Quantidade != 0)
		{
			if(PD[i].Control == 1)
			{
				int position = 1, arrowPress;
				do
				{
					cout << " Entrega [" << i << "] " << endl;
					cout << " Codigo: " << PD[i].Codigo << endl;
					cout << " Quantidade: " << PD[i].Quantidade << endl;
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 14);
					criaMenuLinhaSuperior();
					criaMenuLinhaHorizontal(STRTAM);
					criaMenuItem(STRTAM, " Entrega ");
					arrow(1, position);
					criaMenuItem(STRTAM, "[1] ACEITAR");
					arrow(2, position);
					criaMenuItem(STRTAM, "[2] RECUSAR");
					criaMenuLinhaRodape(STRTAM);
					cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
					arrowPress = getch();
					system("CLS");
					fflush(stdin);

					if (arrowPress == 80 && position != ENT_MAX)
						position++;
					else if (arrowPress == 72 && position != ENT_MIN)
						position--;
					else
						position = position;
				}
				while (arrowPress != 13);
				if(position == 1)
				{
					int fim;
					int **MDist;
					MDist = AlocaMDist(TAM3);
					MDist = LerMatriz(MDist, TAM3);
					fim = PD[i].Bairro;
					Dijkstra(MDist, TAM3, 0, fim);
					system("pause");
					free(MDist);
					SAVED2(Arquivo, i, PD, 2);
				}
			}
		}
	}
}

int **AlocaMDist(int n)
{
	int i;
	int **Md;
	Md = (int**)malloc(n * sizeof(int*));
	for(i = 0; i < n; i++)
		Md[i] = (int*)malloc(n * sizeof(int));

	return Md;
}

int **LerMatriz(int **M, int n)
{
	int i, j;
	FILE *ArqM;
	ArqM = fopen("Gr17.txt", "r");
	if(ArqM == NULL)
	{
		cout << "Arquivo inexistente ou com problema!" << endl;
		return 0;
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			fscanf(ArqM, "%d", &M[i][j]);
	fclose(ArqM);
	return M;
}

void MostrarResultado(int n, int ini, float dist[TAM3], float pred[TAM3], int fim)
{
	int i, k, ind = 0, j, rota[TAM3];
	for(i = 0; i < n; i++)
	{
		//int k, ind=0;
		if((i != ini) && (i == fim)) //cometar para mostrar todas as rotas
		{
			dist[i] = (dist[i] * 14) / 60;
			if(dist[i] >= 60)
			{
				dist[i] = dist[i] / 60;
				cout << setprecision(2) << "\n Tempo Estimado para entrega: " << dist[i] << " horas " << endl;
			}
			else
			{
				cout << "\n Tempo Estimado para entrega: " << dist[i] << " minutos " << endl;
			}
			//cout << "\nMenor distancia do vertice " << ini << " ao vertice " << i << " = " << dist[i] << endl;
			cout << "Melhor Rota: ";
			rota[ind] = i;
			j = i;
			do
			{
				j = pred[j];
				ind++;
				rota[ind] = j;
			}
			while(j != ini);
			//para exibir cada rota
			while(ind >= 0)
			{
				if(ind != 0)
					cout << rota[ind] << "->";
				else
					cout << rota[ind];
				ind--;
			}
		}

	}

}

void Dijkstra(int **G, int n, int inicial, int fim)
{
	float custo[n][n], distancia[n], pred[n];
	int visitado[n], cont, distanciamin, proxno, i, j;
	int caminho[n];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			custo[i][j] = G[i][j];
	for(i = 0; i < n; i++)
	{
		distancia[i] = custo[inicial][i];
		pred[i] = inicial;
		visitado[i] = 0;
	}
	distancia[inicial] = 0;
	visitado[inicial] = 1;
	cont = 1;
	while(cont < n - 1)
	{
		distanciamin = BIG;
		for(i = 0; i < n; i++)
			if(distancia[i] < distanciamin && !visitado[i])
			{
				distanciamin = distancia[i];
				proxno = i;
			}

		//verifica se existe melhor caminho atraves do proximo node
		visitado[proxno] = 1;
		for(i = 0; i < n; i++)
		{
			if(!visitado[i])
				if(distanciamin + custo[proxno][i] < distancia[i])
				{
					distancia[i] = distanciamin + custo[proxno][i];
					pred[i] = proxno;
				}
		}
		cont++;
	}
	//imprime o caminho e a distancia de cada node ou de um no inicio ao fim
	MostrarResultado(n, inicial, distancia, pred, fim);
}

int Pedidos(FILE* Arquivo, int pos, Pedido PD[100])
{
	pos = IniciarPedidos(Arquivo, PD);
	int i = 0;
	for(i = 0; i <= pos; i++)
	{
#define PED_MAX 2
#define PED_MIN 1
		system("cls");
		if(PD[i].Codigo == 0 && PD[i].Quantidade == 0) cout << endl << "Não possui pedidos";
		if(PD[i].Codigo != 0 && PD[i].Quantidade != 0)
		{
			if(PD[i].Control != 1)
			{
				int position = 1, arrowPress;
				do
				{
					cout << " Pedido [" << i << "] " << endl;
					cout << " Codigo: " << PD[i].Codigo << endl;
					cout << " Quantidade: " << PD[i].Quantidade << endl;
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 14);
					criaMenuLinhaSuperior();
					criaMenuLinhaHorizontal(STRTAM);
					criaMenuItem(STRTAM, " PEDIDO ");
					arrow(1, position);
					criaMenuItem(STRTAM, "[1] ACEITAR");
					arrow(2, position);
					criaMenuItem(STRTAM, "[2] RECUSAR");
					criaMenuLinhaRodape(STRTAM);
					cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
					arrowPress = getch();
					system("CLS");
					fflush(stdin);

					if (arrowPress == 80 && position != PED_MAX)
						position++;
					else if (arrowPress == 72 && position != PED_MIN)
						position--;
					else
						position = position;
				}
				while (arrowPress != 13);
				if(position == 1)
				{
					SAVED2(Arquivo, i, PD, 1);
				}
			}
		}
	}
}

int Saida()
{
	string Saida = " Saindo do Programa . . . |";
	imprimirArcoIris(Saida);
	return 0;
};

//==============================================================================
//     LINHA SUPERIOR DO MENU
//==============================================================================
void criaMenuLinhaSuperior()
{
	int i;
	printf("%c", 201);
	for(i = 0; i < STRTAM; i++)
		printf("%c", 205);
	printf("%c\n", 187);
}

//==============================================================================
//     RODAPÉ DO MENU
//==============================================================================
void criaMenuLinhaRodape(int tamX)
{
	int i;
	printf("%c", 200);
	for(i = 0; i < STRTAM; i++)
		printf("%c", 205);
	printf("%c\n", 188);
}

//==============================================================================
//     ADICIONA LINHAS DO MENU
//==============================================================================
void criaMenuItem(int tamX, char str[])
{
	printf("%c", 186);
	printf("%-*s", tamX, str);
	printf("%c\n", 186);
}

//==============================================================================
//     ADICIONA LINHAS HORIZONTAIS AO MENU
//==============================================================================
void criaMenuLinhaHorizontal(int tamX)
{
	int i;
	printf("%c", 204);
	for(i = 0; i < tamX; i++)
		printf("%c", 205);
	printf("%c\n", 185);
}

void arrow (int position, int arrowPosition)
{
	(position == arrowPosition) ? cout << "->" : cout << " ";
} /* Fim da Função  */
