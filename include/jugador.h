#include "tablero.h"
class Jugador{
	private:
		char nombre[50];
		int puntos, turno, p_ganadas;
	
		void dialogoEscoger();
	public:
		Jugador(const char datos[], int ficha);
		int getPuntos() const;
		int getTurno() const;
		void sumarPuntuacion(const Tablero& tablero);
		void cambiarNombre(char datos[]);
		const char* getNombre();
		void escogerPosicion(std::istream& is, std::ostream os, Tablero& tablero);
};