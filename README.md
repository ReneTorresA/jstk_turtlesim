
# ROS Arduino Application README
## Descripción
Este proyecto es una aplicación de ROS que utiliza un módulo de Joystick junto con Arduino para controlar el movimiento de la tortuga de turtlesim de ROS. Proporciona una comunicación entre la computadora central (PC o microcontrolador) y el Arduino a través de ROS serial.


![Aplicación ROS](/src/docs/presentacion/presentacion_latex/images/turtlesim.png)



## Requisitos
- ROS noetic http://wiki.ros.org/noetic
- Placa Arduino compatible
- Módulo de Joystick
- Librería Rosserial Arduino http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup
- Python 3 https://www.python.org/

El sistema operativo usado en este proyecto es una distribución de Linux basada en Ubuntu 20.04.


## Instalación
1. Clone el repositorio de github en la carpeta src de su espacio de trabajo de ROS. Para esto abra una terminal y ejecute el siguiente comando:


```sh
cd ~/catkin_ws/src
git clone https://github.com/ReneTorresA/jstk_turtlesim.git
```
2. Una vez clonado el repositorio se recomienda agregar el path a la terminal. Para esto ejecute el siguiente comando en la carpta del espacio de trabajo:
```sh
cd ~/catkin_ws
source devel/setup.bash 
```

3. Finalmente para ejecutar la aplicación inicie el archivo .launch del proyecto de la siguiente manera:
```sh
roslaunch jstk_turtlesim jstk_turtlesim.launch
```


## Estructura del proyecto

La estructura del proyecto es la siguiente:

    catkin_ws
    |-- CMakeLists.txt
    |-- package.xml
    |-- build
    |-- devel
    |-- src
        |-- jstk_turtlesim
            |-- src
                |-- scripts
                    |-- button_subscriber.py
                |-- launch
                    |-- jstk_turtlesim.launch
                |-- arduino
                    |-- jstk_turtlesim.ino
                |-- docs
                    |-- presentacion
                        |-- presentacion.pdf
                        |-- presentacion_latex
                    |-- tutorial
                        |-- tutorial.pdf
                        |-- tutorial_latex
                |-- CMakeLists.txt
                |-- package.xml
