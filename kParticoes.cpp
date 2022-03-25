#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vetor = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 }; //Vetor exemplo
vector<int> alocados; //Vetor para identificar em qual subvetor um index esta alocado
int n = vetor.size();
int maiorK = 0;
int somaTotal = 0;
int subvetor;

void printarVetor() { //Escreve na tela o vetor utilizado na execucao
    cout << "{";
    for (int i = 0; i < vetor.size(); i++) {
        cout << " " << vetor[i] << " ";
    }
    cout << "}" << endl << endl;
}

void printarSolucao(int i) { //Escreve na tela as solucoes encontradas para o vetor utilizado
    cout << "Solucao encontrada para K = " << i << ": Valor total de cada subvetor = " << somaTotal / i << endl;

    for (int j = 1; j <= i; j++) {
        cout << "S" << j << "{";
        for (int l = 0; l < n; l++)
        {
            if (alocados[l] == j) {
                cout << " " << vetor[l] << " ";
                continue;
            }
        }

        if (j == i) {
            cout << "}";
            continue;
        }

        cout << "}, " << endl;
    }
    cout << endl << endl;
}

bool podeParticionar(int inicioIteracao, int k, int somaEmProgresso, int somaParticao) { //Metodo para particionar o vetor original de acordo com seus subvetores
    if (somaEmProgresso > somaParticao) { //Se a soma do subvetor ficar maior que a soma maxima da particao, retorna falso para resolver a recursividade
        return false;
    }

    if (somaEmProgresso == somaParticao) { //Se a soma do subvetor ficar iguala soma maxima da particao, passa para o proximo subveetor e continua a recursividade
        subvetor--;
        return podeParticionar(0, k - 1, 0, somaParticao); //Recursividade para o proximo subvetor
    }

    if (subvetor == 0) { //Se nao houver mais subvetores a solucao sera valida
        return true;
    }

    for (int i = inicioIteracao; i < n; i++) {
        if (alocados[i] == 0) { //Se o numero esta disponivel, utiliza-o na proxima verificacao
            alocados[i] = subvetor;

            if (podeParticionar(i + 1, k, somaEmProgresso + vetor[i], somaParticao)) { //Recursividade para preencher o subvetor atual
                return true;
            }
            alocados[i] = 0; //Backtracking para desalocar a combinacao atual
        }
    }

    return false; //Retorna falso para resolver a recursividade
}

bool podeParticionarSubvetores(int k) { //Metodo que verifica a possibilida de buscar uma solucao para a quantidade de subvetores recebidos
    if (somaTotal % k != 0) { //Se o resto da soma total pelo numero de particoes for diferente de 0, nao teremos uma solucao
        return false;
    }

    int somaParticao = somaTotal / k; //Identifica a soma maxima de cada subvetor
    alocados = vector<int>(n, 0); //Zerar o vetor que salva a posicao de cada numero do vetor em seu subvetor
    subvetor = k;

    return podeParticionar(0, k, 0, somaParticao); //Inicio da recursividade
}

bool inputarVetor() { //Recebe o vetor pelo input
    int num = 0;

    cin >> num;

    if (num <= 0) {
        return false;
    }

    do {
        vetor.insert(vetor.end(), 1, num);
        cin >> num;
    } while (num > 0);

    return true;
}

void kParticao() { //Inicio do desafio
    vetor.clear();
    alocados.clear();

    cout << "Problema das K-Particoes" << endl;
    cout << "Informe os numeros do vetor, apenas positivos inteiros maiores que zero, informe 0 para finalizar" << endl;

    if (!inputarVetor()) { //Se o vetor for vazio, finaliza a execucao
        cout << "O vetor nao pode ser vazio, finalizando execucao!" << endl;
        return;
    }

    int maiorValor = *max_element(vetor.begin(), vetor.end()); //Maior valor do vetor para utilizar na validacao do maior K possivel

    for (auto numero : vetor) { //Laco para encontrar o valor total da soma do vetor
        somaTotal += numero; 
    };

    maiorK = somaTotal / maiorValor; //Maior numero de subvetores que eu possivel

    cout << "\n\nVetor: ";
    printarVetor();

    if (maiorK == 1) { //Se K = 1, so existe uma solucao, o proprio vetor
        cout << "Solucao unica: K = 1\nS1";
        printarVetor();

        return;
    }

    for (int i = 2; i <= maiorK; i++) {
        if (podeParticionarSubvetores(i)) { //Chama do metodo para verificar se existe a possibilidade de dividir o vetor original na quantidade de subvetores informados
            printarSolucao(i);
            continue;
        }

        cout << "Nao ha solucao conhecida para K = " << i << endl << endl;
    }
}

int main()
{
    kParticao();
    system("pause");
    return 0;
}