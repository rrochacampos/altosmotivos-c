#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define MAXPEC 4000
#define MAXFOR 200
#define MAXENT 200

struct peca
{
    int codigo, quantidadeEmEstoque, quantidadeMinima;
    char descricao[30], tipo[30];
};

struct fornecedor
{
    char cnpj[20], razaoSocial[40], endereco[50], telefone[12], tipo[30];
    float preco;
};

struct entrega
{
    char cnpj[20];
    int codigo;
    float preco;
    int quantidade;
};

typedef struct peca Peca;
typedef struct fornecedor Fornecedor;
typedef struct entrega Entrega;

/*
1. Objetivo da fun��o: converter o texto para min�sculo, para ordernar corretamente,
j� que as letras min�sculas e mai�sculas se diferenciam na tabela ASCII.
2. Resumo de seu funcionamento: em um for, � convertido cada caractere do texto recebido para min�sculo.
3. Descri��o dos par�metros de entrada: � recebido o texto que o usu�rio inseriu.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado o mesmo texto que o usu�rio inseriu,
por�m com todas as letras min�sculas.
5. Observa��es:
*/
char converterParaMinusculo(char texto[])
{
    int tamanho, i;
    tamanho = strlen(texto);
    for (i=0;i<tamanho; i++)
    {
        texto[i] = tolower(texto[i]);
    }
    return(texto);
}

/*
1. Objetivo da fun��o: preencher todos os campos de uma vari�vel do tipo Peca.
2. Resumo de seu funcionamento: � utilizado uma string de apoio para converter o texto
para min�sculo quando invocada a fun��o, de resto basta preencher os campos.
3. Descri��o dos par�metros de entrada:
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado uma vari�vel do tipo Peca.
5. Observa��es:
*/
Peca digitaPeca()
{
    char texto[30];
    Peca nova;
    fflush(stdin);
    printf("\nDigite o codigo da peca: ");
    scanf("%i", &nova.codigo);
    fflush(stdin);
    printf("\nDigite a descricao da peca: ");
    gets(texto);
    converterParaMinusculo(texto);
    strcpy(nova.descricao, texto);
    fflush(stdin);
    printf("\nDigite o tipo da peca: ");
    gets(texto);
    converterParaMinusculo(texto);
    strcpy(nova.tipo, texto);
    fflush(stdin);
    printf("\nDigite a quantidade em estoque da peca: ");
    scanf("%i", &nova.quantidadeEmEstoque);
    fflush(stdin);
    printf("\nDigite o estoque minimo da peca: ");
    scanf("%i", &nova.quantidadeMinima);
    return(nova);
}

/*
1. Objetivo da fun��o: verificar se existe alguma pe�a com o mesmo c�digo.
2. Resumo de seu funcionamento: em um for, � comparado o c�digo de cada peca existente com
o c�digo da peca inserida. Caso encontre, � retornado 1. Caso contr�rio, � retornado 0.
3. Descri��o dos par�metros de entrada: � recebida a pe�a inserida, as pe�as existentes e o n�mero de pe�as.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado um valor booleano.
5. Observa��es:
*/
int existePeca(Peca umaPeca, Peca pecas[], int quantasPecas)
{
    int i, achou = 0;

    for(i = 0; i < quantasPecas && !achou; i++)
    {
        if(umaPeca.codigo == pecas[i].codigo)
        {
            achou = 1;
        }
    }
    return(achou);
}

/*
1. Objetivo da fun��o: inserir uma nova pe�a.
2. Resumo de seu funcionamento: primeiro � verificado se o n�mero m�ximo de pe�as foi atingido. Caso n�o tenho sido,
uma vari�vel do tipo "Peca" recebe os dados inseridos na fun��o "digitaPeca". Ap�s isso � verificado se o c�digo j� existe,
invocando a fun��o "existePeca". Caso exista, o procedimento � repetido at� que o usu�rio insira um c�digo diferente. Caso
seja um c�digo novo, a pe�a � inserida.
3. Descri��o dos par�metros de entrada: � recebido as pe�as existentes e a quantidade de pe�as, apontando o endere�o na mem�ria,
j� que o valor ser� alterado.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado um valor booleano.
5. Observa��es:
*/
int inserirNovaPeca(Peca pecas[], int *quantasPecas)
{
    Peca novaPeca;
    int oQueRetorna = 1;
    if(*quantasPecas == MAXPEC)
    {
        oQueRetorna = 0;
    }
    else
    {
        do
        {
            novaPeca = digitaPeca();
            if(existePeca(novaPeca, pecas, *quantasPecas))
            {
                puts("\nERRO. O codigo da peca ja esta cadastrado.");
            }
        }
        while(existePeca(novaPeca, pecas, *quantasPecas));
        pecas[(*quantasPecas)++] = novaPeca;
    }
    return(oQueRetorna);
}

