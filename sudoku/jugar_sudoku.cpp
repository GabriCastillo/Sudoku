#include <iostream>
#include <array>
using namespace std;
const int CUADRO=9;
const int TOTAL=45;
typedef array <int,CUADRO>Columnas;
typedef array<Columnas,CUADRO>Sudoku;
struct coordenadas
{
    int fila=0;
    int columna=0;
};
typedef array<coordenadas,81>Consta;
struct Lugare_Fijos
{
    Consta sitios;
    int lim=0;
};
///////////////////////////////////////////////
void mostrar(const Sudoku&sk)
{
    cout<<endl;
    cout<<"* "<<" "<<" "<<" 0 1 2 "<<" "<<" 3 4 5 "<<" "<<" 6 7 8"<<endl;
    cout<<"-------------------------------"<<endl;
    for(int i=0; i<CUADRO; i++)
    {
        cout<<i<<": "<<"| ";

        for(int k=0; k<CUADRO; k++)
        {

            cout<<sk[i][k]<<" ";
            if((k+1)%3==0)
            {
                cout<<"| ";
            }

        }
        cout<<endl;
        if((i+1)%3==0)
        {

            cout<<"-----------------------------"<<endl;

        }
    }

}
//////////////////////////////////////////////////////////////////
void limites(const Sudoku&sk, Lugare_Fijos&cuadro_ocupado)
{
    for(int i=0; i<CUADRO; i++)
    {

        for(int k=0; k<CUADRO; k++)
        {

            if(sk[i][k]>0)
            {
                cuadro_ocupado.sitios[cuadro_ocupado.lim].fila=i;
                cuadro_ocupado.sitios[cuadro_ocupado.lim].columna=k;
                cuadro_ocupado.lim++;

            }
        }
    }
}
/////////////////////////////////////////////////
void inicializar(Sudoku&sk, Lugare_Fijos&cuadro_ocupado)
{
    cout<<"los sudokus estan ordenados por orden de dificultad. elije un numero del 1 al 5 (actualmente solo hay 2): ";
    int nivel=0;
    cin>>nivel;
    switch (nivel)
    {
    case 1:
        sk=
        {
            {
                {{6,0,0,8,0,0,4,0,1}},
                {{8,9,0,6,0,0,0,0,3}},
                {{4,0,0,1,0,3,7,6,0}},
                {{0,0,0,5,0,1,0,0,0}},
                {{0,4,0,0,0,0,0,0,0}},
                {{0,0,9,2,8,0,3,7,6}},
                {{0,0,5,0,1,8,6,3,0}},
                {{3,0,8,0,2,0,5,0,7}},
                {{1,0,0,0,6,5,8,2,0}}
            }
        };
        limites(sk,cuadro_ocupado);
        mostrar(sk);
        break;

    case 2:
        sk=
        {
            {
                {{5,3,0,0,7,0,0,0,0}},
                {{6,0,0,1,9,5,0,0,0}},
                {{0,9,8,0,0,0,0,6,0}},
                {{8,0,0,0,6,0,0,0,3}},
                {{4,0,0,8,0,3,0,0,1}},
                {{7,0,0,0,2,0,0,0,6}},
                {{0,6,0,0,0,0,2,8,0}},
                {{0,0,0,4,1,9,0,0,5}},
                {{0,0,0,0,8,0,0,7,9}}
            }
        };
        limites(sk,cuadro_ocupado);
        mostrar(sk);
        break;
    }
}
//////////////////////////////////////////////////
bool ver_columnas(const Sudoku&sk)
{
    bool ok=true;
    for(int i=0; i<CUADRO; i++)
    {
        int suma=0;
        for(int k=0; k<CUADRO; k++)
        {
            suma=suma+sk[k][i];
        }

        if(suma!=TOTAL)
        {
            cout<<"Error en la columna <"<<i<<">"<<endl;
            ok=false;
        }
    }
    return ok;
}

bool ver_filas(const Sudoku&sk)
{
    bool ok=true;
    for(int i=0; i<CUADRO; i++)
    {
        int suma=0;
        for(int k=0; k<CUADRO; k++)
        {
            suma=suma+sk[i][k];
        }
        if(suma!=TOTAL)
        {
            cout<<"Error en la fila <"<<i<<">"<<endl;
        }
    }
    return ok;
}

