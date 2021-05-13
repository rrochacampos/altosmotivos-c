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
1. Objetivo da função: converter o texto para minúsculo, para ordernar corretamente,
já que as letras minúsculas e maiúsculas se diferenciam na tabela ASCII.
2. Resumo de seu funcionamento: em um for, é convertido cada caractere do texto recebido para minúsculo.
3. Descrição dos parâmetros de entrada: é recebido o texto que o usuário inseriu.
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado o mesmo texto que o usuário inseriu,
porém com todas as letras minúsculas.
5. Observações:
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
1. Objetivo da função: preencher todos os campos de uma variável do tipo Peca.
2. Resumo de seu funcionamento: é utilizado uma string de apoio para converter o texto
para minúsculo quando invocada a função, de resto basta preencher os campos.
3. Descrição dos parâmetros de entrada:
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado uma variável do tipo Peca.
5. Observações:
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
1. Objetivo da função: verificar se existe alguma peça com o mesmo código.
2. Resumo de seu funcionamento: em um for, é comparado o código de cada peca existente com
o código da peca inserida. Caso encontre, é retornado 1. Caso contrário, é retornado 0.
3. Descrição dos parâmetros de entrada: é recebida a peça inserida, as peças existentes e o número de peças.
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado um valor booleano.
5. Observações:
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
1. Objetivo da função: inserir uma nova peça.
2. Resumo de seu funcionamento: primeiro é verificado se o número máximo de peças foi atingido. Caso não tenho sido,
uma variável do tipo "Peca" recebe os dados inseridos na função "digitaPeca". Após isso é verificado se o código já existe,
invocando a função "existePeca". Caso exista, o procedimento é repetido até que o usuário insira um código diferente. Caso
seja um código novo, a peça é inserida.
3. Descrição dos parâmetros de entrada: é recebido as peças existentes e a quantidade de peças, apontando o endereço na memória,
já que o valor será alterado.
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado um valor booleano.
5. Observações:
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
1. Objetivo da função: preencher todos os campos de uma variável do tipo Fornecedor.
2. Resumo de seu funcionamento: é utilizado uma string de apoio para converter o texto
para minúsculo quando invocada a função, de resto basta preencher os campos.
3. Descrição dos parâmetros de entrada:
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado uma variável do tipo Fornecedor.
5. Observações:
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
1. Objetivo da função: verificar se existe algum fornecedor com o mesmo CNPJ.
2. Resumo de seu funcionamento: em um for, é comparado o CNPJ de cada fornecedor existente com
o CNPJ do fornecedor inserido. Caso encontre, é retornado 1. Caso contrário, é retornado 0.
3. Descrição dos parâmetros de entrada: é recebida o fornecedor inserido, os fornecedores existentes e o número de fornecedores.
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado um valor booleano.
5. Observações:
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
1. Objetivo da função: inserir um novo fornecedor.
2. Resumo de seu funcionamento: primeiro é verificado se o número máximo de fornecedores foi atingido. Caso não tenho sido,
uma variável do tipo "Fornecedor" recebe os dados inseridos na função "digitaFornecedor". Após isso é verificado se o CNPJ já existe,
invocando a função "existeFornecedor". Caso exista, o procedimento é repetido até que o usuário insira um CNPJ diferente. Caso
seja um CNPJ novo, o fornecedor é inserido.
3. Descrição dos parâmetros de entrada: é recebido os fornecedores existentes e a quantidade de fornecedores, apontando o endereço na memória,
já que o valor será alterado.
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado um valor booleano.
5. Observações:
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
1. Objetivo da função: imprimir as peças por ordem alfabética de descrição da peça.
2. Resumo de seu funcionamento: é utilizada uma variável aux e um array do tipo Peca que recebe as peças existente, para não mexer na ordem orginal das peças.
Depois é feita uma comparação: caso a descrição da peca de indice "i" seja maior que a da peça de indice "i2" (o que significa que vem depois),
a variável aux recebe a peça de indice "i", a peca de indice "i" recebe a peca de indice "i2" e a peca de indice "i2" recebe aux. Ou seja, é feita uma troca
de posição entre a peca de indice "i" pela peça de "i2". Após isso, todos os campos da variável "umaPeca" são impressos.
3. Descrição dos parâmetros de entrada: é recebida as peça existentes e a quantidade de peças.
4. Descrição dos parâmetros de saída e/ou valores retornados:
5. Observações:
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
1. Objetivo da função: imprimir os fornecedores ordenados por tipo de peça que fornecem.
2. Resumo de seu funcionamento: é utilizada uma variável aux e um array do tipo Fornecedor que recebe os fornecedores existente, para não mexer na ordem orginal
dos fornecedores. Depois é feita uma comparação: caso o tipo do fornecedor de indice "i" seja maior que o do fornecedor de indice "i2" (o que significa que vem depois),
a variável aux recebe o fornecedor de indice "i", o fornecedor de indice "i" recebe o fornecedor de indice "i2" e o fornecedor de indice "i2" recebe aux. Ou seja, é feita uma troca
de posição entre o fornecedor de indice "i" pelo fornecedor de "i2". Após isso, todos os campos da variável "umFornecedor" são impressos.
3. Descrição dos parâmetros de entrada: é recebida os fornecedores existentes e a quantidade de fornecedores.
4. Descrição dos parâmetros de saída e/ou valores retornados:
5. Observações:
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
1. Objetivo da função: imprimir o menu de opções.
2. Resumo de seu funcionamento: função simples, que apenas imprime o menu de opções.
3. Descrição dos parâmetros de entrada:
4. Descrição dos parâmetros de saída e/ou valores retornados:
5. Observações:
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
1. Objetivo da função: digitar uma opção.
2. Resumo de seu funcionamento: função para receber o caractere que o usuário digitar.
Caso seja minúsculo, ele é convertido para maiúsculo.
3. Descrição dos parâmetros de entrada:
4. Descrição dos parâmetros de saída e/ou valores retornados: é retornado o caractere digitado.
5. Observações:
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
1. Objetivo da função: adicionar uma entrega.
2. Resumo de seu funcionamento: é adicionada uma nova entrega contendo os dados do fornecedor e da peça.
3. Descrição dos parâmetros de entrada: entregas existentes, fornecedores existentes, indice do fornecedor com o menor preço,
número de entregas apontando o endereço, peças existentes, indice da peça indicada e o menor valor.
4. Descrição dos parâmetros de saída e/ou valores retornados:
5. Observações: quando esta funçao é invocada, o programa para e eu não consegui descobrir o problema. Se for não invocada, o programa
roda normalmente, mas não é adicionada nenhuma entrega.
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
1. Objetivo da função: repor o estoque da peça.
2. Resumo de seu funcionamento: primeiro é somado quantos fornecedores do tipo da peça são encontrados. Caso seja maior que 0,
o usuário irá digitar o preço mínimo de cada fornecedor do tipo requisitado. Em seguida é feita a comparação para ver qual fornecedor
possui o menor preço. É invocada a função "adicionarEntrega" e os dados atuais da peça são impressos.
3. Descrição dos parâmetros de entrada: peças existentes, fornecedores existentes, número de fornecedores, entregas existentes,
número de entregas com o endereço, índice da peça.
4. Descrição dos parâmetros de saída e/ou valores retornados:
5. Observações:
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

        //adicionarEntrega(entregas, fornecedores, indiceFornecedor, *quantasEntregas, pecas, i, valor); //função precisa ser invocada para adicionar nas entregas

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
1. Objetivo da função: imprimir peça com estoque abaixo do permitido.
2. Resumo de seu funcionamento: é verificado se a peça o índice "i" está com o estoque abaixo do permitido. Caso esteja, as informações
da peça são impressas, em seguida é invocada a função "reporEstoque".
3. Descrição dos parâmetros de entrada: peças existentes, número de peças, fornecedores existentes, número de fornecedores, entregas existentes,
número de entregas com o endereço.
4. Descrição dos parâmetros de saída e/ou valores retornados: retorna um valor booleano.
5. Observações:
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
1. Objetivo da função: retirar uma quantia do estoque de uma peça.
2. Resumo de seu funcionamento: o usuário digita um código de peça. Caso exista a peça, o usuário digita umaquantia para retirar
da peça indicada. Caso a quantia seja maior que a quantia em estoque, é exibida uma mensagem. Caso não seja, é feita a retirada e exibida
uma mensagem. Depois é verificado se o estoque atual está abaixo do permitido: caso esteja, é exibida uma mensagem.
3. Descrição dos parâmetros de entrada: peças existentes e número de peças.
4. Descrição dos parâmetros de saída e/ou valores retornados: retorna um valor booleano.
5. Observações:
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
1. Objetivo da função: imprimir entregas.
2. Resumo de seu funcionamento: caso o número de peças seja maior que 0, as informações de cada peça são impressas.
Caso contrário, é exibida uma mensagem que não há entregas.
3. Descrição dos parâmetros de entrada: entregas existentes e número de entregas.
4. Descrição dos parâmetros de saída e/ou valores retornados:
5. Observações:
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
