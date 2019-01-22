#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class Locuinta{
private:
    string *numeClient;
    int suprafataUtila;
    float discount;

public:

    Locuinta(){
        this->numeClient = NULL;
        this->suprafataUtila = 0;
        this->discount = 0;
    }

    Locuinta(string *numeClient, int suprafataUtila, float discount){
        this->numeClient = numeClient;
        this->suprafataUtila = suprafataUtila;
        this->discount = discount;
    }

    Locuinta(const Locuinta &temp){
        this->numeClient = temp.numeClient;
        this->suprafataUtila = temp.suprafataUtila;
        this->discount = temp.discount;
    }

    Locuinta operator=(const Locuinta &temp){
         this->numeClient = temp.numeClient;
        this->suprafataUtila = temp.suprafataUtila;
        this->discount = temp.discount;
        return *this;
    }

    ~Locuinta(){
        if(this->numeClient != NULL){
            delete this->numeClient;
        }
    }

    Locuinta operator--(){  //pre
        if(this->discount >= 1){
        this->discount--;
        }else{
            cout<<"Discountul va ajunge negativ. Operatia nu s-a efectuat.\n";
        }
        return *this;
    }

    Locuinta operator--(int){  //post
        Locuinta copie = *this;
        if(this->discount >= 1){
        this->discount--;
        }else{
            cout<<"Discountul va ajunge negativ. Operatia nu s-a efectuat.\n";
        }
        return copie;
    }
    

        Locuinta operator++(){  //pre
        if(this->discount <= 9){
        this->discount++;
        }else{
            cout<<"Discountul va ajunge mai mare decat 10. Operatia nu s-a efectuat.\n";
        }
        return *this;
    }

    Locuinta operator++(int){  //post
        Locuinta copie = *this;
        if(this->discount <= 9){
        this->discount++;
        }else{
            cout<<"Discountul va ajunge mai mare decat 10. Operatia nu s-a efectuat.\n";
        }
        return copie;
    }


    operator int(){
        return this->suprafataUtila;
    }

    float getDiscount(){
        return discount;
    }

    string *getNumeClient(){
        return this->numeClient;
    }

    int getSuprafataUtila(){
        return this->suprafataUtila;
    }

    void setNumeClient(string* numeClient){
        if(this->numeClient != NULL){
            delete this->numeClient;
        }
        this->numeClient = numeClient;
    }

    void setDiscount(float discount){
        this->discount = discount;
    }

    void setSuprafataUtila(int suprafataUtila){
        this->suprafataUtila = suprafataUtila;
    }

    virtual void calculChirie(int x, int y) {}



};


class Apartament : public Locuinta{
private:
    int etaj;

public:

    Apartament() : Locuinta(){
        this->etaj = 0;
    }

    Apartament(string *numeClient, int suprafataUtila, float discount, int etaj) : Locuinta(numeClient,suprafataUtila,discount){
        this->etaj = etaj;
    }

    Apartament(const Apartament &temp): Locuinta((Locuinta)temp){
        this->etaj = temp.etaj;
    }

    friend ifstream &operator>>(ifstream &in, Apartament &temp){
        string * numeClient = new string();
        in>>*numeClient;
        temp.setNumeClient(numeClient);
        int suprafataUtila;
        in>>suprafataUtila;
        temp.setSuprafataUtila(suprafataUtila);
        float discount;
        in>>discount;
        temp.setDiscount(discount);
        in>>temp.etaj;
        return in;
    }

    int getEtaj(){
        return etaj;
    }

     virtual void calculChirie(int x, int y){
        cout<<"Chiria este: "<< x * this->getSuprafataUtila() * (1- y * this->getDiscount()/100.0);
     }
};


class Casa : public Locuinta{
private:
    int suprafataCurte;
    int nrEtaje;
    float * suprafataEtaje;

public:
    Casa(): Locuinta(){
        this->suprafataCurte = 0;
        this->nrEtaje = 0;
        this->suprafataEtaje = NULL;
    }

    Casa(string *numeClient, int suprafataUtila, float discount,
        int suprafataCurte,int nrEtaje,float * suprafataEtaje) : Locuinta(numeClient,suprafataUtila,discount){
        
        this->suprafataCurte = suprafataCurte;
        this->nrEtaje = nrEtaje;
        this->suprafataEtaje = new float[this->nrEtaje];
        for(int i=0; i < this->nrEtaje; i++){
            this->suprafataEtaje[i] = suprafataEtaje[i];
        }
    }

    Casa(const Casa &temp): Locuinta((Casa)temp){
        this->suprafataCurte = temp.suprafataCurte;
        this->nrEtaje = temp.nrEtaje;
        this->suprafataEtaje = new float[this->nrEtaje];
        for(int i=0; i < this->nrEtaje; i++){
            this->suprafataEtaje[i] = temp.suprafataEtaje[i];
        }
    }

        virtual void calculChirie(int x, int y){
        cout<<"Chhhiria este: "<< x * (getSuprafataUtila() + 0.2 * this->suprafataCurte) * (1 - y * getDiscount()/100.0);
     }



};

int main(){

    Locuinta locuinta;
    cout<<int(locuinta);

    cout<<(++locuinta).getDiscount(); //post incrementare
    cout<<locuinta.getDiscount()<<endl;
    

    Apartament ap1;
    float *setaje = new float[2];
    setaje[0] = 50;
    setaje[1] = 55;
    string * numeclient = new string();
    *numeclient = "Nume client";
    Casa c1(numeclient,50,8,100,2,setaje);
    ifstream f("fisier.txt");
    f>>ap1;

    cout<<*ap1.getNumeClient()<<" "<<ap1.getSuprafataUtila()<<" "<<ap1.getDiscount()<<" "<<ap1.getEtaj()<<endl;

    f.close();
    Apartament ap2(ap1);
    ap1.setSuprafataUtila(500);

    //Locuinta  **vectortestare = new Locuinta*[3];

    // vectortestare[0] = &ap1;
    // vectortestare[1] = &c1;
    // vectortestare[2] = &ap2;
    // cout<<"****************************"<<endl;
    // for(int i=0;i<3;i++){
    //     vectortestare[i]->calculChirie(5,4);
    // }

    vector<Locuinta*> listaLocuinte;
    listaLocuinte.push_back(&ap2);
    listaLocuinte.push_back(&c1);
    vector<Locuinta*>::iterator it;

    // for(it=listaLocuinte.begin();it!=listaLocuinte.end();it++){
    //     cout<<it->getEtaj()<<endl;
    // }
    return 0;
}