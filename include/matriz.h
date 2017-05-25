#ifndef _MATRIZ_H
#define _MATRIZ_H 
class Matriz{
	private:
		int matriz[10][10];
		int n_cols, n_fils;
	
	public:
		Matriz(); 
		Matriz(int n);
		Matriz(int fils, int cols);
		int getFils() const;
		void setFils(int n);
		int getCols() const;
		void setCols(int n);
		int getPosition(int fils, int cols) const;
		void setPosition(int fils, int cols, int n);
		
		


};
#endif