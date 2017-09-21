//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
// eldar ver:0.2
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
       
       Gtk::ScrolledWindow m_SW_Relocation, m_SW_SymTab, m_SW_Dynamic, m_SW_Note, m_SW_String, m_SW_Gnu_Verdef, m_SW_Gnu_Verneed, m_SW_Gnu_Versym;
       Gtk::TextView       m_TV_Relocation, m_TV_SymTab, m_TV_Dynamic, m_TV_Note, m_TV_String, m_TV_Gnu_Verdef, m_TV_Gnu_Verneed, m_TV_Gnu_Versym;

       Glib::RefPtr<Gtk::TextBuffer> pTB_Relocation, pTB_SymTab, pTB_Dynamic, pTB_Note, pTB_String, pTB_Gnu_Verdef, pTB_Gnu_Verneed, pTB_Gnu_Versym;

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
       
       int open_file();
       
       char* pfile;
       
       // 64Bit
       Elf64_Ehdr* pElf64;
       Elf64_Phdr* pPHead64;
       Elf64_Shdr* pSHead64;
       Elf64_Shdr* pSHStr64;

       int read64bit(char* pfile);

       int show_ELF64_Head();
       int show_ELF64_PHead();
       int show_ELF64_SHead();
       
       int show_Section64();
       
       int show_Relocation64(Elf64_Shdr* pSHead);
       int show_Dynamic64(Elf64_Shdr* pSHead);
       int show_SymTab64(Elf64_Shdr* pSHead);
       int show_Note64(Elf64_Shdr* pSHead);
       int show_String64(Elf64_Shdr* pSHead);
       int show_GNU_Verdef64(Elf64_Shdr* pSHead);
       int show_GNU_Verneed64(Elf64_Shdr* pSHead);
       int show_GNU_Versym64(Elf64_Shdr* pSHead);
       
       uint32_t cDynSum64;
       
       vector<string> vGNUSymbol64;
       
       bool bShnum64; // true if pElf64->e_shnum == SHN_UNDEF
       
       ////////////////////////
       //32Bit
       
       int read32bit(char* pfile);
              
       Elf32_Ehdr* pElf32;
       Elf32_Phdr* pPHead32;
       Elf32_Shdr* pSHead32;
       Elf32_Shdr* pSHStr32;
       
       int show_ELF32_Head();
       int show_ELF32_PHead();
       int show_ELF32_SHead();
       
       int show_Section32();
       
       int show_Relocation32(Elf32_Shdr* pSHead);
       int show_Dynamic32(Elf32_Shdr* pSHead);
       int show_SymTab32(Elf32_Shdr* pSHead);
       int show_Note32(Elf32_Shdr* pSHead);
       int show_String32(Elf32_Shdr* pSHead);
       int show_GNU_Verdef32(Elf32_Shdr* pSHead);
       int show_GNU_Verneed32(Elf32_Shdr* pSHead);
       int show_GNU_Versym32(Elf32_Shdr* pSHead);
       
       uint32_t cDynSum32;
       
       vector<string> vGNUSymbol32;
       
       bool bShnum32; // true if pElf32->e_shnum == SHN_UNDEF
       
       /////////////////////////////
       
       Gtk::TreeModel::Row appand(Gtk::TreeModel::Row* pParent, SAppend* pSAppend);
 };

#endif // _C_APP_H_
