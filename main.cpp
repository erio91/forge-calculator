//
//  main.cpp
//  PBL 2

#include <iostream>
#include <math.h>  
using namespace std;

int main(int argc, const char * argv[])
{
    int xxx;
    const double PI = 3.141592654;
    //Numero de bloques
    int N = 1;
    double capacidadprensa;
    cout<<"Capacidad de la prensa? (toneladas)"<<endl;
    cin>>capacidadprensa;
    
    cout<<"Numero de bloques?"<<endl;
    cin>>N;
    
    //Propiedades de cada bloque
    int tipo[N];
    double alturacavidad[N];
    double largocavidad[N];
    double radiocavidad[N];
    double mfriccion[N];
    double anchoflash[N];
    double alturaflash[N];
    
    //El identificador de cada bloque (bloque 1, bloque 2, etc...)
    int numerobloque = 1;
    
    double temperatura = 1;
    double alturainicial[N];
    
    //Temperatura de la pieza
    cout<<"Temperatura de la pieza?*"<<endl;
    cin>>temperatura;
    
    //Variables de salida
    double epsilonflash[N];
    double epsiloncavidad[N];
    double sigmacavidad[N];
    double sigmaflash[N];
    double sigmaep[N];
    double sigmaea[N];
    double fuerzacp[N];
    double fuerzafp[N];
    double fuerzaca[N];
    double fuerzafa[N];
    double fuerzasa[N];
    double fuerzasp[N];
    double Rmayus[N];
    double fuerzatotalsa = 0;
    double fuerzatotalsp = 0;
    double fuerzatotal = 0;
    
    double k = ((6.26*pow(10,-5.0)*pow(temperatura,2.0)-.191968*temperatura+160.9974))*1000;
    double n = (1.7*pow(10,-7.0)*pow(temperatura,2.0)-5.41*pow(10,-4.0)*temperatura+.53695);
    
    cout<<"Cual es la k?"<<endl;
    cin>>k;
    cout<<"Cual es la n?"<<endl;
    cin>>n;
    
    
    //Entrada de todos los datos
    for (int i=0; i<N; i++) {
        cout<<"Que tipo de flujo tiene el bloque "<<numerobloque<<"?"<<endl;
        cout<<"(1:Flujo plano, 2:Flujo aximetrico)"<<endl;
        cin>>tipo[i];
        cout<<"Altura inicial de la pieza en el bloque "<<numerobloque<<"?"<<endl;
        cin>>alturainicial[i];
        cout<<"Que altura tiene la cavidad del bloque "<<numerobloque<<"? (H)"<<endl;
        cin>>alturacavidad[i];
        if (tipo[i]==1) {
            cout<<"Cual es el largo de la cavidad del bloque "<<numerobloque<<"? (L)"<<endl;
            cin>>largocavidad[i];
        } else {
            cout<<"Cual es radio (mitad del ancho de la cavidad) del bloque "<<numerobloque<<"? (r)"<<endl;
            cin>>radiocavidad[i];
        }
        cout<<"Que ancho tiene el flash del bloque "<<numerobloque<<"? (w)"<<endl;
        cin>>anchoflash[i];
        cout<<"Que altura tiene el flash del bloque "<<numerobloque<<"? (t)"<<endl;
        cin>>alturaflash[i];
        cout<<"Que factor de friccion tiene el bloque "<<numerobloque<<"? (m)"<<endl;
        cin>>mfriccion[i];
        
        epsiloncavidad[i] = log(alturainicial[i]/alturacavidad[i]);
        epsilonflash[i] = log(alturainicial[i]/alturaflash[i]);
        sigmacavidad[i] = k*pow(epsiloncavidad[i],n);
        sigmaflash[i] = k*pow(epsilonflash[i],n);
        
        if (tipo[i]==1) {
            sigmaep[i] = (2.0/sqrt(3.0))*sigmaflash[i]*(1.0+mfriccion[i]*anchoflash[i]/alturaflash[i]);
            fuerzacp[i] = (sigmaep[i]+largocavidad[i]/(2.0*alturacavidad[i])*mfriccion[i]/sqrt(3.0)*sigmacavidad[i])*largocavidad[i];
            fuerzafp[i] = (2.0/sqrt(3.0))*anchoflash[i]*sigmaflash[i]*(2.0+mfriccion[i]*anchoflash[i]/alturaflash[i]);
            fuerzasp[i] = fuerzafp[i]+fuerzacp[i];
            fuerzatotalsp = fuerzatotalsp + fuerzasp[i];
            
            
            cout<<"fuerza de seccion "<<numerobloque<<" "<<fuerzatotalsp<<endl;
            
        } else {
            Rmayus[i] = radiocavidad[i] + anchoflash[i];
            sigmaea[i] = (2.0/sqrt(3.0)*mfriccion[i]*anchoflash[i]/alturaflash[i]+1)*sigmaflash[i];
            fuerzaca[i] = 2.0*PI*pow(radiocavidad[i],2.0)*((mfriccion[i]*sigmacavidad[i]*radiocavidad[i])/(sqrt(3.0)*3.0*alturacavidad[i])+sigmaea[i]/2.0);
            fuerzafa[i] = 2.0*PI*sigmaflash[i]*((-2.0*mfriccion[i]/(3.0*sqrt(3.0)*alturaflash[i]))*(pow(Rmayus[i],3.0)-pow(radiocavidad[i],3.0))+(1.0+2.0*mfriccion[i]/sqrt(3.0)*Rmayus[i]/alturaflash[i])*((pow(Rmayus[i],2.0)-pow(radiocavidad[i],2.0))/2.0));
            fuerzasa[i] = fuerzaca[i] + fuerzafa[i];
            fuerzatotalsa = fuerzatotalsa + fuerzasa[i];
            
            
            cout<<"fuerza de seccion "<<numerobloque<<" "<<fuerzatotalsa<<endl;
            //cout<<"R "<<Rmayus<<endl;
            //cout<<"sigmaflash: "<<sigmaflash[i]<<endl;
            //cout<<"sigma ea"<<sigmaea[i]<<endl;
        }

        numerobloque=numerobloque+1;
        cout<<"esfuerzo de flujo: "<<sigmacavidad[i]<<endl;
        //cout<<"esfuerzo flash"<<sigmaflash[i]<<endl;
        //cout<<"i"<<i<<endl;
        //cout<<sigmaea[i]<<endl;
        //cout<<sigmaflash[i]<<endl;

    }
    
    fuerzatotal = (fuerzatotalsa + fuerzatotalsp)*pow(2204.62262,-1.0);
    cout<<"Fuerza total: "<<(fuerzatotalsa + fuerzatotalsp)<<endl;
    cout<<" "<<endl;
    cout<<"Fuerza requerida es de: "<<fuerzatotal<<" toneladas"<<endl;

    cout<<" "<<endl;
    
    double x = fuerzatotal/capacidadprensa * 100;
    cout<<" "<<endl;
    
    if (0<x<40) {
        cout<<"La prensa usara un "<<x<<"% de su capacidad. ";
        cout<<"Se cobrara una tarifa A. (La mas baja).";
    } else {
        if (40<x<60) {
            cout<<"La prensa usara un "<<x<<"% de su capacidad.";
            cout<<"Se cobrara una tarifa B.";
        } else {
            if (60<x<80) {
                cout<<"La prensa usara un "<<x<<"% de su capacidad.";
                cout<<"Se cobrara una tarifa C.";
            } else {
                if (80<x<100) {
                    cout<<"La prensa usara un "<<x<<"% de su capacidad.";
                    cout<<"Se cobrara una tarifa D.";
                } else {
                    cout<<"No se puede forjar la pieza con el equipo actual.";
                }
            }
        }
    }

    cin>>xxx;
}



