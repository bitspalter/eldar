//////////////////////////////////////////////////////////////////////////////////
// [ TreeView_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_TreeView.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]
//////////////////////////////////////////////////////////////////////////////////
C_TreeView::C_TreeView(){

   //Create the Tree model:
   TStore = Gtk::TreeStore::create(Columns);
   set_model(TStore);

   //////////////////////////////////////////////
   
   Gtk::TreeViewColumn* pColumn = nullptr;
   int column_count = 0;

   column_count = append_column("Nr", cell[0]);
   pColumn      = get_column(column_count - 1);
   pColumn->set_cell_data_func(cell[0], sigc::mem_fun(*this, &C_TreeView::on_cell_0));
   
   column_count = append_column("Offset", cell[1]);
   pColumn      = get_column(column_count - 1);
   pColumn->set_cell_data_func(cell[1], sigc::mem_fun(*this, &C_TreeView::on_cell_1));
   
   column_count = append_column("Size", cell[2]);
   pColumn      = get_column(column_count - 1);
   pColumn->set_cell_data_func(cell[2], sigc::mem_fun(*this, &C_TreeView::on_cell_2));
   
   column_count = append_column("Value", cell[3]);
   pColumn      = get_column(column_count - 1);
   pColumn->set_cell_data_func(cell[3], sigc::mem_fun(*this, &C_TreeView::on_cell_3));
   
   column_count = append_column("Meaning", cell[4]);
   pColumn      = get_column(column_count - 1);
   pColumn->set_cell_data_func(cell[4], sigc::mem_fun(*this, &C_TreeView::on_cell_4));

   ////////////////////////////////////////
   
   //Make all the columns reorderable:
   //This is not necessary, but it's nice to show the feature.
   //You can use TreeView::set_column_drag_function() to more
   //finely control column drag and drop.
   for(guint i = 0; i < 5; i++){
      auto column = get_column(i);
      column->set_reorderable();
      column->set_resizable(true);
      column->set_expand(true);
   }
   
   /////////////////////////////////////////
   
   colorB1 = Gdk::RGBA("#232729");
   colorF1 = Gdk::RGBA("#777777");
   
   colorB2 = Gdk::RGBA("#2c3133");
   colorF2 = Gdk::RGBA("#777777");
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_cell_0 ]
//////////////////////////////////////////////////////////////////////////////////
void C_TreeView::on_cell_0(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter){
   Gtk::TreeModel::Row row = *iter;
   
   int i_dec = row[Columns.hidden];

   Gtk::CellRendererText* text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
   
   if(text_renderer){
      text_renderer->property_foreground_rgba() = (i_dec % 2 ? colorF1 : colorF2);
      text_renderer->property_background_rgba() = (i_dec % 2 ? colorB1 : colorB2);
      text_renderer->property_text()            =  row[Columns.nr];
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_cell_1 ]
//////////////////////////////////////////////////////////////////////////////////
void C_TreeView::on_cell_1(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter){
   Gtk::TreeModel::Row row = *iter;

   int i_dec = row[Columns.hidden];

   Gtk::CellRendererText* text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
   
   if(text_renderer){
      text_renderer->property_foreground_rgba() = (i_dec % 2 ? colorF1 : colorF2);
      text_renderer->property_background_rgba() = (i_dec % 2 ? colorB1 : colorB2);
      text_renderer->property_text()            =  row[Columns.offset];
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_cell_2 ]
//////////////////////////////////////////////////////////////////////////////////
void C_TreeView::on_cell_2(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter){
   Gtk::TreeModel::Row row = *iter;

   int i_dec = row[Columns.hidden];

   Gtk::CellRendererText* text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
   
   if(text_renderer){
      text_renderer->property_foreground_rgba() = (i_dec % 2 ? colorF1 : colorF2);
      text_renderer->property_background_rgba() = (i_dec % 2 ? colorB1 : colorB2);
      text_renderer->property_text()            =  row[Columns.size];
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_cell_3 ]
//////////////////////////////////////////////////////////////////////////////////
void C_TreeView::on_cell_3(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter){
   Gtk::TreeModel::Row row = *iter;

   int i_dec = row[Columns.hidden];

   Gtk::CellRendererText* text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
   
   if(text_renderer){
      text_renderer->property_foreground_rgba() = (i_dec % 2 ? colorF1 : colorF2);
      text_renderer->property_background_rgba() = (i_dec % 2 ? colorB1 : colorB2);
      text_renderer->property_text()            =  row[Columns.value];
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_cell_4 ]
//////////////////////////////////////////////////////////////////////////////////
void C_TreeView::on_cell_4(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter){
   Gtk::TreeModel::Row row = *iter;

   int i_dec = row[Columns.hidden];

   Gtk::CellRendererText* text_renderer = dynamic_cast<Gtk::CellRendererText*>(renderer);
   
   if(text_renderer){
      text_renderer->property_foreground_rgba() = (i_dec % 2 ? colorF1 : colorF2);
      text_renderer->property_background_rgba() = (i_dec % 2 ? colorB1 : colorB2);
      text_renderer->property_text()            =  row[Columns.meaning];
   }
}
