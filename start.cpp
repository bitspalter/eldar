#include "C_App.hpp"
#include <gtkmm/application.h>
#include <giomm/application.h>

//////////////////////////////////////////////////////////////////////////////////
// [ main ]  
//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.eldar.v2", Gio::APPLICATION_NON_UNIQUE);

   C_App CApp;

   return(app->run(CApp));
}
