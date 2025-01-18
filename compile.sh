rm -rf build/*
cd build
cmake ..
bear -- make
cp umidificador_pico.uf2 /media/pedrohcs8/RPI-RP2
$shell
