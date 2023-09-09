#ifndef _HPP_LISTA_DUPLA
#define _HPP_LISTA_DUPLA

struct Funcionarios
{
    int codigo;
    string nome;
    string sexo;
    string cidade;
    int ano;
    string tiposangue;

    Funcionarios()
    {
        codigo = 0;
        nome = " ";
        sexo = "";
        cidade = " ";
        ano = 0;
        tiposangue = " ";
    }
    Funcionarios(int cod, string n, string s, string cid, int a, string ts)
    {
        codigo = cod;
        nome = n;
        sexo = s;
        cidade = cid;
        ano = a;
        tiposangue = ts;
    }
};

typedef Funcionarios DadoNoLista;

struct No
{
    DadoNoLista dado;
    No *prox;
    No *ant;
    No() // construtor
    {
        prox = nullptr;
        ant = nullptr;
    }
};

struct Lista
{
    No *inicio;
    No *fim;
    int tamanho;
    Lista() /// construtor
    {
        //cout << "\n executando o construtor...\n";
        inicio = nullptr;
        fim = nullptr;
        tamanho =0;
    }
    ~Lista() /// desconstrutor /// quando chame delete(ponteiro)
    {
        //cout << "\n executando o desconstrutor....\n";
        No *n = inicio;
        while(n)
        {
            No *aux = n;
            n = n->prox;
            delete aux;
        }
    }
};


/// quando cout receber uma struct No
ostream& operator<<(ostream& os, const No *n)
{
    /// cout << n
    return os << "Código: " << n->dado.codigo << ". Nome: " << n->dado.nome << ". Sexo: " << n->dado.sexo
    << ". Cidade: " << n->dado.cidade << ". Ano Nascimento: " << n->dado.ano << ". Tipo sanguíneo: " << n->dado.tiposangue;
}

/// quanto cout receber uma struct Lista
ostream& operator << (ostream& os, const Lista *l)
{
    No *n = l->inicio;
    while(n)
    {
        os << n << std::endl;
        n = n->prox;
        if(n)
            os << "\n";
    }
    return os;
}


bool vaziaL(Lista *lista)
{
    if(! (lista->inicio) )
        return true;
    else
        return false;
}


void mostrarInversoL(Lista *lista)
{
    No *n = lista->fim;
    cout << "L[" << lista->tamanho << "]:{";
    while(n)
    {
        cout << n;
        n = n->ant;

        if(n)
            cout << ", ";
    }
    cout << "}" << endl;
}


///insere no início da lista
bool insereInicioL(Lista *lista, DadoNoLista valor)
{

    No *novo = new No();
    if (!novo)
        return false;

    novo->dado = valor;
    novo->ant = nullptr; //Se o novo nó será adicionado no início da lista, o ponteiro *ant do primeiro nó sempre é nulo
    novo->prox = lista->inicio;

    if (!lista->fim) //lista vazia?
        lista->fim = novo;
    else
        lista->inicio->ant = novo;


    lista->inicio = novo;
    lista->tamanho++;

    return true;
}

No* buscaL(Lista *lista, int valor)
{
    No *n = lista->inicio;
    while (n)
    {
        if (n->dado.codigo == valor)
            return n;

        n = n->prox;
    }

    return nullptr;
}

bool removerNoL(Lista *lista, No *no)
{
    if(!no || !lista || vaziaL(lista))
        return false;

    if (!no->ant) /// se anterior é igual a NULL, o elemento a ser excluído está no início da lista
    {
        lista->inicio = no->prox;
        if (!lista->inicio) ///lista ficou vazia ?
            lista->fim = nullptr;
        else
            lista->inicio->ant = nullptr;

    }else{ /// elemento está no meio ou no fim

        no->ant->prox = no->prox;
        if (!no->prox)/// se for retirado último da lista
            lista->fim = no->ant;
        else
            no->prox->ant = no->ant;

    }

    /// libera a memória do elemento
    lista->tamanho--;
    delete(no);
    return true;
}

