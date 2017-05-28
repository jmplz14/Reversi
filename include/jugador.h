#include "tablero.h"
class Jugador{
	private:
		char nombre[50];
		int puntos, turno, p_ganadas;
	
		void dialogoEscoger(std::istream& is, std::ostream& os, Tablero& tablero);
	public:
		Jugador(const char datos[], int ficha);
		int getPuntos() const;
		int getTurno() const;
		void sumarPuntuacion(const Tablero& tablero);
		void cambiarNombre(const char datos[]);
		const char* getNombre() const;
		void escogerPosicion(std::istream& is, std::ostream& os, Tablero &tablero);
		
};