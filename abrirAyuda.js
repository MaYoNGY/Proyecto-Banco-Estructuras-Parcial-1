const { exec } = require('child_process');

const rutaChm = 'C:\\Users\\camev\\Desktop\\Proyecto-Banco-Estructuras-Parcial-FINAL\\Proyecto-Banco-Estructuras-Parcial-1\\ayuda.chm';

exec(`start "" "${rutaChm}"`, (error) => {
  if (error) {
    console.error('No se pudo abrir el archivo CHM:', error);
  } else {
    console.log('Archivo CHM abierto correctamente.');
  }
});
