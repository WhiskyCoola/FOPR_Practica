#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int FILA_DE_CARTES = 7;
const int NUMERO_DE_MAGATZEMS = 4;
struct start{
    int n_columna;
    char tipus; 
};
typedef vector<string>Fila;
typedef vector<Fila>Matriu;
//*/ Mostrar automaticamente estado y movimientos en caso de completar todos los almacenes. 
//PRE:
//POST:
int conversio_string_a_int(char a){
    int n;
    if(a == 'J'){
        n = 11;
    } else if(a == 'Q'){
        n = 12; 
    } else if(a == 'K'){
        n = 13; 
    } else if(a == 'A'){
        n = 1; 
    } else if(a == '0'){
        n= 0;
    } else n = a - 48;

    return n;
}

//PRE:
//POST:
int Color(char entrada){
    int c; // 1 == rojo; 0 == negro.
    if(entrada == 'T' or entrada == 'P') c = 0;
    else c = 1;

    return c;
}
//PRE:
//POST:
 void Pila_Descarta(vector<string>& Pila_Vector){//Descarta la primera carta y se muestra la siguiente. NUEVA VERSION
    unsigned int mida = Pila_Vector.size();
    string primer = Pila_Vector[0];

    for(unsigned int i=0; i<mida-1; ++i) Pila_Vector[i] = Pila_Vector[i+1];
    //Inv:
    Pila_Vector[mida-1] = primer;
}
//PRE:
//POST:
string Color_i_Simbol(char n1){
    string res;  //res = resultado; guarda el valor en string que identifica color y simbolo de la carta en cuestion.
    if(n1 == 'P'){
        res = "NP";  
    } else if(n1 == 'T'){
        res = "NT";  
    } else if( n1 == 'D'){
        res = "VD"; 
    } else  res = "VC"; 

    return res;
}

//PRE:
//POST:
string conversor_simbol(string entrada){
    string simbol;
    //int ultima_posicio = entrada.size()-1;
    char S = entrada[entrada.size()-1];
    if(entrada[1] != '0'){
        if(S == 'C'){
        simbol = entrada[0];
        simbol += "\033[0;31m\u2665\033[0m";
    } else if(S == 'D'){
        simbol = entrada[0];
        simbol += "\033[0;31m\u2666\033[0m";
    } else if(S == 'P'){
        simbol = entrada[0];
        simbol += "\u2660";
    } else if(S == 'T'){
        simbol = entrada[0];              
        simbol += "\u2663";
    }
    } else {
        if(S == 'C'){
        simbol = entrada[0];
        simbol += entrada[1];
        simbol += "\033[0;31m\u2665\033[0m";
    } else if(S == 'D'){
        simbol = entrada[0];
        simbol += entrada[1];
        simbol += "\033[0;31m\u2666\033[0m";
    } else if(S == 'P'){
        simbol = entrada[0];
        simbol += entrada[1];
        simbol += "\u2660";
    } else if(S == 'T'){
        simbol = entrada[0];
        simbol += entrada[1];
        simbol += "\u2663";
    }
    }      
    
    return simbol;
}
//PRE:
//POST:

