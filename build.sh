make -f Makefile.vita
echo destroy | nc 192.168.0.106 1338
echo "Uploading binary to PSVita..."
curl --ftp-method nocwd -T eboot.bin ftp://192.168.0.106:1337/ux0:/app/VITAGL005/ > /dev/null 2>&1
echo launch VITAGL005 | nc 192.168.0.106 1338
