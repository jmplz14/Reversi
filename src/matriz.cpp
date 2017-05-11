#include "matriz.h"
#include <assert.h>
void Matriz::setFils( int n){
	assert( n < 0 || n > 10);
	n_fils = n;
}
void Matriz::setCols( int n){
	assert( n < 0 || n > 10);
	n_cols = n;
}

Matriz::Matriz(){
	n_cols = 0;
	n_fils = 0;
}

Matriz::Matriz(int n){
	Matriz::setFils(n);
	Matriz::setCols(n);
}

Matriz::Matriz(int fils, int cols){
	Matriz::setFils(fils);
	Matriz::setCols(cols);
}

int Matriz::getFils() const{
	return n_fils;
}

int Matriz::getCols() const{	
	return n_cols;	
}

void Matriz::setPosition(int fils, int cols, int n){
	assert( fils < 0 || fils >= n_fils || cols < 0 || cols >= n_cols);
	matriz[fils][cols] = n;
}
int Matriz::getPosition(int fils, int cols) const{
	assert( fils < 0 || fils >= n_fils || cols < 0 || cols >= n_cols);
	return matriz[fils][cols];
}























