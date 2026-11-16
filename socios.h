#ifndef SOCIOS_H
#define SOCIOS_H

void limpiarBuffer();
void inicializarUsuarioAdmin();
int existeDni(const char dniBuscado[]);
void registrarSocio();
void listarSocios();
void buscarSocioPorId();
void buscarSocioPorDni();
void modificarSocio();
void cambiarEstadoSocio();
int iniciarSesion(char nombreLogueado[]);
void verMisDatos(const char nombreLogueado[]);

#endif