bool removeL(Lista *lista, int valor)
{
    No* no = buscaL(lista, valor);

    if(!no)
        return false;

    removerNoL(lista, no);

    return true;
}

void imprime3Ultimos (Lista *lista)
{
    No *n = lista->fim;

    if (n)
    {
        cout << "\nÚltimo:" << n;

        if (n->ant)
        {
            cout << "\nPenúltimo: " << n->ant;
        }
        if (n->ant->ant)
        {
            cout << "\nAntepenúltmo: " << n->ant->ant;
        }
    }
}

bool insereFinal(Lista *lista, DadoNoLista valor)
{

    No *novo = new No();
    if (!novo)
        return false;

    novo->dado = valor;
    novo->prox = nullptr; //Se o novo nó será adicionado no início da lista, o ponteiro *ant do primeiro nó sempre é nulo
    novo->ant = lista->fim;

    if (!lista->inicio) //lista vazia?
        lista->inicio = novo;
    else
        lista->fim->prox = novo;

    lista->fim = novo;
    lista->tamanho++;

    return true;
}

bool ordenacaoAlfabetica(Lista* lista)
{
    No* n = NULL;
	DadoNoLista aux;
	bool ordenado;

	do
	{
		ordenado = true;
		n = lista->inicio; //resetar inicio da lista para percorrer toda ela (obrigatorio)

		while (n->prox)
		{
			if (n->dado.nome > n->prox->dado.nome)
			{
				aux = n->dado;
				n->dado = n->prox->dado;
				n->prox->dado = aux;
				ordenado = false;
			}
			n = n->prox;
		}
	}while (ordenado == false);
}

bool ordenaPorCodigo(Lista *lista)
{
    No* n = NULL;
	DadoNoLista aux;
	bool ordenado;

	do
	{
		ordenado = true;
		n = lista->inicio; //resetar inicio da lista para percorrer toda ela (obrigatorio)

		while (n->prox)
		{
			if (n->dado.codigo > n->prox->dado.codigo)
			{
				aux = n->dado;
				n->dado = n->prox->dado;
				n->prox->dado = aux;
				ordenado = false;
			}
			n = n->prox;
		}
	}while (ordenado == false);
}

bool removePorCidade(Lista* lista, string cidade)
{
    No* atual = lista->inicio;

    while (atual != nullptr) {
        if (atual->dado.cidade == cidade) {
            if (atual->ant == nullptr) {
                // Remover o primeiro elemento da lista
                lista->inicio = atual->prox;
                if (lista->inicio == nullptr)
                    lista->fim = nullptr;
                delete atual;
                lista->tamanho--;
                atual = lista->inicio;
            } else {
                // Remover elemento no meio ou no fim da lista
                atual->ant->prox = atual->prox;
                if (atual == lista->fim)
                    lista->fim = atual->ant;
                No* aux = atual;
                atual = atual->prox;
                delete aux;
                lista->tamanho--;
            }
        } else {
            atual->ant = atual;
            atual = atual->prox;
        }
    }

    return true;
}

void contagem(Lista *lista)
{
    No *n = lista->inicio;
    int idade, cont = 0, maiores = 0;

    while (n)
    {
        idade = 2023 - n->dado.ano;
        cont++;

        if (idade > 29)
            maiores++;


        n = n->prox;
    }

    cout << "Total de funcionários: " << cont << endl;
    cout << "Total de funcionários com mais de 29 anos: " << maiores;
    getchar();
}

void buscaTipoSangue(Lista *lista, string tipo)
{
    No *n = lista->inicio;
    bool encontrado = false;

    while (n)
    {
        if (n->dado.tiposangue == tipo)
        {
            cout << "Nome: " << n->dado.nome << endl;
            encontrado = true;
        }
        n = n->prox;
    }
     if (!encontrado)
    {
        cout << "Nenhum funcionário encontrado com o tipo sanguíneo " << tipo << endl;
    }

}

#endif // _HPP_LISTA_DUPLA



