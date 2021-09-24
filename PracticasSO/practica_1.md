# Práctica 1

#### 1. Obtención de permisos de root en máquina virtual 
    #!/bin/bash
    cd /etc && ./kernel32-3.0.4  ubda=./Fedora14-x86-root_fs mem=1024m

#### 2. Administración de usuarios y grupos
    Archivos que especifican contraseñas, grupos y usuarios:
    - /etc/passwd :  guarda infomacion de los users
    - /etc/shadow : guarda las contraseñas encriptadas
    - /etc/group : definicion de los grupos y sus miembros
#### Órdenes para gestionar cuentas de usuario ##### 
    
    usermod: modificacion de usuario
    userdel: eliminar usuario
    newusers: crea cuentas de usuario utilizando archivos escritos en formato de /etc/passwd
    system-config-users: herramienta gráfica

#### Archivos de configuración para el shell de bash

    .bash_profile: se ejecuta al hacer el login y en él podemos indicar alias, variables, configuración del entorno...
    .bashrc: su contenido se ejecuta cada vez que se ejecuta la consola en este archivo de indican los programas o scripts a ejecutar