void Moure_Cap_a_Magatzem(vector<string>& Pila_Vector, vector<int>& Ultim_Posicio, Matriu& Columnes, Matriu& Magatzem, int posicio, start& ini_tipo, int y, char m_o_c,  string& Carta_Moguda){ // Carta moguda es la carta por almacenar, "posicio" indica dónde se ubicará.//Tanto Pila a Almacen como Columna a Almacen, se ha definido en la funcio "Comandes_Moviments"
    int M_columna = posicio; // == columna donde se guardara la carta
    int carta_m;

    if(Carta_Moguda[0] == '1' and Carta_Moguda[1] == '0') carta_m = 10;
    else carta_m = conversio_string_a_int(Carta_Moguda[0]);

    string cmp;
    if(y == 0) cmp = Magatzem[M_columna][y];
    else cmp = Magatzem[M_columna][y-1];// cmp = ultimo valor del vector de la fila de la matriz
    
    int i = ini_tipo.n_columna;
    int aux;

    if(cmp[0] == '1' and cmp[1] == '0') aux = 10;
    else aux = conversio_string_a_int(cmp[0]);
//cout<<"Carta moguda: "<<Carta_Moguda<<endl;
    if(y == 0 and Carta_Moguda[0]=='A') {
        Magatzem[M_columna][y] = Carta_Moguda;
        Ultim_Posicio[7+posicio] += 1;
        if(m_o_c != 'P'){
           Ultim_Posicio[conversio_string_a_int(ini_tipo.tipus)-1] -=1;
        Columnes[conversio_string_a_int(ini_tipo.tipus)-1][i-1] = " "; 
        } else {
            Pila_Descarta(Pila_Vector);
            Pila_Vector.pop_back();
        }

    } else if(y == 0 and Carta_Moguda[0] != 'A') {
        cout<<"Error: A un magatzem buit sols es pot moure un as"<<endl;

    } else if((aux != carta_m - 1) or (Color_i_Simbol(cmp[cmp.size()-1]) != Color_i_Simbol(Carta_Moguda[Carta_Moguda.size()-1]))){
       cout<<"Error: No hi ha concordança de valor i/o pal"<<endl;

    } else if((aux == carta_m - 1) and (Color_i_Simbol(cmp[cmp.size()-1]) == Color_i_Simbol(Carta_Moguda[Carta_Moguda.size()-1]))){
        Magatzem[M_columna][y] = Carta_Moguda;
        Ultim_Posicio[7+posicio] += 1;
        if(m_o_c == 'P'){
            Pila_Descarta(Pila_Vector);
            Pila_Vector.pop_back();
        } else {
        Ultim_Posicio[conversio_string_a_int(ini_tipo.tipus)-1] -=1;
        Columnes[conversio_string_a_int(ini_tipo.tipus)-1][i-1] = " ";
        }
    }
}              
//PRE:
//POST:
void Moure_Entre_Columna(vector<string>& Pila_Vector, vector<int>& Ultim_Posicio, Matriu& Columnes, int posicio, start& ini_tipo, int y, char m_o_c, string& Carta_Moguda){
    int M_columna = posicio;
    int carta_m;
    int i = ini_tipo.n_columna;
    string cmp;

    if(Carta_Moguda[0] == '1' and Carta_Moguda[1] == '0') carta_m = 10;
    else carta_m = conversio_string_a_int(Carta_Moguda[0]); // Carta_moguda es el valor de la pila.
    // parte declaracion columna

    if(y == 0) cmp = Columnes[M_columna][y];
    else cmp = Columnes[M_columna][y-1];

    int aux;
    if(cmp[0] == '1' and cmp[1] == '0') aux = 10;    //cmp es un string y aux es su traduccion en int i aux es la ultima carta de la fila de la columna destino. Se compara si aux es la carta anterior a carta_m, y ademas si es mismo color y simbolo.
    else aux = conversio_string_a_int(cmp[0]);

    if(y == 0 and Carta_Moguda[0]=='K') {
        Columnes[M_columna][y] = Carta_Moguda;  
        Ultim_Posicio[posicio] += 1;
        if(m_o_c != 'P'){
            Ultim_Posicio[conversio_string_a_int(ini_tipo.tipus)-1] -=1;
        Columnes[conversio_string_a_int(ini_tipo.tipus)-1][i-1] = " ";
        } else {
            Pila_Descarta(Pila_Vector);
            Pila_Vector.pop_back();
        }

    } else if(y == 0 and Carta_Moguda[0] != 'K'){
       cout<<"A una columna buida sols es pot moure un rei"<<endl; 

    } else if((aux-1 != carta_m) or (Color(cmp[cmp.size()-1]) == Color(Carta_Moguda[Carta_Moguda.size()-1]))){
        cout<<"No hi ha concordança de valor i/o pal"<<endl;
    //    cout<<"Color anterior: "<<Color(cmp[cmp.size()-1])<<"       "<<"color posterior: "<<Color(Carta_Moguda.size()-1)<<endl;
    //    cout<<"carta anterior: "<<aux<<"    "<<"carta posterior: "<<carta_m<<endl;
    } else if(aux-1 == carta_m and (Color(cmp[cmp.size()-1]) != Color(Carta_Moguda[Carta_Moguda.size()-1]))){
    //    cout<<"carta anterior: "<<aux<<"    "<<"carta posterior: "<<carta_m<<endl;
        Columnes[M_columna][y] = Carta_Moguda;  
        Ultim_Posicio[posicio] += 1;
        if(m_o_c == 'P'){
            Pila_Descarta(Pila_Vector);
            Pila_Vector.pop_back();
        } else {
           Ultim_Posicio[conversio_string_a_int(ini_tipo.tipus)-1] -=1;
        Columnes[conversio_string_a_int(ini_tipo.tipus)-1][i-1] = " "; 
        }
    } //else cout<<"ERROR";
}
int Veure_Ultima_Carta(vector<int>& Ultim_Posicio, string carta_per_moure){
    int res;
    char n = carta_per_moure[1]; // ultim caracter de la columna/magatzem on el volem moure
    int x = conversio_string_a_int(n);
    char m = carta_per_moure[0];// primer caracter de columna/magatzem a on el volem moure
    if(m == 'M'){
        res = Ultim_Posicio[6+x];
    } else res = Ultim_Posicio[x-1];
    if(res == -1) res = 0;
    return res; // res indica la mida on és la ultima carta.
} 
//PRE:
//POST:
void Comandes_Moviments(vector<int>& Ultim_Posicio, Matriu& Columnes, Matriu& Magatzem, vector<string>& Pila_Vector, string& Carta_Moguda){
    string posicio_inicial,desti;
    unsigned int numero_cartes; 
    cin>>posicio_inicial>>numero_cartes>>desti;

    int num_inici = conversio_string_a_int(posicio_inicial[posicio_inicial.size()-1])-1; // num_inici es la columna indicada donde se mueve la carta
    
    int num_desti = conversio_string_a_int(desti[desti.size()-1]) -1; // num:desti es la columna indicada donde se guardara la carta
   
    int x = Veure_Ultima_Carta(Ultim_Posicio, posicio_inicial); // .size() de la ultima carta de la columna de posicio_inicial
    
    int y = Veure_Ultima_Carta(Ultim_Posicio, desti); // Y = mida ultima carta desti.

    start ini_tipo;
    ini_tipo.n_columna = x;
    ini_tipo.tipus = posicio_inicial[posicio_inicial.size()-1];
    char moc = 'P';
    if(posicio_inicial[0] == 'C'){
        //Si se coge la carta inicial desde las columnas...
        if(x == 0) Carta_Moguda = Columnes[num_inici][x];
        else Carta_Moguda = Columnes[num_inici][x-1]; // CUIDADO,  Columnes[num_inici].size()-1 esta MAL, YA QUE LA ULTIMA POSICION DE LA MATRIZ SIEMPRE VA A SER LA 13, YA QUE INICIALMENTE ESTA DECLARADO A 13
        moc = 'C';
        if(desti[0] == 'M') Moure_Cap_a_Magatzem(Pila_Vector, Ultim_Posicio, Columnes, Magatzem, num_desti, ini_tipo, y, moc, Carta_Moguda);  // num_desti == int posicio
        else if(desti[0] == 'C') Moure_Entre_Columna(Pila_Vector, Ultim_Posicio, Columnes, num_desti, ini_tipo, y, moc, Carta_Moguda);
        else if(desti[0] == 'P') cout<<"No es poden moure cartes a la pila"<<endl;
        else cout<<"Origen del moviment no valid"<<endl;

    } else if (posicio_inicial[0] == 'P'){ 
        if(Pila_Vector.size() == 0) cout<<"Pila buida"<<endl;
        else {
            Carta_Moguda = Pila_Vector[0];
            
            if(desti[0] == 'M' ) Moure_Cap_a_Magatzem(Pila_Vector, Ultim_Posicio, Columnes, Magatzem, num_desti, ini_tipo, y, moc, Carta_Moguda);
            else if(desti[0] == 'C') Moure_Entre_Columna(Pila_Vector, Ultim_Posicio, Columnes, num_desti, ini_tipo, y, moc, Carta_Moguda);//  Pila_A_Columna_o_Magatzem(Ultim_Posicio, Columnes, Magatzem, num_desti, moc, Pila_Vector, y, Carta_Moguda);
            else if(desti[0] == 'P') cout<<"No es poden moure cartes a la pila"<<endl;
            else cout<<"Origen del moviment no valid"<<endl;
        }
        
    } else if(posicio_inicial[0]== 'M'){
        moc = 'M';
        if(x == 0) Carta_Moguda = Magatzem[num_inici][x];
        else Carta_Moguda = Magatzem[num_inici][x-1];

        if(desti[0] == 'C') Moure_Entre_Columna(Pila_Vector, Ultim_Posicio, Columnes, num_desti, ini_tipo, y, moc, Carta_Moguda);
        else if(desti[0] == 'P') cout<<"No es poden moure cartes a la pila"<<endl;
        else cout<<"Origen del moviment no valid"<<endl;
   
    }
    
}

