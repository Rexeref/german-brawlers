clear

echo ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ LINUX

gcc -Wall -I head/ -o bin/german-brawlers.bin src/gameFunctions.c src/linux/linuxFunctions.c src/fightAbilities.c src/main.c

echo ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ WINDOWS

x86_64-w64-mingw32-gcc -Wall -I head/ -o bin/german-brawlers.exe src/gameFunctions.c src/windows/windowsFunctions.c src/fightAbilities.c src/main.c
