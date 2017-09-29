//////////////////////////////////////////////////////////////////////////////////
// [ TreeView_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
//
// [::Last modi: 19.03.17 L.ey (µ~)::]
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
       virtual ~C_TreeView();

       ////////////////////////
       //Tree model columns:
       class ModelColumns : public Gtk::TreeModel::ColumnRecord {
           
          public:

            ModelColumns(){add(m_col_nr); add(m_col_offset); add(m_col_size); add(m_col_value); add(m_col_meaning); add(m_col_hidden);}

            Gtk::TreeModelColumn<Glib::ustring> m_col_nr;
            Gtk::TreeModelColumn<Glib::ustring> m_col_offset;
            Gtk::TreeModelColumn<Glib::ustring> m_col_size;
            Gtk::TreeModelColumn<Glib::ustring> m_col_value;
            Gtk::TreeModelColumn<Glib::ustring> m_col_meaning;
            Gtk::TreeModelColumn<int> m_col_hidden;
       };

       ModelColumns m_Columns;
      
       Gtk::CellRendererText m_cell[5];
       
       void on_cell_0(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_1(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_2(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_3(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       void on_cell_4(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
       
       /////////////////////////
      
       Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
       
       /////////////////////////
       
       Gdk::RGBA colorB1, colorF1, colorB2, colorF2;
 };
 
#endif // _C_TREEVIEW_H_