/*
1. Objetivo da fun��o: preencher todos os campos de uma vari�vel do tipo Fornecedor.
2. Resumo de seu funcionamento: � utilizado uma string de apoio para converter o texto
para min�sculo quando invocada a fun��o, de resto basta preencher os campos.
3. Descri��o dos par�metros de entrada:
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado uma vari�vel do tipo Fornecedor.
5. Observa��es:
*/
Fornecedor digitaFornecedor()
{
    char texto[30];
    Fornecedor novo;
    fflush(stdin);
    printf("\nDigite o CNPJ do fornecedor: ");
    gets(novo.cnpj);
    fflush(stdin);
    printf("\nDigite a razao social: ");
    gets(novo.razaoSocial);
    fflush(stdin);
    printf("\nDigite o endereco: ");
    gets(novo.endereco);
    fflush(stdin);
    printf("\nDigite o telefone: ");
    gets(novo.telefone);
    fflush(stdin);
    printf("\nDigite o tipo de peca oferecida pelo fornecedor: ");
    gets(texto);
    converterParaMinusculo(texto);
    strcpy(novo.tipo, texto);
    return(novo);
}

/*
1. Objetivo da fun��o: verificar se existe algum fornecedor com o mesmo CNPJ.
2. Resumo de seu funcionamento: em um for, � comparado o CNPJ de cada fornecedor existente com
o CNPJ do fornecedor inserido. Caso encontre, � retornado 1. Caso contr�rio, � retornado 0.
3. Descri��o dos par�metros de entrada: � recebida o fornecedor inserido, os fornecedores existentes e o n�mero de fornecedores.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado um valor booleano.
5. Observa��es:
*/
int existeFornecedor(Fornecedor umFornecedor, Fornecedor fornecedores[], int quantosFornecedores)
{
    int i, achou = 0;
    for(i = 0; i < quantosFornecedores && !achou; i++)
    {
        if(strcmp(umFornecedor.cnpj, fornecedores[i].cnpj) == 0)
        {
            achou = 1;
        }
    }
    return(achou);
}

/*
1. Objetivo da fun��o: inserir um novo fornecedor.
2. Resumo de seu funcionamento: primeiro � verificado se o n�mero m�ximo de fornecedores foi atingido. Caso n�o tenho sido,
uma vari�vel do tipo "Fornecedor" recebe os dados inseridos na fun��o "digitaFornecedor". Ap�s isso � verificado se o CNPJ j� existe,
invocando a fun��o "existeFornecedor". Caso exista, o procedimento � repetido at� que o usu�rio insira um CNPJ diferente. Caso
seja um CNPJ novo, o fornecedor � inserido.
3. Descri��o dos par�metros de entrada: � recebido os fornecedores existentes e a quantidade de fornecedores, apontando o endere�o na mem�ria,
j� que o valor ser� alterado.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado um valor booleano.
5. Observa��es:
*/
int inserirNovoFornecedor(Fornecedor fornecedores[], int *quantosFornecedores)
{
    Fornecedor novoFornecedor;
    int oQueRetorna = 1;
    if(*quantosFornecedores == MAXFOR)
    {
        oQueRetorna = 0;
    }
    else
    {
        do
        {
            novoFornecedor = digitaFornecedor();
            if(existeFornecedor(novoFornecedor, fornecedores, *quantosFornecedores))
            {
                puts("\nERRO. O CNPJ inserido jah estah cadastrado.");
            }
        }
        while(existeFornecedor(novoFornecedor, fornecedores, *quantosFornecedores));
        fornecedores[(*quantosFornecedores)++] = novoFornecedor;
    }
    return(oQueRetorna);
}

