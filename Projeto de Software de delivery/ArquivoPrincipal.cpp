#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "BiblioGA.h"

using namespace std;

Cliente C2[100];
Empresa EMp[100];
Itens ITe[100];
Pedido PDi[100];

FILE* Arq;
#define STRTAM 40
int TAM;
//-----------------------------------------------------------------------------
//     FUNÇÃO PARA CRIAR UM ARQUIVO
//-----------------------------------------------------------------------------
void AbrirArquivo(char *NomeArq)
{
	Arq = fopen(NomeArq, "ab");
	if(Arq != NULL)
		printf("\n  Arquivo aberto com sucesso!");

}

int login_cliente, senha_cliente;
int login_empresa, senha_empresa;
int main()
{
	int Achou, OPC, TAM;

	OPC = MenuPrincipal();

	switch(OPC)
	{
	case 1:
		OPC = MenuPrincipalCliente();
		switch(OPC)
		{
		case 1:
			TAM = IniciarCliente(Arq, C2); //INICIAR
			Achou = LoginCliente(Arq, C2, login_cliente, senha_cliente); //CONFIRMAR LOGIN
			if(Achou != 0)
			{
				TAM = IniciarPedidos(Arq, PDi);
				AbrirArquivo("Pedidos.bin");
				MenuCliente(Arq, TAM, PDi, Achou);
			}
			break;
		case 2:
			TAM = IniciarCliente(Arq, C2); //INICIAR
			AbrirArquivo("DadosCliente.bin");
			CadastrarCliente(Arq, C2, TAM); //Cadastro de itens
			fclose(Arq);
			break;
		case 3:
			Saida();
			break;
		}
		break;
	case 2:
		OPC = MenuPrincipalEmpresa();
		switch(OPC)
		{
		case 1:
			TAM = IniciarEmpresa(Arq, EMp); //INICIAR
			Achou = LoginEmpresa(Arq, EMp, login_empresa, senha_empresa);
			if(Achou == 1)
			{
#define EMPRESAa_MAX 3
#define EMPRESAa_MIN 1
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
					criaMenuItem(STRTAM, "[1] Pedidos Pendentes");
					arrow(2, position);
					criaMenuItem(STRTAM, "[2]  Demais funções");
					arrow(3, position);
					criaMenuItem(STRTAM, "[2] Entregas Pendentes");
					criaMenuLinhaRodape(STRTAM);
					cout << " Informe sua opção: Use as setas  para cima e baixo" << endl;
					arrowPress = getch();
					system("CLS");
					fflush(stdin);

					if (arrowPress == 80 && position != EMPRESAa_MAX)
						position++;
					else if (arrowPress == 72 && position != EMPRESAa_MIN)
						position--;
					else
						position = position;
				}
				while (arrowPress != 13);

				switch(position)
				{
				case 1:
					TAM = IniciarPedidos(Arq, PDi);
					AbrirArquivo("Pedidos.bin");
					Pedidos(Arq, TAM, PDi);
					break;
				case 2:
					IniciarPedidos(Arq, PDi);
					AbrirArquivo("Pedidos.bin");
					TAM = IniciarItens(Arq, ITe);
					AbrirArquivo("DadosIT.bin");
					MenuEmpresa(Arq, ITe, TAM, PDi);
					break;
				case 3:
					TAM = IniciarPedidos(Arq, PDi);
					AbrirArquivo("Pedidos.bin");
					Entregas(Arq, TAM, PDi);
					break;
				default:
					break;
				}
			}
			break;
		case 2:
			TAM = IniciarEmpresa(Arq, EMp); //INICIAR
			AbrirArquivo("DadosEmpresa.bin");
			CadastrarEmpresa(Arq, EMp, TAM); //Cadastro de itens
			break;
		case 3:
			Saida();
			break;
		}
		break;
	case 3:
		Saida();
		break;
	}

	return 0;
}
