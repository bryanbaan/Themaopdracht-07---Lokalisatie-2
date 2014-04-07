How to run this project in Visual Studio:

This program makes use of the corona library to open, create and save images. Therefore its required to set the 
Includes and Libraries correctly in the project properties. The project can be opened by opening "THO7 Practicum week 2.sln"

1.Right click on the project in visual studio
2. Go to: configuration properties > VC++ directories
3. edit the include directories to the include directory in the corona folder.
4. edit the library directories to the lib folder in the corona folder.
5. Go to: Linker > input
6. edit the Additional dependencies and add the lib file from the lib folder inside corona to the list

In test.cpp the functions made in the median class can be tested. Make sure you refer to the correct image-path.
Ive also added a timer library that can be used to time whatever you want (by default it will output the time that it takes
to run the function that is responsible for applying the median filter.

The pictures will be saved to the project directory by default.

Now the program should run

Good luck!