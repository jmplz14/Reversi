#include "matriz.h"
#include <assert.h>

Matriz::Matriz(){
	anadirDatos(0,0);
}

Matriz::Matriz(int n){
	anadirDatos(n,n);
}

Matriz::Matriz(int fils, int cols){
	anadirDatos(fils,cols);
}
void Matriz::anadirDatos(int fils, int cols){
	assert( fils >= 0 && cols >= 0);
	if(fils == 0 || cols == 0){
		matriz=0;
	}else{
		
		matriz = new int [fils * cols];
	}
	n_fils = fils;
	n_cols = cols;
}
Matriz::~Matriz(){
	delete [] matriz;
}
Matriz& Matriz::operator=(const Matriz& m){
	if(this!=&m){
		delete[] this->matriz;
		if(m.matriz == 0){
			this->n_fils = this->n_cols = 0;
			this-> matriz = 0;
		}else{
			this->n_fils = m.n_fils;
			this->n_cols = m.n_cols;
			this->matriz = new int[this->n_fils * this->n_cols];		
			int total=this->n_fils * this->n_cols;
			for(int i = 0; i < total; i++)
				this->matriz[i] = m.matriz[i];
		}
	}
		
}
Matriz::Matriz(const Matriz& m){
	if (m.matriz == 0 ){
		this->n_fils = this->n_cols = 0;
		this-> matriz = 0;
	}else{
		this->n_fils = m.n_fils;
		this->n_cols = m.n_cols;
		this->matriz = new int[this->n_fils * this->n_cols];		
		int total=this->n_fils * this->n_cols;
		for(int i = 0; i < total; i++)
			this->matriz[i] = m.matriz[i];
	}
}

int Matriz::getFils() const{
	return n_fils;
	
}

int Matriz::getCols() const{	
	return n_cols;	
}

void Matriz::setPosition(int fils, int cols, int n){
	assert( (fils >= 0 && fils < n_fils ) && (cols >= 0 && cols < n_cols) );
	matriz[fils * n_cols + cols] = n;
}
int Matriz::getPosition(int fils, int cols) const{
	assert( (fils >= 0 && fils < n_fils ) && (cols >= 0 && cols < n_cols) );
	return matriz[fils * n_cols + cols];
}























