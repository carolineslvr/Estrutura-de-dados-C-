#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
#include<fstream>

using namespace std;

#include "lista_dupla4.hpp"

main()
{
	setlocale (LC_ALL , "Portuguese");

	int pos, cod, menu;
	DadoNoLista valor;
    No* aux = nullptr;
    bool teste;
    Lista *lista = new Lista();


    ifstream arq("cadastro.txt");
    string codigo, nome, sexo, cidade, ano, tiposangue;

    while(!arq.eof()) //abc1256#2000#volkswagen#fusca
    {

        if (getline(arq,  codigo, '#')  &&
            getline(arq, nome,   '#') &&
            getline(arq, sexo, '#') &&
            getline(arq, cidade, '#') &&
            getline(arq, ano, '#') &&
            getline(arq, tiposangue))
        {
            insereFinal(lista, Funcionarios(stoi(codigo), nome, sexo, cidade, stoi(ano), tiposangue));
        }
    }

    do
    {
        system("cls");

        cout << "********MENU DE OP��ES********" << endl;
        cout << "* 0 - Sair                   *" << endl;
        cout << "* 1 - Mostrar lista          *" << endl;
        cout << "* 2 - Ordenar lista          *" << endl;
        cout << "* 3 - Remover Funcion�rio    *" << endl;
        cout << "* 4 - Remover por cidade     *" << endl;
        cout << "* 5 - Informa��es            *" << endl;
        cout << "* 6 - Tipos sangu�neos       *" << endl;
        cout << "**************************" << endl;
        cout << "Sua escolha: ";
        cin >> menu;
        fflush(stdin);

        system("cls");

        if (vaziaL(lista) && (menu > 1 && menu <= 6))
        {
            cout << "Lista vazia! Sem funcion�rios para gerenciar.";
            getchar();
            continue;
        }

        if (menu == 1)
        {
            cout << lista << endl;
            getchar();

        } else if (menu == 2)
        {
            int escolha;

            do
            {
                cout << "Digite 1 para ordena��o alfab�tica ou 2 para ordena��o por c�digo: ";
                cin >> escolha;
                fflush(stdin);

                if (escolha != 1 && escolha != 2)
                {
                    cout << "Op��o inv�lida! Tente novamente.";
                    getchar();
                    system("cls");
                }

            } while (escolha != 1 && escolha != 2);

            if (escolha == 1)
            {
                ordenacaoAlfabetica(lista);

                cout << "Lista de funcion�rios em ordem alfab�tica:\n";
                cout << lista;
                getchar();

            } else if (escolha == 2)
            {
                ordenaPorCodigo(lista);

                cout << "Lista de funcion�rios ordenada por c�digo:\n";
                cout << lista;
                getchar();
            }

        } else if (menu == 3)
        {
            cout << "Informe o c�digo do funcion�rio que deseja remover: ";
            cin >> cod;
            fflush(stdin);

            if (removeL(lista, cod))
            {
                cout << "Funcion�rio c�digo: " << cod << " removido com sucesso!";
                getchar();

            } else
            {
                cout << "Ocorreu um erro ao remover o funcion�rio " << cod << ". ";
                getchar();
            }

        } else if (menu == 4)
        {
            string cidade;

            cout << "Remover da lista os funcion�rios da cidade: ";
            cin >> cidade;
            fflush(stdin);

            if(removePorCidade(lista, cidade))
            {
                cout << "Funcion�rios da cidade " << cidade << " foram removidos da lista com sucesso!";
                getchar();

            } else
            {
                cout << "Ocorreu um erro ao remover os funcion�rios registrados na cidade " << cidade << ". ";
                getchar();
            }

        } else if (menu == 5)
        {
            contagem(lista);
            getchar();

        } else if (menu == 6)
        {
            string t;

            cout << "Informe o tipo sangu�neo que deseja buscar: ";
            cin >> t;
            fflush(stdin);

            cout << "Funcion�rios com o tipo sangu�neo " << t << ":\n";

            buscaTipoSangue(lista, t);
            getchar();

        } else if (menu == 0)
        {
            cout << "\nProgama encerrado com sucesso!\n";
            delete(lista);
            return EXIT_SUCCESS;
        }

    } while (menu != 0);

}


