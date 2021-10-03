# Práctica 2

### Dispositivos loop

En sistemas operativos Unix-like, un loop device, vnd (vnode disk) o lofi (loop file interface) es un dispositivo virtual que hace que se pueda acceder a un fichero como un dispositivo de bloques.

Antes de su uso, se tiene que conectar el loop device a un archivo existente en el sistema de ficheros. Esta asociación proporciona al usuario una interfaz que permite que se use el archivo como un dispositivo de bloque. Por tanto, si el fichero contiene todo un sistema de archivos, este puede ser montado como si fuera un disco.

Este tipo de archivos se usan a veces para almacenar imágenes ISO de discos y disquetes. Montar un archivo que contiene un sistema de archivos en un loop device hace que se pueda acceder a los archivos de ese sistema de ficheros. Aparecen en el directorio del punto de montaje.

### 1. Creando dispositivos virtuales loop

    mknod /dev/loop? {b|c} major minor
    b: block device
    c: character device
    major: major number of the device file
    minor: minor number of the device file
  
### 2. Creando un archivo de 20 MB y otro de 30MB en el sistema de archivos

    dd if=/dev/zero of=/root/archivo_SA?0 bs=2k count=10000
    dd: dataset definition
    if: origen (input file)
    /dev/zero : es una partición vacía por defecto
    of: output file
    bs: block size

### 3. Asociamos los dispositivos virtuales a los archivos que describirán la partición

    losetup /dev/loop?/archivo_SA?0

### 4. Comprobamos las tablas de particiones

    fdisk -l 

### 5. Creando una partición

    fdisk /dev/loop0
    ...
 
### 6. Creando un sistema de archivos

    makefs -t "tipo_de_sistema" /dev/loop0p1
    
### 7. Comprobaciones tune2fs

    tune2fs -l dispositivo: muestra por pantalla el contenido del superbloque
    tune2fs -c max-mount-counts dispositivo: establece el numero de montajes máximos sin que se realice una comprobación del dispositivo
    tune2fs -L label dispositivo: pone una etiqueta al sistema de archivos
    
### 8. Archivo fstab

  Cuando tenemos un dispositivo, para usarlo debemos montarlo con la orden mount
    
    mount device
    
  Para configurar automáticamente el punto de montaje y el sistema de archivos de un dispositivo para que esté listo cuando se use el mount hay que editar 
  /etc/fstab. Que tiene el siguiente formato:
  
  
  
  
  
