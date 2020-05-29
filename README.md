# trolletVita

trolletVita is a (simple) game I'm working on for PSVita.
Still working on getting the basic stuff going.

## Build instructions (GNU/Linux)
First of all, you need VitaSDK, follow the instructions on https://vitasdk.org/ 


After you've installed VitaSDK and added VITASDK to your $PATH, you need to add libvita2d. <br />
Follow the "Porting libraries" section of vitasdk.org. <br />
clone vitasdk/packages, run vita-makepkg in the libvita2d folder and install it with vdpm. <br />

Building trolletVita:

```
git clone https://github.com/burbruee/trolletVita.git
cd trolletVita
cmake .
make
```

After that you should see trolletVita.vpk built. Transfer to vita over ftp and install with vitaShell.