//PRE:
//POST:
void Estat_Joc(vector<int>& Ultim_Posicio, Matriu& Columnes,Matriu& Magatzem, vector<string>& Pila_Vector, int& Comptador_D_Estat){
    string mostra_carta_pila =  Pila_Vector[0];
    if(Pila_Vector.size() != 0) cout<<"Pila: "<<conversor_simbol(mostra_carta_pila)<<endl;
    else cout<<"Pila: "<<"-"<<endl;

    for(int i = 0; i < NUMERO_DE_MAGATZEMS; ++i){
        //Inv:
        unsigned int x = Ultim_Posicio[7+i];
        string mag = Magatzem[i][12];
        string a = Magatzem[i][0];

        if(x == 0){ 
            cout<<"Mag "<<i+1<<": -";  
        } else if(a != " "){  
           cout<<"Mag "<<i+1<<": ";
           for( unsigned int j = 0; j < x; ++j){
                string Dades_Magatzem = Magatzem[i][j];
                cout<<conversor_simbol(Dades_Magatzem);
                if(j < x-1) cout<<" ";
            }
        }
    /*    if(a != " "){  // == pasa a ser != y 'K' pasa a ser ' '
            cout<<"Mag "<<i+1<<": ";
          //  cout<<" x: "<< x<<endl;
            for( unsigned int j = 0; j < x; ++j){ // magatzem[0].size() passa a ser "y"
                //Inv:
                string Dades_Magatzem = Magatzem[i][j];
                cout<<conversor_simbol(Dades_Magatzem);
                if(j < x-1) cout<<" ";
            }
        } else if(x == 0){  // quitamos else if(a[0] != 'A')
           cout<<"Mag "<<i+1<<": -"; 
        } */
        /* else {
            cout<<"Mag "<<i+1<<": ";
            for( unsigned int j = 0; j < x; ++j){
                //Inv:
                string Dades_Magatzem = Magatzem[i][j];
                cout<<conversor_simbol(Dades_Magatzem);
                if(j < x) cout<<" "; // cambio j<12 a j<x
            } */
        
    cout<<endl;
    }
    for(int i = 0; i<FILA_DE_CARTES; ++i){
        //Inv:
        unsigned int y = Ultim_Posicio[i];
        string col = Columnes[i][12];
        string b = Columnes[i][0];
        
        if(b != " "){
            cout<<"Col "<<i+1<<": ";
            for( unsigned int j = 0; j < y; ++j){ // cambio de j<= y a j<y
                //Inv:
                string Carta_Temp = Columnes[i][j];
                cout<<conversor_simbol(Carta_Temp);
                if(j < y-1) cout<<" "; // cambio j<12 a j<y
            }
        } 
        else if(b[0] == ' '){
           cout<<"Col "<<i+1<<": -"; 
        } 
    cout<<endl;
    }
    cout<<"---"<<endl;
}

