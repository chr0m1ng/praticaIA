#include <iostream>
#include <stdlib.h> 
#include <time.h>

using namespace std;

typedef struct
{
    int x;
    int y;
    int custo;
    string op;
}tVaccumCleaner;

void imprimeCasa(tVaccumCleaner, int **, int, int);
void imprimeCasaBonita(tVaccumCleaner, int **, int, int);
void gotoInicio(tVaccumCleaner *, int **, int, int);
void gotoFim(tVaccumCleaner *, int **, int, int);

int main()
{
    int **casa;
    int linha, coluna;
    tVaccumCleaner VCleaner;
    int qtdComodosSujos;

    cout << "Informe formato da casa(Linha x Coluna): ";
    cin >> linha >> coluna;

    //Alocação da casa
    casa = new int*[linha];
    if(casa == NULL)
    {
        cout << "MEMORY ERROR" << endl;
        exit(-1);
    }
    for(int i = 0; i < linha; i++)
    {
        casa[i] = new int[coluna];
        if(casa[i] == NULL)
        {
            cout << "MEMORY ERROR" << endl;
            exit(-1);
        }
    }
    for(int i = 0; i < linha; i++)
        for(int j = 0; j < coluna; j++)
            casa[i][j] = 0;

    srand(time(NULL));
    qtdComodosSujos = rand() % (linha * coluna) + 1;

    for(int i = 0; i < qtdComodosSujos; i++)
    {
        int x = rand() % linha;
        int y = rand() % coluna;
        if(casa[x][y]) //Caso o comodo já esteja sujo não vai ser contabilizado
            i--;
        casa[x][y] = 1;
    }

    //Leitura da posição do VCleaner e criação
    cout << "Informe posicao inicial do aspirador de po(X e Y): ";
    cin >> VCleaner.x >> VCleaner.y;

    while(VCleaner.x > linha - 1 || VCleaner.x < 0 || VCleaner.y > coluna - 1 || VCleaner.y < 0)
    {
        cout << "Nao eh possivel colocar o aspirador de po fora da casa" << endl;
        cout << "Informe uma nova posicao do aspirador de po(X e Y): ";
        cin >> VCleaner.x >> VCleaner.y;
    }
    VCleaner.custo = 0;
    VCleaner.op = "Ligando";

    imprimeCasaBonita(VCleaner, casa, linha, coluna);

    gotoInicio(&VCleaner, casa, linha, coluna);
    gotoFim(&VCleaner, casa, linha, coluna);

    cout << "------------------------TUDO LIMPO------------------------" << endl;
    cout << "Custo Final: " << VCleaner.custo << endl; 

    for(int i = 0; i < linha; i++)
        delete[] casa[i];
    delete casa;

    return 0;
}

void gotoInicio(tVaccumCleaner *VCleaner, int **casa, int linha, int coluna)
{
    if(VCleaner->x == 0 && VCleaner->y == 0)
    {
        if(casa[0][0])
        {
            VCleaner->op = "Limpando";
            VCleaner->custo++;
            casa[0][0] = 0;
        }
        if(VCleaner->op == "Ligando")
            return;
        imprimeCasaBonita(*VCleaner, casa, linha, coluna);
        return;
    }

    if(casa[VCleaner->x][VCleaner->y])
    {
        VCleaner->op = "Limpando";
        VCleaner->custo++;
        casa[VCleaner->x][VCleaner->y] = 0;
        imprimeCasaBonita(*VCleaner, casa, linha, coluna);
    }

    if(VCleaner->x)
    {
        VCleaner->op = "Andando para Cima";
        VCleaner->custo++;
        VCleaner->x--;
        imprimeCasaBonita(*VCleaner, casa, linha, coluna);
    }
    else
    {
        VCleaner->op = "Andando para Esquerda";
        VCleaner->custo++;
        VCleaner->y--;
        imprimeCasaBonita(*VCleaner, casa, linha, coluna);
    }

    if(VCleaner->x == 0 && VCleaner->y == 0)
    {
        if(casa[0][0])
        {
            VCleaner->op = "Limpando";
            VCleaner->custo++;
            casa[0][0] = 0;
            imprimeCasaBonita(*VCleaner, casa, linha, coluna);
        }
        return;
    }
    gotoInicio(VCleaner, casa, linha, coluna);
}

