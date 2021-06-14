#include <global.hh>
#include <Timing.hpp>
#include <iostream>
#include <random>
#include <iomanip>
#include <stdio.h>
#include <cstdlib>




bool* get_vecinos(int x, int y, int fil, int col){
	bool* vecinosB=new bool[8];
	int vecinos[8][2]={{x-1,y-1},{x,y-1},{x+1,y-1},{x-1,y},{x+1,y},{x-1,y+1},{x,y+1},{x+1,y+1}};
	for (int i=7 ; i>=0 ; i--){
		if(vecinos[i][0]<0 || vecinos[i][0]>(col-1) || vecinos[i][1]<0 || vecinos[i][1]>(fil-1)){
			vecinosB[i]=false;
		}else{
			vecinosB[i]=true;
		}
	}
	return vecinosB;
}

float generar_numero(){
    return (float)(rand())/RAND_MAX;
}

void mostrar(char **matriz, int fil, int col){
    for(int i=0;i< fil;i++){
        for(int j=0;j< col;j++){
            std::cout<<matriz[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout << std::endl;
}

char** generar_vacia(int fil, int col){
	char** matriz = new char*[fil];
    for (int i=0 ; i<fil ; i++){
    	matriz[i] = new char[col];
        for (int j=0 ; j<col ; j++){
            matriz[i][j]='#';
        }
    }
    return matriz;
}

char** stepP(char **matriz, int fil, int col, int32_t nt){
    char** vacia=generar_vacia(fil,col);
    for (int i=0 ;  i<fil ; i++){
    	#pragma omp parallel for num_threads(nt)
    	for (int j=0 ; j<col ; j++){
    		int cont=0;
    		int vecinos[8][2]={{i-1,j-1},{i,j-1},{i+1,j-1},{i-1,j},{i+1,j},{i-1,j+1},{i,j+1},{i+1,j+1}};
    		bool* vecinosB=get_vecinos(i,j,fil,col);
    		for (int k=0; k<8 ; k++){
    			if(vecinosB[k]){
    				if(matriz[vecinos[k][0]][vecinos[k][1]]=='*'){
    					cont=cont+1;
    				}
    			}
    		}
    		if(matriz[i][j]=='#' && cont==3){

    			vacia[i][j]='*';
    		}else if(matriz[i][j]=='*' && (cont==2 || cont==3)){
    			vacia[i][j]='*';
    		}else{
    			vacia[i][j]='#';
    		}

    	}
    }
    return vacia;
}

char** stepS(char **matriz, int fil, int col){
    char** vacia=generar_vacia(fil,col);
    for (int i=0 ;  i<fil ; i++){
    	for (int j=0 ; j<col ; j++){
    		int cont=0;
    		int vecinos[8][2]={{i-1,j-1},{i,j-1},{i+1,j-1},{i-1,j},{i+1,j},{i-1,j+1},{i,j+1},{i+1,j+1}};
    		bool* vecinosB=get_vecinos(i,j,fil,col);
    		for (int k=0; k<8 ; k++){
    			if(vecinosB[k]){
    				if(matriz[vecinos[k][0]][vecinos[k][1]]=='*'){
    					cont=cont+1;
    				}
    			}
    		}
			if(matriz[i][j]=='#' && cont==3){
    			vacia[i][j]='*';
    		}else if(matriz[i][j]=='*' && (cont==2 || cont==3)){
    			vacia[i][j]='*';
    		}else{
    			vacia[i][j]='#';
    		}
    		

    	}
    }
    return vacia;
}

int main(int argc , char *argv []){
    int col=5;
    int fil=5;
    float prob=0.8;
    int32_t nt=omp_get_max_threads();
	bool seq=false;
	bool show=false;
	int iter=10;

	std::string mystr;
	for (int i=0; i < argc; i++) {
		mystr=argv[i];
		if (mystr == "-ncol") {
			col = atoi(argv[i+1]);
		}
		if (mystr == "-nfil") {
			fil = atoi(argv[i+1]);
		}
		if (mystr == "-nt") {
			nt = atoi(argv[i+1]);
		}
		if (mystr == "-plive") {
			prob = atoi(argv[i+1]);
		}
		if (mystr == "-seq") {
			seq = true;
		}
		if (mystr == "-show") {
			show = true;
		}
		if (mystr == "-iter") {
			iter = atoi(argv[i+1]);
		}
	}


    char** matriz = new char*[fil];
    for (int i=0 ; i<fil ; i++){
    	matriz[i] = new char[col];
        for (int j=0 ; j<col ; j++){
            if(prob>=generar_numero()){
                matriz[i][j]='*';
            }else{
               	matriz[i][j]='#';
            }
        }
    }
    if(show){
		mostrar(matriz,fil,col);
	}
	Timer t1;
	double time=0;
    for (int i=0 ; i<iter ; i++){
		t1.start();
    	if(seq){
    		matriz=stepS(matriz,fil,col);
    	}else{
    		matriz=stepP(matriz,fil,col,nt);
    	}
    	t1.stop();
    	time=time+t1.elapsed<std::chrono::milliseconds>();
		if(show){
			mostrar(matriz,fil,col);
		}
    	
    }
    std::cout << "elapsed:" << time << "ms\n";
    std::cout << "elapsed everage per iteration:" << time/iter << "ms\n";
    

    return (EXIT_SUCCESS);
}



/*
int main(int argc , char *argv []) {
	std::random_device dev;  
	
	//Por omisión, se paraleliza con la capacidad del HW
	int32_t nt    = omp_get_max_threads();
	int32_t aSize = 20;
	std::cout << nt << std::endl;
	///////////////////////////////////////
	//  Read command-line parameters
	std::string mystr;
	for (size_t i=0; i < argc; i++) {
		mystr=argv[i];
		if (mystr == "-nt") {
			nt = atoi(argv[i+1]);
		}
		if (mystr == "-asize") {
			aSize = atoi(argv[i+1]);
		}
	}
	
	auto datos = new uint32_t[aSize];

	std::mt19937 gen(dev()); 
	std::uniform_int_distribution<> unif(0, 10000);

	//LLenar vector con algo...
	Timer t1;
	
	t1.start();
	#pragma omp parallel for num_threads(nt)
	for(size_t i = 0; i < aSize; ++i){	
		datos[i] = unif(gen);
		
		int32_t thID = omp_get_thread_num();
		#pragma omp critical
		{
			std::cout << "thID:" << thID << ", dato[" << i << "]="<< datos[i] << std::endl;
		}
	}
	t1.stop();
	
	std::cout << "elapsed:" <<  t1.elapsed<std::chrono::milliseconds>() << "ms\n";
	
	
	
	return(EXIT_SUCCESS);
}*/
