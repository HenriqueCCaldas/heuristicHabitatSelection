#include "povoamento.h"


int main()
{
        cout<<"Quantos povoamentos existem?"<<endl;
        int n_pov, n_esp;
        cin>>n_pov;
        cout<<"Quantas especies existem?"<<endl;
        cin>>n_esp;
        lista_povoamentos R(n_pov);



        for(int i=0;i<n_pov;++i){
            R.seliciona_povoamento(i).resize_especies(n_esp);
            R.seliciona_povoamento(i).resize_vizinhanca(n_pov);
            R.seliciona_povoamento(i).get_numero()=i+1;
        }

        ifstream ficheiro1{"matriz_especies.txt"};
        if(!ficheiro1)
            throw runtime_error("Leitura do ficheiro 1 nao efetuada.");
        int n;
        for(int i=0;i<n_pov;i++){
            for(int j=0;j<n_esp;j++){
                ficheiro1>>n;
                R.seliciona_povoamento(i).get_especies().at(j)=n;
            }
        }
        ficheiro1.close();
        cout<<endl;

        ifstream ficheiro2 {"matriz_vizinhos.txt"};
        if(!ficheiro2)
            throw runtime_error("Leitura do ficheiro 2 nao efetuada.");
        for(int i=0;i<n_pov;i++){
            for(int j=0;j<n_pov;j++){
                ficheiro2>>n;
                R.seliciona_povoamento(i).get_vizinhanca().at(j)=n;
            }
        }
        ficheiro2.close();

        for(int k=0;k<n_pov;++k){
            cout<<"Matriz das especies: ";
            for(int i=0;i<n_esp;++i){
                cout<<R.seliciona_povoamento(k).get_especies().at(i)<<" ";
            }
            cout<<endl;
        }
        for(int k=0;k<n_pov;++k){
            cout<<"Matriz das vizinhancas: ";
            for(int i=0;i<n_pov;++i){
                cout<<R.seliciona_povoamento(k).get_vizinhanca().at(i)<<" ";
            }
            cout<<endl;
        }
        /*cout<<"Introduza os seus dados"<<endl<<"Matriz das Especies"<<endl;                 //Para utilizar na leitura da consola
    int auxiliar;
    for(int i=0;i<n_pov;++i){
        cout<<"Povoamento "<<i+1<<" :";
        R.seliciona_povoamento(i).get_numero()=i+1;
        for(int j=0;j<n_esp;++j){
            cin>>auxiliar;
            R.seliciona_povoamento(i).get_especies().at(j)=auxiliar;
        }
        cout<<endl;
    }
    for(int i=0;i<n_pov;++i){
        cout<<"Matriz das Vizinhancas"<<endl<<"Povoamento "<<i+1<<" :";
        for(int j=0;j<n_pov;++j){
            cin>>auxiliar;
            R.seliciona_povoamento(i).get_vizinhanca().at(j)=auxiliar;
        }
        cout<<endl;
    }
    */
        for (unsigned int i=0;i<R.get_ls().size();++i){                                                              //Zerar a lista destino
            R.get_ls().at(i)=0;
        }
        R.elimina_povoamento_vazio();
        R.sort_vizinhos();
        R.sort_especies();
        adiciona_lista(R,0);
        lista_especies conta_requisitos(n_esp);
        unsigned int i=0, k=0;
        vector <vector <int>> tabu;
        while(i!=conta_requisitos.get().size() and k<R.get_ls().size()) {
            i=0;
            cout<<endl<<"Inicio iteracao "<<k+1<<endl;
            iteracao(R,conta_requisitos, tabu);
            for(unsigned int j=0;j<conta_requisitos.get().size();++j){
                i=conta_requisitos.get().at(j)+i;
            }
            cout<<endl<<i<<" especies cumprem os requisitos. Ainda faltam "<<n_esp-i<<endl;
            k++;
        }

        cout<<endl<<"Lista Ordenada: "<<endl;
        for(int i=0; i<R.get_ls().size(); ++i){
            cout<<R.seliciona_povoamento(i).get_numero()<<" ";
        }
        cout<<endl<<endl;
        //Apresentacao dos resultados
        cout<<"Povoamentos escolhidos: ";
        for(int k=0;k<R.get_ls().size();++k){
            if(R.get_ls().at(k)==1){
                cout<<R.seliciona_povoamento(k).get_numero()<<" ";
            }
        }
        cout<<endl<<endl<<"Povoamentos nao escolhidos: ";
        for(int i=0;i<R.get_ls().size();++i){
            if(R.get_ls().at(i)==0){
                cout<<R.seliciona_povoamento(i).get_numero()<<" ";
            }
        }
        return 0;

}


