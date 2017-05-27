#ifndef _TABLERO_H
#define _TABLERO_H 
#include "matriz.h"
class Tablero{
	private:
		Matriz matriz;
		bool finalizado;
		bool turno_J1;
		int n_fichas, n_fichas_colocadas;
		int transformarCharCol( char col) const;
		bool comprobarLineas(int fil , int col , int ficha) const;
		// a esta funcion se le pasa la fil y la columna aparte de lo valores que vamos a ir sumando
		// estas para ir recorriendo el vector y ver si es una linea valida
		bool recorrerMatrizCompro (int fil , int i_fils, int col , int i_cols, int ficha ) const;
		// devuelve true si las coordenas estan dentro del tablero falso en caso contrario
		bool comprobarCoordenadas(int fil , int col) const;
		// comprobar ficha opuesta devuelve true si la ficha no es ella misma 
		// ejemplo: si ficha es 1 devolvera falso si se envia un 2 o un 0
		bool comprobarFichaOpuesta(int ficha , int posicion) const;
		// Inf = inferior Sup = superor Der = derecha Izq=izquierda Dia=diagonal Rec=recta
		bool comprobarDiaSupIzq(int fil , int col, int ficha) const;
		bool comprobarDiaSupDer(int fil , int col, int ficha) const;
		bool comprobarDiaInfIzq(int fil , int col, int ficha) const;
		bool comprobarDiaInfDer(int fil , int col, int ficha) const;
		bool comprobarRecIzq(int fil , int col, int ficha) const;
		bool comprobarRecDer(int fil , int col , int ficha) const;
		bool comprobarRecSup(int fil , int col , int ficha) const;
		bool comprobarRecInf(int fil , int col , int ficha) const;
	public:
		Tablero();
		Tablero(int fils);
		Tablero(int fils, int cols);
		int getFils() const;
		int getCols() const;
		int getPosicion(char col, int fil) const;
		int turnoActual() const;
		bool estadoTablero() const;
		int obtenerGanador() const;
		int obtenerPuntuacion(int jugador) const;
		bool consultarPosicion(char col, int fil) const;
		bool posibilidadMovimiento(int jugador) const;
		bool colocarFicha(char col, int fil);
		void vaciarTablero();
	




};
#endif