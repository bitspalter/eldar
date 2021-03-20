//////////////////////////////////////////////////////////////////////////////////
// [ TreeView_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
//
// [::Last modi: 20.03.21 L.ey (µ~)::]
//
//
#ifndef _C_TREEVIEW_H_
 #define _C_TREEVIEW_H_

 #include <iostream>
 
 using namespace std;
 
 #include <gtkmm.h>

//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
 const int C_TREEVIEW_ERROR = 0x00;
 const int C_TREEVIEW_READY = 0x01;

//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////
   
 class C_TreeView : public Gtk::TreeView {
   
    public:
       
       C_TreeView();
       virtual ~C_TreeView(){};

       ////////////////////////
       //Tree model columns:
       class ModelColumns : public Gtk::TreeModel::ColumnRecord {
           
          public:

            ModelColumns(){add(nr); add(offset); add(size); add(value); add(meaning); add(hidden);}

            Gtk::TreeModelColumn<Glib::ustring> nr;
            Gtk::TreeModelColumn<Glib::ustring> offset;
            Gtk::TreeModelColumn<Glib::ustring> size;
            Gtk::TreeModelColumn<Glib::ustring> value;
            Gtk::TreeModelColumn<Glib::ustring> meaning;
            Gtk::TreeModelColumn<int>           hidden;
       };

       ModelColumns Columns;
      
       Gtk::CellRendererText cell[5];
       
       void on_cell_0(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_1(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_2(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_3(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_4(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);

       /////////////////////////
      
       Glib::RefPtr<Gtk::TreeStore> TStore;
       
       /////////////////////////
       
       Gdk::RGBA colorB1, colorF1, colorB2, colorF2;
 };
 
#endif // _C_TREEVIEW_H_
