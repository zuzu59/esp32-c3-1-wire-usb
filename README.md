# esp32-c3-1-wire-usb
Mesure simplement la température avec des sondes 1-wire et l'affiche sur la console série

zf241017.1553


## Buts
Mesure simplement la température avec des sondes 1-wire et l'affiche sur la console série.


## Problématique
Le système de domotique utilisé (Siemens) pour commander le système de chauffage n'a que des entrées USB, il faut donc envoyer la température sur le port USB.


## Moyens
Pour cela on va utiliser un MCU esp32-c3 super mini, sans la partie WIFI (en mode Arduino), pour lire des sondes de températures 1-wire DS18B20 et sortir sur le port USB les valeurs des sondes.


### Câblage des sondes de température
L'avantage de travailler avec des sondes de température 1-wire DS18B20, non seulement elles sont très précises, mais en plus elles sont toutes branchées sur un bus un fil (1-wire).<br>
Elles possèdent donc chacune une adresse afin de les différencier et il est très facile de les lire une après l'autre.<br>
On peut en mettre quasiment autant que l'on veut sur seulement qu'un port du MCU.


### Format de sortie
Le format de sortie est le suivant, par exemple pour quatre sondes de température:

````
sensor0:22.94,sensor1:23.62,sensor2:23.12,sensor3:22.81,
````


### Moyen de tester
Le port USB du MCU est vu comme une interface série à 19'200Bds, il faut donc un émulateur de terminal série pour le tester, comme par exemple **screen** sur Linux. <br>
Par exemple sur mon MAC je fais:
````
screen /dev/cu.usbmodem142301 19200
````

Quand j'ai terminé, je sors avec CTRL+A suivi de la touche 'k'


### Comment lister les devices USB (lsusb) ?
Sous LINUX la commande lsusb permet de lister les devices USB, sur MAC OS X il faut faire ceci:
````
system_profiler SPUSBDataType
````

Enlever la clef
````
system_profiler SPUSBDataType > t1
````

Remettre la clef
````
system_profiler SPUSBDataType > t2
diff t1 t2
````

On peut après quand on est certain que la machine **voit** le MCU faire un:
````
ls -al /dev |grep -i usb
````


## Installation
Pour flasher le MCU esp32-c3 super mini on utilise Arduino IDE !

Simplement charger le projet dans l'IDE Arduino et installer, si necéssaire, les libs pour le 1-wire.

ATTENTION, pour pouvoir le flasher il faut le mettre en mode flashing en appuyant sur le petit bouton **boot** et tout en le laissant appuyer un petit coup le bouton **reset**. Après le flashing, il faut redonner un petit coup sur le bouton **reset**


## Sources
https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/<br>


