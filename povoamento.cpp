#include "povoamento.h"

povoamento::povoamento(){
    especies.resize(1);
    vizinhanca.resize(1);
    especies.at(0)=0;
    vizinhanca.at(0)=0;
    numero=1;
}
povoamento::povoamento(const int &viz, const int &esp){
    especies.resize(esp);
    vizinhanca.resize(viz);
    for(unsigned int i=0;i<especies.size();++i){
        especies.at(i)=0;
    }
    for(unsigned int i=0;i<vizinhanca.size();++i){
        vizinhanca.at(i)=0;
    }
    numero=1;
}
void povoamento::resize_especies(const int& i){
    especies.resize(i);
}
void povoamento::resize_vizinhanca(const int& i){
    vizinhanca.resize(i);
}
int povoamento::get_nmr_especies_(){                                        //Número de espécies
    int r=0;
    for (unsigned int i=0;i<especies.size();++i){
        r=+especies.at(i);
    }
    return r;
}
int povoamento::get_nmr_vizinhanca(){                                      //Número de vizinhos
    int r=0;
    for (unsigned int i=0;i<vizinhanca.size();++i){
        r=r+vizinhanca.at(i);
    }
    return r;
}
povoamento& povoamento::operator = (const povoamento& aux){
    resize_especies(aux.especies.size());
    resize_vizinhanca(aux.vizinhanca.size());
    numero=aux.numero;
    for(unsigned int i=0;i<especies.size();i++){
        especies.at(i)=aux.especies.at(i);
    }
    for(unsigned int i=0;i<vizinhanca.size();++i){
        vizinhanca.at(i)=aux.vizinhanca.at(i);
    }
    return *this;
};
lista_povoamentos::lista_povoamentos(){
    povoamento Aux;
    lista.resize(1);
    ls.resize(1);
    ls.at(0)=0;
    lista.at(0)=Aux;
}
lista_povoamentos::lista_povoamentos(const int& n){
    lista.resize(n);
    ls.resize(n);
    for(unsigned int i=0;i<ls.size();++i){
        ls.at(i)=0;
    }
}
lista_povoamentos::lista_povoamentos(const vector <povoamento>& aux){ //Por definição, constroi assumindo todos os povoamentos na lista;
    lista.resize(aux.size());
    ls.resize(aux.size());
    for(unsigned int i=0;i<lista.size();++i){
        lista.at(i)=aux.at(i);
        ls.at(i)=1;
    }
}
void lista_povoamentos::insere_ls_povoamento(const int &n){
    ls.at(n)=1;
}
void lista_povoamentos::remove_ls_povoamento(const int& n){
    ls.at(n)=0;
}
void lista_povoamentos::sort_vizinhos(){
    povoamento aux;
    for(unsigned int i=0;i<lista.size();++i){
        for(unsigned j=i+1;j<lista.size();++j){
            if(lista.at(i).get_nmr_vizinhanca()<lista.at(j).get_nmr_vizinhanca()){
                aux=lista.at(i);
                lista.at(i)=lista.at(j);
                lista.at(j)=aux;

            }
        }
    }
}
povoamento& lista_povoamentos::seliciona_povoamento(int& n){ //ATENÇÃO: O número n é o número do povoamento correspondente à posição n do vetor.
    return lista.at(n);
}
void lista_povoamentos::sort_especies(){
    povoamento aux;
    for(unsigned int i=0;i<ls.size();++i){
        for(unsigned j=i+1;j<ls.size();++j){
            if(lista.at(i).get_nmr_especies_()<lista.at(j).get_nmr_especies_() and lista.at(i).get_nmr_vizinhanca()<=lista.at(j).get_nmr_vizinhanca()){
                aux=lista.at(i);
                lista.at(i)=lista.at(j);
                lista.at(j)=aux;

            }
        }
    }
}
lista_especies::lista_especies(){ //O tamanho do vetor é sempre correspondente ao número total de espécies!!!!! Variáveis binárias!!!
    species.resize(1);
    species={0};
}
lista_especies::lista_especies(const int &aux){
    species.resize(aux);
    for(unsigned int i=0;i<species.size();++i){
        species.at(i)=0;
    }
}
vector <int>& lista_especies:: get(){
    return species;
}
iostream& operator >>(iostream& is, vector<int>& aux) {
    for(unsigned int i=0;i<<aux.size();++i){
        is>>aux.at(i);
    }
    return is;
}
bool operator == (vector <int>& a, vector <int>& b){
    if(a.size()!=b.size())
        return false;
    else{
        int j=0;
        for(unsigned int i=0;i<a.size();++i){
            if(a.at(i)!=b.at(i))
                j=-1;
        }
        if (j==-1){
            return false;
        }
        else
            return true;
    }
}
void adiciona_lista(lista_povoamentos& R, const int& n){
    R.insere_ls_povoamento(n);
}
void iteracao( lista_povoamentos& R, lista_especies&  aux, vector <vector <int>>& tabu){
    int a=0,b=0,i=0,j=0;
    int posicao_especie=-1, posicao_povoamento=-1;                                                                                                    //utilizado para lançar erro
    vector <int> ta (2);
    while(a!=1 and i<R.get_ls().size()){                                                                                                          //enquanto houver povoamentos
            while(b!=1 and j<R.seliciona_povoamento(i).get_especies().size()){
                    if(R.seliciona_povoamento(i).get_especies().at(j)==1 and aux.get().at(j)==0 and R.get_ls().at(i)==1){                             //está na povoamento, não cumpre os requisitos e está na rede;
                        b=1;
                        a=1;
                        posicao_especie=j;
                        posicao_povoamento=i;
                        ta.at(0)=posicao_especie;
                        ta.at(1)=posicao_povoamento;
                }
                ++j;
            }
            j=0;
            ++i;
        }
    cout<<endl<<"Especie a analisar: "<<posicao_especie+1<<endl<<"Povoamento a analisar: "<<R.seliciona_povoamento(posicao_povoamento).get_numero()<<endl;
    if(posicao_especie==-1){                                                                                                                         //caso seja impossível encontrar espécie que não cumpra os requisitos em R
        int k=0;
        while (R.get_ls().at(k)!=0 and k<R.get_ls().size()){                                                                                         //seleciona um povoamento que ainda não está em R                                                                                                                //encontra um povoamento que não esteja na rede para adicioná-lo
            k++;
        }
        R.insere_ls_povoamento(k);
    }
    else{
        int c=0;
        for(unsigned int i=0;i<tabu.size();++i){                                                                                                     //verificação da não pertença à lista tabu;
            if(tabu.at(i)==ta){
                c=1;
            }
        }
        if(c==1){
            return;
        }
        else {
            a=0, b=0, i=0, j=-1;
            while (a!=1 and i<R.get_ls().size()){
                    if(R.get_ls().at(i)==0 and R.seliciona_povoamento(i).get_especies().at(posicao_especie)==1 and R.seliciona_povoamento(i).get_vizinhanca().at(R.seliciona_povoamento(posicao_povoamento).get_numero()-1)==1){                                //não está em R, contêm a espécie, está na vizinhança e não é o próprio povoamento
                        j=i;
                        a=1;
                    }
                ++i;
            }
            if(j!=-1){
                R.insere_ls_povoamento(j);                                                                                                                //adiciona o povoamento à rede e marca a espécie a cumprir o requisito
                cout<<"Povoamento a inserir: "<<R.seliciona_povoamento(j).get_numero()<<endl;
                verificacao(R,aux);
                cout<<"Atualizacao lista de requisitos: ";
                for(unsigned int i=0;i<aux.get().size();++i){
                    cout<<aux.get().at(i)<<" ";
                }
                cout<<endl;
            }
            else{
                tabu.push_back(ta);
            }
        }
    }
}
void verificacao (lista_povoamentos& R, lista_especies& aux){
    int a=-1;int k=0;
    for(int esp=0; esp<aux.get().size();++esp){                                                                                                       //para cada uma das especies
        a=-1;
        for(int pov=0;pov<R.get_ls().size();++pov){
            if(R.seliciona_povoamento(pov).get_especies().at(esp)==1 and R.get_ls().at(pov)==1){                                                       //se a espécie está no povoamento Pov e Pov pertence à rede
                k=0;
                while (k<R.get_ls().size() and a!=1){
                    if(R.seliciona_povoamento(pov).get_vizinhanca().at(R.seliciona_povoamento(k).get_numero()-1)==1
                    and R.seliciona_povoamento(k).get_especies().at(esp)==1 and R.get_ls().at(k)==1 and k!=pov){      //se o povoamento K esta na vizinhança de pov, k tem a especie, esta na rede e nao e =pov
                        aux.get().at(esp)=1;
                        a=1;
                    }
                    k++;
                }
            }
        }
    }
}
