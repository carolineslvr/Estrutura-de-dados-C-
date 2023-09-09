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

        cout << "********MENU DE OPÇÕES********" << endl;
        cout << "* 0 - Sair                   *" << endl;
        cout << "* 1 - Mostrar lista          *" << endl;
        cout << "* 2 - Ordenar lista          *" << endl;
        cout << "* 3 - Remover Funcionário    *" << endl;
        cout << "* 4 - Remover por cidade     *" << endl;
        cout << "* 5 - Informações            *" << endl;
        cout << "* 6 - Tipos sanguíneos       *" << endl;
        cout << "**************************" << endl;
        cout << "Sua escolha: ";
        cin >> menu;
        fflush(stdin);

        system("cls");

        if (vaziaL(lista) && (menu > 1 && menu <= 6))
        {
            cout << "Lista vazia! Sem funcionários para gerenciar.";
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
                cout << "Digite 1 para ordenação alfabética ou 2 para ordenação por código: ";
                cin >> escolha;
                fflush(stdin);

                if (escolha != 1 && escolha != 2)
                {
                    cout << "Opção inválida! Tente novamente.";
                    getchar();
                    system("cls");
                }

            } while (escolha != 1 && escolha != 2);

            if (escolha == 1)
            {
                ordenacaoAlfabetica(lista);

                cout << "Lista de funcionários em ordem alfabética:\n";
                cout << lista;
                getchar();

            } else if (escolha == 2)
            {
                ordenaPorCodigo(lista);

                cout << "Lista de funcionários ordenada por código:\n";
                cout << lista;
                getchar();
            }

        } else if (menu == 3)
        {
            cout << "Informe o código do funcionário que deseja remover: ";
            cin >> cod;
            fflush(stdin);

            if (removeL(lista, cod))
            {
                cout << "Funcionário código: " << cod << " removido com sucesso!";
                getchar();

            } else
            {
                cout << "Ocorreu um erro ao remover o funcionário " << cod << ". ";
                getchar();
            }

        } else if (menu == 4)
        {
            string cidade;

            cout << "Remover da lista os funcionários da cidade: ";
            cin >> cidade;
            fflush(stdin);

            if(removePorCidade(lista, cidade))
            {
                cout << "Funcionários da cidade " << cidade << " foram removidos da lista com sucesso!";
                getchar();

            } else
            {
                cout << "Ocorreu um erro ao remover os funcionários registrados na cidade " << cidade << ". ";
                getchar();
            }

        } else if (menu == 5)
        {
            contagem(lista);
            getchar();

        } else if (menu == 6)
        {
            string t;

            cout << "Informe o tipo sanguíneo que deseja buscar: ";
            cin >> t;
            fflush(stdin);

            cout << "Funcionários com o tipo sanguíneo " << t << ":\n";

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


