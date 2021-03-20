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
 #include <fstream>
 using namespace std;
 
 #include <elf.h>
 #include <sys/mman.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>

 #include "C_GUI.hpp"
 
//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
 const int C_APP_ERROR = 0x00;
 const int C_APP_READY = 0x01;

 const int32_t magic = 0x464C457F;
 
 /* Note segment for SystemTap probes.  */
 #define NT_STAPSDT	3
 #define ALIGN_UP(addr, align)(((addr) + (align) - 1) & (~((align) - 1)))

//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////
 
 class C_App : public C_GUI { 
  
    public:
        
       C_App();
       virtual ~C_App(){};

    protected:

       //////////////////////////////////
       //Signal handlers:
       void on_button_open();
       void on_button_save();

       void on_tv_elf_changed();
       void on_tv_pro_changed();
       void on_tv_sec_changed();
       
       //////////////////////////////////
       
       int save_file(fstream* pFStream);
       
       //////////////////////////////////
       int open_file();

       int      hFile  = {-1};
       char*    pFile  = {nullptr};
       uint64_t cFile  = {0};
       bool     bFile  = {false};
       string   sFile;
       
       struct stat st;
          
       //////////////////////////////////
       // 64Bit
       Elf64_Ehdr* pElf64   = {nullptr};
       Elf64_Phdr* pPHead64 = {nullptr};
       Elf64_Shdr* pSHead64 = {nullptr};
       Elf64_Shdr* pSHStr64 = {nullptr};

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
       
       uint32_t cDynSum64 = {0};
       
       vector<string> vGNUSymbol64;
       
       bool bShnum64 = {false}; // true if pElf64->e_shnum == SHN_UNDEF
       
       //////////////////////////////
       //32Bit     
       Elf32_Ehdr* pElf32   = {nullptr};
       Elf32_Phdr* pPHead32 = {nullptr};
       Elf32_Shdr* pSHead32 = {nullptr};
       Elf32_Shdr* pSHStr32 = {nullptr};
       
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
       
       uint32_t cDynSum32 = {0};
       
       vector<string> vGNUSymbol32;
       
       bool bShnum32 = {false}; // true if pElf32->e_shnum == SHN_UNDEF
       
       /////////////////////////////////
       
       int show_hex(Gtk::TextView* pTV, uint64_t Offset, uint64_t Size);
 };

#endif // _C_APP_H_
