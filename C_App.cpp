//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_App.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]  
//////////////////////////////////////////////////////////////////////////////////
C_App::C_App(){

   this->resize(750, 500);
   
   //////////////////////////////////////////////////////////////
   // Button
   sbutton.open.set_label("open");
   sbutton.open.set_size_request(110, 30);
   sbutton.open.signal_clicked().connect(sigc::mem_fun(*this, &C_App::on_button_open));
   
   ////////////////

   Pango::FontDescription fdsc("Courier New 10"); 
  
   m_TV_Relocation.override_font(fdsc);
   m_TV_SymTab.override_font(fdsc);
   m_TV_Dynamic.override_font(fdsc);
   m_TV_Note.override_font(fdsc);
   m_TV_String.override_font(fdsc);
   m_TV_Gnu_Verdef.override_font(fdsc);
   m_TV_Gnu_Verneed.override_font(fdsc);
   m_TV_Gnu_Versym.override_font(fdsc);
   
   Gdk::RGBA colorB = Gdk::RGBA("#232729");
   Gdk::RGBA colorF = Gdk::RGBA("#777777");
   
   m_TV_Relocation.override_color(colorF);
   m_TV_SymTab.override_color(colorF);
   m_TV_Dynamic.override_color(colorF);
   m_TV_Note.override_color(colorF);
   m_TV_String.override_color(colorF);
   m_TV_Gnu_Verdef.override_color(colorF);
   m_TV_Gnu_Verneed.override_color(colorF);
   m_TV_Gnu_Versym.override_color(colorF);
   
   m_TV_Relocation.override_background_color(colorB);
   m_TV_SymTab.override_background_color(colorB);
   m_TV_Dynamic.override_background_color(colorB);
   m_TV_Note.override_background_color(colorB);
   m_TV_String.override_background_color(colorB);
   m_TV_Gnu_Verdef.override_background_color(colorB);
   m_TV_Gnu_Verneed.override_background_color(colorB);
   m_TV_Gnu_Versym.override_background_color(colorB);
   
   //////////////////////////////////////////////////////////////
   
   m_SW_Elf.add(CTV_ELF);
   m_SW_Elf.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Pro.add(CTV_Program);
   m_SW_Pro.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Sec.add(CTV_Section);
   m_SW_Sec.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   //////////////////////////
   
   m_SW_Relocation.add(m_TV_Relocation);
   m_SW_Relocation.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_SymTab.add(m_TV_SymTab);
   m_SW_SymTab.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Dynamic.add(m_TV_Dynamic);
   m_SW_Dynamic.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Note.add(m_TV_Note);
   m_SW_Note.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

   m_SW_String.add(m_TV_String);
   m_SW_String.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Gnu_Verdef.add(m_TV_Gnu_Verdef);
   m_SW_Gnu_Verdef.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Gnu_Verneed.add(m_TV_Gnu_Verneed);
   m_SW_Gnu_Verneed.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   m_SW_Gnu_Versym.add(m_TV_Gnu_Versym);
   m_SW_Gnu_Versym.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   //////////////////////////////////////////////////////////////
   // Notebook
   m_NB_Main.append_page(m_SW_Elf, "ELF header");
   m_NB_Main.append_page(m_SW_Pro, "Program header");
   m_NB_Main.append_page(m_SW_Sec, "Section header");
   m_NB_Main.append_page(m_VB_Sec, "Section");
   
   m_NB_Main.signal_switch_page().connect(sigc::mem_fun(*this, &C_App::on_notebook_switch_page));

   ///////////////////////////
   
   m_NB_Sec.append_page(m_SW_Relocation,  "Relocation");
   m_NB_Sec.append_page(m_SW_SymTab,      "Symbol Table");
   m_NB_Sec.append_page(m_SW_Dynamic,     "Dynamic");
   m_NB_Sec.append_page(m_SW_Note,        "Notes");
   m_NB_Sec.append_page(m_SW_String,      "Strings");
   m_NB_Sec.append_page(m_SW_Gnu_Verdef,  "GNU Verdef");
   m_NB_Sec.append_page(m_SW_Gnu_Verneed, "GNU Verneed");
   m_NB_Sec.append_page(m_SW_Gnu_Versym,  "GNU Versym");
   
   m_VB_Sec.pack_start(m_NB_Sec);
   
   //////////////////////////////////////////////////////////////
   // TextBuffer
   pTB_Relocation  = Gtk::TextBuffer::create();
   pTB_SymTab      = Gtk::TextBuffer::create();
   pTB_Dynamic     = Gtk::TextBuffer::create();
   pTB_Note        = Gtk::TextBuffer::create();
   pTB_String      = Gtk::TextBuffer::create();
   pTB_Gnu_Verdef  = Gtk::TextBuffer::create();
   pTB_Gnu_Verneed = Gtk::TextBuffer::create();
   pTB_Gnu_Versym  = Gtk::TextBuffer::create();
   
   //////////////////////////////////////////////////////////////
   // HeaderBar
   set_titlebar(m_header_bar);
   
   m_header_bar.set_title("eldar");
   m_header_bar.set_subtitle("Welcome");
   m_header_bar.set_show_close_button();
   m_header_bar.pack_start(sbutton.open);

   ///////////////////////////////////////////////////////

   add(m_VB_Main);

   m_VB_Main.pack_start(m_NB_Main);
   
   ////////////////////////
   
   signal_configure_event().connect(sigc::mem_fun(*this, &C_App::on_configure_changed), false);
   
   ////////////////////////
   
   show_all_children();
   
   ////////////////////////
   
   pfile    = nullptr;
   
   pElf64   = nullptr;
   pPHead64 = nullptr;
   pSHead64 = nullptr;
   pSHStr64 = nullptr;
   
   bShnum64 = false;
   
   pElf32   = nullptr;
   pPHead32 = nullptr;
   pSHead32 = nullptr;
   pSHStr32 = nullptr;
   
   bShnum32 = false;
}
//////////////////////////////////////////////////////////////////////////////////
// [ Destructor ]
//////////////////////////////////////////////////////////////////////////////////
C_App::~C_App(){
  
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_button_open ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_button_open(){

   Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
   dialog.set_transient_for(*this);

   dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
   dialog.add_button("_Open",   Gtk::RESPONSE_OK);

   int result = dialog.run();

   switch(result){
      case(Gtk::RESPONSE_OK):{
         sFile = dialog.get_filename();
         m_header_bar.set_subtitle(sFile.data());
         open_file();
         break;
      }
      case(Gtk::RESPONSE_CANCEL): break;
      default: break;
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_notebook_switch_page ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num){
   //cout << "Switched to tab with index " << page_num << endl;
}
//////////////////////////////////////////////////////////////////////////////////
// [ open_file ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::open_file(){
   uint64_t cFile = 0;
   int file = -1;
   struct stat st;
   
   ///////////////////////////////////////////////////////
   // clear everything   
   
   CTV_ELF.m_refTreeModel->clear();
   CTV_Program.m_refTreeModel->clear();
   CTV_Section.m_refTreeModel->clear();
   
   ///////////////////////
   
   pTB_Relocation->set_text("");
   m_TV_Relocation.set_buffer(pTB_Relocation);
   
   pTB_Dynamic->set_text("");
   m_TV_Dynamic.set_buffer(pTB_Dynamic);
   
   pTB_SymTab->set_text("");
   m_TV_SymTab.set_buffer(pTB_SymTab);
   
   pTB_Note->set_text("");
   m_TV_Note.set_buffer(pTB_Note);

   pTB_String->set_text("");
   m_TV_String.set_buffer(pTB_String);
   
   pTB_Gnu_Verdef->set_text("");
   m_TV_Gnu_Verdef.set_buffer(pTB_Gnu_Verdef);
   
   pTB_Gnu_Verneed->set_text("");
   m_TV_Gnu_Verneed.set_buffer(pTB_Gnu_Verneed);
   
   pTB_Gnu_Versym->set_text("");
   m_TV_Gnu_Versym.set_buffer(pTB_Gnu_Versym);
   
   ///////////////////////

   pfile = nullptr;
   
   ///////////////////////
   
   pElf64   = nullptr;
   pPHead64 = nullptr;
   pSHead64 = nullptr;
   pSHStr64 = nullptr;
   
   bShnum64 = false;
   
   vGNUSymbol64.clear();
   vGNUSymbol64.resize(10);
   vGNUSymbol64[0] = "Local";
   vGNUSymbol64[1] = "Global";
   
   ///////////////////////
   
   pElf32   = nullptr;
   pPHead32 = nullptr;
   pSHead32 = nullptr;
   pSHStr32 = nullptr;
   
   bShnum32 = false;
   
   vGNUSymbol32.clear();
   vGNUSymbol32.resize(10);
   vGNUSymbol32[0] = "Local";
   vGNUSymbol32[1] = "Global";
   
   ///////////////////////////////////////////////////////
   
   if(stat(sFile.data(), &st) != 0){
      m_header_bar.set_subtitle("ERROR: stat(file)");
      return(C_APP_ERROR);
   }
   
   cFile = st.st_size; 
   
   cout << "Name:" << sFile.data() << " Size:" << cFile << " bytes" << endl;
   
   if((file = open(sFile.data(), O_RDONLY)) == -1){
      m_header_bar.set_subtitle("ERROR: open(file)");
      return(C_APP_ERROR); 
   }
   
   if((pfile = (char*)mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, file, 0)) == MAP_FAILED){
      m_header_bar.set_subtitle("ERROR: mmap(file)");
      return(C_APP_ERROR);  
   }
   
   //////////////////////////////////////////////////
   
   if(*((int32_t*)(&pfile[0])) != magic){
      m_header_bar.set_subtitle("ERROR: no ELF file");
      return(C_APP_ERROR); 
   }

   if(pfile[EI_CLASS] == ELFCLASS32) read32bit(pfile);
   else
   if(pfile[EI_CLASS] == ELFCLASS64) read64bit(pfile);
   else m_header_bar.set_subtitle("ERROR: ELFCLASS32 unsupported");
       
   //////////////////////////////////////////////////
   
   munmap(pfile, st.st_size);
   
   ::close(file);
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ read64bit ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::read64bit(char* pfile){

   //cout << "show_ELF64_Head" << endl;
   
   pElf64 = (Elf64_Ehdr*)pfile;
   
   show_ELF64_Head();
   
   //cout << "show_ELF64_PHead" << endl;
      
   pPHead64 = (Elf64_Phdr*)(pfile + pElf64->e_phoff);
   
   show_ELF64_PHead();
   
   //cout << "show_ELF64_SHead" << endl;
      
   pSHead64 = (Elf64_Shdr*)(pfile + pElf64->e_shoff);
   
   if(pElf64->e_shstrndx != SHN_UNDEF)
      pSHStr64 = &pSHead64[pElf64->e_shstrndx];

   show_ELF64_SHead();
   
   //cout << "show_Section64" << endl;
      
   pSHead64 = (Elf64_Shdr*)(pfile + pElf64->e_shoff);
   
   show_Section64();
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ read32bit ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::read32bit(char* pfile){
    
   cout << "show_ELF32_Head" << endl;
   
   pElf32 = (Elf32_Ehdr*)pfile;
   
   show_ELF32_Head();
   
   cout << "show_ELF32_PHead" << endl;
      
   pPHead32 = (Elf32_Phdr*)(pfile + pElf32->e_phoff);
   
   show_ELF32_PHead();
   
   cout << "show_ELF32_SHead" << endl;
      
   pSHead32 = (Elf32_Shdr*)(pfile + pElf32->e_shoff);
   
   if(pElf32->e_shstrndx != SHN_UNDEF)
      pSHStr32 = &pSHead32[pElf32->e_shstrndx];

   show_ELF32_SHead();
   
   cout << "show_Section32" << endl;
      
   pSHead32 = (Elf32_Shdr*)(pfile + pElf32->e_shoff);
   
   show_Section32();
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF64_Head ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF64_Head(){
 
   int Offset = 0, n = 1;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &CTV_ELF;
   sAppend.pNumber   = &sNumber;
   sAppend.pOffset   = &sOffset;
   sAppend.pSize     = &sSize;
   sAppend.pValue    = &sValue;
   sAppend.pMeaning  = &sMeaning;
   sAppend.pHidden   = &n;
   
   ///////////////////////////////////////////////////////////

   sNumber << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize   << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue  << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_MAG0]
                                       << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_MAG1]
                                       << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_MAG2]
                                       << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_MAG3];
   sMeaning << "magic Number";

   appand(nullptr, &sAppend);
   
   Offset += 4;
   
   ///////////////////////////////////////////////////////////

   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_CLASS];
   sMeaning << "64-Bit";

   appand(nullptr, &sAppend);
   
   Offset += 1;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_DATA];
   
   if(pElf64->e_ident[EI_DATA] == ELFDATA2LSB) sMeaning << "little-endian";
   else
   if(pElf64->e_ident[EI_DATA] == ELFDATA2MSB) sMeaning << "big-endian";
   else                                        sMeaning << "Unknown data format";

   appand(nullptr, &sAppend);
   
   Offset += 1;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_VERSION];
   
   if(pElf64->e_ident[EI_VERSION] == EV_CURRENT) sMeaning << "original elf";
   else
   if(pElf64->e_ident[EI_VERSION] == EV_NONE)    sMeaning << "invalid elf";    
   else                                          sMeaning << "unknown elf"; 
   
   appand(nullptr, &sAppend);

   Offset += 1;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_OSABI];
   
   sMeaning << "OS-ABI: ";
   switch(pElf64->e_ident[EI_OSABI]){
      case 0x00: sMeaning << "System V";       break;
      case 0x01: sMeaning << "HP-UX";          break;
      case 0x02: sMeaning << "NetBSD";         break;
      case 0x03: sMeaning << "Linux";          break;
      case 0x04: sMeaning << "GNU Hurd";       break;
      case 0x06: sMeaning << "Solaris";        break;
      case 0x07: sMeaning << "AIX";            break;
      case 0x08: sMeaning << "IRIX";           break;
      case 0x09: sMeaning << "FreeBSD";        break;
      case 0x0A: sMeaning << "Tru64";          break;
      case 0x0B: sMeaning << "Novell Modesto"; break;
      case 0x0C: sMeaning << "OpenBSD";        break;
      case 0x0D: sMeaning << "OpenVMS";        break;
      case 0x0E: sMeaning << "NonStop Kernel"; break;
      case 0x0F: sMeaning << "AROS";           break;
      case 0x10: sMeaning << "Fenix OS";       break;
      case 0x11: sMeaning << "CloudABI";       break;
      case 0x53: sMeaning << "Sortix";         break;
      case 0x61: sMeaning << "ARM";            break;
      default:   sMeaning << "Unknown";        break;
   }
   
   appand(nullptr, &sAppend);

   Offset += 1;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_ABIVERSION];
   sMeaning << "specifies the ABI version"; 
   
   appand(nullptr, &sAppend);
   
   Offset += 1;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 7;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD]
                                        << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD + 1]
                                        << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD + 2]
                                        << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD + 3]
                                        << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD + 4]
                                        << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD + 5]
                                        << setw(2) << setfill('0') << (int)pElf64->e_ident[EI_PAD + 6];
   sMeaning << "currently unused";
   
   appand(nullptr, &sAppend);
   
   Offset += 7;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_type;

   sMeaning << "Filetype: ";
   switch(pElf64->e_type){
      case ET_NONE: sMeaning << "None";          break;
      case ET_REL:  sMeaning << "Relocatable";   break;    
      case ET_EXEC: sMeaning << "Executable";    break;
      case ET_DYN:  sMeaning << "Shared object"; break;
      case ET_CORE: sMeaning << "Core";          break;
      default:      sMeaning << "Unknown";
   } 
   
   appand(nullptr, &sAppend);
   
   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_machine;
   
   sMeaning << "Machinetype: ";
   switch(pElf64->e_machine){
      case 0x00: sMeaning << "None";    break;
      case 0x02: sMeaning << "SPARC";   break;
      case 0x03: sMeaning << "x86";     break;
      case 0x08: sMeaning << "MIPS";    break;
      case 0x14: sMeaning << "PowerPC"; break;
      case 0x16: sMeaning << "S390";    break;
      case 0x28: sMeaning << "ARM";     break;
      case 0x2A: sMeaning << "SuperH";  break;
      case 0x32: sMeaning << "IA-64";   break;
      case 0x3E: sMeaning << "x86-64";  break;
      case 0xB7: sMeaning << "AArch64"; break;
      case 0xF3: sMeaning << "RISC-V";  break;
      default:   sMeaning << "Unknown";
   }

   appand(nullptr, &sAppend);
   
   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf64->e_version;
   
   if(pElf64->e_version == EV_CURRENT) sMeaning << "original elf";
   else
   if(pElf64->e_version == EV_NONE)    sMeaning << "invalid elf";    
   else                                sMeaning << "unknown elf"; 
   
   appand(nullptr, &sAppend);

   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2)  << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2)  << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
   sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pElf64->e_entry;
   sMeaning << "Entrypoint";
   
   appand(nullptr, &sAppend);
   
   Offset += 8;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2)  << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2)  << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
   sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pElf64->e_phoff;
   sMeaning << "Offset Program Header";
   
   appand(nullptr, &sAppend);
   
   Offset += 8;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2)  << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2)  << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
   sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pElf64->e_shoff;
   sMeaning << "Offset Section Header";
   
   appand(nullptr, &sAppend);

   Offset += 8;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf64->e_flags;
   sMeaning << "Depends on the target architecture";
   
   appand(nullptr, &sAppend);

   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_flags;
   sMeaning << "Size of ELF Header";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_phentsize;
   sMeaning << "Size of Program Header Table";
   
   appand(nullptr, &sAppend);

   Offset += 2;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_phnum;
   sMeaning << "Entries in Program Header Table";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_shentsize;
   sMeaning << "Size of Section Header Table";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_shnum;
   
   if(pElf64->e_shnum == SHN_UNDEF){
      sMeaning << "Entries in Section Header Table (Undefined)";
      bShnum64 = true;
   }else{
      sMeaning << "Entries in Section Header Table";
      bShnum64 = false;
   }
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf64->e_shstrndx;
   sMeaning << "Index of the Section with Section Names";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF64_PHead ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF64_PHead(){

   uint64_t Offset = pElf64->e_phoff;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   Gtk::TreeModel::Row row;
   
   int Hidden = 0;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &CTV_Program;
   sAppend.pNumber   = &sNumber;
   sAppend.pOffset   = &sOffset;
   sAppend.pSize     = &sSize;
   sAppend.pValue    = &sValue;
   sAppend.pMeaning  = &sMeaning;
   sAppend.pHidden   = &Hidden;
   
   ///////////////////////////////////////////////////////////

   for(int n = 0; n < pElf64->e_phnum; n++){
       
      Hidden = n + 1;
      
      sNumber  << "Segment: 0x" << hex << uppercase << setw(2)  << setfill('0') << n + 1;
      sOffset  << "0x"          << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x"          << hex << uppercase << setw(2)  << setfill('0') << 4;
      sValue   << "0x"          << hex << uppercase << setw(8)  << setfill('0') << pPHead64->p_type;
      
      switch(pPHead64->p_type){
         case PT_NULL:         sMeaning << "unused";                      break;
         case PT_LOAD:         sMeaning << "loadable segment";            break;
         case PT_DYNAMIC:      sMeaning << "dynamic linking information"; break;
         case PT_INTERP:       sMeaning << "interpreter";                 break;
         case PT_NOTE:         sMeaning << "auxiliary information";       break;
         case PT_SHLIB:        sMeaning << "reserved";                    break;
         case PT_PHDR:         sMeaning << "program header table";        break; 
         case PT_TLS:          sMeaning << "Thread-Local Storage";        break;
         case PT_GNU_EH_FRAME: sMeaning << "GCC Exception Frames";        break;
         case PT_GNU_STACK:    sMeaning << "GNU Stack Extension";         break;
         case PT_GNU_RELRO:    sMeaning << "GCC Dynamic relocation";      break;
         default:
         if(pPHead64->p_type >= PT_LOPROC && pPHead64->p_type <= PT_HIPROC){
            sMeaning << "processor-specific"; 
         }else
         if(pPHead64->p_type >= PT_LOOS && pPHead64->p_type <= PT_HIOS){    
            sMeaning << "os-specific";
         }else{
            sMeaning << "unknown";
         }  
      }

      row = appand(nullptr, &sAppend);
   
      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8)  << setfill('0') << pPHead64->p_flags;
      sMeaning << "Segment-dependent flags"; 

      appand(&row, &sAppend);
   
      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pPHead64->p_offset;
      sMeaning << "Address in File"; 

      appand(&row, &sAppend);

      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pPHead64->p_vaddr;
      sMeaning << "Address in Memory"; 

      appand(&row, &sAppend);
   
      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pPHead64->p_paddr;
      sMeaning << "physical address"; 

      appand(&row, &sAppend);

      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pPHead64->p_filesz;
      sMeaning << "Size in File"; 

      appand(&row, &sAppend);

      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pPHead64->p_memsz;
      sMeaning << "Size in Memory"; 

      appand(&row, &sAppend);

      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pPHead64->p_align;
      sMeaning << "alignment"; 

      appand(&row, &sAppend);

      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      pPHead64++;
   }
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF64_SHead ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF64_SHead(){

   uint64_t Offset = pElf64->e_shoff;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   Gtk::TreeModel::Row row;
   
   int shnum = 0, Hidden = 0;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &CTV_Section;
   sAppend.pNumber   = &sNumber;
   sAppend.pOffset   = &sOffset;
   sAppend.pSize     = &sSize;
   sAppend.pValue    = &sValue;
   sAppend.pMeaning  = &sMeaning;
   sAppend.pHidden   = &Hidden;
   
   /////////////////////////////////////////////////////////// 
   
   if(bShnum64) shnum = pSHead64->sh_size;
   else         shnum = pElf64->e_shnum;
   
   for(int n = 0; n < shnum; n++){
       
      Hidden = n + 1;
      
      sNumber  << "Section: 0x" << hex << uppercase << setw(2)  << setfill('0') << n + 1;
      sOffset  << "0x"          << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x"          << hex << uppercase << setw(2)  << setfill('0') << 4;
      sValue   << "0x"          << hex << uppercase << setw(8)  << setfill('0') << pSHead64->sh_name;
      
      if(pSHStr64 != nullptr)
         sMeaning << "Name: " << (char*)(pfile + pSHStr64->sh_offset + pSHead64->sh_name); 
      else
         sMeaning << "Name: Unknown";
      
      row = appand(nullptr, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8)  << setfill('0') << pSHead64->sh_type;

      switch(pSHead64->sh_type){
         case SHT_NULL:           sMeaning << "inactive";                   break;
         case SHT_PROGBITS:       sMeaning << "program info";               break;
         case SHT_SYMTAB:         sMeaning << "symbol table";               break;
         case SHT_STRTAB:         sMeaning << "string table";               break;
         case SHT_HASH:           sMeaning << "hash table";                 break;
         case SHT_DYNAMIC:        sMeaning << "dynamic linking";            break;
         case SHT_NOTE:           sMeaning << "file info";                  break;
         case SHT_NOBITS:         sMeaning << "no space";                   break;
         case SHT_SHLIB:          sMeaning << "reserved";                   break;
         case SHT_DYNSYM:         sMeaning << "symbol table";               break;
         case SHT_INIT_ARRAY:     sMeaning << "Array of constructors";      break;
         case SHT_FINI_ARRAY:     sMeaning << "Array of destructors";       break;
         case SHT_PREINIT_ARRAY:  sMeaning << "Array of preconstructors";   break;
         case SHT_GROUP:          sMeaning << "Section group";              break;
         case SHT_SYMTAB_SHNDX:   sMeaning << "Extended section indeces";   break;
         case SHT_NUM:            sMeaning << "Number of defined types";    break;
         case SHT_GNU_ATTRIBUTES: sMeaning << "Object attributes";          break;
         case SHT_GNU_HASH:       sMeaning << "GNU hash table";             break;
         case SHT_GNU_LIBLIST:    sMeaning << "Prelink library list";       break;
         case SHT_CHECKSUM:       sMeaning << "Checksum for DSO content";   break;
         case SHT_GNU_verdef:     sMeaning << "Version definition section"; break;
         case SHT_GNU_verneed:    sMeaning << "Version needs section";      break;
         case SHT_GNU_versym:     sMeaning << "Version symbol table";       break;
         case SHT_RELA:           sMeaning << "relocation with addends";    break;
         case SHT_REL:            sMeaning << "relocation without addends"; break;
         default:
         if(pSHead64->sh_type >= SHT_LOPROC && pSHead64->sh_type <= SHT_HIPROC){
            sMeaning << "processor-specific"; 
         }else
         if(pSHead64->sh_type >= SHT_LOUSER && pSHead64->sh_type <= SHT_HIUSER){
            sMeaning << "application-specific"; 
         }else
         if(pSHead64->sh_type >= SHT_LOOS && pSHead64->sh_type <= SHT_HIOS){    
            sMeaning << "os-specific"; 
         }else{
            sMeaning << "type:unknown"; 
         }
      }
      
      appand(&row, &sAppend);
   
      Offset += 4;
      

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pSHead64->sh_flags;

      sMeaning << "flags:";
      
      if(pSHead64->sh_flags & SHF_WRITE)            sMeaning << "[WRITE]";
      if(pSHead64->sh_flags & SHF_ALLOC)            sMeaning << "[ALLOC]";
      if(pSHead64->sh_flags & SHF_EXECINSTR)        sMeaning << "[EXECINSTR]";
      if(pSHead64->sh_flags & SHF_MERGE)            sMeaning << "[MERGE]";
      if(pSHead64->sh_flags & SHF_STRINGS)          sMeaning << "[STRINGS]";
      if(pSHead64->sh_flags & SHF_INFO_LINK)        sMeaning << "[INFO_LINK]";
      if(pSHead64->sh_flags & SHF_LINK_ORDER)       sMeaning << "[LINK_ORDER]";
      if(pSHead64->sh_flags & SHF_OS_NONCONFORMING) sMeaning << "[OS_NONCONFORMING]";
      if(pSHead64->sh_flags & SHF_GROUP)            sMeaning << "[GROUP]";
      if(pSHead64->sh_flags & SHF_TLS)              sMeaning << "[TLS]";
      if(pSHead64->sh_flags & SHF_MASKOS)           sMeaning << "[MASKOS]";
      if(pSHead64->sh_flags & SHF_ORDERED)          sMeaning << "[ORDERED]";
      if(pSHead64->sh_flags & SHF_EXCLUDE)          sMeaning << "[EXCLUDE]";
      if(pSHead64->sh_flags & SHF_MASKPROC)         sMeaning << "[MASKPROC]";
      
      appand(&row, &sAppend);
   
      Offset += 8;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pSHead64->sh_addr;
      sMeaning << "Address in Memory";
      
      appand(&row, &sAppend);
   
      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pSHead64->sh_offset;
      sMeaning << "Address in File";
      
      appand(&row, &sAppend);

      Offset += 8;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pSHead64->sh_size;
      sMeaning << "Size in File";
      
      appand(&row, &sAppend);

      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8)  << setfill('0') << pSHead64->sh_link;
      sMeaning << "Depending on the type of section";
      
      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8)  << setfill('0') << pSHead64->sh_info;
      sMeaning << "Depending on the type of section";
      
      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pSHead64->sh_addralign;
      sMeaning << "alignment";
      
      appand(&row, &sAppend);

      Offset += 8;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2)  << setfill('0') << 8;
      sValue   << "0x" << hex << uppercase << setw(16) << setfill('0') << pSHead64->sh_entsize;
      
      if(!pSHead64->sh_entsize) sMeaning << "not fixed-size entries";
      else                      sMeaning << "fixed-size entries";
      
      appand(&row, &sAppend);
   
      Offset += 8;

      ///////////////////////////////////////////////////////////////
      
      pSHead64++;
   }
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ appand ]
//////////////////////////////////////////////////////////////////////////////////
Gtk::TreeModel::Row C_App::appand(Gtk::TreeModel::Row* pParent, SAppend* pSAppend){
   
   Gtk::TreeModel::iterator iter;
   Gtk::TreeModel::Row row;
   
   if(pParent == nullptr) iter = pSAppend->pTreeView->m_refTreeModel->append();
   else                   iter = pSAppend->pTreeView->m_refTreeModel->append(pParent->children());

   row = *iter;
   
   row.set_value(0,  pSAppend->pNumber->str());
   row.set_value(1,  pSAppend->pOffset->str());
   row.set_value(2,  pSAppend->pSize->str());
   row.set_value(3,  pSAppend->pValue->str());
   row.set_value(4,  pSAppend->pMeaning->str());
   row.set_value(5, *pSAppend->pHidden);
   
   // Hack
   pSAppend->pNumber->str("");
   pSAppend->pOffset->str("");
   pSAppend->pSize->str("");
   pSAppend->pValue->str("");
   pSAppend->pMeaning->str("");
   
   pSAppend->pNumber->str().clear();
   pSAppend->pOffset->str().clear();
   pSAppend->pSize->str().clear();
   pSAppend->pValue->str().clear();
   pSAppend->pMeaning->str().clear();
   
   return(row); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Section64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Section64(){
    
   Elf64_Shdr* pSHead = (Elf64_Shdr*)(pfile + pElf64->e_shoff);
   
   int shnum = 0;
   
   vector<Elf64_Shdr*> vNote;
   vector<Elf64_Shdr*> vSymTab;
   vector<Elf64_Shdr*> vDynamic;
   vector<Elf64_Shdr*> vRelocation; 
   vector<Elf64_Shdr*> vGHash;
   vector<Elf64_Shdr*> vGDef;
   vector<Elf64_Shdr*> vGNeed;
   vector<Elf64_Shdr*> vGSym;
   vector<Elf64_Shdr*> vStrings;
   
   if(bShnum64) shnum = pSHead64->sh_size;
   else         shnum = pElf64->e_shnum;
   
   for(int n = 0; n < shnum; n++){   
      switch(pSHead->sh_type){
         //case SHT_NULL:           cout << "(inactive)"                   << endl; break;    
         //case SHT_PROGBITS:       cout << "(program info)"               << endl; break;
         case SHT_SYMTAB:           vSymTab.push_back(pSHead);  break;
         case SHT_STRTAB:           vStrings.push_back(pSHead); break;
         //case SHT_HASH:           cout << "(hash table)"                 << endl; break;
         case SHT_DYNAMIC:          vDynamic.push_back(pSHead); break;
         case SHT_NOTE:             vNote.push_back(pSHead);    break;
         //case SHT_NOBITS:         cout << "(no space)"                   << endl; break;
         //case SHT_SHLIB:          cout << "(reserved)"                   << endl; break;
         case SHT_DYNSYM:           vSymTab.push_back(pSHead);  break;
         //case SHT_INIT_ARRAY:     cout << "(Array of constructors)"      << endl; break;
         //case SHT_FINI_ARRAY:     cout << "(Array of destructors)"       << endl; break;
         //case SHT_PREINIT_ARRAY:  cout << "(Array of preconstructors)"   << endl; break;
         //case SHT_GROUP:          cout << "(Section group)"              << endl; break;
         //case SHT_SYMTAB_SHNDX:   cout << "(Extended section indeces)"   << endl; break;
         //case SHT_NUM:            cout << "(Number of defined types)"    << endl; break;
         //case SHT_GNU_ATTRIBUTES: cout << "(Object attributes)"          << endl; break;
         case SHT_GNU_HASH:         vGHash.push_back(pSHead); break;
         //case SHT_GNU_LIBLIST:    cout << "(Prelink library list)"       << endl; break;
         //case SHT_CHECKSUM:       cout << "(Checksum for DSO content)"   << endl; break;
         case SHT_GNU_verdef:       vGDef.push_back(pSHead);  break;
         case SHT_GNU_verneed:      vGNeed.push_back(pSHead); break;                     
         case SHT_GNU_versym:       vGSym.push_back(pSHead);  break;
         case SHT_RELA:             vRelocation.push_back(pSHead); break;
         case SHT_REL:              vRelocation.push_back(pSHead); break;
         default:
         if(pSHead->sh_type >= SHT_LOPROC && pSHead->sh_type <= SHT_HIPROC){
            //cout << "(reserved for processor-specific semantics)" << endl;
         }else
         if(pSHead->sh_type >= SHT_LOUSER && pSHead->sh_type <= SHT_HIUSER){
            //cout << "(reserved for application programs)" << endl;
         }else
         if(pSHead->sh_type >= SHT_LOOS && pSHead->sh_type <= SHT_HIOS){    
            //cout << "(reserved for os-specific semantics)" << endl;
         }else{
            //cout << "(unknown)" << endl; 
         }
      }
      
      pSHead++;    
   }
   
   ///////////////////////////////////////////////////////////
   
   cout << "show_Dynamic64" << endl;
      
   for(auto pSHead: vDynamic) show_Dynamic64(pSHead);
    
   //////////////////////////////////
   
   cout << "show_Relocation64" << endl;
   
   for(auto pSHead: vRelocation) show_Relocation64(pSHead);
   
   //////////////////////////////////
   
   cout << "show_SymTab64" << endl;
   
   for(auto pSHead: vSymTab) show_SymTab64(pSHead);
   
   //////////////////////////////////
   
   cout << "show_Note64" << endl;
   
   for(auto pSHead: vNote) show_Note64(pSHead); 
   
   //////////////////////////////////
   
   cout << "show_String64" << endl;
   
   for(auto pSHead: vStrings) show_String64(pSHead);
   
   //////////////////////////////////
   
   cout << "show_GNU_Verdef64" << endl;
   
   for(auto pSHead: vGDef) show_GNU_Verdef64(pSHead);
   
   //////////////////////////////////
   
   cout << "show_GNU_Verneed64" << endl;
   
   for(auto pSHead: vGNeed) show_GNU_Verneed64(pSHead);
   
   //////////////////////////////////
   
   cout << "show_GNU_Versym64" << endl;
   
   for(auto pSHead: vGSym) show_GNU_Versym64(pSHead);

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////
// [ show_Relocation64 ]
/////////////////////////////////////////////////////////////////
int C_App::show_Relocation64(Elf64_Shdr* pSHead){

   ostringstream sData;
   
   Elf64_Rela* pRela = nullptr;
   Elf64_Rel*  pRel  = nullptr;
   
   int cRelo = 0;
   
   uint64_t Symbol = 0, Type = 0;
   
   sData << m_TV_Relocation.get_buffer()->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else 
      sData << "Name:Unknown" << endl;
 
   //////////////////////////////////////////////////
   
   if(pSHead->sh_type == SHT_RELA){
      pRela = (Elf64_Rela*)(pfile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf64_Rela);
   }else{
      pRel  = (Elf64_Rel*)(pfile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf64_Rel);
   }
   
   Elf64_Shdr* pSymHead = &pSHead64[pSHead->sh_link];
   Elf64_Shdr* pStrHead = &pSHead64[pSymHead->sh_link];
   
   Elf64_Sym* pSymTab = (Elf64_Sym*)(pfile + pSymHead->sh_offset);   
   
   //////////////////////////////////////////////////
   
   for(int n = 0; n < cRelo; n++){
      sData << "0x" << hex << uppercase << setw(4)  << setfill('0') << right << n;
      
      if(pSHead->sh_type == SHT_RELA){
         sData << " Offset:0x" << hex << uppercase << setw(16) << setfill('0') << pRela->r_offset;
         sData << " Addend:0x" << hex << uppercase << setw(16) << setfill('0') << pRela->r_addend;
         sData << " Info:0x"   << hex << uppercase << setw(16) << setfill('0') << pRela->r_info;
         Type   = ELF64_R_TYPE(pRela->r_info);
         Symbol = ELF64_R_SYM(pRela->r_info);
      }else{
         sData << " Offset:0x" << hex << uppercase << setw(16) << setfill('0') << pRel->r_offset;
         sData << " Info:0x"   << hex << uppercase << setw(16) << setfill('0') << pRel->r_info;
         Type   = ELF64_R_TYPE(pRel->r_info);
         Symbol = ELF64_R_SYM(pRel->r_info);
      }
      
      sData << " Type:";
      switch(Type){
         case R_X86_64_NONE:            sData << setw(20) << setfill(' ') << left << "R_X86_64_NONE";            break;   
         case R_X86_64_64:              sData << setw(20) << setfill(' ') << left << "R_X86_64_64";              break;
         case R_X86_64_PC32:            sData << setw(20) << setfill(' ') << left << "R_X86_64_PC32";            break;   
         case R_X86_64_GOT32:           sData << setw(20) << setfill(' ') << left << "R_X86_64_GOT32";           break;
         case R_X86_64_PLT32:           sData << setw(20) << setfill(' ') << left << "R_X86_64_PLT32";           break;   
         case R_X86_64_COPY:            sData << setw(20) << setfill(' ') << left << "R_X86_64_COPY";            break;
         case R_X86_64_GLOB_DAT:        sData << setw(20) << setfill(' ') << left << "R_X86_64_GLOB_DAT";        break;   
         case R_X86_64_JUMP_SLOT:       sData << setw(20) << setfill(' ') << left << "R_X86_64_JUMP_SLOT";       break;
         case R_X86_64_RELATIVE:        sData << setw(20) << setfill(' ') << left << "R_X86_64_RELATIVE";        break;   
         case R_X86_64_GOTPCREL:        sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPCREL";        break;
         case R_X86_64_32:              sData << setw(20) << setfill(' ') << left << "R_X86_64_32";              break;   
         case R_X86_64_32S:             sData << setw(20) << setfill(' ') << left << "R_X86_64_32S";             break;
         case R_X86_64_16:              sData << setw(20) << setfill(' ') << left << "R_X86_64_16";              break;   
         case R_X86_64_PC16:            sData << setw(20) << setfill(' ') << left << "R_X86_64_PC16";            break;
         case R_X86_64_8:               sData << setw(20) << setfill(' ') << left << "R_X86_64_8";               break;   
         case R_X86_64_PC8:             sData << setw(20) << setfill(' ') << left << "R_X86_64_PC8";             break;
         case R_X86_64_DTPMOD64:        sData << setw(20) << setfill(' ') << left << "R_X86_64_DTPMOD64";        break;   
         case R_X86_64_DTPOFF64:        sData << setw(20) << setfill(' ') << left << "R_X86_64_DTPOFF64";        break;
         case R_X86_64_TPOFF64:         sData << setw(20) << setfill(' ') << left << "R_X86_64_TPOFF64";         break;   
         case R_X86_64_TLSGD:           sData << setw(20) << setfill(' ') << left << "R_X86_64_TLSGD";           break;
         case R_X86_64_TLSLD:           sData << setw(20) << setfill(' ') << left << "R_X86_64_TLSLD";           break;   
         case R_X86_64_DTPOFF32:        sData << setw(20) << setfill(' ') << left << "R_X86_64_DTPOFF32";        break;
         case R_X86_64_GOTTPOFF:        sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTTPOFF";        break;   
         case R_X86_64_TPOFF32:         sData << setw(20) << setfill(' ') << left << "R_X86_64_TPOFF32";         break;
         case R_X86_64_PC64:            sData << setw(20) << setfill(' ') << left << "R_X86_64_PC64";            break;   
         case R_X86_64_GOTOFF64:        sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTOFF64";        break;
         case R_X86_64_GOTPC32:         sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPC32";         break;   
         case R_X86_64_GOT64:           sData << setw(20) << setfill(' ') << left << "R_X86_64_GOT64";           break;
         case R_X86_64_GOTPCREL64:      sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPCREL64";      break;   
         case R_X86_64_GOTPC64:         sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPC64";         break;
         case R_X86_64_GOTPLT64:        sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPLT64";        break; 
         case R_X86_64_PLTOFF64:        sData << setw(20) << setfill(' ') << left << "R_X86_64_PLTOFF64";        break;
         case R_X86_64_SIZE32:          sData << setw(20) << setfill(' ') << left << "R_X86_64_SIZE32";          break;  
         case R_X86_64_SIZE64:          sData << setw(20) << setfill(' ') << left << "R_X86_64_SIZE64";          break;
         case R_X86_64_GOTPC32_TLSDESC: sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPC32_TLSDESC"; break;  
         case R_X86_64_TLSDESC_CALL:    sData << setw(20) << setfill(' ') << left << "R_X86_64_TLSDESC_CALL";    break;
         case R_X86_64_TLSDESC:         sData << setw(20) << setfill(' ') << left << "R_X86_64_TLSDESC";         break;  
         case R_X86_64_IRELATIVE:       sData << setw(20) << setfill(' ') << left << "R_X86_64_IRELATIVE";       break;
         case R_X86_64_RELATIVE64:      sData << setw(20) << setfill(' ') << left << "R_X86_64_RELATIVE64";      break;  
         case R_X86_64_GOTPCRELX:       sData << setw(20) << setfill(' ') << left << "R_X86_64_GOTPCRELX";       break;
         case R_X86_64_REX_GOTPCRELX:   sData << setw(20) << setfill(' ') << left << "R_X86_64_REX_GOTPCRELX";   break;  
         case R_X86_64_NUM:             sData << setw(20) << setfill(' ') << left << "R_X86_64_NUM";             break;
         default:                       sData << setw(20) << setfill(' ') << left << "unknown";
      }

      sData << " Symbol:" << (char*)(pfile + pStrHead->sh_offset + pSymTab[Symbol].st_name) << endl;

      if(pSHead->sh_type == SHT_RELA) pRela++;
      else                            pRel++;
   }

   //////////////////////////////////////////////////
   
   pTB_Relocation->set_text(sData.str());
   
   m_TV_Relocation.set_buffer(pTB_Relocation);
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Dynamic64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Dynamic64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << m_TV_Dynamic.get_buffer()->get_text().data();
      
   //////////////////////////////////////////////////
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 

   Elf64_Dyn* pDyn = (Elf64_Dyn*)(pfile + pSHead->sh_offset);
   
   int cDyn = pSHead->sh_size / sizeof(Elf64_Dyn); 
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   for(int n = 0; n < cDyn; n++){
      if(pDyn->d_tag == DT_NULL) break;
      sData << "0x"      << hex << uppercase << setw(2)  << setfill('0') << n;
      sData << " Tag:0x" << hex << uppercase << setw(16) << setfill('0') << pDyn->d_tag;
      
      switch(pDyn->d_tag){
         case DT_NEEDED: 
            sData << setw(20) << setfill(' ') << "(DT_NEEDED)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " Name:" << (char*)(pfile + pStrHead->sh_offset + pDyn->d_un.d_val) << endl;
            break;   
         case DT_PLTRELSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PLTRELSZ)";
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_PLTGOT: 
            sData << setw(20) << setfill(' ') << "(DT_PLTGOT)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_HASH:            
            sData << setw(20) << setfill(' ') << "(DT_HASH)";
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_STRTAB:          
            sData << setw(20) << setfill(' ') << "(DT_STRTAB)";
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMTAB:          
            sData << setw(20) << setfill(' ') << "(DT_SYMTAB)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELA:            
            sData << setw(20) << setfill(' ') << "vDT_RELA)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_RELASZ:          
            sData << setw(20) << setfill(' ') << "(DT_RELASZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_RELAENT:         
            sData << setw(20) << setfill(' ') << "(DT_RELAENT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_STRSZ:           
            sData << setw(20) << setfill(' ') << "(DT_STRSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;   
         case DT_SYMENT:          
            sData << setw(20) << setfill(' ') << "(DT_SYMENT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_INIT:            
            sData << setw(20) << setfill(' ') << "(DT_INIT)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_FINI:            
            sData << setw(20) << setfill(' ') << "(DT_FINI)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_SONAME:          
            sData << setw(20) << setfill(' ') << "(DT_SONAME)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RPATH:           
            sData << setw(20) << setfill(' ') << "(DT_RPATH)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_REL:             
            sData << setw(20) << setfill(' ') << "(DT_REL)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELSZ:           
            sData << setw(20) << setfill(' ') << "(DT_RELSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RELENT:          
            sData << setw(20) << setfill(' ') << "(DT_RELENT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PLTREL:          
            sData << setw(20) << setfill(' ') << "(DT_PLTREL)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_DEBUG:           
            sData << setw(20) << setfill(' ') << "(DT_DEBUG)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_JMPREL:          
            sData << setw(20) << setfill(' ') << "(DT_JMPREL)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_INIT_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAY)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_FINI_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAY)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_INIT_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAYSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_FINI_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAYSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_RUNPATH:         
            sData << setw(20) << setfill(' ') << "(DT_RUNPATH)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS:           
            sData << setw(20) << setfill(' ') << "(DT_FLAGS)";
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PREINIT_ARRAY:   
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAY)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_PREINIT_ARRAYSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAYSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_NUM:             
            sData << setw(20) << setfill(' ') << "(DT_NUM)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PROCNUM:         
            sData << setw(20) << setfill(' ') << "(DT_PROCNUM)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         case DT_VERSYM:          
            sData << setw(20) << setfill(' ') << "(DT_VERSYM)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_RELACOUNT:       
            sData << setw(20) << setfill(' ') << "(DT_RELACOUNT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_RELCOUNT:        
            sData << setw(20) << setfill(' ') << "(DT_RELCOUNT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS_1:         
            sData << setw(20) << setfill(' ') << "(DT_FLAGS_1)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERDEF:          
            sData << setw(20) << setfill(' ') << "(DT_VERDEF)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERDEFNUM:       
            sData << setw(20) << setfill(' ') << "(DT_VERDEFNUM)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERNEED:         
            sData << setw(20) << setfill(' ') << "(DT_VERNEED)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERNEEDNUM:      
            sData << setw(20) << setfill(' ') << "(DT_VERNEEDNUM)";
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_AUXILIARY:       
            sData << setw(20) << setfill(' ') << "(DT_AUXILIARY)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FILTER:          
            sData << setw(20) << setfill(' ') << "(DT_FILTER)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         //case DT_VALRNGLO:      cout << "DT_VALRNGLO"        << endl; break;
         case DT_GNU_PRELINKED:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_PRELINKED)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_CONFLICTSZ:  
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICTSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_LIBLISTSZ:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLISTSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_CHECKSUM:        
            sData << setw(20) << setfill(' ') << "(DT_CHECKSUM)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPADSZ:        
            sData << setw(20) << setfill(' ') << "(DT_PLTPADSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVEENT:         
            sData << setw(20) << setfill(' ') << "(DT_MOVEENT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVESZ:          
            sData << setw(20) << setfill(' ') << "(DT_MOVESZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_FEATURE_1:       
            sData << setw(20) << setfill(' ') << "(DT_FEATURE_1)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_POSFLAG_1:       
            sData << setw(20) << setfill(' ') << "(DT_POSFLAG_1)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINSZ:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINSZ)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINENT:        
            sData << setw(20) << setfill(' ') << "(DT_SYMINENT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         //case DT_VALRNGHI:      cout << "DT_VALRNGHI"        << endl; break;
         //////////////////////////////////////////////////////////////////////
         //case DT_ADDRRNGLO:     cout << "DT_ADDRRNGLO"       << endl; break;
         case DT_GNU_HASH:        
            sData << setw(20) << setfill(' ') << "(DT_GNU_HASH)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_PLT:    
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_PLT)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_GOT:     
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_GOT)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_CONFLICT:    
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICT)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_LIBLIST:     
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLIST)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_CONFIG:          
            sData << setw(20) << setfill(' ') << "(DT_CONFIG)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_DEPAUDIT:        
            sData << setw(20) << setfill(' ') << "(DT_DEPAUDIT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_AUDIT:           
            sData << setw(20) << setfill(' ') << "(DT_AUDIT)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPAD:          
            sData << setw(20) << setfill(' ') << "(DT_PLTPAD)"; 
            sData << " Val: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVETAB:         
            sData << setw(20) << setfill(' ') << "(DT_MOVETAB)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMINFO:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINFO)"; 
            sData << " Ptr: 0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         //case DT_ADDRRNGHI:     cout << "DT_ADDRRNGHI"       << endl; break;
      }
         
      pDyn++;
   }
   
   //////////////////////////////////////////////////
   
   pTB_Dynamic->set_text(sData.str());
   
   m_TV_Dynamic.set_buffer(pTB_Dynamic);
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_SymTab64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_SymTab64(Elf64_Shdr* pSHead){
    
   ostringstream sData;

   sData << m_TV_SymTab.get_buffer()->get_text().data();
   
   //////////////////////////////////////////////////
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   Elf64_Sym* pSymTab = (Elf64_Sym*)(pfile + pSHead->sh_offset);
   
   int cSymTab64 = pSHead->sh_size / sizeof(Elf64_Sym);
   
   if(pSHead->sh_type == SHT_DYNSYM) cDynSum64 = cSymTab64;
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   //////////////////////////////////////////////////
   
   for(int n = 0; n < cSymTab64; n++){
      sData << "0x"       << hex << uppercase << setw(4) << setfill('0') << n;
      sData << " Info:0x" << hex << uppercase << setw(2) << setfill('0') << (int)pSymTab->st_info;

      sData << " Bind:";
      switch(ELF64_ST_BIND(pSymTab->st_info)){
         case STB_LOCAL:  sData << setw(10) << setfill(' ') << "(Local)";  break;    
         case STB_GLOBAL: sData << setw(10) << setfill(' ') << "(Global)"; break;
         case STB_WEAK:   sData << setw(10) << setfill(' ') << "(Weak)";   break;
         default:
         if(ELF64_ST_BIND(pSymTab->st_info) >= STB_LOOS && ELF64_ST_BIND(pSymTab->st_info) <= STB_HIOS){
            sData << "(os-specific)";  
         }else
         if(ELF64_ST_BIND(pSymTab->st_info) >= STB_LOPROC && ELF64_ST_BIND(pSymTab->st_info) <= STB_HIPROC){
            sData << "(processor-specific)";    
         }else{
            sData << "(unknown)"; 
         }   
      }
      
      sData << " Type:";
      switch(ELF64_ST_TYPE(pSymTab->st_info)){
         case STT_NOTYPE:  sData << setw(10) << setfill(' ') << "(NOTYPE)";  break;
         case STT_OBJECT:  sData << setw(10) << setfill(' ') << "(OBJECT)";  break; 
         case STT_FUNC:    sData << setw(10) << setfill(' ') << "(FUNC)";    break;
         case STT_SECTION: sData << setw(10) << setfill(' ') << "(SECTION)"; break; 
         case STT_FILE:    sData << setw(10) << setfill(' ') << "(FILE)";    break;
         case STT_COMMON:  sData << setw(10) << setfill(' ') << "(COMMON)";  break;
         case STT_TLS:     sData << setw(10) << setfill(' ') << "(TLS)";     break;
         default:
         if(ELF64_ST_TYPE(pSymTab->st_info) >= STT_LOOS && ELF64_ST_TYPE(pSymTab->st_info) <= STT_HIOS){
            sData << "(os-specific)"; 
         }else
         if(ELF64_ST_TYPE(pSymTab->st_info) >= STT_LOPROC && ELF64_ST_TYPE(pSymTab->st_info) <= STT_HIPROC){
            sData << "(processor-specific)";    
         }else{
            sData << "(unknown)"; 
         }
      }

      sData << " Other:0x" << setw(2)  << setfill('0') << (int)pSymTab->st_other;
      sData << " Shndx:0x" << setw(4)  << setfill('0') << pSymTab->st_shndx;
      sData << " Value:0x" << setw(16) << setfill('0') << pSymTab->st_value;
      sData << " Size:0x"  << setw(16) << setfill('0') << pSymTab->st_size;
      
      sData << " Name:" << (char*)(pfile + pStrHead->sh_offset + pSymTab->st_name) << endl;

      pSymTab++;    
   }   

   //////////////////////////////////////////////////
   
   pTB_SymTab->set_text(sData.str());
   
   m_TV_SymTab.set_buffer(pTB_SymTab);

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Note64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Note64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
   
   sData << m_TV_Note.get_buffer()->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
      
   //////////////////////////////////////////////////
   
   while(Size){
       
      Elf64_Nhdr* pNote = (Elf64_Nhdr*)(pfile + pSHead->sh_offset + Offset);

      sData << "Name:" << (char*)(pNote) + sizeof(Elf64_Nhdr);

      sData << " Type:";

      switch(pNote->n_type){
         case NT_GNU_ABI_TAG:
            sData << "(NT_GNU_ABI_TAG)";      
            
            if(pNote->n_descsz == 0x10){
            
               int32_t* pDesc = (int32_t*)((char*)(pNote) + sizeof(Elf64_Nhdr) + ALIGN_UP(pNote->n_namesz, 4));
               
               sData << " OS:";
               switch(pDesc[0]){
                  case ELF_NOTE_OS_LINUX:    sData << "Linux";   break;
                  case ELF_NOTE_OS_GNU:      sData << "GNU";     break;
                  case ELF_NOTE_OS_SOLARIS2: sData << "Solaris"; break;
                  case ELF_NOTE_OS_FREEBSD:  sData << "FreeBSD"; break;   
               }
               
               sData << " ABI:" << dec << pDesc[1] << "." << pDesc[2] << "." << pDesc[3] << endl;
            }
            
            break;
         case NT_GNU_HWCAP:        
            sData << "(NT_GNU_HWCAP)";        
            break; 
         case NT_GNU_BUILD_ID:     
            sData << "(NT_GNU_BUILD_ID)";
            
            if(pNote->n_descsz){
               unsigned char* pID = (unsigned char*)((unsigned char*)(pNote) + sizeof(Elf64_Nhdr) + ALIGN_UP(pNote->n_namesz, 4));
               sData << " Build ID:";
               for(uint32_t n = 0; n < pNote->n_descsz; n++)
                  sData << hex << uppercase << setw(2) << setfill('0') << (int)*pID++;
               sData << endl;
            }

            break;
         case NT_GNU_GOLD_VERSION: 
            sData << "(NT_GNU_GOLD_VERSION)";

            if(pNote->n_descsz)
               sData <<  " Version:" << (char*)((char*)(pNote) + sizeof(Elf64_Nhdr) + ALIGN_UP(pNote->n_namesz, 4)) << endl;
            
            break;
         default: sData << "unknown";
      }
      
      Size   -= (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf64_Nhdr));
      Offset += (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf64_Nhdr));
   }

   //////////////////////////////////////////////////
   
   pTB_Note->set_text(sData.str());
   
   m_TV_Note.set_buffer(pTB_Note);
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verneed64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_String64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   uint64_t Size = pSHead->sh_size, Offset = pSHead->sh_offset;
   
   sData << m_TV_String.get_buffer()->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 
       
   //////////////////////////////////////////////////
   
   int n = 0;
   
   while(Size){
    
      sData << "0x" << hex << uppercase << setw(4) << setfill('0') << n;    
      sData << " Offset:0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sData << " " << (char*)(pfile + Offset) << endl;
      
      Size   -= strlen((char*)(pfile + Offset)) + 1;
      Offset += strlen((char*)(pfile + Offset)) + 1;
      n++;
   }
   
   //////////////////////////////////////////////////
   
   pTB_String->set_text(sData.str());
   
   m_TV_String.set_buffer(pTB_String);
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verdef64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verdef64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << m_TV_Gnu_Verdef.get_buffer()->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;

   ////////////////////////////////////////////////// 
    
   Elf64_Verdef*  pVerdef  = nullptr;
   Elf64_Verdaux* pVerdaux = nullptr; 
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
   
   while(Size){
       
      pVerdef = (Elf64_Verdef*)(pfile + pSHead->sh_offset + Offset); 
       
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerdef->vd_version; 
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerdef->vd_cnt;
      sData << " ndx:0x"    << hex << setw(4) << setfill('0') << pVerdef->vd_ndx; 
      sData << " hash:0x"   << hex << setw(4) << setfill('0') << pVerdef->vd_hash << endl; 
       
      Size   -= sizeof(Elf64_Verdef);
      Offset += sizeof(Elf64_Verdef); 
       
      pVerdaux = (Elf64_Verdaux*)(((char*)(pVerdef) + pVerdef->vd_aux)); 
       
      for(int n = 0; n < pVerdef->vd_cnt; n++){
         sData << "  name:0x" << hex << setw(8) << setfill('0') << pVerdaux->vda_name;     
         sData << " " << (char*)(pfile + pStrHead->sh_offset + pVerdaux->vda_name) << endl; 
         
         if(!n){
            if(pVerdef->vd_ndx > vGNUSymbol64.size() - 1) vGNUSymbol64.resize(pVerdef->vd_ndx + 10);
            vGNUSymbol64[pVerdef->vd_ndx] = (char*)(pfile + pStrHead->sh_offset + pVerdaux->vda_name);   
         }
         
         Size   -= sizeof(Elf64_Verdaux);
         Offset += sizeof(Elf64_Verdaux);
          
         pVerdaux++; 
          
      }
   }

   //////////////////////////////////////////////////
   
   pTB_Gnu_Verdef->set_text(sData.str());
   
   m_TV_Gnu_Verdef.set_buffer(pTB_Gnu_Verdef);
   
   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verneed64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verneed64(Elf64_Shdr* pSHead){
    
   ostringstream sData;

   sData << m_TV_Gnu_Verneed.get_buffer()->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
   
   ////////////////////////////////////////////////// 
   
   Elf64_Verneed* pVerneed = nullptr;
   Elf64_Vernaux* pVernaux = nullptr; 
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;

   while(Size){   
      pVerneed = (Elf64_Verneed*)(pfile + pSHead->sh_offset + Offset);
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerneed->vn_version;
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerneed->vn_cnt;
      sData << " Name:" << (char*)(pfile + pStrHead->sh_offset + pVerneed->vn_file) << endl;

      Size   -= sizeof(Elf64_Verneed);
      Offset += sizeof(Elf64_Verneed);
      
      pVernaux = (Elf64_Vernaux*)(((char*)(pVerneed) + pVerneed->vn_aux));
      
      for(int n = 0; n < pVerneed->vn_cnt; n++){
         sData << "  Hash:0x" << hex << setw(8) << setfill('0') << pVernaux->vna_hash; 
         sData << " Flags:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_flags;
         sData << " Other:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_other;
         sData << " Name:" << (char*)(pfile + pStrHead->sh_offset + pVernaux->vna_name) << endl;
         
         if(pVernaux->vna_other > vGNUSymbol64.size() - 1) vGNUSymbol64.resize(pVernaux->vna_other + 10);
         vGNUSymbol64[pVernaux->vna_other] = (char*)(pfile + pStrHead->sh_offset + pVernaux->vna_name);
         
         pVernaux++;
         
         Size   -= sizeof(Elf64_Vernaux);
         Offset += sizeof(Elf64_Vernaux);
      }
   }

   //////////////////////////////////////////////////
   
   pTB_Gnu_Verneed->set_text(sData.str());
   
   m_TV_Gnu_Verneed.set_buffer(pTB_Gnu_Verneed);
   
   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Versym64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Versym64(Elf64_Shdr* pSHead){
    
   ostringstream sData;

   sData << m_TV_Gnu_Versym.get_buffer()->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   ////////////////////////////////////////////////// 

   Elf64_Half* pVerdef = (Elf64_Half*)(pfile + pSHead->sh_offset);
   
   int cSym = pSHead->sh_size / sizeof(Elf64_Half);
   
   for(int n = 0; n < cSym; n++){
      int val = *pVerdef++;
      if(val >= 0x8000) val &= 0xFF; // can't figure out what 0x80 means :o(
      sData << "0x"          << hex << right << uppercase << setw(4) << setfill('0') << n;
      sData << " Version:0x" << hex << uppercase << setw(4) << setfill('0') << val;
      sData << " " << setw(20) << setfill(' ') << left << vGNUSymbol64[val].data();
      if(!((n + 1) % 4)) sData << endl;
   }

   //////////////////////////////////////////////////
   
   pTB_Gnu_Versym->set_text(sData.str());
   
   m_TV_Gnu_Versym.set_buffer(pTB_Gnu_Versym);
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_configure_changed ]
//////////////////////////////////////////////////////////////////////////////////
bool C_App::on_configure_changed(GdkEventConfigure* configure_event){
   //m_SWindowPro.set_size_request(configure_event->width, configure_event->height);
   
   //m_Notebook.set_size_request(configure_event->width - 100, configure_event->height - 200);
   
   return(false);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF32_Head ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF32_Head(){
 
   int Offset = 0, n = 1;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &CTV_ELF;
   sAppend.pNumber   = &sNumber;
   sAppend.pOffset   = &sOffset;
   sAppend.pSize     = &sSize;
   sAppend.pValue    = &sValue;
   sAppend.pMeaning  = &sMeaning;
   sAppend.pHidden   = &n;
   
   ///////////////////////////////////////////////////////////

   sNumber << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize   << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue  << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_MAG0]
                                       << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_MAG1]
                                       << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_MAG2]
                                       << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_MAG3];
   sMeaning << "magic Number";

   appand(nullptr, &sAppend);
   
   Offset += 4;
   
   ///////////////////////////////////////////////////////////

   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_CLASS];
   sMeaning << "32-Bit";

   appand(nullptr, &sAppend);
   
   Offset += 1;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_DATA];
   
   if(pElf32->e_ident[EI_DATA] == ELFDATA2LSB) sMeaning << "little-endian";
   else
   if(pElf32->e_ident[EI_DATA] == ELFDATA2MSB) sMeaning << "big-endian";
   else                                        sMeaning << "Unknown data format";

   appand(nullptr, &sAppend);
   
   Offset += 1;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_VERSION];
   
   if(pElf32->e_ident[EI_VERSION] == EV_CURRENT) sMeaning << "original elf";
   else
   if(pElf32->e_ident[EI_VERSION] == EV_NONE)    sMeaning << "invalid elf";    
   else                                          sMeaning << "unknown elf"; 
   
   appand(nullptr, &sAppend);

   Offset += 1;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_OSABI];
   
   sMeaning << "OS-ABI: ";
   switch(pElf32->e_ident[EI_OSABI]){
      case 0x00: sMeaning << "System V";       break;
      case 0x01: sMeaning << "HP-UX";          break;
      case 0x02: sMeaning << "NetBSD";         break;
      case 0x03: sMeaning << "Linux";          break;
      case 0x04: sMeaning << "GNU Hurd";       break;
      case 0x06: sMeaning << "Solaris";        break;
      case 0x07: sMeaning << "AIX";            break;
      case 0x08: sMeaning << "IRIX";           break;
      case 0x09: sMeaning << "FreeBSD";        break;
      case 0x0A: sMeaning << "Tru64";          break;
      case 0x0B: sMeaning << "Novell Modesto"; break;
      case 0x0C: sMeaning << "OpenBSD";        break;
      case 0x0D: sMeaning << "OpenVMS";        break;
      case 0x0E: sMeaning << "NonStop Kernel"; break;
      case 0x0F: sMeaning << "AROS";           break;
      case 0x10: sMeaning << "Fenix OS";       break;
      case 0x11: sMeaning << "CloudABI";       break;
      case 0x53: sMeaning << "Sortix";         break;
      case 0x61: sMeaning << "ARM";            break;
      default:   sMeaning << "Unknown";        break;
   }
   
   appand(nullptr, &sAppend);

   Offset += 1;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 1;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_ABIVERSION];
   sMeaning << "specifies the ABI version"; 
   
   appand(nullptr, &sAppend);
   
   Offset += 1;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 7;
   sValue   << "0x" << hex << uppercase << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD]
                                        << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD + 1]
                                        << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD + 2]
                                        << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD + 3]
                                        << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD + 4]
                                        << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD + 5]
                                        << setw(2) << setfill('0') << (int)pElf32->e_ident[EI_PAD + 6];
   sMeaning << "currently unused";
   
   appand(nullptr, &sAppend);
   
   Offset += 7;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_type;

   sMeaning << "Filetype: ";
   switch(pElf32->e_type){
      case ET_NONE: sMeaning << "None";          break;
      case ET_REL:  sMeaning << "Relocatable";   break;    
      case ET_EXEC: sMeaning << "Executable";    break;
      case ET_DYN:  sMeaning << "Shared object"; break;
      case ET_CORE: sMeaning << "Core";          break;
      default:      sMeaning << "Unknown";
   } 
   
   appand(nullptr, &sAppend);
   
   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_machine;
   
   sMeaning << "Machinetype: ";
   switch(pElf32->e_machine){
      case 0x00: sMeaning << "None";    break;
      case 0x02: sMeaning << "SPARC";   break;
      case 0x03: sMeaning << "x86";     break;
      case 0x08: sMeaning << "MIPS";    break;
      case 0x14: sMeaning << "PowerPC"; break;
      case 0x16: sMeaning << "S390";    break;
      case 0x28: sMeaning << "ARM";     break;
      case 0x2A: sMeaning << "SuperH";  break;
      case 0x32: sMeaning << "IA-64";   break;
      case 0x3E: sMeaning << "x86-64";  break;
      case 0xB7: sMeaning << "AArch64"; break;
      case 0xF3: sMeaning << "RISC-V";  break;
      default:   sMeaning << "Unknown";
   }

   appand(nullptr, &sAppend);
   
   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf32->e_version;
   
   if(pElf32->e_version == EV_CURRENT) sMeaning << "original elf";
   else
   if(pElf32->e_version == EV_NONE)    sMeaning << "invalid elf";    
   else                                sMeaning << "unknown elf"; 
   
   appand(nullptr, &sAppend);

   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf32->e_entry;
   sMeaning << "Entrypoint";
   
   appand(nullptr, &sAppend);
   
   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf32->e_phoff;
   sMeaning << "Offset Program Header";
   
   appand(nullptr, &sAppend);
   
   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf32->e_shoff;
   sMeaning << "Offset Section Header";
   
   appand(nullptr, &sAppend);

   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
   sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pElf32->e_flags;
   sMeaning << "Depends on the target architecture";
   
   appand(nullptr, &sAppend);

   Offset += 4;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_flags;
   sMeaning << "Size of ELF Header";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_phentsize;
   sMeaning << "Size of Program Header Table";
   
   appand(nullptr, &sAppend);

   Offset += 2;
   
   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_phnum;
   sMeaning << "Entries in Program Header Table";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_shentsize;
   sMeaning << "Size of Section Header Table";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_shnum;
   
   if(pElf32->e_shnum == SHN_UNDEF){
      sMeaning << "Entries in Section Header Table (Undefined)";
      bShnum32 = true;
   }else{
      sMeaning << "Entries in Section Header Table";
      bShnum32 = false;
   }
   
   appand(nullptr, &sAppend);

   Offset += 2;

   ///////////////////////////////////////////////////////////
   
   sNumber  << "0x" << hex << uppercase << setw(2) << setfill('0') << n++;
   sOffset  << "0x" << hex << uppercase << setw(2) << setfill('0') << Offset;
   sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 2;
   sValue   << "0x" << hex << uppercase << setw(4) << setfill('0') << pElf32->e_shstrndx;
   sMeaning << "Index of the Section with Section Names";
   
   appand(nullptr, &sAppend);

   Offset += 2;

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF32_PHead ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF32_PHead(){

   uint32_t Offset = pElf32->e_phoff;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   Gtk::TreeModel::Row row;
   
   int Hidden = 0;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &CTV_Program;
   sAppend.pNumber   = &sNumber;
   sAppend.pOffset   = &sOffset;
   sAppend.pSize     = &sSize;
   sAppend.pValue    = &sValue;
   sAppend.pMeaning  = &sMeaning;
   sAppend.pHidden   = &Hidden;
   
   /////////////////////////////////////////////////////////// 

   for(int n = 0; n < pElf32->e_phnum; n++){
       
      Hidden = n + 1;
      
      sNumber  << "Segment: 0x" << hex << uppercase << setw(2) << setfill('0') << n + 1;
      sOffset  << "0x"          << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x"          << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x"          << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_type;
      
      switch(pPHead32->p_type){
         case PT_NULL:         sMeaning << "unused";                      break;
         case PT_LOAD:         sMeaning << "loadable segment";            break;
         case PT_DYNAMIC:      sMeaning << "dynamic linking information"; break;
         case PT_INTERP:       sMeaning << "interpreter";                 break;
         case PT_NOTE:         sMeaning << "auxiliary information";       break;
         case PT_SHLIB:        sMeaning << "reserved";                    break;
         case PT_PHDR:         sMeaning << "program header table";        break; 
         case PT_TLS:          sMeaning << "Thread-Local Storage";        break;
         case PT_GNU_EH_FRAME: sMeaning << "GCC Exception Frames";        break;
         case PT_GNU_STACK:    sMeaning << "GNU Stack Extension";         break;
         case PT_GNU_RELRO:    sMeaning << "GCC Dynamic relocation";      break;
         default:
         if(pPHead32->p_type >= PT_LOPROC && pPHead32->p_type <= PT_HIPROC){
            sMeaning << "processor-specific"; 
         }else
         if(pPHead32->p_type >= PT_LOOS && pPHead32->p_type <= PT_HIOS){    
            sMeaning << "os-specific";
         }else{
            sMeaning << "unknown";
         }  
      }

      row = appand(nullptr, &sAppend);
   
      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_offset;
      sMeaning << "Address in File"; 

      appand(&row, &sAppend);

      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_vaddr;
      sMeaning << "Address in Memory"; 

      appand(&row, &sAppend);
   
      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_paddr;
      sMeaning << "physical address"; 

      appand(&row, &sAppend);

      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_filesz;
      sMeaning << "Size in File"; 

      appand(&row, &sAppend);

      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_memsz;
      sMeaning << "Size in Memory"; 

      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_flags;
      sMeaning << "Segment-dependent flags"; 

      appand(&row, &sAppend);
   
      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pPHead32->p_align;
      sMeaning << "alignment"; 

      appand(&row, &sAppend);

      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      pPHead32++;
   }
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF32_SHead ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF32_SHead(){

   uint32_t Offset = pElf32->e_shoff;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   Gtk::TreeModel::Row row;
   
   int shnum = 0, Hidden = 0;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &CTV_Section;
   sAppend.pNumber   = &sNumber;
   sAppend.pOffset   = &sOffset;
   sAppend.pSize     = &sSize;
   sAppend.pValue    = &sValue;
   sAppend.pMeaning  = &sMeaning;
   sAppend.pHidden   = &Hidden;
   
   ///////////////////////////////////////////////////////////
   
   if(bShnum32) shnum = pSHead32->sh_size;
   else         shnum = pElf32->e_shnum;
   
   for(int n = 0; n < shnum; n++){
       
      Hidden = n + 1;
      
      sNumber  << "Section: 0x" << hex << uppercase << setw(2) << setfill('0') << n + 1;
      sOffset  << "0x"          << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x"          << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x"          << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_name;
      
      if(pSHStr32 != nullptr)
         sMeaning << "Name: " << (char*)(pfile + pSHStr32->sh_offset + pSHead32->sh_name); 
      else
         sMeaning << "Name: Unknown";

      row = appand(nullptr, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize   << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue  << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_type;

      switch(pSHead32->sh_type){
         case SHT_NULL:           sMeaning << "inactive";                   break;
         case SHT_PROGBITS:       sMeaning << "program info";               break;
         case SHT_SYMTAB:         sMeaning << "symbol table";               break;
         case SHT_STRTAB:         sMeaning << "string table";               break;
         case SHT_HASH:           sMeaning << "hash table";                 break;
         case SHT_DYNAMIC:        sMeaning << "dynamic linking";            break;
         case SHT_NOTE:           sMeaning << "file info";                  break;
         case SHT_NOBITS:         sMeaning << "no space";                   break;
         case SHT_SHLIB:          sMeaning << "reserved";                   break;
         case SHT_DYNSYM:         sMeaning << "symbol table";               break;
         case SHT_INIT_ARRAY:     sMeaning << "Array of constructors";      break;
         case SHT_FINI_ARRAY:     sMeaning << "Array of destructors";       break;
         case SHT_PREINIT_ARRAY:  sMeaning << "Array of preconstructors";   break;
         case SHT_GROUP:          sMeaning << "Section group";              break;
         case SHT_SYMTAB_SHNDX:   sMeaning << "Extended section indeces";   break;
         case SHT_NUM:            sMeaning << "Number of defined types";    break;
         case SHT_GNU_ATTRIBUTES: sMeaning << "Object attributes";          break;
         case SHT_GNU_HASH:       sMeaning << "GNU hash table";             break;
         case SHT_GNU_LIBLIST:    sMeaning << "Prelink library list";       break;
         case SHT_CHECKSUM:       sMeaning << "Checksum for DSO content";   break;
         case SHT_GNU_verdef:     sMeaning << "Version definition section"; break;
         case SHT_GNU_verneed:    sMeaning << "Version needs section";      break;
         case SHT_GNU_versym:     sMeaning << "Version symbol table";       break;
         case SHT_RELA:           sMeaning << "relocation with addends";    break;
         case SHT_REL:            sMeaning << "relocation without addends"; break;
         default:
         if(pSHead32->sh_type >= SHT_LOPROC && pSHead32->sh_type <= SHT_HIPROC){
            sMeaning << "processor-specific"; 
         }else
         if(pSHead32->sh_type >= SHT_LOUSER && pSHead32->sh_type <= SHT_HIUSER){
            sMeaning << "application-specific"; 
         }else
         if(pSHead32->sh_type >= SHT_LOOS && pSHead32->sh_type <= SHT_HIOS){    
            sMeaning << "os-specific"; 
         }else{
            sMeaning << "type:unknown"; 
         }
      }
      
      appand(&row, &sAppend);
   
      Offset += 4;
      

      ///////////////////////////////////////////////////////////////
      
      sOffset << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize   << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue  << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_flags;
      
      sMeaning << "flags:";
      if(pSHead32->sh_flags & SHF_WRITE)            sMeaning << "[WRITE]";
      if(pSHead32->sh_flags & SHF_ALLOC)            sMeaning << "[ALLOC]";
      if(pSHead32->sh_flags & SHF_EXECINSTR)        sMeaning << "[EXECINSTR]";
      if(pSHead32->sh_flags & SHF_MERGE)            sMeaning << "[MERGE]";
      if(pSHead32->sh_flags & SHF_STRINGS)          sMeaning << "[STRINGS]";
      if(pSHead32->sh_flags & SHF_INFO_LINK)        sMeaning << "[INFO_LINK]";
      if(pSHead32->sh_flags & SHF_LINK_ORDER)       sMeaning << "[LINK_ORDER]";
      if(pSHead32->sh_flags & SHF_OS_NONCONFORMING) sMeaning << "[OS_NONCONFORMING]";
      if(pSHead32->sh_flags & SHF_GROUP)            sMeaning << "[GROUP]";
      if(pSHead32->sh_flags & SHF_TLS)              sMeaning << "[TLS]";
      if(pSHead32->sh_flags & SHF_MASKOS)           sMeaning << "[MASKOS]";
      if(pSHead32->sh_flags & SHF_ORDERED)          sMeaning << "[ORDERED]";
      if(pSHead32->sh_flags & SHF_EXCLUDE)          sMeaning << "[EXCLUDE]";
      if(pSHead32->sh_flags & SHF_MASKPROC)         sMeaning << "[MASKPROC]";
      
      appand(&row, &sAppend);
   
      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_addr;
      sMeaning << "Address in Memory";
      
      appand(&row, &sAppend);
   
      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_offset;
      sMeaning << "Address in File";
      
      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_size;
      sMeaning << "Size in File";
      
      appand(&row, &sAppend);

      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_link;
      sMeaning << "Depending on the type of section";
      
      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_info;
      sMeaning << "Depending on the type of section";
      
      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_addralign;
      sMeaning << "alignment";
      
      appand(&row, &sAppend);

      Offset += 4;
      
      ///////////////////////////////////////////////////////////////
      
      sOffset  << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sSize    << "0x" << hex << uppercase << setw(2) << setfill('0') << 4;
      sValue   << "0x" << hex << uppercase << setw(8) << setfill('0') << pSHead32->sh_entsize;
      
      if(!pSHead32->sh_entsize) sMeaning << "not fixed-size entries";
      else                      sMeaning << "fixed-size entries";
      
      appand(&row, &sAppend);
   
      Offset += 4;

      ///////////////////////////////////////////////////////////////
      
      pSHead32++;
   }
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Section32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Section32(){
    
   Elf32_Shdr* pSHead = (Elf32_Shdr*)(pfile + pElf32->e_shoff);
   
   int shnum = 0;
   
   vector<Elf32_Shdr*> vNote;
   vector<Elf32_Shdr*> vSymTab;
   vector<Elf32_Shdr*> vDynamic;
   vector<Elf32_Shdr*> vRelocation; 
   vector<Elf32_Shdr*> vGHash;
   vector<Elf32_Shdr*> vGDef;
   vector<Elf32_Shdr*> vGNeed;
   vector<Elf32_Shdr*> vGSym;
   vector<Elf32_Shdr*> vStrings;
   
   if(bShnum32) shnum = pSHead32->sh_size;
   else         shnum = pElf32->e_shnum;
   
   for(int n = 0; n < shnum; n++){   
      switch(pSHead->sh_type){
         //case SHT_NULL:           cout << "(inactive)"                   << endl; break;    
         //case SHT_PROGBITS:       cout << "(program info)"               << endl; break;
         case SHT_SYMTAB:           vSymTab.push_back(pSHead);  break;
         case SHT_STRTAB:           vStrings.push_back(pSHead); break;
         //case SHT_HASH:           cout << "(hash table)"                 << endl; break;
         case SHT_DYNAMIC:          vDynamic.push_back(pSHead); break;
         case SHT_NOTE:             vNote.push_back(pSHead);    break;
         //case SHT_NOBITS:         cout << "(no space)"                   << endl; break;
         //case SHT_SHLIB:          cout << "(reserved)"                   << endl; break;
         case SHT_DYNSYM:           vSymTab.push_back(pSHead);  break;
         //case SHT_INIT_ARRAY:     cout << "(Array of constructors)"      << endl; break;
         //case SHT_FINI_ARRAY:     cout << "(Array of destructors)"       << endl; break;
         //case SHT_PREINIT_ARRAY:  cout << "(Array of preconstructors)"   << endl; break;
         //case SHT_GROUP:          cout << "(Section group)"              << endl; break;
         //case SHT_SYMTAB_SHNDX:   cout << "(Extended section indeces)"   << endl; break;
         //case SHT_NUM:            cout << "(Number of defined types)"    << endl; break;
         //case SHT_GNU_ATTRIBUTES: cout << "(Object attributes)"          << endl; break;
         case SHT_GNU_HASH:         vGHash.push_back(pSHead); break;
         //case SHT_GNU_LIBLIST:    cout << "(Prelink library list)"       << endl; break;
         //case SHT_CHECKSUM:       cout << "(Checksum for DSO content)"   << endl; break;
         case SHT_GNU_verdef:       vGDef.push_back(pSHead);  break;
         case SHT_GNU_verneed:      vGNeed.push_back(pSHead); break;                     
         case SHT_GNU_versym:       vGSym.push_back(pSHead);  break;
         case SHT_RELA:             vRelocation.push_back(pSHead); break;
         case SHT_REL:              vRelocation.push_back(pSHead); break;
         default:
         if(pSHead->sh_type >= SHT_LOPROC && pSHead->sh_type <= SHT_HIPROC){
            //cout << "(reserved for processor-specific semantics)" << endl;
         }else
         if(pSHead->sh_type >= SHT_LOUSER && pSHead->sh_type <= SHT_HIUSER){
            //cout << "(reserved for application programs)" << endl;
         }else
         if(pSHead->sh_type >= SHT_LOOS && pSHead->sh_type <= SHT_HIOS){    
            //cout << "(reserved for os-specific semantics)" << endl;
         }else{
            //cout << "(unknown)" << endl; 
         }
      }
      
      pSHead++;    
   }
    
   ///////////////////////////////////////////////////////////
   
   cout << "show_Dynamic32" << endl;
      
   for(auto pSHead: vDynamic) show_Dynamic32(pSHead);
   
   //////////////////////////////////
   
   cout << "show_Relocation32" << endl;
   
   for(auto pSHead: vRelocation) show_Relocation32(pSHead);
   
   //////////////////////////////////
   
   cout << "show_SymTab32" << endl;
   
   for(auto pSHead: vSymTab) show_SymTab32(pSHead);
   
   //////////////////////////////////
   
   cout << "show_Note32" << endl;
   
   for(auto pSHead: vNote) show_Note32(pSHead); 
   
   //////////////////////////////////
   
   cout << "show_String32" << endl;
   
   for(auto pSHead: vStrings) show_String32(pSHead);
   
   //////////////////////////////////
   
   cout << "show_GNU_Verdef32" << endl;
   
   for(auto pSHead: vGDef) show_GNU_Verdef32(pSHead);
   
   //////////////////////////////////
   
   cout << "show_GNU_Verneed32" << endl;
   
   for(auto pSHead: vGNeed) show_GNU_Verneed32(pSHead);
   
   //////////////////////////////////
   
   cout << "show_GNU_Versym32" << endl;
   
   for(auto pSHead: vGSym) show_GNU_Versym32(pSHead);
   
   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Dynamic32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Dynamic32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << m_TV_Dynamic.get_buffer()->get_text().data();
      
   //////////////////////////////////////////////////   
    
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 

   Elf32_Dyn* pDyn = (Elf32_Dyn*)(pfile + pSHead->sh_offset);
   
   int cDyn = pSHead->sh_size / sizeof(Elf64_Dyn); 
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   for(int n = 0; n < cDyn; n++){
      if(pDyn->d_tag == DT_NULL) break;
      sData << "0x"      << hex << uppercase << setw(2) << setfill('0') << n;
      sData << " Tag:0x" << hex << uppercase << setw(8) << setfill('0') << pDyn->d_tag;
      
      switch(pDyn->d_tag){
         case DT_NEEDED: 
            sData << setw(20) << setfill(' ') << "(DT_NEEDED)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " Name:" << (char*)(pfile + pStrHead->sh_offset + pDyn->d_un.d_val) << endl;
            break;   
         case DT_PLTRELSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PLTRELSZ)";
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_PLTGOT: 
            sData << setw(20) << setfill(' ') << "(DT_PLTGOT)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_HASH:            
            sData << setw(20) << setfill(' ') << "(DT_HASH)";
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_STRTAB:          
            sData << setw(20) << setfill(' ') << "(DT_STRTAB)";
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMTAB:          
            sData << setw(20) << setfill(' ') << "(DT_SYMTAB)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELA:            
            sData << setw(20) << setfill(' ') << "vDT_RELA)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_RELASZ:          
            sData << setw(20) << setfill(' ') << "(DT_RELASZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_RELAENT:         
            sData << setw(20) << setfill(' ') << "(DT_RELAENT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_STRSZ:           
            sData << setw(20) << setfill(' ') << "(DT_STRSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;   
         case DT_SYMENT:          
            sData << setw(20) << setfill(' ') << "(DT_SYMENT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_INIT:            
            sData << setw(20) << setfill(' ') << "(DT_INIT)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_FINI:            
            sData << setw(20) << setfill(' ') << "(DT_FINI)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_SONAME:          
            sData << setw(20) << setfill(' ') << "(DT_SONAME)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RPATH:           
            sData << setw(20) << setfill(' ') << "(DT_RPATH)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_REL:             
            sData << setw(20) << setfill(' ') << "(DT_REL)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELSZ:           
            sData << setw(20) << setfill(' ') << "(DT_RELSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RELENT:          
            sData << setw(20) << setfill(' ') << "(DT_RELENT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PLTREL:          
            sData << setw(20) << setfill(' ') << "(DT_PLTREL)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_DEBUG:           
            sData << setw(20) << setfill(' ') << "(DT_DEBUG)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_JMPREL:          
            sData << setw(20) << setfill(' ') << "(DT_JMPREL)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_INIT_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAY)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_FINI_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAY)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_INIT_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAYSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_FINI_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAYSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_RUNPATH:         
            sData << setw(20) << setfill(' ') << "(DT_RUNPATH)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS:           
            sData << setw(20) << setfill(' ') << "(DT_FLAGS)";
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PREINIT_ARRAY:   
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAY)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_PREINIT_ARRAYSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAYSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_NUM:             
            sData << setw(20) << setfill(' ') << "(DT_NUM)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PROCNUM:         
            sData << setw(20) << setfill(' ') << "(DT_PROCNUM)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         case DT_VERSYM:          
            sData << setw(20) << setfill(' ') << "(DT_VERSYM)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_RELACOUNT:       
            sData << setw(20) << setfill(' ') << "(DT_RELACOUNT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_RELCOUNT:        
            sData << setw(20) << setfill(' ') << "(DT_RELCOUNT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS_1:         
            sData << setw(20) << setfill(' ') << "(DT_FLAGS_1)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERDEF:          
            sData << setw(20) << setfill(' ') << "(DT_VERDEF)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERDEFNUM:       
            sData << setw(20) << setfill(' ') << "(DT_VERDEFNUM)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERNEED:         
            sData << setw(20) << setfill(' ') << "(DT_VERNEED)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERNEEDNUM:      
            sData << setw(20) << setfill(' ') << "(DT_VERNEEDNUM)";
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_AUXILIARY:       
            sData << setw(20) << setfill(' ') << "(DT_AUXILIARY)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FILTER:          
            sData << setw(20) << setfill(' ') << "(DT_FILTER)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         //case DT_VALRNGLO:      cout << "DT_VALRNGLO"        << endl; break;
         case DT_GNU_PRELINKED:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_PRELINKED)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_CONFLICTSZ:  
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICTSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_LIBLISTSZ:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLISTSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_CHECKSUM:        
            sData << setw(20) << setfill(' ') << "(DT_CHECKSUM)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPADSZ:        
            sData << setw(20) << setfill(' ') << "(DT_PLTPADSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVEENT:         
            sData << setw(20) << setfill(' ') << "(DT_MOVEENT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVESZ:          
            sData << setw(20) << setfill(' ') << "(DT_MOVESZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_FEATURE_1:       
            sData << setw(20) << setfill(' ') << "(DT_FEATURE_1)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_POSFLAG_1:       
            sData << setw(20) << setfill(' ') << "(DT_POSFLAG_1)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINSZ:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINSZ)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINENT:        
            sData << setw(20) << setfill(' ') << "(DT_SYMINENT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         //case DT_VALRNGHI:      cout << "DT_VALRNGHI"        << endl; break;
         //////////////////////////////////////////////////////////////////////
         //case DT_ADDRRNGLO:     cout << "DT_ADDRRNGLO"       << endl; break;
         case DT_GNU_HASH:        
            sData << setw(20) << setfill(' ') << "(DT_GNU_HASH)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_PLT:    
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_PLT)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_GOT:     
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_GOT)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_CONFLICT:    
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICT)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_LIBLIST:     
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLIST)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_CONFIG:          
            sData << setw(20) << setfill(' ') << "(DT_CONFIG)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_DEPAUDIT:        
            sData << setw(20) << setfill(' ') << "(DT_DEPAUDIT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_AUDIT:           
            sData << setw(20) << setfill(' ') << "(DT_AUDIT)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPAD:          
            sData << setw(20) << setfill(' ') << "(DT_PLTPAD)"; 
            sData << " Val: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVETAB:         
            sData << setw(20) << setfill(' ') << "(DT_MOVETAB)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMINFO:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINFO)"; 
            sData << " Ptr: 0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         //case DT_ADDRRNGHI:     cout << "DT_ADDRRNGHI"       << endl; break;
      }
         
      pDyn++;
   }
   
   //////////////////////////////////////////////////
   
   pTB_Dynamic->set_text(sData.str());
   
   m_TV_Dynamic.set_buffer(pTB_Dynamic);
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Relocation32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Relocation32(Elf32_Shdr* pSHead){

   ostringstream sData;
   
   Elf32_Rela* pRela = nullptr;
   Elf32_Rel*  pRel  = nullptr;
   
   int cRelo = 0;
   
   uint32_t Symbol = 0, Type = 0;
   
   sData << m_TV_Relocation.get_buffer()->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 
   
   //////////////////////////////////////////////////  
    
   if(pSHead->sh_type == SHT_RELA){
      pRela = (Elf32_Rela*)(pfile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf32_Rela);
   }else{
      pRel  = (Elf32_Rel*)(pfile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf32_Rel);
   }
   
   Elf32_Shdr* pSymHead = &pSHead32[pSHead->sh_link];
   Elf32_Shdr* pStrHead = &pSHead32[pSymHead->sh_link];
   
   Elf32_Sym* pSymTab = (Elf32_Sym*)(pfile + pSymHead->sh_offset);
   
   //////////////////////////////////////////////////
   
   for(int n = 0; n < cRelo; n++){
      sData << "0x" << hex << uppercase << setw(4)  << setfill('0') << right << n;
      
      if(pSHead->sh_type == SHT_RELA){
         sData << " Offset:0x" << hex << uppercase << setw(8) << setfill('0') << pRela->r_offset;
         sData << " Addend:0x" << hex << uppercase << setw(8) << setfill('0') << pRela->r_addend;
         sData << " Info:0x"   << hex << uppercase << setw(8) << setfill('0') << pRela->r_info;
         Type   = ELF32_R_TYPE(pRela->r_info);
         Symbol = ELF32_R_SYM(pRela->r_info);
      }else{
         sData << " Offset:0x" << hex << uppercase << setw(8) << setfill('0') << pRel->r_offset;
         sData << " Info:0x"   << hex << uppercase << setw(8) << setfill('0') << pRel->r_info;
         Type   = ELF32_R_TYPE(pRel->r_info);
         Symbol = ELF32_R_SYM(pRel->r_info);
      }
      
      sData << " Type:";
      switch(Type){
         case R_386_NONE:          sData << setw(20) << setfill(' ') << left << "R_386_NONE";          break;   
         case R_386_32:            sData << setw(20) << setfill(' ') << left << "R_386_32";            break;
         case R_386_PC32:          sData << setw(20) << setfill(' ') << left << "R_386_PC32";          break;   
         case R_386_GOT32:         sData << setw(20) << setfill(' ') << left << "R_386_GOT32";         break;
         case R_386_PLT32:         sData << setw(20) << setfill(' ') << left << "R_386_PLT32";         break;   
         case R_386_COPY:          sData << setw(20) << setfill(' ') << left << "R_386_COPY";          break;
         case R_386_GLOB_DAT:      sData << setw(20) << setfill(' ') << left << "R_386_GLOB_DAT";      break;   
         case R_386_JMP_SLOT:      sData << setw(20) << setfill(' ') << left << "R_386_JMP_SLOT";      break;
         case R_386_RELATIVE:      sData << setw(20) << setfill(' ') << left << "R_386_RELATIVE";      break;   
         case R_386_GOTOFF:        sData << setw(20) << setfill(' ') << left << "R_386_GOTOFF";        break;
         case R_386_GOTPC:         sData << setw(20) << setfill(' ') << left << "R_386_GOTPC";         break;   
         case R_386_32PLT:         sData << setw(20) << setfill(' ') << left << "R_386_32PLT";         break;
         case R_386_TLS_TPOFF:     sData << setw(20) << setfill(' ') << left << "R_386_TLS_TPOFF";     break;   
         case R_386_TLS_IE:        sData << setw(20) << setfill(' ') << left << "R_386_TLS_IE";        break;
         case R_386_TLS_GOTIE:     sData << setw(20) << setfill(' ') << left << "R_386_TLS_GOTIE";     break;   
         case R_386_TLS_LE:        sData << setw(20) << setfill(' ') << left << "R_386_TLS_LE";        break;
         case R_386_TLS_GD:        sData << setw(20) << setfill(' ') << left << "R_386_TLS_GD";        break;   
         case R_386_TLS_LDM:       sData << setw(20) << setfill(' ') << left << "R_386_TLS_LDM";       break;
         case R_386_16:            sData << setw(20) << setfill(' ') << left << "R_386_16";            break;   
         case R_386_PC16:          sData << setw(20) << setfill(' ') << left << "R_386_PC16";          break;
         case R_386_8:             sData << setw(20) << setfill(' ') << left << "R_386_8";             break;   
         case R_386_PC8:           sData << setw(20) << setfill(' ') << left << "R_386_PC8";           break;
         case R_386_TLS_GD_32:     sData << setw(20) << setfill(' ') << left << "R_386_TLS_GD_32";     break;   
         case R_386_TLS_GD_PUSH:   sData << setw(20) << setfill(' ') << left << "R_386_TLS_GD_PUSH";   break;
         case R_386_TLS_GD_CALL:   sData << setw(20) << setfill(' ') << left << "R_386_TLS_GD_CALL";   break;   
         case R_386_TLS_GD_POP:    sData << setw(20) << setfill(' ') << left << "R_386_TLS_GD_POP";    break;
         case R_386_TLS_LDM_32:    sData << setw(20) << setfill(' ') << left << "R_386_TLS_LDM_32";    break;   
         case R_386_TLS_LDM_PUSH:  sData << setw(20) << setfill(' ') << left << "R_386_TLS_LDM_PUSH";  break;
         case R_386_TLS_LDM_CALL:  sData << setw(20) << setfill(' ') << left << "R_386_TLS_LDM_CALL";  break;   
         case R_386_TLS_LDM_POP:   sData << setw(20) << setfill(' ') << left << "R_386_TLS_LDM_POP";   break;
         case R_386_TLS_LDO_32:    sData << setw(20) << setfill(' ') << left << "R_386_TLS_LDO_32";    break; 
         case R_386_TLS_IE_32:     sData << setw(20) << setfill(' ') << left << "R_386_TLS_IE_32";     break;
         case R_386_TLS_LE_32:     sData << setw(20) << setfill(' ') << left << "R_386_TLS_LE_32";     break;  
         case R_386_TLS_DTPMOD32:  sData << setw(20) << setfill(' ') << left << "R_386_TLS_DTPMOD32";  break;
         case R_386_TLS_DTPOFF32:  sData << setw(20) << setfill(' ') << left << "R_386_TLS_DTPOFF32";  break;  
         case R_386_TLS_TPOFF32:   sData << setw(20) << setfill(' ') << left << "R_386_TLS_TPOFF32";   break;
         case R_386_SIZE32:        sData << setw(20) << setfill(' ') << left << "R_386_SIZE32";        break;  
         case R_386_TLS_GOTDESC:   sData << setw(20) << setfill(' ') << left << "R_386_TLS_GOTDESC";   break;
         case R_386_TLS_DESC_CALL: sData << setw(20) << setfill(' ') << left << "R_386_TLS_DESC_CALL"; break;  
         case R_386_TLS_DESC:      sData << setw(20) << setfill(' ') << left << "R_386_TLS_DESC";      break;
         case R_386_IRELATIVE:     sData << setw(20) << setfill(' ') << left << "R_386_IRELATIVE";     break;  
         case R_386_GOT32X:        sData << setw(20) << setfill(' ') << left << "R_386_GOT32X";        break;
         case R_386_NUM:           sData << setw(20) << setfill(' ') << left << "R_386_NUM";           break;
         default:                  sData << setw(20) << setfill(' ') << left << "unknown";
      }

      sData << " Symbol:" << (char*)(pfile + pStrHead->sh_offset + pSymTab[Symbol].st_name) << endl;

      if(pSHead->sh_type == SHT_RELA) pRela++;
      else                            pRel++;
   }

   //////////////////////////////////////////////////
   
   pTB_Relocation->set_text(sData.str());
   
   m_TV_Relocation.set_buffer(pTB_Relocation);
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_SymTab32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_SymTab32(Elf32_Shdr* pSHead){
    
   ostringstream sData;

   sData << m_TV_SymTab.get_buffer()->get_text().data();
   
   //////////////////////////////////////////////////  
    
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   Elf32_Sym* pSymTab = (Elf32_Sym*)(pfile + pSHead->sh_offset);
   
   int cSymTab32 = pSHead->sh_size / sizeof(Elf32_Sym);
   
   if(pSHead->sh_type == SHT_DYNSYM) cDynSum32 = cSymTab32;
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   //////////////////////////////////////////////////
   
   for(int n = 0; n < cSymTab32; n++){
      sData << "0x"       << hex << uppercase << setw(4) << setfill('0') << n;
      sData << " Info:0x" << hex << uppercase << setw(2) << setfill('0') << (int)pSymTab->st_info;

      sData << " Bind:";
      switch(ELF32_ST_BIND(pSymTab->st_info)){
         case STB_LOCAL:  sData << setw(10) << setfill(' ') << "(Local)";  break;    
         case STB_GLOBAL: sData << setw(10) << setfill(' ') << "(Global)"; break;
         case STB_WEAK:   sData << setw(10) << setfill(' ') << "(Weak)";   break;
         default:
         if(ELF32_ST_BIND(pSymTab->st_info) >= STB_LOOS && ELF32_ST_BIND(pSymTab->st_info) <= STB_HIOS){
            sData << "(os-specific)";  
         }else
         if(ELF32_ST_BIND(pSymTab->st_info) >= STB_LOPROC && ELF32_ST_BIND(pSymTab->st_info) <= STB_HIPROC){
            sData << "(processor-specific)";    
         }else{
            sData << "(unknown)"; 
         }   
      }
      
      sData << " Type:";
      switch(ELF32_ST_TYPE(pSymTab->st_info)){
         case STT_NOTYPE:  sData << setw(10) << setfill(' ') << "(NOTYPE)";  break;
         case STT_OBJECT:  sData << setw(10) << setfill(' ') << "(OBJECT)";  break; 
         case STT_FUNC:    sData << setw(10) << setfill(' ') << "(FUNC)";    break;
         case STT_SECTION: sData << setw(10) << setfill(' ') << "(SECTION)"; break; 
         case STT_FILE:    sData << setw(10) << setfill(' ') << "(FILE)";    break;
         case STT_COMMON:  sData << setw(10) << setfill(' ') << "(COMMON)";  break;
         case STT_TLS:     sData << setw(10) << setfill(' ') << "(TLS)";     break;
         default:
         if(ELF32_ST_TYPE(pSymTab->st_info) >= STT_LOOS && ELF32_ST_TYPE(pSymTab->st_info) <= STT_HIOS){
            sData << "(os-specific)"; 
         }else
         if(ELF32_ST_TYPE(pSymTab->st_info) >= STT_LOPROC && ELF32_ST_TYPE(pSymTab->st_info) <= STT_HIPROC){
            sData << "(processor-specific)";    
         }else{
            sData << "(unknown)"; 
         }
      }

      sData << " Other:0x" << setw(2) << setfill('0') << (int)pSymTab->st_other;
      sData << " Shndx:0x" << setw(4) << setfill('0') << pSymTab->st_shndx;
      sData << " Value:0x" << setw(8) << setfill('0') << pSymTab->st_value;
      sData << " Size:0x"  << setw(8) << setfill('0') << pSymTab->st_size;
      
      sData << " Name:" << (char*)(pfile + pStrHead->sh_offset + pSymTab->st_name) << endl;

      pSymTab++;    
   }   

   //////////////////////////////////////////////////
   
   pTB_SymTab->set_text(sData.str());
   
   m_TV_SymTab.set_buffer(pTB_SymTab);
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Note32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Note32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
   
   sData << m_TV_Note.get_buffer()->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
      
   ////////////////////////////////////////////////// 
    
   while(Size){
       
      Elf32_Nhdr* pNote = (Elf32_Nhdr*)(pfile + pSHead->sh_offset + Offset);

      sData << "Name:" << (char*)(pNote) + sizeof(Elf32_Nhdr);

      sData << " Type:";

      switch(pNote->n_type){
         case NT_GNU_ABI_TAG:
            sData << "(NT_GNU_ABI_TAG)";      
            
            if(pNote->n_descsz == 0x10){
            
               int32_t* pDesc = (int32_t*)((char*)(pNote) + sizeof(Elf32_Nhdr) + ALIGN_UP(pNote->n_namesz, 4));
               
               sData << " OS:";
               switch(pDesc[0]){
                  case ELF_NOTE_OS_LINUX:    sData << "Linux";   break;
                  case ELF_NOTE_OS_GNU:      sData << "GNU";     break;
                  case ELF_NOTE_OS_SOLARIS2: sData << "Solaris"; break;
                  case ELF_NOTE_OS_FREEBSD:  sData << "FreeBSD"; break;   
               }
               
               sData << " ABI:" << dec << pDesc[1] << "." << pDesc[2] << "." << pDesc[3] << endl;
            }
            
            break;
         case NT_GNU_HWCAP:        
            sData << "(NT_GNU_HWCAP)";        
            break; 
         case NT_GNU_BUILD_ID:     
            sData << "(NT_GNU_BUILD_ID)";
            
            if(pNote->n_descsz){
               unsigned char* pID = (unsigned char*)((unsigned char*)(pNote) + sizeof(Elf32_Nhdr) + ALIGN_UP(pNote->n_namesz, 4));
               sData << " Build ID:";
               for(uint32_t n = 0; n < pNote->n_descsz; n++)
                  sData << hex << uppercase << setw(2) << setfill('0') << (int)*pID++;
               sData << endl;
            }

            break;
         case NT_GNU_GOLD_VERSION: 
            sData << "(NT_GNU_GOLD_VERSION)";

            if(pNote->n_descsz)
               sData <<  " Version:" << (char*)((char*)(pNote) + sizeof(Elf32_Nhdr) + ALIGN_UP(pNote->n_namesz, 4)) << endl;
            
            break;
         default: sData << "unknown";
      }
      
      Size   -= (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf64_Nhdr));
      Offset += (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf64_Nhdr));
   }

   //////////////////////////////////////////////////
   
   pTB_Note->set_text(sData.str());
   
   m_TV_Note.set_buffer(pTB_Note);
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_String32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_String32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   uint32_t Size = pSHead->sh_size, Offset = pSHead->sh_offset;
   
   sData << m_TV_String.get_buffer()->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 
       
   //////////////////////////////////////////////////   
    
   int n = 0;
   
   while(Size){
    
      sData << "0x" << hex << uppercase << setw(4) << setfill('0') << n;    
      sData << " Offset:0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sData << " " << (char*)(pfile + Offset) << endl;
      
      Size   -= strlen((char*)(pfile + Offset)) + 1;
      Offset += strlen((char*)(pfile + Offset)) + 1;
      n++;
   }
    
   //////////////////////////////////////////////////
   
   pTB_String->set_text(sData.str());
   
   m_TV_String.set_buffer(pTB_String);
   
   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verdef32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verdef32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << m_TV_Gnu_Verdef.get_buffer()->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;

   ////////////////////////////////////////////////// 

   Elf32_Verdef*  pVerdef  = nullptr;
   Elf32_Verdaux* pVerdaux = nullptr; 
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
    
   while(Size){
       
      pVerdef = (Elf32_Verdef*)(pfile + pSHead->sh_offset + Offset); 
       
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerdef->vd_version; 
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerdef->vd_cnt;
      sData << " ndx:0x"    << hex << setw(4) << setfill('0') << pVerdef->vd_ndx; 
      sData << " hash:0x"   << hex << setw(4) << setfill('0') << pVerdef->vd_hash << endl; 
       
      Size   -= sizeof(Elf32_Verdef);
      Offset += sizeof(Elf32_Verdef); 
       
      pVerdaux = (Elf32_Verdaux*)(((char*)(pVerdef) + pVerdef->vd_aux)); 
       
      for(int n = 0; n < pVerdef->vd_cnt; n++){
         sData << "  name:0x" << hex << setw(8) << setfill('0') << pVerdaux->vda_name;     
         sData << " " << (char*)(pfile + pStrHead->sh_offset + pVerdaux->vda_name) << endl; 
         
         if(!n){
            if(pVerdef->vd_ndx > vGNUSymbol32.size() - 1) vGNUSymbol32.resize(pVerdef->vd_ndx + 10);
            vGNUSymbol32[pVerdef->vd_ndx] = (char*)(pfile + pStrHead->sh_offset + pVerdaux->vda_name);   
         }
         
         Size   -= sizeof(Elf32_Verdaux);
         Offset += sizeof(Elf32_Verdaux);
          
         pVerdaux++; 
          
      }
   }
   
   //////////////////////////////////////////////////
   
   pTB_Gnu_Verdef->set_text(sData.str());
   
   m_TV_Gnu_Verdef.set_buffer(pTB_Gnu_Verdef);
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verneed32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verneed32(Elf32_Shdr* pSHead){
    
   ostringstream sData;

   sData << m_TV_Gnu_Verneed.get_buffer()->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;

   //////////////////////////////////////////////////  
    
   Elf32_Verneed* pVerneed = nullptr;
   Elf32_Vernaux* pVernaux = nullptr; 
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;

   while(Size){
      pVerneed = (Elf32_Verneed*)(pfile + pSHead->sh_offset + Offset);
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerneed->vn_version;
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerneed->vn_cnt;
      sData << " Name:" << (char*)(pfile + pStrHead->sh_offset + pVerneed->vn_file) << endl;

      Size   -= sizeof(Elf32_Verneed);
      Offset += sizeof(Elf32_Verneed);

      pVernaux = (Elf32_Vernaux*)(((char*)(pVerneed) + pVerneed->vn_aux));
      
      for(int n = 0; n < pVerneed->vn_cnt; n++){
         sData << "  Hash:0x" << hex << setw(8) << setfill('0') << pVernaux->vna_hash; 
         sData << " Flags:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_flags;
         sData << " Other:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_other;
         sData << " Name:" << (char*)(pfile + pStrHead->sh_offset + pVernaux->vna_name) << endl;

         if(pVernaux->vna_other > vGNUSymbol32.size() - 1) vGNUSymbol32.resize(pVernaux->vna_other + 10);
         vGNUSymbol32[pVernaux->vna_other] = (char*)(pfile + pStrHead->sh_offset + pVernaux->vna_name);

         Size   -= sizeof(Elf32_Vernaux);
         Offset += sizeof(Elf32_Vernaux);

         pVernaux++;
      }
   }

   //////////////////////////////////////////////////
   
   pTB_Gnu_Verneed->set_text(sData.str());
   
   m_TV_Gnu_Verneed.set_buffer(pTB_Gnu_Verneed);
   
   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Versym32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Versym32(Elf32_Shdr* pSHead){
    
   ostringstream sData;

   sData << m_TV_Gnu_Versym.get_buffer()->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pfile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   ////////////////////////////////////////////////// 
    
   Elf32_Half* pVerdef = (Elf32_Half*)(pfile + pSHead->sh_offset);
   
   int cSym = pSHead->sh_size / sizeof(Elf32_Half);

   for(int n = 0; n < cSym; n++){
      uint16_t val = *pVerdef++;
      if(val >= 0x8000) val &= 0xFF; // can't figure out what 0x80 means :o(
      sData << "0x"          << hex << right << uppercase << setw(4) << setfill('0') << n;
      sData << " Version:0x" << hex << uppercase << setw(4) << setfill('0') << val;
      sData << " " << setw(20) << setfill(' ') << left << vGNUSymbol32[val].data();
      if(!((n + 1) % 4)) sData << endl;
   }
   
   //////////////////////////////////////////////////
   
   pTB_Gnu_Versym->set_text(sData.str());
   
   m_TV_Gnu_Versym.set_buffer(pTB_Gnu_Versym);
   
   return(C_APP_READY); 
}