//PRE:
//POST:
void Menu_General(vector<int>& Ultim_Posicio, Matriu& Columnes, Matriu& Magatzem, vector<string>& Pila_Vector, string& Carta_Moguda, int& Comptador_D_Estat){
    bool acabat = false; //Menu de cin: Introduccion de indicaciones; Aqui Empieza y termina todo.
    char entrada; //While(cin);
    
	while (not acabat and cin>>entrada) {
        //Inv: 
        
        if(entrada == 'D'){
            if(Pila_Vector.size() == 0){
                cout<<"Pila buida"<<endl;
            } else {
                 Pila_Descarta(Pila_Vector);
                 cout<<"Pila: "<<conversor_simbol(Pila_Vector[0])<<endl;
            ++Comptador_D_Estat;
            }
        } else if (entrada == 'M'){
            Comandes_Moviments(Ultim_Posicio, Columnes, Magatzem, Pila_Vector, Carta_Moguda);//UNICO COMANDO QUE REQUIERE MAS DE UN CIN.
            ++Comptador_D_Estat;

            string p = Magatzem[0][12], s = Magatzem[1][12], t = Magatzem[2][12], q = Magatzem[3][12];
            if(p[0] == 'K' and s[0]  == 'K' and t[0] == 'K' and q[0] == 'K'){
                Estat_Joc(Ultim_Posicio, Columnes, Magatzem, Pila_Vector, Comptador_D_Estat);
                cout<<"Felicitats has guanyat!! Ho has fet en "<<Comptador_D_Estat<<" moviment."<<endl;
                acabat = true;
                }

        } else if (entrada == 'Z'){
            cout<<"No has guanyat i has fet "<<Comptador_D_Estat<<" moviments."<<endl;
            acabat = true; // falta añadir el cout status aqui.
        } else if (entrada == 'S'){
            Estat_Joc(Ultim_Posicio, Columnes, Magatzem, Pila_Vector, Comptador_D_Estat);// Cout dels moviments totals.
        }
	}   
}

