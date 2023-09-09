#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
#include<fstream>

using namespace std;

#include "fila-dinamica6.hpp"
#include "pilha-dinamica5.hpp"

main()
{
    setlocale (LC_ALL, "Portuguese");


    Fila fg, fe, aux;
    Pilha animals, animald, aux1;
    Atendimento valor, v;
    int cont, total, domesticos, grave, menor, i;
    int *menu = new int;
    string m;
    bool resultado, primeiro;


    do
    {
        system("cls");

        cout << "********** MENU DE OPÇÕES **********" << endl;
        cout << "* 1 - Cadastrar animal             *" << endl;
        cout << "* 2 - Atender animal               *" << endl;
        cout << "* 3 - Verificar filas              *" << endl;
        cout << "* 4 - Dados gerais                 *" << endl;
        cout << "* 5 - Fichas já atendidas          *" << endl;
        cout << "* 6 - Remover ficha                *" << endl;
        cout << "* 7 - Quadro grave e menor idade   *" << endl;
        cout << "* 8 - Sair                         *" << endl;
        cout << "************************************" << endl;
        cout << "Sua escolha: ";
        cin >> *menu;
        fflush(stdin);

        system("cls");

        if ((vaziaF(&fg) && vaziaF(&fe)) && (*menu == 2 or *menu == 3 or *menu == 4))
        {
            cout << "Não há animais na fila de atendimento!";
            getchar();
            continue;
        }
        if (*menu == 1)
        {
            cout << "Informe o nome do animal: ";
            getline(cin, valor.nome);
            fflush(stdin);

            cout << "Informe a idade do animal: ";
            cin >> valor.idade;
            fflush(stdin);

            cout << "Informe se é doméstico (D) ou selvagem (S): ";
            cin >> valor.tipo;
            fflush(stdin);

            cout << "Informe o quadro clínico do animal (G para grave ou E para estável): ";
            cin >> valor.quadro;
            fflush(stdin);

            if (valor.quadro == 'G' or valor.quadro == 'g')
            {
                resultado = enfileiraF(&fg, valor);

                if(resultado == true)
                {
                    cout << "Animal cadastrado com sucesso e incluído na fila de atendimentos prioritários.";
                    getchar();
                }
                else
                {
                    cout << "Desculpe! Ocorreu um erro ao cadastrar o animal.";
                    getchar();
                }
            }
            else if (valor.quadro == 'e' or valor.quadro == 'E')
            {
                resultado = enfileiraF(&fe, valor);

                if(resultado == true)
                {
                    cout << "Animal cadastrado com sucesso e incluído na fila de atendimentos não prioritários.";
                    getchar();
                }
                else
                {
                    cout << "Desculpe! Ocorreu um erro ao cadastrar o animal.";
                    getchar();
                }
            }

        }
        else if (*menu == 2)
        {
            cont++;
            if (!vaziaF(&fg) && cont <= 3)
            {
                valor = desenfileiraF(&fg);
                if (valor.tipo == 'd' or valor.tipo == 'D')
                {
                    empilhaP(&animald, valor);

                }
                else if (valor.tipo == 's' or valor.tipo == 'S')
                {
                    empilhaP(&animals, valor);
                }

                cout << "O animal " << valor.nome << " foi atendido com sucesso na fila de atendimentos prioritários!";

                getchar();

            }
            else if (!vaziaF(&fe))
            {
                valor = desenfileiraF(&fe);
                if (valor.tipo == 'd' or valor.tipo == 'D')
                {
                    empilhaP(&animald, valor);

                }
                else if (valor.tipo == 's' or valor.tipo == 'S')
                {
                    empilhaP(&animals, valor);
                }
                cout << "O animal " << valor.nome << " foi atendido com sucesso na fila de atendimentos não prioritários!";
                cont = 0;
                getchar();
            }
        }
        else if (*menu == 3)
        {
            cout << "Fila de atendimentos prioritários:\n";
            mostraF(&fg);

            cout << "\nFila de atendimentos não prioritários:\n";
            mostraF(&fe);

            getchar();

        }
        else if (*menu == 4)
        {
            total = 0;
            grave = 0;
            domesticos = 0;
            while (!vaziaF(&fg))
            {
                v = desenfileiraF(&fg);
                enfileiraF(&aux, v);
                total++;
                grave++;

                if (v.tipo == 'd' or v.tipo == 'D')
                {
                    domesticos++;
                }
            }
            while (!vaziaF(&aux))
            {
                v = desenfileiraF(&aux);
                enfileiraF(&fg, v);
            }
            while (!vaziaF(&fe))
            {
                v = desenfileiraF(&fe);
                enfileiraF(&aux, v);
                total++;

                if (v.tipo == 'd' or v.tipo == 'D')
                {
                    domesticos++;
                }
            }
            while (!vaziaF(&aux))
            {
                v = desenfileiraF(&aux);
                enfileiraF(&fe, v);
            }

            cout << "Total de fichas em atendimento: " << total << endl;
            cout << "Porcentagem de animais em estado grave: " << ((float)grave / (float)total) * 100 << "%" << endl;
            cout << "Total de animais domésticos: " << domesticos;
            getchar();
        }
        else if (*menu == 5)
        {
            cout << "Animais domésticos já atendidos:\n";
            mostraP(&animald);

            cout <<"\nAnimais selvagens já atendidos:\n";
            mostraP(&animals);

            getchar();
        }
        else if (*menu == 6)
        {
            cout << "Informe a pilha da qual deseja retirar uma ficha: ";
            cin >> valor.tipo;
            fflush(stdin);

            if (valor.tipo == 'd' or valor.tipo == 'D')
            {
                valor = desempilhaP(&animald);
                cout << "A ficha do animal " << valor.nome << " foi retirada com sucesso da pilha de animais domésticos.";
                getchar();
            }
            else if (valor.tipo == 's' or valor.tipo == 'S')
            {
                valor = desempilhaP(&animals);
                cout << "A ficha do animal " << valor.nome << " foi retirada com sucesso da pilha de animais selvagens.";
                getchar();
            }
        }
        else if (*menu == 7)
        {
            primeiro = true;

            while (!vaziaP(&animald))
            {
                v = desempilhaP(&animald);
                empilhaP(&aux1, v);

                if(v.quadro == 'g' or v.quadro == 'G')
                {
                    if (primeiro)
                    {
                        menor = v.idade;
                        m = v.nome;
                        primeiro = false;
                    }
                    else if (v.idade < menor)
                    {
                        menor = v.idade;
                        m = v.nome;
                    }
                }
            }
            while (!vaziaP(&aux1))
            {
                v = desempilhaP(&aux1);
                empilhaP(&animald, v);
            }
            primeiro = true;

            while (!vaziaP(&animals))
            {
                v = desempilhaP(&animals);
                empilhaP(&aux1, v);

                if(v.quadro == 'g' or v.quadro == 'G')
                {
                    if (i == 0)
                    {
                        menor = v.idade;
                        m = v.nome;
                        primeiro = false;
                    }
                    else if (v.idade < menor)
                    {
                        menor = v.idade;
                        m = v.nome;
                    }
                }
            }
            while (!vaziaP(&aux1))
            {
                v = desempilhaP(&aux1);
                empilhaP(&animals, v);
            }

            cout << "O animal mais novo em estado grave tem " << menor << " anos de idade e se chama " << m << ". ";
            getchar();

        }
        else if (*menu == 8)
        {
            cout << "\nPrograma encerrado com sucesso!\n";
            destroiF(&fe);
            destroiF(&fg);
            destroiF(&aux);
            destroiP(&animals);
            destroiP(&animald);
            destroiP(&aux1);

            return EXIT_SUCCESS;
        }
        else
        {
            cout << "Opção inválida! Tente novamente.\n";
            getchar();
        }
    } while (*menu != 8);
}

