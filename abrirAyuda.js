const { exec } = require('child_process');

// Corregir la ruta con dobles barras invertidas y el nombre correcto del archivo
const rutaChm = 'C:\\Users\\anatu\\Documents\\Estructuras\\Proyecto Version 1.4\\Proyecto-Banco-Estructuras-Parcial-1\\ayuda.chm';

exec(`start "" "${rutaChm}"`, (error) => {
  if (error) {
    console.error('No se pudo abrir el archivo CHM:', error);
  } else {
    console.log('Archivo CHM abierto correctamente.');
  }
});