/*
1. Objetivo da fun��o: imprimir as pe�as por ordem alfab�tica de descri��o da pe�a.
2. Resumo de seu funcionamento: � utilizada uma vari�vel aux e um array do tipo Peca que recebe as pe�as existente, para n�o mexer na ordem orginal das pe�as.
Depois � feita uma compara��o: caso a descri��o da peca de indice "i" seja maior que a da pe�a de indice "i2" (o que significa que vem depois),
a vari�vel aux recebe a pe�a de indice "i", a peca de indice "i" recebe a peca de indice "i2" e a peca de indice "i2" recebe aux. Ou seja, � feita uma troca
de posi��o entre a peca de indice "i" pela pe�a de "i2". Ap�s isso, todos os campos da vari�vel "umaPeca" s�o impressos.
3. Descri��o dos par�metros de entrada: � recebida as pe�a existentes e a quantidade de pe�as.
4. Descri��o dos par�metros de sa�da e/ou valores retornados:
5. Observa��es:
*/
void pecasOrdemAlfabetica(Peca pecas[], int quantasPecas)
{
    Peca umaPeca[quantasPecas], aux;
    int i, i2;

    for (i=0; i<quantasPecas; i++)
    {
        umaPeca[i] = pecas[i];
    }
    for (i=0; i<quantasPecas; i++)
    {
        for (i2 = i; i2<quantasPecas; i2++)
        {
            if (strcmp(umaPeca[i].descricao, umaPeca[i2].descricao) > 0)
            {
                aux = umaPeca[i];
                umaPeca[i] = umaPeca[i2];
                umaPeca[i2] = aux;
            }
        }
    }
    for (i=0; i<quantasPecas; i++)
    {
        printf("\nDescricao: %s", umaPeca[i].descricao);
        printf("\nCodigo da peca: %i", umaPeca[i].codigo);
        printf("\nTipo: %s", umaPeca[i].tipo);
        printf("\nQuantidade em estoque: %i", umaPeca[i].quantidadeEmEstoque);
        printf("\nQuantidade minima: %i\n", umaPeca[i].quantidadeMinima);
    }
}

/*
1. Objetivo da fun��o: imprimir os fornecedores ordenados por tipo de pe�a que fornecem.
2. Resumo de seu funcionamento: � utilizada uma vari�vel aux e um array do tipo Fornecedor que recebe os fornecedores existente, para n�o mexer na ordem orginal
dos fornecedores. Depois � feita uma compara��o: caso o tipo do fornecedor de indice "i" seja maior que o do fornecedor de indice "i2" (o que significa que vem depois),
a vari�vel aux recebe o fornecedor de indice "i", o fornecedor de indice "i" recebe o fornecedor de indice "i2" e o fornecedor de indice "i2" recebe aux. Ou seja, � feita uma troca
de posi��o entre o fornecedor de indice "i" pelo fornecedor de "i2". Ap�s isso, todos os campos da vari�vel "umFornecedor" s�o impressos.
3. Descri��o dos par�metros de entrada: � recebida os fornecedores existentes e a quantidade de fornecedores.
4. Descri��o dos par�metros de sa�da e/ou valores retornados:
5. Observa��es:
*/
void fornecedoresTipoPeca(Fornecedor fornecedores[], int quantosFornecedores)
{
    Fornecedor umFornecedor[quantosFornecedores], aux;
    int i, i2;

    for (i=0; i<quantosFornecedores; i++)
    {
        umFornecedor[i] = fornecedores[i];
    }
    for (i=0; i<quantosFornecedores; i++)
    {
        for (i2 = i; i2<quantosFornecedores; i2++)
        {
            if (strcmp(umFornecedor[i].tipo, umFornecedor[i2].tipo) > 0)
            {
                aux = umFornecedor[i];
                umFornecedor[i] = umFornecedor[i2];
                umFornecedor[i2] = aux;
            }
        }
    }
    for (i=0; i<quantosFornecedores; i++)
    {
        printf("\nTipo de peca: %s", umFornecedor[i].tipo);
        printf("\nCNPJ: %s", umFornecedor[i].cnpj);
        printf("\nFornecedor: %s", umFornecedor[i].razaoSocial);
        printf("\nEndereco: %s", umFornecedor[i].endereco);
        printf("\nTelefone: %s\n", umFornecedor[i].telefone);
    }
}

/*
1. Objetivo da fun��o: imprimir o menu de op��es.
2. Resumo de seu funcionamento: fun��o simples, que apenas imprime o menu de op��es.
3. Descri��o dos par�metros de entrada:
4. Descri��o dos par�metros de sa�da e/ou valores retornados:
5. Observa��es:
*/
void exibeMenu()
{
    printf("[AltosMotivos]");
    printf("\nMenu de Opcoes");
    printf("\n1 | Inserir nova peca");
    printf("\n2 | Inserir novo fornecedor");
    printf("\n3 | Retirada de estoque");
    printf("\n4 | Relatorio de pecas por ordem alfabetica da descricao");
    printf("\n5 | Relatorio de fornecedores ordenado por tipo de peca");
    printf("\n6 | Relatorio de pecas com estoque abaixo do permitido");
    printf("\n7 | Relatorio de entrega de pecas");
    printf("\nS | Sair\n");
}

