#include "C_App.hpp"
#include <gtkmm/application.h>

int main(int argc, char *argv[]){
  
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.eldar.v2");

   C_App CApp;

   return(app->run(CApp));
}
