# Práctica 2

## Dispositivos loop

En sistemas operativos Unix-like, un loop device, vnd (vnode disk) o lofi (loop file interface) es un dispositivo virtual que hace que se pueda acceder a un fichero como un dispositivo de bloques.

Antes de su uso, se tiene que conectar el loop device a un archivo existente en el sistema de ficheros. Esta asociación proporciona al usuario una interfaz que permite que se use el archivo como un dispositivo de bloque. Por tanto, si el fichero contiene todo un sistema de archivos, este puede ser montado como si fuera un disco.

Este tipo de archivos se usan a veces para almacenar imágenes ISO de discos y disquetes. Montar un archivo que contiene un sistema de archivos en un loop device hace que se pueda acceder a los archivos de ese sistema de ficheros. Aparecen en el directorio del punto de montaje.

### 1. Creando dispositivos virtuales loop

    mknod /dev/loop? {b|c} major minor
    b: block device
    c: character device
    major: major number of the device file => 7 (tipo bloque)
    minor: minor number of the device file => ? (nº de dispositivo loop)
  
### 2. Creando un archivo de 20 MB y otro de 30MB en el sistema de archivos

    dd if=/dev/zero of=/root/archivo_SA?0 bs=2k count=10000
    dd: dataset definition
    if: origen (input file)
    /dev/zero : es una partición vacía por defecto
    of: output file
    bs: block size

### 3. Asociamos los dispositivos virtuales a los archivos que describirán la partición

    losetup /dev/loop? /root/archivo_SA?0

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
  
    /dev/dispositivo    /mnt/puntomontaje   SA  rw|ro,user|noauto   0 0
    
## Gestores de paquetes

    yum list: lista paquetes disponibles para instalar
    yum list installed: lista paquetes instalados
    yum list updates: muestra todos los paquetes con actualizaciones disponibles
    yum install nombre_paquete: instalar un paquete
    yum update: actualiza todos los paquetes instalados
    yum remove nombre_paquete: elimina un paquete
  
### Gestor de paquetes rpm  

    rpm -i paquete: instala un paquete
    rpm -e paquete: elimina un paquete
    rpm -U paquete: actualiza un paquete y elimina el anterior
    rpm -F nombre_servidor_http/ftp: se busca el paque en un servidor y se prepara la actualizacion
    rpm -qa | grep paquete | sort: busca información de un paquete
    rpm -qi paquete: muestra información de un paquete
    rpm -V paquete: verifica la integridad de un paquete
    

## Cuotas

Existe una forma más flexible de limitar el uso de disco por parte de los usuarios del sistema. Este control se lleva a cabo mediante un sistema de
cuotas. Las cuotas de disco permiten limitar el número de recursos de un SA que va a poder utilizar un usuario. 

- Límite hard: El usuario no puede sobrepasarlo
- Límite soft:  Siempre debe configurarse como un número de recursos inferior al límite hard y se puede sobrepasar durante cierto tiempo, pero sin llegar a superar al límite hard. Transcurrido el tiempo que estipule el administrador para poder estar por encima del límite soft, el sistema de cuotas actúa como si se hubiese superado el límite hard . Este tiempo durante el cual se puede superar el límite soft se conoce con el nombre de periodo de gracia.


### 1. Sistemas de quotas para el sistema de cuotas

    -Primero editamos /etc/fstab y añadimos en en pass usrquota/grpquota para añadir la funcionalidad de cuotas a un sistema de archivos
    -Montamos de nuevo el SA mount -o remount punto_montaje
    -Creamos el archivo aquota.user para llevar el control de las cuotas en el SA: quotacheck -nm punto_montaje
    -Encendemos el sistema de quotas: quotaon -a
    -Editamos la cuota para un usuario: edquota username
    -Establecemos el límite del periodo de gracia: edquota -t username
    -Miramos las estadíasticas de las cuotas para todos los usuarios: repquota <SA>
    
    
    
    
  