void gotoFim(tVaccumCleaner *VCleaner, int **casa, int linha, int coluna)
{
    if(VCleaner->x == linha - 1 && VCleaner->y == coluna - 1) //Caso já entrou na funcao no final da matriz
        return;

    for(int i = 0; i < linha; i++)
    {
        if(!VCleaner->y) //Se Aspirador estiver no inicio da linha vai pro fim limpando
        {
            while(VCleaner->y < coluna - 1)
            {
                if(casa[VCleaner->x][VCleaner->y])
                {
                    VCleaner->op = "Limpando";
                    VCleaner->custo++;
                    casa[VCleaner->x][VCleaner->y] = 0;
                    imprimeCasaBonita(*VCleaner, casa, linha, coluna);
                }
                VCleaner->op = "Andando para Direita";
                VCleaner->custo++;
                VCleaner->y++;
                imprimeCasaBonita(*VCleaner, casa, linha, coluna);
            }
        }
        else
        {
            while(VCleaner->y > 0)
            {
                if(casa[VCleaner->x][VCleaner->y])
                {
                    VCleaner->op = "Limpando";
                    VCleaner->custo++;
                    casa[VCleaner->x][VCleaner->y] = 0;
                    imprimeCasaBonita(*VCleaner, casa, linha, coluna);
                }
                VCleaner->op = "Andando para Esquerda";
                VCleaner->custo++;
                VCleaner->y--;
                imprimeCasaBonita(*VCleaner, casa, linha, coluna);
            }
        }
        if(casa[VCleaner->x][VCleaner->y])
        {
            VCleaner->op = "Limpando";
            VCleaner->custo++;
            casa[VCleaner->x][VCleaner->y] = 0;
            imprimeCasaBonita(*VCleaner, casa, linha, coluna);
        }
        if(VCleaner->x + 1 != linha)
        {
            VCleaner->op = "Andando para baixo";
            VCleaner->x++;
            VCleaner->custo++;
            imprimeCasaBonita(*VCleaner, casa, linha, coluna);
        }
    }
    if(linha % 2 == 0) //Caso tenha numero par de linhas falta limpar o inicio da ultima linha
    {
        while(VCleaner->y)
        {
            if(casa[VCleaner->x][VCleaner->y])
            {
                VCleaner->op = "Limpando";
                VCleaner->custo++;
                casa[VCleaner->x][VCleaner->y] = 0;
                imprimeCasaBonita(*VCleaner, casa, linha, coluna);
            }
            VCleaner->op = "Andando para Direita";
            VCleaner->custo++;
            VCleaner->y--;
            imprimeCasaBonita(*VCleaner, casa, linha, coluna);
        }
    }
}

void imprimeCasaBonita(tVaccumCleaner VCleaner, int **casa, int linha, int coluna)
{
    cout << "------------------------Info Aspirador------------------------" << endl;
    cout << "Posicao X: " << VCleaner.x << "\nPosicao Y: " << VCleaner.y << "\nOperacao: " << VCleaner.op << "\nCusto Atual: " << VCleaner.custo;
    cout << endl << endl << "-----------------------------Casa-----------------------------" << endl;
    for(int i = 0; i <= coluna; i++)
        cout << "---";
    if(coluna % 2 == 0)
        cout << "--" << endl;
    else
        cout << "-" << endl;
    for(int i = 0; i < linha; i++)
    {
        for(int w = 0; w < 4; w++)
        {
            cout << "|";
            for(int j = 0; j < coluna; j++)
            {
                if(VCleaner.x == i && VCleaner.y == j && casa[i][j]) //Caso comodo sujo e aspirador dentro
                {
                    if(w == 0)
                        cout << " A |";
                    if(w == 1)
                        cout << " * |";
                    if(w == 2)
                        cout << "***|";
                    if(w == 3)
                        cout << "   |";
                }
                else if(VCleaner.x == i && VCleaner.y == j)
                {
                    if(w == 2)
                        cout << " A |";
                    else
                        cout << "   |";
                }
                else if(casa[i][j])
                {
                    if(w == 0)
                        cout << "   |";
                    if(w == 1)
                        cout << " * |";
                    if(w == 2)
                        cout << "***|";
                    if(w == 3)
                        cout << "   |";
                }
                else
                    cout << "   |";
            }
            cout << endl;
        }
        for(int k = 0; k <= coluna; k++)
            cout << "---";
        if(coluna % 2 == 0)
            cout << "--" << endl;
        else
            cout << "-" << endl;
    }
    cout << endl; 
}

void imprimeCasa(tVaccumCleaner VCleaner, int **casa, int linha, int coluna)
{
    cout << "------------------------Info Aspirador------------------------" << endl;
    cout << "Posicao X: " << VCleaner.x << "\nPosicao Y: " << VCleaner.y << "\nOperacao: " << VCleaner.op << "\nCusto Atual: " << VCleaner.custo;
    cout << endl << "-----------------------------Casa-----------------------------" << endl;
    for(int i = 0; i < linha; i++)
    {
        for(int j = 0; j < coluna; j++)
        {
            if(VCleaner.x == i && VCleaner.y == j)
                cout << casa[i][j] << "A\t";
            else
                cout << casa[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}