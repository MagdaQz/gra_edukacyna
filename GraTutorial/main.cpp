#include "App.h"
#include <iostream>
 
int main(int argc, char *argv[]) {
    std::cout 
      << "      strza�ki lewo/prawo - poruszanie si� postaci�\n"
      << "      strza�ki g�ra/d� - poruszanie si� postaci�"
      << " przytrzymanie klawisza d - bieganie"
      << std::endl;
 
    App app(600, 400, false);
    app.Run();
    return 0;
}