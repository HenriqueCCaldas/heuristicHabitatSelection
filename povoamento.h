#include <vector>
#include <iostream>
#include <ios>
#include <fstream>
#include <string>

using namespace std;

class povoamento
{
    vector <int> vizinhanca;                                        //identifica os povoamentos na vizinhança
    vector <int> especies;                                          //identifica as especies no povoamento
    int numero;                                                     //identifica o número real do povoamento e não a posição no vetor

public:
    povoamento();
    povoamento(const int&,const int&);
    void resize_vizinhanca(const int&);
    void resize_especies(const int&);
    int get_nmr_vizinhanca();
    int get_nmr_especies_();
    povoamento& operator =( const povoamento&);
    vector <int>& get_especies(){
        return especies;
    }
    vector <int>& get_vizinhanca(){
        return vizinhanca;
    }
    int& get_numero(){
        return numero;
    }
};

class lista_povoamentos
{
    vector <povoamento> lista;                                       //indica os povoamentos totais na área a estudar
    vector <int> ls;                                                 //sinaliza se o povoamento está na rede

public:
    lista_povoamentos();
    lista_povoamentos(const int& n);
    lista_povoamentos(const vector<povoamento>&);
    void sort_vizinhos();
    void sort_especies();
    void insere_ls_povoamento(const int&);                           //para utilizar no conjunto de solução
    void remove_ls_povoamento(const int&);                           //n é a posição do povoamento a remover na lista!
    povoamento& seliciona_povoamento(int &);
    vector <int>& get_ls(){
        return ls;
    }
    void elimina_povoamento_vazio(){
        for(int i=0;i<lista.size();++i){
            if(lista.at(i).get_nmr_especies_()==0){
                for(int j=i;j<lista.size()-1;++j){
                    lista.at(j)=lista.at(j+1);
                    ls.at(j)=ls.at(j+1);
                }
                lista.pop_back();
                ls.pop_back();
            }
        }
    }
};

class lista_especies{

    vector <int> species;

public:
    lista_especies();
    lista_especies(const int&);
    vector <int>& get();
};

iostream & operator >>(iostream& is, vector<int>& aux);

bool operator == (vector <int>&, vector <int>&);

void adiciona_lista(lista_povoamentos&, const int&);

void iteracao(lista_povoamentos&, lista_especies&, vector <vector <int>>&tabu);

void verificacao(lista_povoamentos&, lista_especies&);
