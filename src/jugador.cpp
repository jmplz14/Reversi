#include "tablero.h"
#include "jugador.h"
#include <assert.h>
#include <limits>
Jugador::Jugador(const char datos[], int ficha) {
	assert( (ficha == 1 || ficha == 2) );
	nombre = 0;
	cambiarNombre(datos);
	p_ganadas = 0;
	puntos = 0;
	turno = ficha;
}
Jugador::~Jugador(){
	delete [] nombre;
	nombre = 0; 
}
void Jugador::sumarPuntuacion(const Tablero& tablero){
	int puntuacion = tablero.obtenerPuntuacion(turno) ,  ganador =tablero.obtenerGanador() ;
	puntos += puntuacion;
	p_ganadas = ganador == turno ? p_ganadas + 1 : p_ganadas;
	
}
int Jugador::getGanadas() const{
	return p_ganadas;
}
int Jugador::getPuntos() const{
	return puntos;
}
int Jugador::getTurno() const{
	return turno;
}
Jugador::Jugador(const Jugador& j){
	//como el jugador nunca puede tener a 0 el nombre como minimo tendra un char de una poscion con \0
	//no tenemos que comprobar que nombre = 0
	this->turno = j.turno;
	this->puntos = j.puntos;
	this->p_ganadas = j.p_ganadas;
	this->nombre = 0;
	this->cambiarNombre(j.nombre); 
}
void Jugador::cambiarNombre(const char datos[]){
	//Si se le pasa un nombre sin ningun caracter simplemente crea un 
	//array c de tamano vacio y con esto no obligamos a tener que comprobar que 
	//lo meta vacio
	int cont = 0;
	int tamano = 0;
	
	while (datos[tamano] != '\0')
		tamano++;
	
	//Se le suma uno para obtener el tamaño puesto que lo que se tiene es la ultima posicion
		tamano++;
		   
		delete [] nombre;
		nombre = new char [tamano];		   
		
		while (cont < tamano){
			nombre[cont] = datos[cont];
			cont++;	
		}
}

Jugador& Jugador::operator=(const Jugador& j){
	if (this != &j){
		this->turno = j.turno;
		this->puntos = j.puntos;
		this->p_ganadas = j.p_ganadas;
		this->nombre = 0;
		this->cambiarNombre(j.nombre); 
	}
}

const char* Jugador::getNombre() const{
	//const char* inicio = nombre;
	return nombre;
}
//no se hace funcion bool porque esta funcion entra en bucle siempre que la posicion insertada se erronea de modo que nunca
//se tendra una posicion invalida introducida por el usuario al final de la funcion ni tendremos ningun tipo de error
bool Jugador::escogerPosicion(std::istream& is, std::ostream& os, Tablero& tablero) const {
	assert ( !tablero.estadoTablero() && tablero.turnoActual() == turno );
	//no tengo que hacer comprobacion de si se hay una posicion libre en la que poder colocar
	//la ficha porque si nuestra clase tablero si no puediera mover ningun jugador finalizacia el tablero
	int cols = tablero.getCols(); 
	int fils = tablero.getFils();
	int fil_valida, numero_posibilidades = 0;
	char col_valida = 'a',col_cont = 'a';
	
	bool encontrada,parada = false;
	
	for (int i = 0 ; i < fils && numero_posibilidades < 2; i++){
		for(int j = 0; j < cols && numero_posibilidades < 2 ; j++){
			col_cont += j;
			encontrada=tablero.consultarPosicion(col_cont, i);
			if (encontrada){
				fil_valida = i;
				col_valida = col_cont;
				numero_posibilidades++;
			}
			col_cont = 'a';
		}
	}
	//como minimo siempre tedremos un movimiento puesto que sino nuestra clase tablero no lo pondria como turno actual y 		pasaria al otro jugador.
	if (numero_posibilidades == 1){
		tablero.colocarFicha(col_valida, fil_valida);
		os << nombre << ", solo tenia un movimiento valido("<< col_valida << fil_valida <<")";
	}else{
		parada=dialogoEscoger(is, os, tablero);
			
	}
	tablero.escribir(os);
	if ( !parada && !tablero.estadoTablero() && tablero.turnoActual() == turno){
		if (turno == 1 ){
			os << "Jugador 2 no tiene posibilidad de movimientos tiene que pasar turno." << std::endl; 
		}else{
			os << "Jugador 1 no tiene posibilidad de movimientos tiene que pasar turno." << std::endl; 		
		}
	}
	return parada;
}
void Jugador::limpiarEntrada(std::istream& is) const {
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

bool Jugador::dialogoEscoger(std::istream& is,std::ostream& os, Tablero& tablero) const{
	bool estado, parada = false;
	int fil;
	char col_max = 'a',col;
	col_max += tablero.getCols()-1; 
	os << std::endl << getNombre() << ", escoja una columan (letra a-" << col_max << ") y una fila (0-" << tablero.getFils()-1 << "): ";
	is >> col;
	if(is && col == '!'){
		parada = true;
	}else{
		is >> fil;
		if(is){
			estado = tablero.consultarPosicion(col,fil);
		}else{
			estado = false;
			limpiarEntrada(is);
		}
		while (!estado && !parada ){
			os << "Introduza una posicion valida: ";
			is >> col;
			if (is && col == '!'){
				parada = true;
			}else{
				is >> fil;
				if (is){
					estado = tablero.consultarPosicion(col,fil);			
				}else{
					estado=false;
					limpiarEntrada(is);
				}
			}
		}	
	}
	// limpiamos la entrada para que en caso de que el jugador metiera una doble posicion no se guradara para el sigueinte 
	//turno y pudiera colocar una ficha en el turno del siguiente jugador;
	//con doble posicion me refiero a por ejemplo que ponga en la entrada a1b3 por lo cual en su turno se usaria la poscion a1
	//y en el siguiente se usaria la posicion b3
	//no lo hago con el is.eof() porque eso obliga a tener que introducir un ctrl+d al usuario al meter la posicion
	limpiarEntrada(is);
	if (!parada){	
		tablero.colocarFicha(col, fil);
	}
	return parada;
}
void Jugador::setTurno(int n){
	assert( n == 1 || n == 2);
	turno = n;
}
void Jugador::setPuntos(int n){
	puntos = n;
}
void Jugador::setGanadas(int n){
	p_ganadas = n;
}	
std::ostream& operator<< (std::ostream& os, const Jugador& j){	
	os <<"!" << j.nombre << std::endl << j.turno << " " << j.p_ganadas << " " << j.puntos << std::endl;
	return os;
}			
std::istream& operator>> (std::istream& is, Jugador& j){
	char nombre[1024],inicio;
	int turno,puntos,ganadas;
	is >> inicio;
	while (inicio != '!'){
		is.ignore(1024,'\n');
		is >> inicio;
	}
	if(inicio == '!'){
		is.getline(nombre,1024,'\n');
		std::cout << nombre << std::endl;
		is >> turno;
		std::cout << turno << std::endl;
		
		Jugador jugador(nombre,turno);		
		is >> ganadas;
		is >> puntos;
		jugador.setPuntos(puntos);
		jugador.setGanadas(ganadas);
		j=jugador;
	}
	

	
	return is;
}

			
			
			
			
			