//////////////////////////////////////////////////////////////
bool corregir(const Sudoku&sk)
{
    int col=0;
    int fil=0;
    int lim=2;
    int errores=0;
    for(int cuadrante=1; cuadrante<=9; cuadrante++)
    {
        int suma=0;
        for (int i=0+fil; i<=lim+fil; i++)
        {
            for(int k=0+col; k<=lim+col; k++)
            {
                suma=suma+sk[i][k];
            }
        }

        if(suma!=TOTAL)
        {
            cout<<"Error en el cuadrante: <"<<cuadrante<<">"<<endl;
            errores++;
        }

        if((cuadrante%3)==0)
        {

            col=0;
            fil=fil+3;
        }
        else
        {
            col=col+3;
        }
    }


    return (errores==0);
}
/////////////////////////////////////////////////////////
bool correccion(const Sudoku&sk, bool fin)
{
    if(ver_columnas(sk)&&ver_filas(sk))
        {
            if(corregir(sk))
            {
                mostrar(sk);
                fin=true;
                cout<<"El sudoku ingresado es valido."<<endl;

            }
            else
            {
                cout<<endl;
                mostrar(sk);
                cout<<"No es un sudoku valido.";
                cout<<endl;
            }
        }
        else
        {
            cout<<endl;
            mostrar(sk);
            cout<<"No es un sudoku valido.";
            cout<<endl;
        }
        return fin;
}
///////////////////////////////////////////////////////////////////////////////////////
bool permitido(const Lugare_Fijos&cuadro_ocupado, int fila, int columna)
{
    bool ok=true;
    for(int i=0;i<cuadro_ocupado.lim;i++)
    {
        if(cuadro_ocupado.sitios[i].fila==fila&&cuadro_ocupado.sitios[i].columna==columna)
        {
            ok=false;
        }
    }
    return ok;
}
///////////////////////////////////////////////////////////////
void aniadir(Sudoku&sk,const Lugare_Fijos&cuadro_ocupado)
{
    int fila=0;
    int columna=0;
    int num=0;
    cout<<"que numero deseas aniadir: ";
    cin>>num;
    cout<<"En que posicion quieres colocarlo (fila columna): ";
    cin>>fila>>columna;
    if(permitido(cuadro_ocupado,fila,columna)&&num<=CUADRO&&num>0&&fila<=CUADRO&&fila>=0&&columna<=CUADRO&&columna>=0)
    {
        sk[fila][columna]=num;
    }else{cout<<"Error en los parametros"<<endl;}

}
/////////////////////////////////////////////////////////
void quitar(Sudoku&sk,const Lugare_Fijos&cuadro_ocupado)
{
    int fila=0;
    int columna=0;
    cout<<"Que posicion quieres eliminar (fila columna): ";
    cin>>fila>>columna;
    if(permitido(cuadro_ocupado,fila,columna)&&fila<=CUADRO&&fila>=0&&columna<=CUADRO&&columna>=0)
    {
        sk[fila][columna]=0;
    }else{cout<<"Error en los parametros"<<endl;}

}

/////////////////////////////////////////////////////////
void jugar(Sudoku&sk,const Lugare_Fijos&cuadro_ocupado, bool&fin)
{
    int op=0;
    do
    {
        cout<<"Presiona (1) para aniadir, presiona (2) para quitar, presiona (3) para corregir, presiona (4) para salir: ";
        cin>>op;
        switch (op)
        {
        case 1:
aniadir(sk,cuadro_ocupado);
mostrar(sk);
            break;

        case 2:
quitar(sk,cuadro_ocupado);
mostrar(sk);
            break;

        case 3:
fin=correccion(sk,fin);
if(fin)
{
    op=4;
}
            break;

        case 4:
            cout<<"Gracias por intentarlo."<<endl;
            fin=true;
            break;

        default:
                cout<<"operacion incorrecta."<<endl;
                break;
        }
    }
    while(op!=4);

}
////////////////////////////////////////////////////////////
int main()
{
    Sudoku SK;
    Lugare_Fijos cuadro_ocupado;
    inicializar(SK,cuadro_ocupado);
    bool fin=false;
    do
    {
        jugar(SK,cuadro_ocupado,fin);


    }while(fin==false);

}

