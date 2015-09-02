#include "App.h"
#include <iostream>
 
int main(int argc, char *argv[]) {
    std::cout 
      << "      strza³ki lewo/prawo - poruszanie siê postaci¹\n"
      << "      strza³ki góra/dó³ - poruszanie siê postaci¹"
      << " przytrzymanie klawisza d - bieganie"
      << std::endl;
 
    App app(600, 400, false);
    app.Run();
    return 0;
}