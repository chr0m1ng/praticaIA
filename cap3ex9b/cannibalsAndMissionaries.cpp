#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef struct strEstado
{
    int missionarioEsq;
    int missionarioDir;
    int canibalEsq;
    int canibalDir;
    string barco;
    struct strEstado *pai;
    vector<struct strEstado *> filhos;
}tEstado;

typedef struct
{
    deque<tEstado *> solucao;
    vector<tEstado *> filaExecucao;
}tCanibaisEMissionarios;

void resolve(tCanibaisEMissionarios *);
void geraFilho(tEstado *);
bool estadoFinal(tEstado);
bool estadoValido(tEstado);
void imprimeEstado(tEstado);
void imprimeEstadoBonito(tEstado);


void resolve(tCanibaisEMissionarios *canisMiss)
{
    for(int i = 0; i < canisMiss->filaExecucao.size(); i++)
    {
        if(estadoFinal(*(canisMiss->filaExecucao[i])))
        {
            canisMiss->solucao.push_back(canisMiss->filaExecucao[i]);
            while(canisMiss->filaExecucao[i]->pai != NULL)
            {
                canisMiss->solucao.push_front(canisMiss->filaExecucao[i]->pai);
                canisMiss->filaExecucao[i] = canisMiss->filaExecucao[i]->pai;
            }
            break;
        }
        geraFilho(canisMiss->filaExecucao[i]);
        for(int j = 0; j < canisMiss->filaExecucao[i]->filhos.size(); j++)
            canisMiss->filaExecucao.push_back(canisMiss->filaExecucao[i]->filhos[j]);
    }
}

void geraFilho(tEstado *estado)
{
    string novoBarco;
    if(estado->barco == "esq")
        novoBarco = "dir";
    else
        novoBarco = "esq";
    
    int movimentos[5][2];

    movimentos[0][0] = 2;
    movimentos[0][1] = 0;
    movimentos[1][0] = 1;
    movimentos[1][1] = 0;
    movimentos[2][0] = 1;
    movimentos[2][1] = 1;
    movimentos[3][0] = 0;
    movimentos[3][1] = 1;
    movimentos[4][0] = 0;
    movimentos[4][1] = 2;

    for(int i = 0; i < 5; i++)
    {
        int missionarioEsq;
        int missionarioDir;
        int canibalEsq;
        int canibalDir;

        if(estado->barco == "esq")
        {
            missionarioEsq = estado->missionarioEsq - movimentos[i][0];
            missionarioDir = estado->missionarioDir + movimentos[i][0];
            canibalEsq = estado->canibalEsq - movimentos[i][1];
            canibalDir = estado->canibalDir + movimentos[i][1];
        }
        else
        {
            missionarioDir = estado->missionarioDir - movimentos[i][0];
            missionarioEsq = estado->missionarioEsq + movimentos[i][0];
            canibalDir = estado->canibalDir - movimentos[i][1];
            canibalEsq = estado->canibalEsq + movimentos[i][1];
        }

        tEstado *filho = new tEstado;
        filho->missionarioEsq = missionarioEsq;
        filho->missionarioDir = missionarioDir;
        filho->canibalEsq = canibalEsq;
        filho->canibalDir = canibalDir;
        filho->barco = novoBarco;
        filho->pai = estado;

        if(estadoValido(*filho))
            estado->filhos.push_back(filho);
    }
}

bool estadoValido(tEstado estado)
{
    if((estado.missionarioEsq < 0) || (estado.missionarioDir < 0) || (estado.canibalEsq < 0) || (estado.canibalDir < 0))
        return false;
    return ((estado.missionarioEsq == 0 || estado.missionarioEsq >= estado.canibalEsq) && (estado.missionarioDir == 0 || estado.missionarioDir >= estado.canibalDir));    
}

bool estadoFinal(tEstado estado)
{
    return estado.missionarioEsq == 0 && estado.canibalEsq == 0 && estado.missionarioDir == 3 && estado.canibalDir == 3;
}

void imprimeEstado(tEstado* estado)
{
    cout << "Missionarios: " << estado->missionarioEsq << "\t| Missionarios: " << estado->missionarioDir << endl;
    cout << "Canibais: " << estado->canibalEsq << "\t| Canibais: " << estado->canibalDir << endl;
}

