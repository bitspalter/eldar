//////////////////////////////////////////////////////////////////////////////////
// [ C_GUI_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_GUI.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]  
//////////////////////////////////////////////////////////////////////////////////
C_GUI::C_GUI(){

   this->set_default_size(920, 600);

   ////////////////////////
   
   signal_configure_event().connect(sigc::mem_fun(*this, &C_GUI::on_configure_changed), false);
   
   //////////////////////////////////////////////////////////////
   // Button
   sbutton.open.set_label("open");
   sbutton.open.set_size_request(110, 30);
   
   sbutton.save.set_label("save");
   sbutton.save.set_size_request(110, 30);
   sbutton.save.set_sensitive(false);
   
   ///////////////////////////////////
   // TreeView 
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
   //shex.ElfHead.window.set_border_width(10);
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
   //shex.ProHead.window.set_border_width(10);
   shex.ProHead.view.override_font(fHex);
   shex.ProHead.view.set_buffer(shex.ProHead.pbuffer);
   shex.ProHead.view.override_color(colorF);
   shex.ProHead.view.override_background_color(colorB);
   
   shex.ProFile.pbuffer = Gtk::TextBuffer::create();
   shex.ProFile.window.add(shex.ProFile.view);
   shex.ProFile.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   //shex.ProFile.window.set_border_width(10);
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
   //shex.SecHead.window.set_border_width(10);
   shex.SecHead.view.override_font(fHex);
   shex.SecHead.view.set_buffer(shex.SecHead.pbuffer);
   shex.SecHead.view.override_color(colorF);
   shex.SecHead.view.override_background_color(colorB);
   
   shex.SecFile.pbuffer = Gtk::TextBuffer::create();
   shex.SecFile.window.add(shex.SecFile.view);
   shex.SecFile.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   //shex.SecFile.window.set_border_width(10);
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
   mNBook.append_page(spaned.VElf, "ELF header");
   mNBook.append_page(spaned.VPro, "Program header");
   mNBook.append_page(spaned.VSec, "Section header");
   mNBook.append_page(sBox,    "Section");

   ///////////////////////////

   sNBook.append_page(ssection.Relocation.window,  "Relocation");
   sNBook.append_page(ssection.SymTab.window,      "Symbol Table");
   sNBook.append_page(ssection.Dynamic.window,     "Dynamic");
   sNBook.append_page(ssection.Note.window,        "Notes");
   sNBook.append_page(ssection.String.window,      "Strings");
   sNBook.append_page(ssection.Gnu_Verdef.window,  "GNU Verdef");
   sNBook.append_page(ssection.Gnu_Verneed.window, "GNU Verneed");
   sNBook.append_page(ssection.Gnu_Versym.window,  "GNU Versym");
   
   sBox.pack_start(sNBook);

   //////////////////////////////////////////////////////////////
   // HeaderBar
   set_titlebar(header);
   
   header.set_title("eldar");
   header.set_subtitle("Welcome");
   header.set_show_close_button();
   header.pack_start(sbutton.open);
   header.pack_start(sbutton.save);
   
   ///////////////////////////////////////////////////////

   add(mBox);

   mBox.pack_start(mNBook);
   
   ////////////////////////
   
   show_all_children();
}
//////////////////////////////////////////////////////////////////////////////////
// [ appand ]
//////////////////////////////////////////////////////////////////////////////////
Gtk::TreeModel::Row C_GUI::appand(Gtk::TreeModel::Row* pParent, SAppend* pSAppend){
   
   Gtk::TreeModel::iterator iter;
   Gtk::TreeModel::Row row;
   
   if(pParent == nullptr) iter = pSAppend->pTreeView->TStore->append();
   else                   iter = pSAppend->pTreeView->TStore->append(pParent->children());

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
// [ on_configure_changed ]
//////////////////////////////////////////////////////////////////////////////////
bool C_GUI::on_configure_changed(GdkEventConfigure* configure_event){
   
   if(configure_event->send_event) return(false);
   
  // if(!this->is_maximized()){
      spaned.VElf.set_position(configure_event->height / 2);
      spaned.HPro.set_position(configure_event->width  / 2);
      spaned.VPro.set_position(configure_event->height / 2);
      spaned.HSec.set_position(configure_event->width  / 2);
      spaned.VSec.set_position(configure_event->height / 2);
   //}
   
   return(false);
}