/*
1. Objetivo da fun��o: digitar uma op��o.
2. Resumo de seu funcionamento: fun��o para receber o caractere que o usu�rio digitar.
Caso seja min�sculo, ele � convertido para mai�sculo.
3. Descri��o dos par�metros de entrada:
4. Descri��o dos par�metros de sa�da e/ou valores retornados: � retornado o caractere digitado.
5. Observa��es:
*/
char digitaOpcao()
{
    char opcao;
    fflush(stdin);
    printf("\nDigite sua opcao: ");
    opcao = toupper(getchar());
    return(opcao);
}

/*
1. Objetivo da fun��o: adicionar uma entrega.
2. Resumo de seu funcionamento: � adicionada uma nova entrega contendo os dados do fornecedor e da pe�a.
3. Descri��o dos par�metros de entrada: entregas existentes, fornecedores existentes, indice do fornecedor com o menor pre�o,
n�mero de entregas apontando o endere�o, pe�as existentes, indice da pe�a indicada e o menor valor.
4. Descri��o dos par�metros de sa�da e/ou valores retornados:
5. Observa��es: quando esta fun�ao � invocada, o programa para e eu n�o consegui descobrir o problema. Se for n�o invocada, o programa
roda normalmente, mas n�o � adicionada nenhuma entrega.
*/
void adicionarEntrega(Entrega entregas[], Fornecedor fornecedores[], int indiceFornecedor, int *quantasEntregas, Peca pecas[], int i, float valor)
{
        strcpy(entregas[*quantasEntregas].cnpj, fornecedores[indiceFornecedor].cnpj);
        entregas[*quantasEntregas].codigo = pecas[i].codigo;
        entregas[*quantasEntregas].preco = valor;
        entregas[*quantasEntregas].quantidade = ((pecas[i].quantidadeMinima - pecas[i].quantidadeEmEstoque) + pecas[i].quantidadeMinima);
        (*quantasEntregas)++;
}

/*
1. Objetivo da fun��o: repor o estoque da pe�a.
2. Resumo de seu funcionamento: primeiro � somado quantos fornecedores do tipo da pe�a s�o encontrados. Caso seja maior que 0,
o usu�rio ir� digitar o pre�o m�nimo de cada fornecedor do tipo requisitado. Em seguida � feita a compara��o para ver qual fornecedor
possui o menor pre�o. � invocada a fun��o "adicionarEntrega" e os dados atuais da pe�a s�o impressos.
3. Descri��o dos par�metros de entrada: pe�as existentes, fornecedores existentes, n�mero de fornecedores, entregas existentes,
n�mero de entregas com o endere�o, �ndice da pe�a.
4. Descri��o dos par�metros de sa�da e/ou valores retornados:
5. Observa��es:
*/
void reporEstoque(Peca pecas[], Fornecedor fornecedores[], int quantosFornecedores, Entrega entregas[], int *quantasEntregas, int i)
{
    int indiceFornecedor=0, fornecedoresEncontrados=0, i2;
    float valor = 0, precoVendedor = 0;

    for (i2=0; i2<quantosFornecedores; i2++)
    {
        if (strcmp(pecas[i].tipo, fornecedores[i2].tipo) == 0)
        {
            fornecedoresEncontrados++;
        }
    }

    if (fornecedoresEncontrados > 0)
    {
        printf("\nFornecedores encontrados para o tipo %s: %i\n", pecas[i].tipo, fornecedoresEncontrados);
        for (i2=0; i2<quantosFornecedores; i2++)
        {
            if (strcmp(pecas[i].tipo, fornecedores[i2].tipo) == 0)
            {
                printf("\nDigite o preco minimo do fornecedor %s: ", fornecedores[i2].razaoSocial);
                fflush(stdin);
                scanf("%f", &precoVendedor);
                fornecedores[i2].preco = precoVendedor;
                valor = fornecedores[i2].preco;
                indiceFornecedor = i2;
            }
        }
        for (i2=0; i2<quantosFornecedores; i2++)
        {
            if (strcmp(pecas[i].tipo, fornecedores[i2].tipo) == 0)
            {
                if(fornecedores[i2].preco < valor)
                {
                    valor = fornecedores[i2].preco;
                    indiceFornecedor = i2;
                }
            }
        }

        //adicionarEntrega(entregas, fornecedores, indiceFornecedor, *quantasEntregas, pecas, i, valor); //fun��o precisa ser invocada para adicionar nas entregas

        printf("\nPeca: %s.", pecas[i].descricao);
        printf("\nTipo: %s.", pecas[i].tipo);
        printf("\nFornecedor com o menor preco: %s, R$ %.2f por peca.", fornecedores[indiceFornecedor].razaoSocial, valor);
        printf("\nEstoque minimo: %i.", pecas[i].quantidadeMinima);
        printf("\nEstoque anterior: %i.", pecas[i].quantidadeEmEstoque);
        printf("\nPecas compradas: %i.", (pecas[i].quantidadeMinima - pecas[i].quantidadeEmEstoque) + pecas[i].quantidadeMinima);
        printf("\nValor total da compra: R$ %.2f.", ((pecas[i].quantidadeMinima - pecas[i].quantidadeEmEstoque) + pecas[i].quantidadeMinima) * valor);
        pecas[i].quantidadeEmEstoque = (pecas[i].quantidadeEmEstoque + (pecas[i].quantidadeMinima - pecas[i].quantidadeEmEstoque)) * 2;
        printf("\nEstoque atual: %i.\n", pecas[i].quantidadeEmEstoque);
    }
    else
    {
        puts("\nNenhum fornecedor encontrado para o tipo da peca!");
    }
}

