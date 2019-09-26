#include "guiIncludes.h"
#include "objects/movieManager.h"
#include "estructuras/LinkedList.h"

movieManager manager;

Fl_Text_Buffer *buff;
Fl_Text_Display *disp;
Fl_Window *win, *mwin;
LinkedList<Fl_Box*> lbx= LinkedList<Fl_Box*>();
Fl_Color c = fl_rgb_color(4,44,98);
Fl_Button *nxt, *bck;
int arrPel[9]={0,1,2,3,4,5,6,7,8};
Fl_Group* Pl_group ;

void button_cb( Fl_Widget*, void* );
void nxt_cb( Fl_Widget* , void*);
void bck_cb( Fl_Widget* , void*);
void info_cb( Fl_Widget* obj , void* data);
void createBoxes(){
    Pl_group->box(FL_UP_BOX);

    {auto *box = new Fl_Button(10, 10, 158, 300, "peli1");
        box->box(FL_UP_FRAME);

    }
    {auto *box1 = new Fl_Button(168, 10, 158, 300, "peli2");
        box1->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button( 326, 10, 158, 300, "peli3");
        box->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button( 484, 10, 158, 300, "peli4");
        box->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button(642, 10, 158, 300, "peli5");
        box->box(FL_UP_BOX);

       }
    {auto *box = new Fl_Button(10, 310, 158, 300, "peli6");
        box->box(FL_UP_BOX);

       }
    {auto *box = new Fl_Button(168, 310, 158, 300, "peli7");
        box->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button(326, 310, 158, 300, "peli8");
        box->box(FL_UP_BOX);

       }
    {auto *box = new Fl_Button(484, 310, 158, 300, "peli9");
        box->box(FL_UP_BOX);


        }
        Pl_group->end();
    Pl_group->hide();
    char *pos;
    Pl_group->child(0)->callback(info_cb,pos="0");
    Pl_group->child(1)->callback(info_cb,pos="1");
    Pl_group->child(2)->callback(info_cb,pos="2");
    Pl_group->child(3)->callback(info_cb,pos="3");
    Pl_group->child(4)->callback(info_cb,pos="4");
    Pl_group->child(5)->callback(info_cb,pos="5");
    Pl_group->child(6)->callback(info_cb,pos="6");
    Pl_group->child(7)->callback(info_cb,pos="7");
    Pl_group->child(8)->callback(info_cb,pos="8");


};
void make_window(){
    win = new Fl_Window(1266, 768,"TECFlix");
    win->begin();

    win->color(c);
    Fl_Button* but = new Fl_Button( 700, 540, 100, 40, "Comenzar" );
    but -> callback( ( Fl_Callback* ) button_cb );
    nxt=new Fl_Button( 750, 620, 100, 40, "@->" );
    bck =new Fl_Button( 650, 620, 100, 40, "@<-" );
    bck->hide();
    nxt->hide();
    Pl_group=new Fl_Group(10, 10, 800, 600);
    createBoxes();

    win->resizable(*disp);
    win->show();





};

void newWind(int pos){
    mwin = new Fl_Window(800, 600);
    mwin->begin();
    mwin->color(c);
    buff = new Fl_Text_Buffer();
    disp = new Fl_Text_Display(10, 10, 780, 500);
    disp->buffer(buff);
    Movie mact=manager.getLActual()->getElement(pos)->getData();
    mwin->label(mact.getTitulo().c_str());
    std::map<std::string, std::string> mapapeli= mact.getMovInfo();
    std::map<std::string, std::string>::iterator itr;
    std::string infoVent="";
    infoVent.append("trailer: ");
    infoVent.append(mact.getTrailer());
    infoVent.append("\n");

    for (itr = mapapeli.begin(); itr != mapapeli.end(); ++itr) {
        infoVent.append(itr->first+": "+itr->second+"\n"+"\n");

    }
    Fl_Button *button_Trailer = new Fl_Button(700,550,80,40,"Trailer");

    buff->text(infoVent.c_str());
    mwin->show();
};


void button_cb( Fl_Widget* obj , void* data ){

    manager.beginPages();


    nxt->show();
    nxt -> callback( ( Fl_Callback* ) nxt_cb );
    bck->show();
    bck->callback(( Fl_Callback* )bck_cb);
    Pl_group->show();

    win->redraw();
    obj->hide();
    };


void nxt_cb( Fl_Widget* obj , void* data){



    manager.nextPage();
}
void bck_cb( Fl_Widget* obj , void* data){
        manager.backPage();
}
void info_cb( Fl_Widget* obj , void* data){

    char *num= (char*)data;

    newWind(atoi(num));
}

int main(int argc, char **argv) {

    make_window();



    return Fl::run();

}