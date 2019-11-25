OPCUA client and server for my engineering thesis at the University of Wroclaw
===========================

## Installation on windows with MCVS 19, G++ 8.2 and CMAKE 3.14.2
  1. Open CMake Gui.
  2. Set build/release folder for building binaries.
  3. Set flag BUILD_DEPS=on.
  4. Generate release version.
  5. Open project and compile FreeOpcUa and googletest.
  6. Open Cmake Gui.
  7. Set build/debug folder for building binaries.
  8. Set flag BUILD_DEPS=off.
  9. Generate debug version.
  10. Open project and compile client and server.
  11. Move all .dll (like opcuacore.dll) from build\release\Externals\FreeOpcUa\src\FreeOpcUa-build\bin\Debug to \build\debug\Debug.
  12. Run server and client.

*  You may need to use prebuilt boost_1_64_0
*  You may need to install libraries mbedtls: sudo apt install libmbedtls-dev
