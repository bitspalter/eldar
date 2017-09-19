//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
// eldar ver:0.1
//
// [::Last modi: 19.09.17 L.ey (µ~)::]
//
//
#ifndef _C_APP_H_
 #define _C_APP_H_

 #include <iostream>
 #include <sstream> 
 #include <iomanip>
 #include <vector>
 
 using namespace std;
 
 #include <elf.h>
 #include <sys/mman.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>

 #define ALIGN_UP(addr, align)(((addr) + (align) - 1) & (~((align) - 1)))
 
 #include <gtkmm.h>
 
 #include "C_TreeView.hpp"
 
//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
 const int C_APP_ERROR = 0x00;
 const int C_APP_READY = 0x01;

 const int32_t magic = 0x464C457F;
 
//////////////////////////////////////////////////////////////////////////////////
// STRUCT
//////////////////////////////////////////////////////////////////////////////////

 struct SButton {
    Gtk::Button open;
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

//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////
 
 class C_App : public Gtk::Window {
  
    public:
        
       C_App();
       virtual ~C_App();

    protected:
        
       Gtk::Box            m_VB_Main, m_VB_Sec;
       Gtk::Layout         m_layout;
       Gtk::HeaderBar      m_header_bar;
       Gtk::Notebook       m_NB_Main, m_NB_Sec;
       Gtk::ScrolledWindow m_SW_Elf, m_SW_Pro, m_SW_Sec;
       
       Gtk::ScrolledWindow m_SW_Relocation, m_SW_SymTab, m_SW_Dynamic, m_SW_Note, m_SW_String, m_SW_Gnu_Verneed, m_SW_Gnu_Versym;
       Gtk::TextView       m_TV_Relocation, m_TV_SymTab, m_TV_Dynamic, m_TV_Note, m_TV_String, m_TV_Gnu_Verneed, m_TV_Gnu_Versym;

       Glib::RefPtr<Gtk::TextBuffer> pTB_Relocation, pTB_SymTab, pTB_Dynamic, pTB_Note, pTB_String, pTB_Gnu_Verneed, pTB_Gnu_Versym;

       SButton sbutton;
       SLabel  slabel;
       
       C_TreeView CTV_ELF{C_TREEVIEW_ELF}, CTV_Program{C_TREEVIEW_PRO}, CTV_Section{C_TREEVIEW_SEC};
       
       ////////////////////////

       //Signal handlers:
       void on_button_open();
       void on_notebook_switch_page(Gtk::Widget* page, guint page_num);
       bool on_configure_changed(GdkEventConfigure* configure_event);
       
       ////////////////////////
       
       string sFile;
       
       ////////////////////////
       char* pfile;
       
       Elf64_Ehdr* pElf64;
       Elf64_Phdr* pPHead64;
       Elf64_Shdr* pSHead64;
       Elf64_Shdr* pSHStr64;

       int open_file();
       
       int read64bit(char* pfile);
       int read32bit(char* pfile);
       
       int show_ELF64_Head();
       int show_ELF64_PHead();
       int show_ELF64_SHead();
       
       int show_Section();
       int show_Relocation(Elf64_Shdr* pSHead);
       int show_Dynamic(Elf64_Shdr* pSHead);
       int show_SymTab(Elf64_Shdr* pSHead);
       int show_Note(Elf64_Shdr* pSHead);
       int show_String(Elf64_Shdr* pSHead);
       int show_GNU_Verneed(Elf64_Shdr* pSHead);
       int show_GNU_Versym(Elf64_Shdr* pSHead);
       
       uint32_t cDynSum;
       
       vector<string> vGNUSymbol;
       
       bool bShnum; // true if pElf64->e_shnum == SHN_UNDEF
       
       ////////////////////////

       Gtk::TreeModel::Row appand(Gtk::TreeModel::Row* pParent, SAppend* pSAppend);
 };

#endif // _C_APP_H_
