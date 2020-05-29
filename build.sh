#make -f Makefile.vita
cd build
cmake ..
make -C ../
cd ..
echo destroy | nc 192.168.0.106 1338
echo "Uploading binary to PSVita..."
curl --ftp-method nocwd -T trolletVita.self ftp://192.168.0.106:1337/ux0:/app/VEFT00001/eboot.bin > /dev/null 2>&1
echo launch VEFT00001 | nc 192.168.0.106 1338