//PRE:
//POST:
void Lectura_Dades(vector<int>& Ultim_Posicio, Matriu& Columnes, Matriu& Magatzem, vector<string>& Pila_Vector, string& Carta_Moguda, int& Comptador_D_Estat){ 
    for(int i=0; i<FILA_DE_CARTES; ++i){
        //Inv:
        unsigned int mida_columna;
        cin>>mida_columna;
        Ultim_Posicio[i] = mida_columna;
        for(unsigned int j=0; j<mida_columna; ++j) cin>>Columnes[i][j];
        //Inv:
    }
   
    //Llenar los 4 almacenes. Formato matriz.
    for(int i=0; i<NUMERO_DE_MAGATZEMS; ++i){
        //Inv:
        unsigned int mida_magatzem;
        cin>>mida_magatzem;
        Ultim_Posicio[7+i]=mida_magatzem;
        for(unsigned int j=0; j<mida_magatzem; ++j)cin>>Magatzem[i][j];
        //Inv:
    }
    //LLenar Pila_Cartes y Columnes_Joc//
    //Pila se inicializa como nos lo indique el estado inicial.
    unsigned int mida_pila;
        string pila_carta;
        cin>>mida_pila;
    for(unsigned int i = 0; i < mida_pila; ++i){
        //Inv:
        cin>>pila_carta;
        Pila_Vector.push_back(pila_carta);
    }
}

//PRE:
//POST:
int main(){
    vector<string> Pila;

    Matriu Columna(7,Fila(13));

    int contador = 0;

    Matriu Emmagatzematge(4,Fila(13));

    string Moved_Card;

    vector<int> last(11,0); 

    Lectura_Dades(last, Columna, Emmagatzematge, Pila, Moved_Card, contador);

    Menu_General(last, Columna, Emmagatzematge, Pila, Moved_Card, contador);
}