/*
1. Objetivo da fun��o: imprimir pe�a com estoque abaixo do permitido.
2. Resumo de seu funcionamento: � verificado se a pe�a o �ndice "i" est� com o estoque abaixo do permitido. Caso esteja, as informa��es
da pe�a s�o impressas, em seguida � invocada a fun��o "reporEstoque".
3. Descri��o dos par�metros de entrada: pe�as existentes, n�mero de pe�as, fornecedores existentes, n�mero de fornecedores, entregas existentes,
n�mero de entregas com o endere�o.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: retorna um valor booleano.
5. Observa��es:
*/
int pecasEstoqueAbaixo(Peca pecas[], int quantasPecas, Fornecedor fornecedores[], int quantosFornecedores, Entrega entregas[], int *quantasEntregas)
{
    int i, achou = 1;
    for (i=0; i<quantasPecas; i++)
    {
        if (pecas[i].quantidadeEmEstoque < pecas[i].quantidadeMinima)
        {
            printf("\nPeca: %s", pecas[i].descricao);
            printf("\nTipo: %s", pecas[i].tipo);
            printf("\nCodigo: %i", pecas[i].codigo);
            printf("\nQuantidade em estoque: %i", pecas[i].quantidadeEmEstoque);
            printf("\nQuantidade minima: %i\n", pecas[i].quantidadeMinima);
            achou = 0;
            reporEstoque(pecas, fornecedores, quantosFornecedores, entregas, *quantasEntregas, i);
        }
    }
    return(achou);
}

/*
1. Objetivo da fun��o: retirar uma quantia do estoque de uma pe�a.
2. Resumo de seu funcionamento: o usu�rio digita um c�digo de pe�a. Caso exista a pe�a, o usu�rio digita umaquantia para retirar
da pe�a indicada. Caso a quantia seja maior que a quantia em estoque, � exibida uma mensagem. Caso n�o seja, � feita a retirada e exibida
uma mensagem. Depois � verificado se o estoque atual est� abaixo do permitido: caso esteja, � exibida uma mensagem.
3. Descri��o dos par�metros de entrada: pe�as existentes e n�mero de pe�as.
4. Descri��o dos par�metros de sa�da e/ou valores retornados: retorna um valor booleano.
5. Observa��es:
*/
int retirarEstoquePeca(Peca pecas[], int quantasPecas)
{
    int i, codigo, achou=1, quantidade;
    char opcao;
    printf("\nDigite o codigo da peca: ");
    fflush(stdin);
    scanf("%i", &codigo);
    for (i=0; i<quantasPecas; i++)
    {
        if (pecas[i].codigo == codigo)
        {
            printf("\nDigite a quantidade que deseja retirar do estoque: ");
            fflush(stdin);
            scanf("%i", &quantidade);
            achou = 0;
            if (quantidade > pecas[i].quantidadeEmEstoque)
            {
                printf("\nQuantidade desejada maior que a quantidade em estoque!");
            }
            else
            {
                pecas[i].quantidadeEmEstoque -= quantidade;
                printf("\nEstoque alterado com sucesso!");
            }
            if (pecas[i].quantidadeEmEstoque < pecas[i].quantidadeMinima)
            {
                printf("\n\nNumero em estoque menor que o permitido apos a retirada!\nConsulte o relatorio 6 para repor.\n");
            }
        }
    }
    return (achou);
}

