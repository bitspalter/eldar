//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_App.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]  
//////////////////////////////////////////////////////////////////////////////////
C_App::C_App(){

   this->set_default_size(920, 600);

   //////////////////////////////////////////////////////////////
   // Button
   sbutton.open.set_label("open");
   sbutton.open.set_size_request(110, 30);
   sbutton.open.signal_clicked().connect(sigc::mem_fun(*this, &C_App::on_button_open));
   
   ///////////////////////////////////
   // TreeView 
   stview.Elf.view.get_selection()->signal_changed().connect(sigc::mem_fun(*this, &C_App::on_tv_elf_changed));
   stview.Pro.view.get_selection()->signal_changed().connect(sigc::mem_fun(*this, &C_App::on_tv_pro_changed));
   stview.Sec.view.get_selection()->signal_changed().connect(sigc::mem_fun(*this, &C_App::on_tv_sec_changed));

   stview.Elf.window.add(stview.Elf.view);
   stview.Elf.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   stview.Pro.window.add(stview.Pro.view);
   stview.Pro.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   stview.Sec.window.add(stview.Sec.view);
   stview.Sec.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ////////////////////////////////////
   // Section
   
   Gdk::RGBA colorB = Gdk::RGBA("#232729");
   Gdk::RGBA colorF = Gdk::RGBA("#777777");
   
   Pango::FontDescription fdsc("Courier New 10"); 
   
   ssection.Relocation.pbuffer = Gtk::TextBuffer::create();
   ssection.Relocation.view.set_buffer(ssection.Relocation.pbuffer);
   ssection.Relocation.view.override_font(fdsc);
   ssection.Relocation.view.override_color(colorF);
   ssection.Relocation.view.override_background_color(colorB);
   ssection.Relocation.window.add(ssection.Relocation.view);
   ssection.Relocation.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.SymTab.pbuffer = Gtk::TextBuffer::create();
   ssection.SymTab.view.set_buffer(ssection.SymTab.pbuffer);
   ssection.SymTab.view.override_font(fdsc);
   ssection.SymTab.view.override_color(colorF);
   ssection.SymTab.view.override_background_color(colorB);
   ssection.SymTab.window.add(ssection.SymTab.view);
   ssection.SymTab.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.Dynamic.pbuffer = Gtk::TextBuffer::create();
   ssection.Dynamic.view.set_buffer(ssection.Dynamic.pbuffer);
   ssection.Dynamic.view.override_font(fdsc);
   ssection.Dynamic.view.override_color(colorF);
   ssection.Dynamic.view.override_background_color(colorB);
   ssection.Dynamic.window.add(ssection.Dynamic.view);
   ssection.Dynamic.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.Note.pbuffer = Gtk::TextBuffer::create();
   ssection.Note.view.set_buffer(ssection.Note.pbuffer);
   ssection.Note.view.override_font(fdsc);
   ssection.Note.view.override_color(colorF);
   ssection.Note.view.override_background_color(colorB);
   ssection.Note.window.add(ssection.Note.view);
   ssection.Note.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.String.pbuffer = Gtk::TextBuffer::create();
   ssection.String.view.set_buffer(ssection.String.pbuffer);
   ssection.String.view.override_font(fdsc);
   ssection.String.view.override_color(colorF);
   ssection.String.view.override_background_color(colorB);
   ssection.String.window.add(ssection.String.view);
   ssection.String.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.Gnu_Verdef.pbuffer = Gtk::TextBuffer::create();
   ssection.Gnu_Verdef.view.set_buffer(ssection.Gnu_Verdef.pbuffer);
   ssection.Gnu_Verdef.view.override_font(fdsc);
   ssection.Gnu_Verdef.view.override_color(colorF);
   ssection.Gnu_Verdef.view.override_background_color(colorB);
   ssection.Gnu_Verdef.window.add(ssection.Gnu_Verdef.view);
   ssection.Gnu_Verdef.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.Gnu_Verneed.pbuffer = Gtk::TextBuffer::create();
   ssection.Gnu_Verneed.view.set_buffer(ssection.Gnu_Verneed.pbuffer);
   ssection.Gnu_Verneed.view.override_font(fdsc);
   ssection.Gnu_Verneed.view.override_color(colorF);
   ssection.Gnu_Verneed.view.override_background_color(colorB);
   ssection.Gnu_Verneed.window.add(ssection.Gnu_Verneed.view);
   ssection.Gnu_Verneed.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   ssection.Gnu_Versym.pbuffer = Gtk::TextBuffer::create();
   ssection.Gnu_Versym.view.set_buffer(ssection.Gnu_Versym.pbuffer);
   ssection.Gnu_Versym.view.override_font(fdsc);
   ssection.Gnu_Versym.view.override_color(colorF);
   ssection.Gnu_Versym.view.override_background_color(colorB);
   ssection.Gnu_Versym.window.add(ssection.Gnu_Versym.view);
   ssection.Gnu_Versym.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

   //////////////////////////////////////////////////////////////
   // Hex
   
   Pango::FontDescription fHex("Courier New 14");
   
   // Tag ////////////////////////
   stag.BG_White = Gtk::TextBuffer::Tag::create();
   stag.BG_White->property_background() = "#777777";
   
   stag.BG_Black = Gtk::TextBuffer::Tag::create();
   stag.BG_Black->property_background() = "#232729";
   
   stag.FG_Black = Gtk::TextBuffer::Tag::create();
   stag.FG_Black->property_foreground() = "#232729";
   
   stag.FG_Green = Gtk::TextBuffer::Tag::create();
   stag.FG_Green->property_foreground() = "#23AA29";
   
   // TagTable ////////////////////
   stag.Table = Gtk::TextBuffer::TagTable::create();
   stag.Table->add(stag.BG_White);
   stag.Table->add(stag.BG_Black);
   stag.Table->add(stag.FG_Black);
   stag.Table->add(stag.FG_Green);
   
   // Text ////////////////////////
   shex.ElfHead.pbuffer = Gtk::TextBuffer::create(stag.Table);
   shex.ElfHead.window.add(shex.ElfHead.view);
   shex.ElfHead.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   shex.ElfHead.window.set_border_width(10);
   shex.ElfHead.view.override_font(fHex);
   shex.ElfHead.view.set_buffer(shex.ElfHead.pbuffer);
   shex.ElfHead.view.override_color(colorF);
   shex.ElfHead.view.override_background_color(colorB);
   
   spaned.VElf.add1(stview.Elf.window);
   spaned.VElf.add2(shex.ElfHead.window);

   /////////////////////////////////
   shex.ProHead.pbuffer = Gtk::TextBuffer::create(stag.Table);
   shex.ProHead.window.add(shex.ProHead.view);
   shex.ProHead.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   shex.ProHead.window.set_border_width(10);
   shex.ProHead.view.override_font(fHex);
   shex.ProHead.view.set_buffer(shex.ProHead.pbuffer);
   shex.ProHead.view.override_color(colorF);
   shex.ProHead.view.override_background_color(colorB);
   
   shex.ProFile.pbuffer = Gtk::TextBuffer::create();
   shex.ProFile.window.add(shex.ProFile.view);
   shex.ProFile.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   shex.ProFile.window.set_border_width(10);
   shex.ProFile.view.override_font(fHex);
   shex.ProFile.view.set_buffer(shex.ProFile.pbuffer);
   shex.ProFile.view.override_color(colorF);
   shex.ProFile.view.override_background_color(colorB);
   
   spaned.HPro.add1(shex.ProHead.window);
   spaned.HPro.add2(shex.ProFile.window);

   spaned.VPro.add1(stview.Pro.window);
   spaned.VPro.add2(spaned.HPro);

   /////////////////////////////////
   shex.SecHead.pbuffer = Gtk::TextBuffer::create(stag.Table);
   shex.SecHead.window.add(shex.SecHead.view);
   shex.SecHead.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   shex.SecHead.window.set_border_width(10);
   shex.SecHead.view.override_font(fHex);
   shex.SecHead.view.set_buffer(shex.SecHead.pbuffer);
   shex.SecHead.view.override_color(colorF);
   shex.SecHead.view.override_background_color(colorB);
   
   shex.SecFile.pbuffer = Gtk::TextBuffer::create();
   shex.SecFile.window.add(shex.SecFile.view);
   shex.SecFile.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   shex.SecFile.window.set_border_width(10);
   shex.SecFile.view.override_font(fHex);
   shex.SecFile.view.set_buffer(shex.SecFile.pbuffer);
   shex.SecFile.view.override_color(colorF);
   shex.SecFile.view.override_background_color(colorB);
   
   spaned.HSec.add1(shex.SecHead.window);
   spaned.HSec.add2(shex.SecFile.window);

   spaned.VSec.add1(stview.Sec.window);
   spaned.VSec.add2(spaned.HSec);

   //////////////////////////////////////////////////////////////
   // Notebook
   m_NB_Main.append_page(spaned.VElf, "ELF header");
   m_NB_Main.append_page(spaned.VPro, "Program header");
   m_NB_Main.append_page(spaned.VSec, "Section header");
   m_NB_Main.append_page(m_VB_Sec,    "Section");

   ///////////////////////////

   m_NB_Sec.append_page(ssection.Relocation.window,  "Relocation");
   m_NB_Sec.append_page(ssection.SymTab.window,      "Symbol Table");
   m_NB_Sec.append_page(ssection.Dynamic.window,     "Dynamic");
   m_NB_Sec.append_page(ssection.Note.window,        "Notes");
   m_NB_Sec.append_page(ssection.String.window,      "Strings");
   m_NB_Sec.append_page(ssection.Gnu_Verdef.window,  "GNU Verdef");
   m_NB_Sec.append_page(ssection.Gnu_Verneed.window, "GNU Verneed");
   m_NB_Sec.append_page(ssection.Gnu_Versym.window,  "GNU Versym");
   
   m_VB_Sec.pack_start(m_NB_Sec);

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
   
   bFile    = false;
   
   pFile    = nullptr;
   
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
// [ open_file ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::open_file(){

   ///////////////////////////////////////////////////////
   // clear everything   
   
   stview.Elf.view.m_refTreeModel->clear();
   stview.Pro.view.m_refTreeModel->clear();
   stview.Sec.view.m_refTreeModel->clear();
   
   ///////////////////////
   
   ssection.Relocation.pbuffer->set_text("");
   ssection.SymTab.pbuffer->set_text("");
   ssection.Dynamic.pbuffer->set_text("");
   ssection.Note.pbuffer->set_text("");
   ssection.String.pbuffer->set_text("");
   ssection.Gnu_Verdef.pbuffer->set_text("");
   ssection.Gnu_Verneed.pbuffer->set_text("");
   ssection.Gnu_Versym.pbuffer->set_text("");
   
   ///////////////////////
   
   shex.ElfHead.pbuffer->set_text("");
   shex.ProHead.pbuffer->set_text("");
   shex.ProFile.pbuffer->set_text("");
   shex.SecHead.pbuffer->set_text("");
   shex.SecFile.pbuffer->set_text("");
   
   ///////////////////////

   if(bFile){
      munmap(pFile, st.st_size);
      ::close(hFile);
      bFile = false;
      pFile = nullptr;
   }
   
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
   
   if((hFile = open(sFile.data(), O_RDONLY)) == -1){
      m_header_bar.set_subtitle("ERROR: open(file)");
      return(C_APP_ERROR); 
   }
   
   if((pFile = (char*)mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, hFile, 0)) == MAP_FAILED){
      m_header_bar.set_subtitle("ERROR: mmap(file)");
      return(C_APP_ERROR);  
   }
   
   //////////////////////////////////////////////////
   
   bFile = true;
   
   //////////////////////////////////////////////////
   
   if(*((int32_t*)(&pFile[0])) != magic){
      m_header_bar.set_subtitle("ERROR: no ELF file");
      return(C_APP_ERROR); 
   }

   if(pFile[EI_CLASS] == ELFCLASS32) read32bit();
   else
   if(pFile[EI_CLASS] == ELFCLASS64) read64bit();
   else m_header_bar.set_subtitle("ERROR: ELFCLASS32 unsupported");

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ read64bit ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::read64bit(){

   cout << "show_ELF64_Head" << endl;
   
   pElf64 = (Elf64_Ehdr*)pFile;
   
   show_ELF64_Head();
   
   cout << "show_ELF64_PHead" << endl;
      
   pPHead64 = (Elf64_Phdr*)(pFile + pElf64->e_phoff);
   
   show_ELF64_PHead();
   
   cout << "show_ELF64_SHead" << endl;
      
   pSHead64 = (Elf64_Shdr*)(pFile + pElf64->e_shoff);
   
   if(pElf64->e_shstrndx != SHN_UNDEF)
      pSHStr64 = &pSHead64[pElf64->e_shstrndx];

   show_ELF64_SHead();
   
   cout << "show_Section64" << endl;
      
   pSHead64 = (Elf64_Shdr*)(pFile + pElf64->e_shoff);
   
   show_Section64();
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF64_Head ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF64_Head(){
 
   int Offset = 0, n = 1;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &stview.Elf.view;
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
   
   //////////////////////////////////
   
   show_hex(&shex.ElfHead.view, 0, sizeof(Elf64_Ehdr));

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
   
   sAppend.pTreeView = &stview.Pro.view;
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
   
   sAppend.pTreeView = &stview.Sec.view;
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
         sMeaning << "Name: " << (char*)(pFile + pSHStr64->sh_offset + pSHead64->sh_name); 
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
      if(pSHead64->sh_flags & SHF_COMPRESSED)       sMeaning << "[COMPRESSED]";
            
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
    
   Elf64_Shdr* pSHead = (Elf64_Shdr*)(pFile + pElf64->e_shoff);
   
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
   
   sData << ssection.Relocation.pbuffer->get_text().data();

   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else 
      sData << "Name:Unknown" << endl;
 
   //////////////////////////////////////////////////
   
   if(pSHead->sh_type == SHT_RELA){
      pRela = (Elf64_Rela*)(pFile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf64_Rela);
   }else{
      pRel  = (Elf64_Rel*)(pFile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf64_Rel);
   }
   
   Elf64_Shdr* pSymHead = &pSHead64[pSHead->sh_link];
   Elf64_Shdr* pStrHead = &pSHead64[pSymHead->sh_link];
   
   Elf64_Sym* pSymTab = (Elf64_Sym*)(pFile + pSymHead->sh_offset);   
   
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

      sData << " Symbol:" << (char*)(pFile + pStrHead->sh_offset + pSymTab[Symbol].st_name) << endl;

      if(pSHead->sh_type == SHT_RELA) pRela++;
      else                            pRel++;
   }

   //////////////////////////////////////////////////
   
   ssection.Relocation.pbuffer->set_text(sData.str());

   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Dynamic64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Dynamic64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << ssection.Dynamic.pbuffer->get_text().data();
      
   //////////////////////////////////////////////////
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 

   Elf64_Dyn* pDyn = (Elf64_Dyn*)(pFile + pSHead->sh_offset);
   
   int cDyn = pSHead->sh_size / sizeof(Elf64_Dyn); 
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   for(int n = 0; n < cDyn; n++){
      if(pDyn->d_tag == DT_NULL) break;
      sData << "0x"      << hex << uppercase << setw(2)  << setfill('0') << n;
      sData << " Tag:0x" << hex << uppercase << setw(16) << setfill('0') << pDyn->d_tag;
      
      switch(pDyn->d_tag){
         case DT_NEEDED: 
            sData << setw(20) << setfill(' ') << "(DT_NEEDED)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " Name:" << (char*)(pFile + pStrHead->sh_offset + pDyn->d_un.d_val) << endl;
            break;   
         case DT_PLTRELSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PLTRELSZ)";
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_PLTGOT: 
            sData << setw(20) << setfill(' ') << "(DT_PLTGOT)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_HASH:            
            sData << setw(20) << setfill(' ') << "(DT_HASH)";
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_STRTAB:          
            sData << setw(20) << setfill(' ') << "(DT_STRTAB)";
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMTAB:          
            sData << setw(20) << setfill(' ') << "(DT_SYMTAB)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELA:            
            sData << setw(20) << setfill(' ') << "(DT_RELA)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_RELASZ:          
            sData << setw(20) << setfill(' ') << "(DT_RELASZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_RELAENT:         
            sData << setw(20) << setfill(' ') << "(DT_RELAENT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_STRSZ:           
            sData << setw(20) << setfill(' ') << "(DT_STRSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;   
         case DT_SYMENT:          
            sData << setw(20) << setfill(' ') << "(DT_SYMENT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_INIT:            
            sData << setw(20) << setfill(' ') << "(DT_INIT)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_FINI:            
            sData << setw(20) << setfill(' ') << "(DT_FINI)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_SONAME:          
            sData << setw(20) << setfill(' ') << "(DT_SONAME)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RPATH:           
            sData << setw(20) << setfill(' ') << "(DT_RPATH)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMBOLIC:    
            sData << setw(20) << setfill(' ') << "(DT_SYMBOLIC)" << endl; 
            break;
         case DT_REL:             
            sData << setw(20) << setfill(' ') << "(DT_REL)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELSZ:           
            sData << setw(20) << setfill(' ') << "(DT_RELSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RELENT:          
            sData << setw(20) << setfill(' ') << "(DT_RELENT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PLTREL:          
            sData << setw(20) << setfill(' ') << "(DT_PLTREL)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_DEBUG:           
            sData << setw(20) << setfill(' ') << "(DT_DEBUG)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TEXTREL:    
            sData << setw(20) << setfill(' ') << "(DT_TEXTREL)" << endl; 
            break;
         case DT_JMPREL:          
            sData << setw(20) << setfill(' ') << "(DT_JMPREL)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_BIND_NOW:    
            sData << setw(20) << setfill(' ') << "(DT_BIND_NOW)" << endl; 
            break;
         case DT_INIT_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAY)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_FINI_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAY)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_INIT_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAYSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_FINI_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAYSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_RUNPATH:         
            sData << setw(20) << setfill(' ') << "(DT_RUNPATH)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS:           
            sData << setw(20) << setfill(' ') << "(DT_FLAGS)";
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PREINIT_ARRAY:   
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAY)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_PREINIT_ARRAYSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAYSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_NUM:             
            sData << setw(20) << setfill(' ') << "(DT_NUM)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PROCNUM:         
            sData << setw(20) << setfill(' ') << "(DT_PROCNUM)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         case DT_VERSYM:          
            sData << setw(20) << setfill(' ') << "(DT_VERSYM)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_RELACOUNT:       
            sData << setw(20) << setfill(' ') << "(DT_RELACOUNT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_RELCOUNT:        
            sData << setw(20) << setfill(' ') << "(DT_RELCOUNT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS_1:         
            sData << setw(20) << setfill(' ') << "(DT_FLAGS_1)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERDEF:          
            sData << setw(20) << setfill(' ') << "(DT_VERDEF)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERDEFNUM:       
            sData << setw(20) << setfill(' ') << "(DT_VERDEFNUM)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERNEED:         
            sData << setw(20) << setfill(' ') << "(DT_VERNEED)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERNEEDNUM:      
            sData << setw(20) << setfill(' ') << "(DT_VERNEEDNUM)";
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_AUXILIARY:       
            sData << setw(20) << setfill(' ') << "(DT_AUXILIARY)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FILTER:          
            sData << setw(20) << setfill(' ') << "(DT_FILTER)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         //case DT_VALRNGLO:      cout << "DT_VALRNGLO"        << endl; break;
         case DT_GNU_PRELINKED:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_PRELINKED)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_CONFLICTSZ:  
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICTSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_LIBLISTSZ:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLISTSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_CHECKSUM:        
            sData << setw(20) << setfill(' ') << "(DT_CHECKSUM)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPADSZ:        
            sData << setw(20) << setfill(' ') << "(DT_PLTPADSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVEENT:         
            sData << setw(20) << setfill(' ') << "(DT_MOVEENT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVESZ:          
            sData << setw(20) << setfill(' ') << "(DT_MOVESZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_FEATURE_1:       
            sData << setw(20) << setfill(' ') << "(DT_FEATURE_1)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_POSFLAG_1:       
            sData << setw(20) << setfill(' ') << "(DT_POSFLAG_1)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINSZ:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINSZ)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINENT:        
            sData << setw(20) << setfill(' ') << "(DT_SYMINENT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         //case DT_VALRNGHI:      cout << "DT_VALRNGHI"        << endl; break;
         //////////////////////////////////////////////////////////////////////
         //case DT_ADDRRNGLO:     cout << "DT_ADDRRNGLO"       << endl; break;
         case DT_GNU_HASH:        
            sData << setw(20) << setfill(' ') << "(DT_GNU_HASH)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_PLT:    
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_PLT)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_GOT:     
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_GOT)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_CONFLICT:    
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICT)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_LIBLIST:     
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLIST)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_CONFIG:          
            sData << setw(20) << setfill(' ') << "(DT_CONFIG)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_DEPAUDIT:        
            sData << setw(20) << setfill(' ') << "(DT_DEPAUDIT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_AUDIT:           
            sData << setw(20) << setfill(' ') << "(DT_AUDIT)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPAD:          
            sData << setw(20) << setfill(' ') << "(DT_PLTPAD)"; 
            sData << " Val:0x" << setw(16) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVETAB:         
            sData << setw(20) << setfill(' ') << "(DT_MOVETAB)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMINFO:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINFO)"; 
            sData << " Ptr:0x" << setw(16) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         //case DT_ADDRRNGHI:     cout << "DT_ADDRRNGHI"       << endl; break;
      }
         
      pDyn++;
   }
   
   //////////////////////////////////////////////////
   
   ssection.Dynamic.pbuffer->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_SymTab64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_SymTab64(Elf64_Shdr* pSHead){
    
   ostringstream sData;

   sData << ssection.SymTab.pbuffer->get_text().data();
   
   //////////////////////////////////////////////////
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   Elf64_Sym* pSymTab = (Elf64_Sym*)(pFile + pSHead->sh_offset);
   
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
      
      sData << " Name:" << (char*)(pFile + pStrHead->sh_offset + pSymTab->st_name) << endl;

      pSymTab++;    
   }   

   //////////////////////////////////////////////////
   
   ssection.SymTab.pbuffer->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Note64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Note64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
   
   sData << ssection.Note.pbuffer->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
      
   //////////////////////////////////////////////////
   
   while(Size){
       
      Elf64_Nhdr* pNote = (Elf64_Nhdr*)(pFile + pSHead->sh_offset + Offset);

      string strName = (char*)(pNote) + sizeof(Elf64_Nhdr);
      
      sData << "Name:" << strName << " Type:";

      if(!strName.compare("GNU")){
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
            default: sData << "unknown" << endl;
         } 
      }else
      if(!strName.compare("stapsdt")){
         uint64_t* pData = nullptr;
         uint64_t Location, Base, Semaphore;
         char* pProvider = nullptr;
         char* pName     = nullptr; 
         char* pArgument = nullptr;
         
         switch(pNote->n_type){
            case NT_STAPSDT:
               sData << "(NT_STAPSDT)";

               pData = (uint64_t*)((char*)(pNote) + sizeof(Elf64_Nhdr) + 8);
               
               Location  = *pData++;
               Base      = *pData++;
               Semaphore = *pData++;
               
               pProvider = (char*)(pData);
               pName     = pProvider + strlen(pProvider) + 1;
               pArgument = pName + strlen(pName) + 1;
               
               sData << " Provider:" << pProvider << " Name:" << pName << endl; 
               
               sData << " Location:0x"  << setw(16) << setfill('0') << Location;
               sData << " Base:0x"      << setw(16) << setfill('0') << Base;
               sData << " Semaphore:0x" << setw(16) << setfill('0') << Semaphore << " Argument:" << pArgument << endl;;
               
               break;     
             
            default: sData << "unknown" << endl; 
         }
      }else{
         sData << "(currently unsupported)" << endl;    
      }

      Size   -= (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf64_Nhdr));
      Offset += (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf64_Nhdr));
   }

   //////////////////////////////////////////////////
   
   ssection.Note.pbuffer->set_text(sData.str());

   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verneed64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_String64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   uint64_t Size = pSHead->sh_size, Offset = pSHead->sh_offset;
   
   sData << ssection.String.pbuffer->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 
       
   //////////////////////////////////////////////////
   
   int n = 0;
   
   while(Size){
    
      sData << "0x" << hex << uppercase << setw(4) << setfill('0') << n;    
      sData << " Offset:0x" << hex << uppercase << setw(16) << setfill('0') << Offset;
      sData << " " << (char*)(pFile + Offset) << endl;
      
      Size   -= strlen((char*)(pFile + Offset)) + 1;
      Offset += strlen((char*)(pFile + Offset)) + 1;
      n++;
   }
   
   //////////////////////////////////////////////////
   
   ssection.String.pbuffer->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verdef64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verdef64(Elf64_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << ssection.Gnu_Verdef.pbuffer->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;

   ////////////////////////////////////////////////// 
    
   Elf64_Verdef*  pVerdef  = nullptr;
   Elf64_Verdaux* pVerdaux = nullptr; 
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
   
   while(Size){
       
      pVerdef = (Elf64_Verdef*)(pFile + pSHead->sh_offset + Offset); 
       
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerdef->vd_version; 
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerdef->vd_cnt;
      sData << " ndx:0x"    << hex << setw(4) << setfill('0') << pVerdef->vd_ndx; 
      sData << " hash:0x"   << hex << setw(4) << setfill('0') << pVerdef->vd_hash << endl; 
       
      Size   -= sizeof(Elf64_Verdef);
      Offset += sizeof(Elf64_Verdef); 
       
      pVerdaux = (Elf64_Verdaux*)(((char*)(pVerdef) + pVerdef->vd_aux)); 
       
      for(int n = 0; n < pVerdef->vd_cnt; n++){
         sData << "  name:0x" << hex << setw(8) << setfill('0') << pVerdaux->vda_name;     
         sData << " " << (char*)(pFile + pStrHead->sh_offset + pVerdaux->vda_name) << endl; 
         
         if(!n){
            if(pVerdef->vd_ndx > vGNUSymbol64.size() - 1) vGNUSymbol64.resize(pVerdef->vd_ndx + 10);
            vGNUSymbol64[pVerdef->vd_ndx] = (char*)(pFile + pStrHead->sh_offset + pVerdaux->vda_name);   
         }
         
         Size   -= sizeof(Elf64_Verdaux);
         Offset += sizeof(Elf64_Verdaux);
          
         pVerdaux++; 
          
      }
   }

   //////////////////////////////////////////////////
   
   ssection.Gnu_Verdef.pbuffer->set_text(sData.str());

   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verneed64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verneed64(Elf64_Shdr* pSHead){
    
   ostringstream sData;

   sData << ssection.Gnu_Verneed.pbuffer->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
   
   ////////////////////////////////////////////////// 
   
   Elf64_Verneed* pVerneed = nullptr;
   Elf64_Vernaux* pVernaux = nullptr; 
   
   Elf64_Shdr* pStrHead = &pSHead64[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;

   while(Size){   
      pVerneed = (Elf64_Verneed*)(pFile + pSHead->sh_offset + Offset);
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerneed->vn_version;
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerneed->vn_cnt;
      sData << " Name:" << (char*)(pFile + pStrHead->sh_offset + pVerneed->vn_file) << endl;

      Size   -= sizeof(Elf64_Verneed);
      Offset += sizeof(Elf64_Verneed);
      
      pVernaux = (Elf64_Vernaux*)(((char*)(pVerneed) + pVerneed->vn_aux));
      
      for(int n = 0; n < pVerneed->vn_cnt; n++){
         sData << "  Hash:0x" << hex << setw(8) << setfill('0') << pVernaux->vna_hash; 
         sData << " Flags:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_flags;
         sData << " Other:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_other;
         sData << " Name:" << (char*)(pFile + pStrHead->sh_offset + pVernaux->vna_name) << endl;
         
         if(pVernaux->vna_other > vGNUSymbol64.size() - 1) vGNUSymbol64.resize(pVernaux->vna_other + 10);
         vGNUSymbol64[pVernaux->vna_other] = (char*)(pFile + pStrHead->sh_offset + pVernaux->vna_name);
         
         pVernaux++;
         
         Size   -= sizeof(Elf64_Vernaux);
         Offset += sizeof(Elf64_Vernaux);
      }
   }

   //////////////////////////////////////////////////
   
   ssection.Gnu_Verneed.pbuffer->set_text(sData.str());
 
   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Versym64 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Versym64(Elf64_Shdr* pSHead){
    
   ostringstream sData;

   sData << ssection.Gnu_Versym.pbuffer->get_text().data();
   
   if(pSHStr64 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr64->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   ////////////////////////////////////////////////// 

   Elf64_Half* pVerdef = (Elf64_Half*)(pFile + pSHead->sh_offset);
   
   int cSym = pSHead->sh_size / sizeof(Elf64_Half);
   
   for(int n = 0; n < cSym; n++){
      int val = *pVerdef++;
      if(val >= 0x8000) val &= 0xFF; // can't figure out what 0x80 means :o(
      sData << "0x"          << hex << right << uppercase << setw(4) << setfill('0') << n;
      sData << " Version:0x" << hex << uppercase << setw(4) << setfill('0') << val;
      sData << " " << setw(17) << setfill(' ') << left << vGNUSymbol64[val].data();
      if(!((n + 1) % 4)) sData << endl;
   }

   //////////////////////////////////////////////////
   
   ssection.Gnu_Versym.pbuffer->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ read32bit ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::read32bit(){
    
   cout << "show_ELF32_Head" << endl;
   
   pElf32 = (Elf32_Ehdr*)pFile;
   
   show_ELF32_Head();
   
   cout << "show_ELF32_PHead" << endl;
      
   pPHead32 = (Elf32_Phdr*)(pFile + pElf32->e_phoff);
   
   show_ELF32_PHead();
   
   cout << "show_ELF32_SHead" << endl;
      
   pSHead32 = (Elf32_Shdr*)(pFile + pElf32->e_shoff);
   
   if(pElf32->e_shstrndx != SHN_UNDEF)
      pSHStr32 = &pSHead32[pElf32->e_shstrndx];

   show_ELF32_SHead();
   
   cout << "show_Section32" << endl;
      
   pSHead32 = (Elf32_Shdr*)(pFile + pElf32->e_shoff);
   
   show_Section32();
   
   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_ELF32_Head ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_ELF32_Head(){
 
   int Offset = 0, n = 1;
   
   ostringstream sNumber, sOffset, sSize, sValue, sMeaning;
   
   SAppend sAppend;
   
   sAppend.pTreeView = &stview.Elf.view;
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
   
   //////////////////////////////////
   
   show_hex(&shex.ElfHead.view, 0, sizeof(Elf32_Ehdr));
   
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
   
   sAppend.pTreeView = &stview.Pro.view;
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
   
   sAppend.pTreeView = &stview.Sec.view;
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
         sMeaning << "Name: " << (char*)(pFile + pSHStr32->sh_offset + pSHead32->sh_name); 
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
      if(pSHead32->sh_flags & SHF_COMPRESSED)       sMeaning << "[COMPRESSED]";
      
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
    
   Elf32_Shdr* pSHead = (Elf32_Shdr*)(pFile + pElf32->e_shoff);
   
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
   
   sData << ssection.Dynamic.pbuffer->get_text().data();
      
   //////////////////////////////////////////////////   
    
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 

   Elf32_Dyn* pDyn = (Elf32_Dyn*)(pFile + pSHead->sh_offset);
   
   int cDyn = pSHead->sh_size / sizeof(Elf64_Dyn); 
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   for(int n = 0; n < cDyn; n++){
      if(pDyn->d_tag == DT_NULL) break;
      sData << "0x"      << hex << uppercase << setw(2) << setfill('0') << n;
      sData << " Tag:0x" << hex << uppercase << setw(8) << setfill('0') << pDyn->d_tag;
      
      switch(pDyn->d_tag){
         case DT_NEEDED: 
            sData << setw(20) << setfill(' ') << "(DT_NEEDED)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " Name:" << (char*)(pFile + pStrHead->sh_offset + pDyn->d_un.d_val) << endl;
            break;   
         case DT_PLTRELSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PLTRELSZ)";
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_PLTGOT: 
            sData << setw(20) << setfill(' ') << "(DT_PLTGOT)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_HASH:            
            sData << setw(20) << setfill(' ') << "(DT_HASH)";
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_STRTAB:          
            sData << setw(20) << setfill(' ') << "(DT_STRTAB)";
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMTAB:          
            sData << setw(20) << setfill(' ') << "(DT_SYMTAB)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELA:            
            sData << setw(20) << setfill(' ') << "(DT_RELA)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_RELASZ:          
            sData << setw(20) << setfill(' ') << "(DT_RELASZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_RELAENT:         
            sData << setw(20) << setfill(' ') << "(DT_RELAENT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_STRSZ:           
            sData << setw(20) << setfill(' ') << "(DT_STRSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;   
         case DT_SYMENT:          
            sData << setw(20) << setfill(' ') << "(DT_SYMENT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break;
         case DT_INIT:            
            sData << setw(20) << setfill(' ') << "(DT_INIT)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_FINI:            
            sData << setw(20) << setfill(' ') << "(DT_FINI)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;   
         case DT_SONAME:          
            sData << setw(20) << setfill(' ') << "(DT_SONAME)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RPATH:           
            sData << setw(20) << setfill(' ') << "(DT_RPATH)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMBOLIC:    
            sData << setw(20) << setfill(' ') << "(DT_SYMBOLIC)" << endl; 
            break;
         case DT_REL:             
            sData << setw(20) << setfill(' ') << "(DT_REL)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_RELSZ:           
            sData << setw(20) << setfill(' ') << "(DT_RELSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_RELENT:          
            sData << setw(20) << setfill(' ') << "(DT_RELENT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PLTREL:          
            sData << setw(20) << setfill(' ') << "(DT_PLTREL)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_DEBUG:           
            sData << setw(20) << setfill(' ') << "(DT_DEBUG)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_TEXTREL:    
            sData << setw(20) << setfill(' ') << "(DT_TEXTREL)" << endl; 
            break;
         case DT_JMPREL:          
            sData << setw(20) << setfill(' ') << "(DT_JMPREL)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_BIND_NOW:    
            sData << setw(20) << setfill(' ') << "(DT_BIND_NOW)" << endl; 
            break;
         case DT_INIT_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAY)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_FINI_ARRAY:      
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAY)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_INIT_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_INIT_ARRAYSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_FINI_ARRAYSZ:    
            sData << setw(20) << setfill(' ') << "(DT_FINI_ARRAYSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << " bytes" << endl;
            break; 
         case DT_RUNPATH:         
            sData << setw(20) << setfill(' ') << "(DT_RUNPATH)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS:           
            sData << setw(20) << setfill(' ') << "(DT_FLAGS)";
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PREINIT_ARRAY:   
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAY)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_PREINIT_ARRAYSZ: 
            sData << setw(20) << setfill(' ') << "(DT_PREINIT_ARRAYSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_NUM:             
            sData << setw(20) << setfill(' ') << "(DT_NUM)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_PROCNUM:         
            sData << setw(20) << setfill(' ') << "(DT_PROCNUM)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         case DT_VERSYM:          
            sData << setw(20) << setfill(' ') << "(DT_VERSYM)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_RELACOUNT:       
            sData << setw(20) << setfill(' ') << "(DT_RELACOUNT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_RELCOUNT:        
            sData << setw(20) << setfill(' ') << "(DT_RELCOUNT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FLAGS_1:         
            sData << setw(20) << setfill(' ') << "(DT_FLAGS_1)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERDEF:          
            sData << setw(20) << setfill(' ') << "(DT_VERDEF)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERDEFNUM:       
            sData << setw(20) << setfill(' ') << "(DT_VERDEFNUM)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_VERNEED:         
            sData << setw(20) << setfill(' ') << "(DT_VERNEED)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break; 
         case DT_VERNEEDNUM:      
            sData << setw(20) << setfill(' ') << "(DT_VERNEEDNUM)";
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_AUXILIARY:       
            sData << setw(20) << setfill(' ') << "(DT_AUXILIARY)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         case DT_FILTER:          
            sData << setw(20) << setfill(' ') << "(DT_FILTER)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break; 
         //////////////////////////////////////////////////////////////////////
         //case DT_VALRNGLO:      cout << "DT_VALRNGLO"        << endl; break;
         case DT_GNU_PRELINKED:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_PRELINKED)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_CONFLICTSZ:  
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICTSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_GNU_LIBLISTSZ:   
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLISTSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_CHECKSUM:        
            sData << setw(20) << setfill(' ') << "(DT_CHECKSUM)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPADSZ:        
            sData << setw(20) << setfill(' ') << "(DT_PLTPADSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVEENT:         
            sData << setw(20) << setfill(' ') << "(DT_MOVEENT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVESZ:          
            sData << setw(20) << setfill(' ') << "(DT_MOVESZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_FEATURE_1:       
            sData << setw(20) << setfill(' ') << "(DT_FEATURE_1)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_POSFLAG_1:       
            sData << setw(20) << setfill(' ') << "(DT_POSFLAG_1)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINSZ:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINSZ)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_SYMINENT:        
            sData << setw(20) << setfill(' ') << "(DT_SYMINENT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         //case DT_VALRNGHI:      cout << "DT_VALRNGHI"        << endl; break;
         //////////////////////////////////////////////////////////////////////
         //case DT_ADDRRNGLO:     cout << "DT_ADDRRNGLO"       << endl; break;
         case DT_GNU_HASH:        
            sData << setw(20) << setfill(' ') << "(DT_GNU_HASH)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_PLT:    
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_PLT)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_TLSDESC_GOT:     
            sData << setw(20) << setfill(' ') << "(DT_TLSDESC_GOT)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_CONFLICT:    
            sData << setw(20) << setfill(' ') << "(DT_GNU_CONFLICT)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_GNU_LIBLIST:     
            sData << setw(20) << setfill(' ') << "(DT_GNU_LIBLIST)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_CONFIG:          
            sData << setw(20) << setfill(' ') << "(DT_CONFIG)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_DEPAUDIT:        
            sData << setw(20) << setfill(' ') << "(DT_DEPAUDIT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_AUDIT:           
            sData << setw(20) << setfill(' ') << "(DT_AUDIT)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_PLTPAD:          
            sData << setw(20) << setfill(' ') << "(DT_PLTPAD)"; 
            sData << " Val:0x" << setw(8) << setfill('0') << pDyn->d_un.d_val << endl;
            break;
         case DT_MOVETAB:         
            sData << setw(20) << setfill(' ') << "(DT_MOVETAB)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         case DT_SYMINFO:         
            sData << setw(20) << setfill(' ') << "(DT_SYMINFO)"; 
            sData << " Ptr:0x" << setw(8) << setfill('0') << pDyn->d_un.d_ptr << endl;
            break;
         //case DT_ADDRRNGHI:     cout << "DT_ADDRRNGHI"       << endl; break;
      }
         
      pDyn++;
   }
   
   //////////////////////////////////////////////////
   
   ssection.Dynamic.pbuffer->set_text(sData.str());

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
   
   sData << ssection.Relocation.pbuffer->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 
   
   //////////////////////////////////////////////////  
    
   if(pSHead->sh_type == SHT_RELA){
      pRela = (Elf32_Rela*)(pFile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf32_Rela);
   }else{
      pRel  = (Elf32_Rel*)(pFile + pSHead->sh_offset);
      cRelo = pSHead->sh_size / sizeof(Elf32_Rel);
   }
   
   Elf32_Shdr* pSymHead = &pSHead32[pSHead->sh_link];
   Elf32_Shdr* pStrHead = &pSHead32[pSymHead->sh_link];
   
   Elf32_Sym* pSymTab = (Elf32_Sym*)(pFile + pSymHead->sh_offset);
   
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

      sData << " Symbol:" << (char*)(pFile + pStrHead->sh_offset + pSymTab[Symbol].st_name) << endl;

      if(pSHead->sh_type == SHT_RELA) pRela++;
      else                            pRel++;
   }

   //////////////////////////////////////////////////
   
   ssection.Relocation.pbuffer->set_text(sData.str());

   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_SymTab32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_SymTab32(Elf32_Shdr* pSHead){
    
   ostringstream sData;

   sData << ssection.SymTab.pbuffer->get_text().data();
   
   //////////////////////////////////////////////////  
    
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   Elf32_Sym* pSymTab = (Elf32_Sym*)(pFile + pSHead->sh_offset);
   
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
      
      sData << " Name:" << (char*)(pFile + pStrHead->sh_offset + pSymTab->st_name) << endl;

      pSymTab++;    
   }   

   //////////////////////////////////////////////////
   
   ssection.SymTab.pbuffer->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_Note32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_Note32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
   
   sData << ssection.Note.pbuffer->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
      
   ////////////////////////////////////////////////// 
    
   while(Size){
       
      Elf32_Nhdr* pNote = (Elf32_Nhdr*)(pFile + pSHead->sh_offset + Offset);

      string strName = (char*)(pNote) + sizeof(Elf32_Nhdr);
      
      sData << "Name:" << strName << " Type:";

      if(!strName.compare("GNU")){
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
            default: sData << "unknown" << endl;
         } 
      }else
      if(!strName.compare("stapsdt")){
         uint32_t* pData = nullptr;
         uint32_t Location, Base, Semaphore;
         char* pProvider = nullptr;
         char* pName     = nullptr; 
         char* pArgument = nullptr;
         
         switch(pNote->n_type){
            case NT_STAPSDT:
               sData << "(NT_STAPSDT)";

               pData = (uint32_t*)((char*)(pNote) + sizeof(Elf32_Nhdr) + 8);
               
               Location  = *pData++;
               Base      = *pData++;
               Semaphore = *pData++;
               
               pProvider = (char*)(pData);
               pName     = pProvider + strlen(pProvider) + 1;
               pArgument = pName + strlen(pName) + 1;
               
               sData << " Provider:" << pProvider << " Name:" << pName << endl; 
               
               sData << " Location:0x"  << setw(8) << setfill('0') << Location;
               sData << " Base:0x"      << setw(8) << setfill('0') << Base;
               sData << " Semaphore:0x" << setw(8) << setfill('0') << Semaphore << " Argument:" << pArgument << endl;;
               
               break;     
             
            default: sData << "unknown" << endl; 
         }
      }else{
         sData << "(currently unsupported)" << endl;    
      }
      Size   -= (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf32_Nhdr));
      Offset += (ALIGN_UP(pNote->n_namesz, 4) + ALIGN_UP(pNote->n_descsz, 4) + sizeof(Elf32_Nhdr));
   }

   //////////////////////////////////////////////////
   
   ssection.Note.pbuffer->set_text(sData.str());

   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_String32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_String32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   uint32_t Size = pSHead->sh_size, Offset = pSHead->sh_offset;
   
   sData << ssection.String.pbuffer->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl; 
       
   //////////////////////////////////////////////////   
    
   int n = 0;
   
   while(Size){
    
      sData << "0x" << hex << uppercase << setw(4) << setfill('0') << n;    
      sData << " Offset:0x" << hex << uppercase << setw(8) << setfill('0') << Offset;
      sData << " " << (char*)(pFile + Offset) << endl;
      
      Size   -= strlen((char*)(pFile + Offset)) + 1;
      Offset += strlen((char*)(pFile + Offset)) + 1;
      n++;
   }
    
   //////////////////////////////////////////////////
   
   ssection.String.pbuffer->set_text(sData.str());

   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verdef32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verdef32(Elf32_Shdr* pSHead){
    
   ostringstream sData;
   
   sData << ssection.Gnu_Verdef.pbuffer->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;

   ////////////////////////////////////////////////// 

   Elf32_Verdef*  pVerdef  = nullptr;
   Elf32_Verdaux* pVerdaux = nullptr; 
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;
    
   while(Size){
       
      pVerdef = (Elf32_Verdef*)(pFile + pSHead->sh_offset + Offset); 
       
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerdef->vd_version; 
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerdef->vd_cnt;
      sData << " ndx:0x"    << hex << setw(4) << setfill('0') << pVerdef->vd_ndx; 
      sData << " hash:0x"   << hex << setw(4) << setfill('0') << pVerdef->vd_hash << endl; 
       
      Size   -= sizeof(Elf32_Verdef);
      Offset += sizeof(Elf32_Verdef); 
       
      pVerdaux = (Elf32_Verdaux*)(((char*)(pVerdef) + pVerdef->vd_aux)); 
       
      for(int n = 0; n < pVerdef->vd_cnt; n++){
         sData << "  name:0x" << hex << setw(8) << setfill('0') << pVerdaux->vda_name;     
         sData << " " << (char*)(pFile + pStrHead->sh_offset + pVerdaux->vda_name) << endl; 
         
         if(!n){
            if(pVerdef->vd_ndx > vGNUSymbol32.size() - 1) vGNUSymbol32.resize(pVerdef->vd_ndx + 10);
            vGNUSymbol32[pVerdef->vd_ndx] = (char*)(pFile + pStrHead->sh_offset + pVerdaux->vda_name);   
         }
         
         Size   -= sizeof(Elf32_Verdaux);
         Offset += sizeof(Elf32_Verdaux);
          
         pVerdaux++; 
          
      }
   }
   
   //////////////////////////////////////////////////
   
   ssection.Gnu_Verdef.pbuffer->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Verneed32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Verneed32(Elf32_Shdr* pSHead){
    
   ostringstream sData;

   sData << ssection.Gnu_Verneed.pbuffer->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;

   //////////////////////////////////////////////////  
    
   Elf32_Verneed* pVerneed = nullptr;
   Elf32_Vernaux* pVernaux = nullptr; 
   
   Elf32_Shdr* pStrHead = &pSHead32[pSHead->sh_link];
   
   uint32_t Size = pSHead->sh_size, Offset = 0;

   while(Size){
      pVerneed = (Elf32_Verneed*)(pFile + pSHead->sh_offset + Offset);
      sData << "Version:0x" << hex << setw(4) << setfill('0') << pVerneed->vn_version;
      sData << " Count:0x"  << hex << setw(4) << setfill('0') << pVerneed->vn_cnt;
      sData << " Name:" << (char*)(pFile + pStrHead->sh_offset + pVerneed->vn_file) << endl;

      Size   -= sizeof(Elf32_Verneed);
      Offset += sizeof(Elf32_Verneed);

      pVernaux = (Elf32_Vernaux*)(((char*)(pVerneed) + pVerneed->vn_aux));
      
      for(int n = 0; n < pVerneed->vn_cnt; n++){
         sData << "  Hash:0x" << hex << setw(8) << setfill('0') << pVernaux->vna_hash; 
         sData << " Flags:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_flags;
         sData << " Other:0x" << hex << setw(4) << setfill('0') << pVernaux->vna_other;
         sData << " Name:" << (char*)(pFile + pStrHead->sh_offset + pVernaux->vna_name) << endl;

         if(pVernaux->vna_other > vGNUSymbol32.size() - 1) vGNUSymbol32.resize(pVernaux->vna_other + 10);
         vGNUSymbol32[pVernaux->vna_other] = (char*)(pFile + pStrHead->sh_offset + pVernaux->vna_name);

         Size   -= sizeof(Elf32_Vernaux);
         Offset += sizeof(Elf32_Vernaux);

         pVernaux++;
      }
   }

   //////////////////////////////////////////////////
   
   ssection.Gnu_Verneed.pbuffer->set_text(sData.str());

   return(C_APP_READY);
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_GNU_Versym32 ]
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_GNU_Versym32(Elf32_Shdr* pSHead){
    
   ostringstream sData;

   sData << ssection.Gnu_Versym.pbuffer->get_text().data();
   
   if(pSHStr32 != nullptr)
      sData << "Name:" << (char*)(pFile + pSHStr32->sh_offset + pSHead->sh_name) << endl;
   else
      sData << "Name:Unknown" << endl;
       
   ////////////////////////////////////////////////// 
    
   Elf32_Half* pVerdef = (Elf32_Half*)(pFile + pSHead->sh_offset);
   
   int cSym = pSHead->sh_size / sizeof(Elf32_Half);

   for(int n = 0; n < cSym; n++){
      uint16_t val = *pVerdef++;
      if(val >= 0x8000) val &= 0xFF; // can't figure out what 0x80 means :o(
      sData << "0x"          << hex << right << uppercase << setw(4) << setfill('0') << n;
      sData << " Version:0x" << hex << uppercase << setw(4) << setfill('0') << val;
      sData << " " << setw(17) << setfill(' ') << left << vGNUSymbol32[val].data();
      if(!((n + 1) % 4)) sData << endl;
   }
   
   //////////////////////////////////////////////////
   
   ssection.Gnu_Versym.pbuffer->set_text(sData.str());

   return(C_APP_READY); 
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_tv_elf_changed ]  
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_tv_elf_changed(){

   shex.ElfHead.pbuffer->remove_all_tags(shex.ElfHead.pbuffer->begin(), shex.ElfHead.pbuffer->end());
    
   Gtk::TreeModel::iterator iter = stview.Elf.view.get_selection()->get_selected(); 
   Gtk::TextBuffer::iterator iStart, iStop;

   if(iter){
      Gtk::TreeModel::Row row = *iter;

      Glib::ustring strOffset = row[stview.Elf.view.m_Columns.m_col_offset];
      Glib::ustring strSize   = row[stview.Elf.view.m_Columns.m_col_size];

      uint64_t Offset = stoi(strOffset.data(), nullptr, 0);
      uint64_t Size   = stoi(strSize.data(),   nullptr, 0);
      uint64_t Teile = Offset / 16;
      uint64_t Start = (Teile + 1) * 14 + Teile * 20 + Offset * 3;
      uint64_t Stop = Start + Size * 3 - 1;
      
      iStart = shex.ElfHead.pbuffer->get_iter_at_offset(Start);
      iStop  = shex.ElfHead.pbuffer->get_iter_at_offset(Stop);
      
      shex.ElfHead.pbuffer->apply_tag(stag.BG_Black, iStart, iStop); 
      shex.ElfHead.pbuffer->apply_tag(stag.FG_Green, iStart, iStop);
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_tv_pro_changed ]  
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_tv_pro_changed(){

   shex.ProHead.pbuffer->remove_all_tags(shex.ProHead.pbuffer->begin(), shex.ProHead.pbuffer->end());
   
   Gtk::TreeModel::iterator iter = stview.Pro.view.get_selection()->get_selected();
   Gtk::TextBuffer::iterator iStart, iStop;
   
   if(iter){
      Gtk::TreeModel::Row row = *iter;
      
      Glib::ustring strOffset = row[stview.Pro.view.m_Columns.m_col_offset];
      Glib::ustring strSize   = row[stview.Pro.view.m_Columns.m_col_size];
      
      uint64_t SegOffset = 0, SegSize = 0, OffsetHdr = 0, SizeHdr = 0;

      Gtk::TreeModel::iterator iParent = row.parent();
      
      if(iParent){
         Gtk::TreeModel::Row rParent= *iParent;
         Glib::ustring strOffset = rParent[stview.Pro.view.m_Columns.m_col_offset];
         OffsetHdr = stoi(strOffset.data(), nullptr, 0);

         if(pFile[EI_CLASS] == ELFCLASS32){
            SegOffset = ((Elf32_Phdr*)(pFile + OffsetHdr))->p_offset;
            SegSize   = ((Elf32_Phdr*)(pFile + OffsetHdr))->p_filesz;
            SizeHdr   = sizeof(Elf32_Phdr);
         }else{
            SegOffset = ((Elf64_Phdr*)(pFile + OffsetHdr))->p_offset;
            SegSize   = ((Elf64_Phdr*)(pFile + OffsetHdr))->p_filesz;
            SizeHdr   = sizeof(Elf64_Phdr);
         }
         
         show_hex(&shex.ProHead.view, OffsetHdr, SizeHdr);
         show_hex(&shex.ProFile.view, SegOffset, SegSize);
         
      }else{
         OffsetHdr = stoi(strOffset.data(), nullptr, 0);
         
         if(pFile[EI_CLASS] == ELFCLASS32){
            SegOffset = ((Elf32_Phdr*)(pFile + OffsetHdr))->p_offset;
            SegSize   = ((Elf32_Phdr*)(pFile + OffsetHdr))->p_filesz;
            SizeHdr   = sizeof(Elf32_Phdr);
         }else{
            SegOffset = ((Elf64_Phdr*)(pFile + OffsetHdr))->p_offset;
            SegSize   = ((Elf64_Phdr*)(pFile + OffsetHdr))->p_filesz;
            SizeHdr   = sizeof(Elf64_Phdr);
         }
         
         show_hex(&shex.ProHead.view, OffsetHdr, SizeHdr);
         show_hex(&shex.ProFile.view, SegOffset, SegSize);
      }
      
      uint64_t Offset = stoi(strOffset.data(), nullptr, 0);
      
      Offset -= OffsetHdr;
      
      uint64_t Size   = stoi(strSize.data(),   nullptr, 0);
      uint64_t Teile = Offset / 16;
      uint64_t Start = (Teile + 1) * 14 + Teile * 20 + Offset * 3;
      uint64_t Stop = Start + Size * 3 - 1;
      
      iStart = shex.ProHead.pbuffer->get_iter_at_offset(Start);
      iStop  = shex.ProHead.pbuffer->get_iter_at_offset(Stop);
      
      shex.ProHead.pbuffer->apply_tag(stag.BG_Black, iStart, iStop); 
      shex.ProHead.pbuffer->apply_tag(stag.FG_Green, iStart, iStop);
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_tv_sec_changed ]  
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_tv_sec_changed(){

   shex.SecHead.pbuffer->remove_all_tags(shex.SecHead.pbuffer->begin(), shex.SecHead.pbuffer->end());
   
   Gtk::TreeModel::iterator iter = stview.Sec.view.get_selection()->get_selected();
   Gtk::TextBuffer::iterator iStart, iStop;
   
   if(iter){
      Gtk::TreeModel::Row row = *iter;
      
      Glib::ustring strOffset = row[stview.Sec.view.m_Columns.m_col_offset];
      Glib::ustring strSize   = row[stview.Sec.view.m_Columns.m_col_size];
      
      uint64_t SegOffset = 0, SegSize = 0, OffsetHdr = 0, SizeHdr = 0;
      
      Gtk::TreeModel::iterator iParent = row.parent();
      
      if(iParent){
         Gtk::TreeModel::Row rParent= *iParent;
         Glib::ustring strOffset = rParent[stview.Sec.view.m_Columns.m_col_offset];
         OffsetHdr = stoi(strOffset.data(), nullptr, 0);
         
         if(pFile[EI_CLASS] == ELFCLASS32){
            SegOffset = ((Elf32_Shdr*)(pFile + OffsetHdr))->sh_offset;
            SegSize   = ((Elf32_Shdr*)(pFile + OffsetHdr))->sh_size;
            SizeHdr   = sizeof(Elf32_Shdr);
         }else{
            SegOffset = ((Elf64_Shdr*)(pFile + OffsetHdr))->sh_offset;
            SegSize   = ((Elf64_Shdr*)(pFile + OffsetHdr))->sh_size;
            SizeHdr   = sizeof(Elf64_Shdr);
         }
         
         show_hex(&shex.SecHead.view, OffsetHdr, SizeHdr);
         show_hex(&shex.SecFile.view, SegOffset, SegSize);
         
      }else{
         OffsetHdr = stoi(strOffset.data(), nullptr, 0);
         
         if(pFile[EI_CLASS] == ELFCLASS32){
            SegOffset = ((Elf32_Shdr*)(pFile + OffsetHdr))->sh_offset;
            SegSize   = ((Elf32_Shdr*)(pFile + OffsetHdr))->sh_size;
            SizeHdr   = sizeof(Elf32_Shdr);
         }else{
            SegOffset = ((Elf64_Shdr*)(pFile + OffsetHdr))->sh_offset;
            SegSize   = ((Elf64_Shdr*)(pFile + OffsetHdr))->sh_size;
            SizeHdr   = sizeof(Elf64_Shdr);
         }
         
         show_hex(&shex.SecHead.view, OffsetHdr, SizeHdr);
         show_hex(&shex.SecFile.view, SegOffset, SegSize);
      }
      
      uint64_t Offset = stoi(strOffset.data(), nullptr, 0);
      
      Offset -= OffsetHdr;
      
      uint64_t Size   = stoi(strSize.data(),   nullptr, 0);
      uint64_t Teile = Offset / 16;
      uint64_t Start = (Teile + 1) * 14 + Teile * 20 + Offset * 3;
      uint64_t Stop = Start + Size * 3 - 1;
      
      iStart = shex.SecHead.pbuffer->get_iter_at_offset(Start);
      iStop  = shex.SecHead.pbuffer->get_iter_at_offset(Stop);
      
      shex.SecHead.pbuffer->apply_tag(stag.BG_Black, iStart, iStop); 
      shex.SecHead.pbuffer->apply_tag(stag.FG_Green, iStart, iStop);
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ show_hex ]  
//////////////////////////////////////////////////////////////////////////////////
int C_App::show_hex(Gtk::TextView* pTV, uint64_t Offset, uint64_t Size){
    
   ostringstream sData; 
    
   uint64_t vaddress = (uint64_t)pFile + Offset, i, j, BYTESPERLINE = 16;
   char ch;

   for(i = 0; i < Size; i += BYTESPERLINE){

      ///////////////////////////////////////////////////////////
      // Offset
      sData << "0x" << hex << uppercase << setw(8) << setfill('0') << Offset + i << " || ";
      
      ///////////////////////////////////////////////////////////
      // Hex
      for(j = 0; j < BYTESPERLINE; j++){
         if(i + j == Size){
            for(uint64_t x = 0; x < (BYTESPERLINE - j - 1); x++) sData << "   ";
            sData << "  ";
            break;
         }
         sData << hex << uppercase << setw(2) << setfill('0') << (int)*(unsigned char*)(vaddress + i + j);
         if(j != BYTESPERLINE - 1) sData << " ";
      }

      ///////////////////////////////////////////////////////////
      // Asccii
      sData << " || ";

      for(j = 0; j < BYTESPERLINE; j++){
         if(i + j == Size) break;
         ch = *(unsigned char*)(vaddress + i + j);
         if(isalnum(ch) || ch == ' ') sData << ch;
         else                         sData << ".";
      }
      sData << endl;
   }
   
   //////////////////////////////////////////////////

   pTV->get_buffer()->set_text(sData.str());

   return(C_APP_READY);  
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_configure_changed ]
//////////////////////////////////////////////////////////////////////////////////
bool C_App::on_configure_changed(GdkEventConfigure* configure_event){
   if(!this->is_maximized()){
      spaned.VElf.set_position(configure_event->height / 2);
      spaned.HPro.set_position(configure_event->width  / 2);
      spaned.VPro.set_position(configure_event->height / 2);
      spaned.HSec.set_position(configure_event->width  / 2);
      spaned.VSec.set_position(configure_event->height / 2);
   }
   return(false);
}
