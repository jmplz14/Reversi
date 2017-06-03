#ifndef _MATRIZ_H
#define _MATRIZ_H 
#include <iostream>
class Matriz{
	private:
		int* matriz;
		int n_cols, n_fils;
		void reservarTamano();
		void anadirDatos(int fils , int cols);

	public:
		Matriz(); 
		Matriz(int n);
		Matriz(int fils, int cols);
		Matriz(const Matriz& m);
		~Matriz();
		friend std::ostream& operator<< (std::ostream& os, const Matriz& m);
		friend std::istream& operator>> (std::istream& is, Matriz& m);
		Matriz& operator=(const Matriz& m);
		int getFils() const;
		int getCols() const;
		int getPosition(int fils, int cols) const;
		void setPosition(int fils, int cols, int n);
		
		


};
#endif