/*
1. Objetivo da fun��o: imprimir entregas.
2. Resumo de seu funcionamento: caso o n�mero de pe�as seja maior que 0, as informa��es de cada pe�a s�o impressas.
Caso contr�rio, � exibida uma mensagem que n�o h� entregas.
3. Descri��o dos par�metros de entrada: entregas existentes e n�mero de entregas.
4. Descri��o dos par�metros de sa�da e/ou valores retornados:
5. Observa��es:
*/
void imprimirEntregas(Entrega entregas[], int quantasEntregas)
{
    if (quantasEntregas > 0)
    {
        int i;
        for (i=0; i<quantasEntregas; i++)
        {
            printf("\nCNPJ do fornecedor: %s", entregas[i].cnpj);
            printf("\nCodigo da peca: %i", entregas[i].codigo);
            printf("\nPreco: %f", entregas[i].preco);
            printf("\nQuantidade comprada: %i", entregas[i].quantidade);
        }
    }
    else if (quantasEntregas == 0)
    {
        puts("\nNenhuma entrega cadastrada!");
    }
}

main()
{

    Peca pecas[MAXPEC] = {1, 500, 200, "parabrisa", "vidraria",
                          2, 200, 100, "lampada", "iluminacao",
                          3, 300, 100, "bateria", "eletrica"
                         };
    Fornecedor fornecedores[MAXFOR] = {"1111.1111", "Alto Pecas Ltda", "Rua XV de Novembro, 185, Centro", "19111112222", "eletrica", 0,
                                       "2222.2222", "Rodas Quentes Ltda", "Rua Brasil, 12, Santo Antonio", "19222227777", "vidraria", 0,
                                       "3333.3333", "Silvas Car Ltda", "Av. Pio XII, 157, Centro", "19666663333", "iluminacao", 0,
                                       "4444.4444", "Cinco Rodas Ltda", "Rua 19 de Julho, 97, Nova Aparecida", "19777775555", "vidraria", 0
                                      };

    Entrega entregas[MAXENT];
    char opcao;
    int quantasPecas=3, quantosFornecedores=4, quantasEntregas=0;

    do
    {
        system("cls");
        exibeMenu();
        opcao = digitaOpcao();
        switch(toupper(opcao))
        {
        case '1': //nova peca
        {

            if(inserirNovaPeca(pecas, &quantasPecas))
            {
                puts("\nNova peca inserida com sucesso.");
            }
            else
            {
                puts("\nERRO ao inserir nova peca.");
            }
            break;
        }
        case '2': //novo fornecedor
        {
            if(inserirNovoFornecedor(fornecedores, &quantosFornecedores))
            {
                puts("\nNovo fornecedor inserido com sucesso.");
            }
            else
            {
                puts("\nERRO ao inserir novo fornecedor.");
            }
            break;
            break;
        }
        case '3': //retirada de peca
        {
            if(retirarEstoquePeca(pecas, quantasPecas))
            {
                puts("\nErro! Codigo de peca nao encontrado.");
            }
            break;
        }
        case '4': //relatorio de pecas por ordem alfabetica de descricao da peca
        {
            pecasOrdemAlfabetica(pecas, quantasPecas);
            break;
        }
        case '5': //relatorio de fornecedores ordenado por tipo de peca
        {
            fornecedoresTipoPeca(fornecedores, quantosFornecedores);
            break;
        }
        case '6': //relatorio de pecas com estoque abaixo do permitido
        {
            if(pecasEstoqueAbaixo(pecas, quantasPecas, fornecedores, quantosFornecedores, entregas, &quantasEntregas))
            {
                puts("\nNenhuma peca estah com o estoque abaixo do permitido!");
            }
            break;
        }
        case '7': //Relatorio de entrega de pecas
        {
            imprimirEntregas(entregas, quantasEntregas);
            break;
        }
        case 'S':
        {
            puts("\nSaindo...");
            break;
        }
        default:
        {
            puts("\nOpcao invalida");
            break;
        }
        }
        printf("\n");
        system("pause");
    }
    while(toupper(opcao) != 'S');
}
