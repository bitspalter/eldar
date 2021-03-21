//////////////////////////////////////////////////////////////////////////////////
// [ C_GUI_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
//
// [::Last modi: 12.03.21 L.ey (µ~)::]
//
//
#ifndef _C_GUI_H_
#define _C_GUI_H_

 #include <iostream>

 using namespace std;
 
 #include <gtkmm.h>
 
 #include "C_TreeView.hpp"
 
//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
 const int C_GUI_ERROR = 0x00;
 const int C_GUI_READY = 0x01;
 
//////////////////////////////////////////////////////////////////////////////////
// STRUCT
//////////////////////////////////////////////////////////////////////////////////
 
 struct SButton {
    Gtk::Button open;
    Gtk::Button save;
 };
 
 //////////////////////////////
 
 struct SLabel {
 };
 
 //////////////////////////////
 
 struct SAppend {
    C_TreeView*    pTreeView;
    ostringstream* pNumber;
    ostringstream* pOffset;
    ostringstream* pSize;
    ostringstream* pValue;
    ostringstream* pMeaning;
    int*           pHidden;
 };
 
 //////////////////////////////
 
 struct SText {
    Gtk::ScrolledWindow window;
    Gtk::TextView view;   
    Glib::RefPtr<Gtk::TextBuffer> pbuffer; 
 };
 
 struct SSection {
    SText Relocation;
    SText SymTab;
    SText Dynamic;
    SText Note;
    SText String;
    SText Gnu_Verdef;
    SText Gnu_Verneed;
    SText Gnu_Versym;
 };
 
 struct SHex {
    SText ElfHead;
    SText ProHead;
    SText ProFile;
    SText SecHead;
    SText SecFile;
 };
 
 //////////////////////////////
 
 struct SPaned {
    Gtk::Paned VElf{Gtk::ORIENTATION_VERTICAL};  
    Gtk::Paned VPro{Gtk::ORIENTATION_VERTICAL};
    Gtk::Paned HPro{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Paned VSec{Gtk::ORIENTATION_VERTICAL};
    Gtk::Paned HSec{Gtk::ORIENTATION_HORIZONTAL};
 };
 
 //////////////////////////////
 
 struct STag {
    Glib::RefPtr<Gtk::TextBuffer::TagTable> Table;   
    Glib::RefPtr<Gtk::TextBuffer::Tag> BG_White;
    Glib::RefPtr<Gtk::TextBuffer::Tag> BG_Black;
    Glib::RefPtr<Gtk::TextBuffer::Tag> FG_Black;
    Glib::RefPtr<Gtk::TextBuffer::Tag> FG_Green;
 };
 
 //////////////////////////////
 
 struct STreeView {
    Gtk::ScrolledWindow window;    
    C_TreeView view; 
 };
 
 struct STView {
    STreeView Elf;
    STreeView Pro;
    STreeView Sec;
 };
 
//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////
 
 class C_GUI : public Gtk::Window {
 
    public:
      
       C_GUI();
       virtual ~C_GUI(){};

    protected:
       
       Gtk::HeaderBar header; 
       Gtk::Box       mBox, sBox;
       Gtk::Notebook  mNBook, sNBook;
       
       //////////////////////////////////
 
       STView   stview;
       STag     stag;
       SPaned   spaned;
       SSection ssection;
       SHex     shex;
       SButton  sbutton;
       SLabel   slabel;
       
       /////////////////////////////////
       
       Gtk::TreeModel::Row appand(Gtk::TreeModel::Row* const pParent, SAppend* const pSAppend);
       
       /////////////////////////////////
       
       bool on_configure_changed(GdkEventConfigure* configure_event);
 };
 
#endif // _C_GUI_H_