void imprimeEstadoBonito(tEstado* estado)
{
    for(int i = 0; i < 8; i++)
    {
        if(i == 0)
            cout << endl;
        if(i == 1)
        {
            if(estado->barco == "esq")
            {
                for(int j = 0; j < 19; j++)
                    cout << " ";
                cout << "*|" << endl;
            }
            else
            {
                for(int j = 0; j < 34; j++)
                    cout << " ";
                cout << "|*" << endl;
            }
        }
        if(i == 2)
        {
            if(estado->barco == "esq")
            {
                for(int j = 0; j < 18; j++)
                    cout << " ";
                cout << "**|" << endl;
            }
            else
            {
                for(int j = 0; j < 34; j++)
                    cout << " ";
                cout << "|**" << endl;
            }
        }
        if(i == 3)
        {
            cout << "Missionarios: " << estado->missionarioEsq << "\t";
            if(estado->barco == "esq")
            {
                for(int j = 0; j < 1; j++)
                    cout << " ";
                cout << "***|";
                for(int j = 0; j < 23; j++)
                    cout << " ";
            }
            else
            {
                for(int j = 0; j < 18; j++)
                    cout << " ";
                cout << "|***";
                for(int j = 0; j < 5; j++)
                    cout << " ";
            }
            cout << "Missionarios: " << estado->missionarioDir << endl;
        }
        if(i == 4)
        {
            cout << "Canibais: " << estado->canibalEsq;
            if(estado->barco == "esq")
            {
                int pulos = 9;
                pulos = estado->missionarioDir + estado->missionarioEsq + estado->canibalDir + estado->canibalEsq - 6 + pulos;
                for(int j = 0; j < pulos; j++)
                    cout << " ";
                for(int j = 0; j < 3 - (estado->missionarioDir + estado->missionarioEsq); j++)
                    cout << "M";
                for(int j = 0; j < 3 - (estado->canibalDir + estado->canibalEsq); j++)
                    cout << "C";
                cout << "|";
                pulos = 23;
                for(int j = 0; j < pulos; j++)
                    cout << " ";
            }
            else
            {
                int pulos = 23;
                for(int j = 0; j < pulos; j++)
                    cout << " ";
                cout << "|";
                pulos = 8;
                pulos = estado->missionarioDir + estado->missionarioEsq + estado->canibalDir + estado->canibalEsq - 6 + pulos;
                for(int j = 0; j < 3 - (estado->missionarioDir + estado->missionarioEsq); j++)
                    cout << "M";
                for(int j = 0; j < 3 - (estado->canibalDir + estado->canibalEsq); j++)
                    cout << "C";
                for(int j = 0; j < pulos; j++)
                    cout << " ";
            }
            cout << "Canibais: " << estado->canibalDir << endl;
        }
        if(i == 5)
        {
            if(estado->barco == "esq")
            {
                for(int j = 0; j < 15; j++)
                    cout << " ";
                cout << "***********" << endl;
            }
            else
            {
                for(int j = 0; j < 29; j++)
                    cout << " ";
                cout << "***********" << endl;
            }
        }
        if(i == 6)
        {
            if(estado->barco == "esq")
            {
                for(int j = 0; j < 16; j++)
                    cout << "-";
            }
            else
            {
                for(int j = 0; j < 30; j++)
                    cout << "-";
            }
            cout << "*********";
            if(estado->barco == "esq")
                for(int j = 0; j < 14; j++)
                    cout << "-";
            for(int j = 0; j < 20; j++)
                cout << "-";
            cout << endl;
        }
        if(i == 7)
        {
            for(int j = 0; j < 59; j++)
                cout << "-";
            cout << endl;
        }
    }
}

int main()
{
    tCanibaisEMissionarios canisMiss;
    tEstado raiz;
    raiz.missionarioEsq = 3;
    raiz.missionarioDir = 0;
    raiz.canibalEsq = 3;
    raiz.canibalDir = 0;
    raiz.barco = "esq";
    raiz.pai = NULL;

    canisMiss.filaExecucao.push_back(&raiz);
    resolve(&canisMiss);
    cout << endl;
    imprimeEstadoBonito(canisMiss.solucao[0]);
    for(int i = 0; i < canisMiss.solucao.size(); i++)
    {
        if(i + 1 < canisMiss.solucao.size())
        {
            tEstado *temp = new tEstado;
            temp->barco = canisMiss.solucao[i]->barco;
            if(temp->barco == "esq")
            {
                temp->missionarioEsq = canisMiss.solucao[i + 1]->missionarioEsq;
                temp->missionarioDir = canisMiss.solucao[i]->missionarioDir;
                temp->canibalEsq = canisMiss.solucao[i + 1]->canibalEsq;
                temp->canibalDir = canisMiss.solucao[i]->canibalDir;
            }
            else
            {
                temp->missionarioEsq = canisMiss.solucao[i]->missionarioEsq;
                temp->missionarioDir = canisMiss.solucao[i + 1]->missionarioDir;
                temp->canibalEsq = canisMiss.solucao[i]->canibalEsq;
                temp->canibalDir = canisMiss.solucao[i + 1]->canibalDir;
            }
            temp->pai = NULL;
            imprimeEstadoBonito(temp);
        }
        cout << endl;
    }
    imprimeEstadoBonito(canisMiss.solucao[canisMiss.solucao.size() - 1]);

    return 0;
}