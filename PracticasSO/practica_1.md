# Práctica 1

#### 0. Arrancar maquina virtual de fedora
    ./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m

#### 1. Obtención de permisos de root en máquina virtual 
    #!/bin/bash
    cd /etc && ./kernel32-3.0.4  ubda=./Fedora14-x86-root_fs mem=1024m

#### 2. Administración de usuarios y grupos
    Archivos que especifican contraseñas, grupos y usuarios:
    - /etc/passwd :  guarda infomacion de los users
    - /etc/shadow : guarda las contraseñas encriptadas
    - /etc/group : definicion de los grupos y sus miembros
#### Órdenes para gestionar cuentas de usuario ##### 
    
    useradd: crea un nuevo usuario
        -g: especifica grupo
        -G: especifica varios grupos
        -M: crea un usuario pero sin el home
    usermod: modificacion de usuario
    userdel: eliminar usuario
    newusers: crea cuentas de usuario utilizando archivos escritos en formato de /etc/passwd
    system-config-users: herramienta gráfica

#### Archivos de configuración para el shell de bash

    .bash_profile: se ejecuta al hacer el login y en él podemos indicar alias, variables, configuración del entorno...
    .bashrc: su contenido se ejecuta cada vez que se ejecuta la consola en este archivo de indican los programas o scripts a ejecutar
    .bash_logout: se ejecuta cuando ceerramos sesión. En él podemos especificar scripts, programas y acciones que deseemos ejecutar al cerrar sesión.

##### Usuarios especiales del sistema

    - root: administrador
    - bin,daemon, lp,sync, shutdown... : para poseer y ejecutar servicios
    - mail, news, ftp... : herramientas y utilidades
    - mysql, xfs... : para ejecutar los servicios en cuestión
    - nobody o nfsnobody: usada por NFS y otras utilidades

### 3.Gestión de grupos

    groupadd nombre_grupo: añade un grupo
    groupmod nombre_grupo: modifica un grupo existente
        -Ej: groupmod -n nombreactual nuevonombre
    groupdel nombre_grupo: elimina un grupo
    newgrp nombre_grupo: cambia de grupo activo
    gpasswd nombre_grupo: añade una contraseña a un grupo
        -a: añade un usuario al gruo en cuestión
    groups nombre_usuario: informa de los grupos
    id user: muestra el numero identificador del usuario
    grpck: determina la consistncia del archivo de grupos

##### Grupos especiales

    root,sys, bin,daemon, adm... :  preconfigurados por UNIX. Los GIDs inferiores a 500 estánreservados para estos grupos
    tty, dialout, cdroom... : grupo para dispositivos
    kernel: usuarios que pueden leer la memoria del kernel
    users: para usuarios normales

### 4. tipos de archivos linux

    /bin: programas de utilidad utilizados por cualquierusuario del sistema
    /sbin: programas de utilidad usados por el root
    /boot: archivos fundamentales para que funcione el boot loader
    /dev: archivos especiales de dispositivo
    /etc: archivos de configuración del sistema
    /home: directorio personal
    /lib: bibliotecas que necesitan los programas alojados en bin y sbin
    /media:punto de montaje para dispositivos extraibles
    /mnt: putto de montaje para dispositivos de manera temporal
    /opt: se ubican los programas que no pertenecen a la distribución
    /proc: sistema de archivos virtual que hace de interfaz entre los procesos y los nucleos del procesador
    /tmp: archivos temporales
    /usr: programas y ejecutables del usuario
    /var: donde se guardan los servicios tipo mysql, apache...
    
### 5. sistema de archivos

    /etc/fstab: file systems table, muestra las particiones y sus sistemas de archivos
    /etc/mtab: lista los sistemas de archivos ya montados
    /proc/filesystems: muestran los tipos de sistemas de archivos existentes
    /proc/mounts: sistemas de archivos que están monttados actualmente

### 6. orden chage

    chage -d ultimo_dia usuario: establece la fecha del último cambio de contraseña
    chage -m min_dias usuario: numero de días mínimo para que el usuario cambie la contraseña
    chage -M max_dias usuario: nº de días máximo que puede mantener la contraseña
    chage -W warn_dias usuario: establece un aviso $warn_dias antes para que el usuario cambie la contraseña
    chage -I inac_dias usuario: numero de días en el que la cuenta se inhabilitará de no haberse cambiado la contraseña
    chage -E exp_días usuario : fecha en el que la cuenta expira y se deshabilita de forma automática
    
    
    
    
    
    
    
    






