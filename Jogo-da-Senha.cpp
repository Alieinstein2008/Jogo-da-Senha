#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distrib(1, 6);

void f_ApresentaInterface(int parametro, int qtdTurnos, int senhaGerada, int qtdAlgarismos){
    switch (parametro)
    {
    case 1:
        cout << "-------------------------------- \n| BOAS-VINDAS AO JOGO DA SENHA |\n-------------------------------- "<<endl;
        cout << "Quantidade de Turnos: " << qtdTurnos << endl;
        cout << "Quantidade de Algarimos: " << qtdAlgarismos << "\n"<< endl;
        break;
    case 2:
        cout << "Parabéns Jogador, você venceu!" <<endl;
        cout << "Senha Gerada: " << senhaGerada <<"\n"<< endl;
        break;
    case 3:
        cout << "Que pena Jogador, você perdeu!"<<endl;
        cout << "A senha secreta era: " << senhaGerada <<"\n"<< endl;
        break;
    default:
        cout << "-------------------------------- \n| BOAS-VINDAS AO JOGO DA SENHA |\n-------------------------------- "<<endl;
        break;
    }
}

int f_BuscaRequisitos(int parametro){
    int requisitoBuscado;
    f_ApresentaInterface(5,0,0,0); /*Imprime a interface default, passando um parametro fora do case*/
    switch(parametro){
        case 1:
            cout << "Seleção de dificuldade:\n1 - Fácil(10 turnos)\n2 - Médio(6 turnos) \n3 - Difícil(3 turnos) \nNumero da opção selecionada: ";
            cin >> requisitoBuscado;
            switch(requisitoBuscado){
                case 1:
                    requisitoBuscado = 10;
                    break;
                case 2:
                    requisitoBuscado = 6;
                    break;
                case 3: 
                    requisitoBuscado = 3;
                    break;
                default:
                    requisitoBuscado = 10;
                    break;
            }
            break;
        case 2:
            cout << "Comprimento do segredo:\n1 - Fácil(2 Algarismos) \n2 - Médio(4 Algarismos) \n3 - Difícil(6 Algarismos) \nNumero da opção selecionada: ";
            cin >> requisitoBuscado;
            switch(requisitoBuscado){
                case 1:
                    requisitoBuscado = 2;
                    break;
                case 2:
                    requisitoBuscado = 4;
                    break;
                case 3: 
                    requisitoBuscado = 6;
                    break;
                default:
                    requisitoBuscado = 4;
                    break;
            };
            break;
    }
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    return requisitoBuscado;
}

int f_Recursiva(int varRec, int qtdAlgarismos){
    int ordemDecimal = pow(10, qtdAlgarismos) / 10; 
    if (varRec / ordemDecimal >= 1){
        return varRec;
    }else{
        int novoAlgarismo = distrib(gen);
        varRec = varRec * ordemDecimal + f_Recursiva(novoAlgarismo, qtdAlgarismos - 1);
        return varRec;
    };
}

int f_GeraSenha(int qtdAlgarismos){
    int primeiroAlgarismo = distrib(gen);
    return f_Recursiva(primeiroAlgarismo, qtdAlgarismos); 
    /*Observação, o número máximo de Algarismos é 9*/
}

bool f_ValidaPalpite(int palpite, int qtdAlgarismos){        
    int qtdAlgarismosInvalidos=0;
    int ordemDecimal = pow(10, qtdAlgarismos) / 10;
    bool comprimentoValido = palpite/ordemDecimal >= 1 && palpite/ordemDecimal < 10 ? true : false;
    if(comprimentoValido){
        for(int cont = 1; cont <= qtdAlgarismos; cont++){
            int algarismoCorrente = palpite/ordemDecimal;
            qtdAlgarismosInvalidos += algarismoCorrente < 1 || algarismoCorrente > 6 ? 1 : 0;
            palpite = palpite % ordemDecimal; 
            ordemDecimal /= 10;
        };
    }
    bool validade = qtdAlgarismosInvalidos == 0 && comprimentoValido == true ? true:false;
    return  validade;
}

bool f_AvaliaPalpite(int palpite, int senhaGerada, int qtdAlgarismos){
    int ordemDecimalDePosicao = pow(10, qtdAlgarismos) / 10;
    int senhaDinamicaDePosicao = senhaGerada, qtdAlgarismosCorretos = 0;

    for (int cont = 1; cont <= qtdAlgarismos; cont++)
    {
        int axP_Palpite = palpite/ordemDecimalDePosicao; 
        int axP_Senha = senhaDinamicaDePosicao/ordemDecimalDePosicao;
        
        if(axP_Palpite == axP_Senha){
            cout << "o";
            qtdAlgarismosCorretos++;
        }else if(axP_Palpite != axP_Senha){
            int qtdOcorrencia = 0;
            int senhaDinamicaDeComparacao = senhaGerada;
            for (int ordemDecimalDinamica = pow(10, qtdAlgarismos) / 10; ordemDecimalDinamica >= 1; ordemDecimalDinamica/=10)
            {   
                int axN_Senha = senhaDinamicaDeComparacao/ordemDecimalDinamica;
                if(axP_Palpite == axN_Senha && qtdOcorrencia == 0){
                    cout << "x";
                    qtdOcorrencia++;
                }else{
                    if(qtdOcorrencia == 0 && ordemDecimalDinamica==1){cout << "_";}
                };
                senhaDinamicaDeComparacao = senhaDinamicaDeComparacao % ordemDecimalDinamica;
            }
        }
        palpite = palpite % ordemDecimalDePosicao;
        senhaDinamicaDePosicao = senhaDinamicaDePosicao % ordemDecimalDePosicao;
        ordemDecimalDePosicao/=10;
    }
    cout<<"\n"<<endl;
    bool palpiteCorreto = qtdAlgarismosCorretos == qtdAlgarismos ? true : false;
    return palpiteCorreto; 

}

int main()
{
    int qtdAlgarismos = f_BuscaRequisitos(2), qtdTurnos = f_BuscaRequisitos(1);
    int senha = f_GeraSenha(qtdAlgarismos);
    int turno = 1, palpite;                                   
    bool vitoria=false, derrota=false;
    f_ApresentaInterface(1,qtdTurnos,senha,qtdAlgarismos);    
    
    cout<<"Turno:" << turno << endl;
    cin >> palpite;
    while(vitoria == false && derrota == false){
        bool palpiteValido = f_ValidaPalpite(palpite,qtdAlgarismos);
        if(palpiteValido){
            bool palpiteCorreto = f_AvaliaPalpite(palpite,senha,qtdAlgarismos);
            if(palpiteCorreto && turno <= qtdTurnos){
                f_ApresentaInterface(2,qtdTurnos,senha,qtdAlgarismos);
                vitoria = true;
            }else if(palpiteCorreto == false && turno < qtdTurnos){
                turno++;
                cout<<"Turno:" << turno << endl;
                cin >> palpite;
            }else if(turno == qtdTurnos){
                derrota = true;
            }
        }else if(turno < qtdTurnos){
            turno++;
            cout<<"\nTurno:" << turno << "\nInsira um palpite válido:\n";
            cin >> palpite;
        }
        else if(turno == qtdTurnos){
                derrota = true;
        }
    }
    if(derrota){
        f_ApresentaInterface(3,qtdTurnos,senha,qtdAlgarismos);
    }
    return 0;
}