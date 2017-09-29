//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
// eldar ver:0.3
//
// [::Last modi: 29.09.17 L.ey (µ~)::]
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
 
 class C_App : public Gtk::Window {
  
    public:
        
       C_App();
       virtual ~C_App();

    protected:
        
       Gtk::HeaderBar m_header_bar; 
       Gtk::Box       m_VB_Main, m_VB_Sec;
       Gtk::Notebook  m_NB_Main, m_NB_Sec;
       
       //////////////////////////////////
 
       STView   stview;
       STag     stag;
       SPaned   spaned;
       SSection ssection;
       SHex     shex;
       SButton  sbutton;
       SLabel   slabel;
 
       //////////////////////////////////
       //Signal handlers:
       void on_button_open();
       bool on_configure_changed(GdkEventConfigure* configure_event);

       void on_tv_elf_changed();
       void on_tv_pro_changed();
       void on_tv_sec_changed();
       
       //////////////////////////////////
       int open_file();
       
       int      hFile;
       char*    pFile;
       uint64_t cFile;
       bool     bFile;
       string   sFile;
       
       //////////////////////////////////
       // 64Bit
       Elf64_Ehdr* pElf64;
       Elf64_Phdr* pPHead64;
       Elf64_Shdr* pSHead64;
       Elf64_Shdr* pSHStr64;

       int read64bit();

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
       
       //////////////////////////////
       //32Bit     
       Elf32_Ehdr* pElf32;
       Elf32_Phdr* pPHead32;
       Elf32_Shdr* pSHead32;
       Elf32_Shdr* pSHStr32;
       
       int read32bit();
       
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
       
       /////////////////////////////////
       
       Gtk::TreeModel::Row appand(Gtk::TreeModel::Row* pParent, SAppend* pSAppend);
       
       /////////////////////////////////
       
       int show_hex(Gtk::TextView* pTV, uint64_t Offset, uint64_t Size);
 };

#endif // _C_APP_H_
