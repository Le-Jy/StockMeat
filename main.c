#include <gtk/gtk.h>
#include "Game/game.h"
#include <math.h>

GtkWidget *fixed;

GtkWidget *fixed2;
GtkWidget *general;
GtkWidget* window;
size_t win = 0;

GtkWidget *bishop;
GtkWidget *rook;
GtkWidget *queen;
GtkWidget *knight;

GtkWidget *title;
GtkWidget *wturn;

GtkWidget *endWindow;

GtkWidget *stack;

GtkWidget *launchGame;
GtkWidget *winnerLabel;

GtkWidget *welcome;
GtkWidget *playLabel;
GtkWidget *stop;
GtkWidget *stopLabel;
GtkWidget *checkLabel;
GtkWidget *checkMateLabel;

int hasmoved;
struct piece** board;
int checkMatevalue;
int check;
unsigned long turn;
int bx,by,bxx,byy;
int castle = 0;

gint x = -1;
gint y = -1;

gint dest_x = -1;
gint dest_y = -1;

GtkWidget *one;
GtkWidget *two;

GtkWidget* toMove;
GtkWidget *choose;
GdkPixbuf* chooseimg;

GtkWidget* getWidget(int x, int y)
{
    GList *children = gtk_container_get_children(GTK_CONTAINER(fixed));
    GtkWidget* res = NULL;
    int len = g_list_length(children);
    for(int i = 0; i < len; i++)
    {
        GtkWidget *widget = (GtkWidget*)g_list_nth_data(children, i);
        int wx,wy;
        gtk_widget_translate_coordinates(widget, gtk_widget_get_toplevel(widget), 0, 0, &wx, &wy);
        wx = wx-76;
        wy = wy-110;
        if(wx == x && wy == y && gtk_widget_get_allocated_width(widget) == 100)
        {
            res = widget;
            break;
        }
    }
    return res;
}

static gboolean button_press_callback (GtkWidget *event_box, GdkEventButton *event)
{
    gtk_widget_set_name(event_box, "box");
    if(x == -1 && y == -1)
    {
        x = event->x;
        y = event->y;
        x = floor(x/100)*100;
        y = floor(y/100)*100;

        int found = 0;
        
        toMove = getWidget(x, y);
        if(toMove != NULL)
        {
            found = 1;
            gtk_fixed_put(GTK_FIXED(fixed), choose, x, y);
        }

        if(found == 0)
        {
            x = -1;
            y = -1;
        }

        return TRUE;
    }

    if(x != -1 && y != -1 && dest_x == -1 && dest_y == -1)
    {
        dest_x = event->x;
        dest_y = event->y;
        dest_x = floor(dest_x/100)*100;
        dest_y = floor(dest_y/100)*100;
    }

    if(dest_x != -1 && x!=-1 && dest_y != -1 && y!=-1)
    {
        gtk_container_remove(GTK_CONTAINER(fixed), choose);
        chooseimg = gdk_pixbuf_new_from_file_at_scale ("chess/choose.png", 100, 100, TRUE, NULL);
        choose = gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE(choose), chooseimg);
        gtk_widget_show(choose);
        
        bx = floor(x/100);                
        by = floor(y/100);
        bxx = floor(dest_x/100);
        byy = floor(dest_y/100);

        if((turn%2 == 0 && board[bx + 8*by]->color == WHITE) || (turn%2 == 1 && board[bx + 8*by]->color == BLACK))
        {
            printf("Start\n");
            if(board[bx+8*by]->role == KING && board[bxx+byy*8]->role == ROOK)
            {
                printf("Try castle\n");
                GtkWidget* first = getWidget(bx*100, by*100);
                GtkWidget* second = getWidget(bxx*100, byy*100);
                if(bxx>bx && canShortCastle(board,board[bx+8*by]))
                {
                    printf("Try short castle\n");
                    castle = 1;
                    shortCastle(board,board[bx+8*by]);
                    bxx = bxx - 1;
                    bx = 5;
                    printf("Did short castle\n");
                    
                    gtk_fixed_move(GTK_FIXED(fixed), first, 600, by*100);
                    gtk_fixed_move(GTK_FIXED(fixed), second, 500, by*100);
                    hasmoved = 1;
                }
                if(bxx<bx && canLongCastle(board,board[bx+8*by]))
                {
                    printf("Try long castle\n");
                    
                    castle = 1;
                    //printf("testr2\n");
                    longCastle(board,board[bx+8*by]);
                    bxx = bxx + 2;
                    bx = 3;
                    hasmoved = 1;
                    //toMove = widget;
                    //printf("%f\n", floor(dest_x));
                    printf("Did long castle\n");
                    
                    gtk_fixed_move(GTK_FIXED(fixed), first, 2*100, by*100);
                    gtk_fixed_move(GTK_FIXED(fixed), second, 3*100, by*100);
                }
            }
            else
            {
                printf("Try to move\n");
                int moved = move(board,board[bx + by*8],bxx,byy);
                if(moved)
                {
                    printf("Did move %i\n",board[bxx+byy*8]->role);
                    if(moved >= 1)
                    {
                        int mx = moved % 8;
                        int my = moved / 8;
                        GList *c = gtk_container_get_children(GTK_CONTAINER(fixed));
                        for (guint i = 0; i < g_list_length(c); ++i) 
                        {
                            GtkWidget* widget = (GtkWidget*)g_list_nth_data(c, i);
                            int wx = 0;
                            int wy = 0;
                            gtk_widget_translate_coordinates(widget, gtk_widget_get_toplevel(widget), 0, 0, &wx, &wy);
                            wx = wx-76;
                            wy = wy-110;
                            wx = wx / 100;
                            wy = wy / 100;
                            if(mx == wx && my == wy && gtk_widget_get_allocated_width(widget) == 100)
                            {
                                gtk_widget_destroy(widget);
                                break;
                            }
                        }
                    }
                    hasmoved = 1;
                    //toMove = widget;
                    //printf("%f\n", floor(dest_x));
                    
                    gtk_fixed_move(GTK_FIXED(fixed), toMove, floor(dest_x/100)*100, floor(dest_y/100)*100);
                }
            }
            
        }

        if(hasmoved == 1)
        {
            
            hasmoved=0;
            if(canPromote(board[bxx+byy*8]))
            {
                // quel role il choisit

                gtk_widget_show (bishop);
                gtk_widget_show (queen);
                gtk_widget_show (knight);
                gtk_widget_show (rook);

                gtk_widget_set_sensitive (GTK_WIDGET(bishop), TRUE);
                gtk_widget_set_sensitive (GTK_WIDGET(queen), TRUE);
                gtk_widget_set_sensitive (GTK_WIDGET(knight), TRUE);
                gtk_widget_set_sensitive (GTK_WIDGET(rook), TRUE);
                printf("role promoted : %i\n",board[bxx+byy*8]->role);

            }
            printf("Try to check\n");
            if(isCheckinG(board,bxx,byy))
            {
                printf("Try to checkmate\n");
                int temp = checkMate(board,board[bxx+byy*8]->color*-1,bxx,byy);
                printf("Checkmate : %i\n",temp);
                castle = 0;
                if(temp)
                {
                    gtk_widget_show(wturn);
                    gtk_widget_show(checkMateLabel);
                    if(board[bxx+byy*8]->color == BLACK)
                    {
                        gtk_label_set_text(GTK_LABEL(wturn), "Black have won");
                    }
                    else
                    {
                        gtk_label_set_text(GTK_LABEL(wturn), "White have won");
                    }
                    return TRUE;
                }
                gtk_widget_show(checkLabel);
                printf("check\n");
            }
            else if(castle && isCheckinG(board,bx,byy))
            {
                printf("Try checkmate castle\n");
                castle = 0;
                int temp = checkMate(board,board[bx+byy*8]->color*-1,bx,byy);
                printf("Checkmate castle : %i\n",temp);
                if(temp)
                {
                    gtk_widget_show(wturn);
                    gtk_widget_show(checkMateLabel);
                    if(board[bx+byy*8]->color == BLACK)
                    {
                        gtk_label_set_text(GTK_LABEL(wturn), "Black have won");
                    }
                    else
                    {
                        gtk_label_set_text(GTK_LABEL(wturn), "White have won");
                    }
                    return TRUE;
                }
                gtk_widget_show (checkLabel);
            }
            else
            {
                gtk_widget_hide (checkLabel);
            }
            turn++;
            if(turn%2 == 1)
            {
                gtk_label_set_text(GTK_LABEL(wturn), "Turn to BLACK");
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(wturn), "Turn to WHITE");
            }
            printf("End\n");            
        }    


        x = -1;
        y = -1;
        dest_x = -1;
        dest_y = -1;
        return TRUE;
    }
    return TRUE;              
}             

void set_image()
{

    chooseimg = gdk_pixbuf_new_from_file_at_scale ("chess/choose.png", 100, 100, TRUE, NULL);

    choose = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(choose), chooseimg);
    gtk_widget_show(choose);

    GdkPixbuf* img = gdk_pixbuf_new_from_file_at_scale ("chess/black/pion.png", 100, 100, TRUE, NULL);
    GdkPixbuf* img2 = gdk_pixbuf_new_from_file_at_scale ("chess/white/pion.png", 100, 100, TRUE, NULL);

    GdkPixbuf* tour = gdk_pixbuf_new_from_file_at_scale ("chess/black/tour.png", 100, 100, TRUE, NULL);
    GdkPixbuf* cavalier = gdk_pixbuf_new_from_file_at_scale ("chess/black/cavalier.png", 100, 100, TRUE, NULL);
    GdkPixbuf* fou = gdk_pixbuf_new_from_file_at_scale ("chess/black/fou.png", 100, 100, TRUE, NULL);
    GdkPixbuf* roi = gdk_pixbuf_new_from_file_at_scale ("chess/black/roi.png", 100, 100, TRUE, NULL);
    GdkPixbuf* reine = gdk_pixbuf_new_from_file_at_scale ("chess/black/reine.png", 100, 100, TRUE, NULL);

    GdkPixbuf* toub = gdk_pixbuf_new_from_file_at_scale ("chess/white/tour.png", 100, 100, TRUE, NULL);
    GdkPixbuf* cavalieb = gdk_pixbuf_new_from_file_at_scale ("chess/white/cavalier.png", 100, 100, TRUE, NULL);
    GdkPixbuf* fob = gdk_pixbuf_new_from_file_at_scale ("chess/white/fou.png", 100, 100, TRUE, NULL);
    GdkPixbuf* rob = gdk_pixbuf_new_from_file_at_scale ("chess/white/roi.png", 100, 100, TRUE, NULL);
    GdkPixbuf* reinb = gdk_pixbuf_new_from_file_at_scale ("chess/white/reine.png", 100, 100, TRUE, NULL);

    // pions noirs

    GtkWidget *image = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), img);
    gtk_widget_show(image);

    GtkWidget *image1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image1), img);
    gtk_widget_show(image1);

    GtkWidget *image2 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), img);
    gtk_widget_show(image2);

    GtkWidget *image3 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image3), img);
    gtk_widget_show(image3);

    GtkWidget *image4 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image4), img);
    gtk_widget_show(image4);

    GtkWidget *image5 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image5), img);
    gtk_widget_show(image5);

    GtkWidget *image6 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image6), img);
    gtk_widget_show(image6);

    GtkWidget *image7 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image7), img);
    gtk_widget_show(image7);

    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image1, 100, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image2, 200, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image3, 300, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image4, 400, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image5, 500, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image6, 600, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image7, 700, 100);

    // tour noir 
    GtkWidget *tourn = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(tourn), tour);
    gtk_widget_show(tourn);

    GtkWidget *tourn1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(tourn1), tour);
    gtk_widget_show(tourn1);

    gtk_fixed_put(GTK_FIXED(fixed), tourn, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), tourn1, 700, 0);

    // cavalier noir
    GtkWidget *cavaliern = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(cavaliern), cavalier);
    gtk_widget_show(cavaliern);

    GtkWidget *cavaliern1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(cavaliern1), cavalier);
    gtk_widget_show(cavaliern1);

    gtk_fixed_put(GTK_FIXED(fixed), cavaliern, 100, 0);
    gtk_fixed_put(GTK_FIXED(fixed), cavaliern1, 600, 0);

    // fou noir
    GtkWidget *foun = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(foun), fou);
    gtk_widget_show(foun);

    GtkWidget *foun1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(foun1), fou);
    gtk_widget_show(foun1);

    gtk_fixed_put(GTK_FIXED(fixed), foun, 200, 0);
    gtk_fixed_put(GTK_FIXED(fixed), foun1, 500, 0);

    // roi noir 
    GtkWidget *roin = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(roin), roi);
    gtk_widget_show(roin);

    gtk_fixed_put(GTK_FIXED(fixed), roin, 400, 0);

    // reine noir 
    GtkWidget *reinen = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(reinen), reine);
    gtk_widget_show(reinen);

    gtk_fixed_put(GTK_FIXED(fixed), reinen, 300, 0);

    // pions blancs

    GtkWidget *pionsb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb), img2);
    gtk_widget_show(pionsb);

    GtkWidget *pionsb1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb1), img2);
    gtk_widget_show(pionsb1);

    GtkWidget *pionsb2 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb2), img2);
    gtk_widget_show(pionsb2);

    GtkWidget *pionsb3 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb3), img2);
    gtk_widget_show(pionsb3);

    GtkWidget *pionsb4 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb4), img2);
    gtk_widget_show(pionsb4);

    GtkWidget *pionsb5 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb5), img2);
    gtk_widget_show(pionsb5);

    GtkWidget *pionsb6 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb6), img2);
    gtk_widget_show(pionsb6);

    GtkWidget *pionsb7 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(pionsb7), img2);
    gtk_widget_show(pionsb7);

    gtk_fixed_put(GTK_FIXED(fixed), pionsb, 0, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb1, 100, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb2, 200, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb3, 300, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb4, 400, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb5, 500, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb6, 600, 600);
    gtk_fixed_put(GTK_FIXED(fixed), pionsb7, 700, 600);
    
    // tour blanc 
    GtkWidget *tourb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(tourb), toub);
    gtk_widget_show(tourb);

    GtkWidget *tourb1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(tourb1), toub);
    gtk_widget_show(tourb1);

    gtk_fixed_put(GTK_FIXED(fixed), tourb, 700, 700);
    gtk_fixed_put(GTK_FIXED(fixed), tourb1, 0, 700);

    // cavalier blanc
    GtkWidget *cavalierb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(cavalierb), cavalieb);
    gtk_widget_show(cavalierb);

    GtkWidget *cavalierb1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(cavalierb1), cavalieb);
    gtk_widget_show(cavalierb1);

    gtk_fixed_put(GTK_FIXED(fixed), cavalierb, 100, 700);
    gtk_fixed_put(GTK_FIXED(fixed), cavalierb1, 600, 700);

    // fou blanc
    GtkWidget *foub = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(foub), fob);
    gtk_widget_show(foub);

    GtkWidget *foub1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(foub1), fob);
    gtk_widget_show(foub1);

    gtk_fixed_put(GTK_FIXED(fixed), foub, 200, 700);
    gtk_fixed_put(GTK_FIXED(fixed), foub1, 500, 700);

    // roi blanc 
    GtkWidget *roib = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(roib), rob);
    gtk_widget_show(roib);

    gtk_fixed_put(GTK_FIXED(fixed), roib, 400, 700);

    // reine noir 
    GtkWidget *reineb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(reineb), reinb);
    gtk_widget_show(reineb);

    gtk_fixed_put(GTK_FIXED(fixed), reineb, 300, 700);

}

void removeWidget()
{
    GList *children = gtk_container_get_children(GTK_CONTAINER(fixed));
    int len = g_list_length(children);
    for(int i = 0; i < len; i++)
    {
        GtkWidget *widget = (GtkWidget*)g_list_nth_data(children, i);
        if(gtk_widget_get_allocated_width(widget) == 100)
            gtk_widget_destroy(widget);
    }
}


void promote_bishop()
{
    promotion(board[bxx+byy*8], BISHOP);
    gtk_widget_set_sensitive (GTK_WIDGET(bishop), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(queen), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(knight), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(rook), FALSE);
    gtk_widget_hide (bishop);
    gtk_widget_hide (queen);
    gtk_widget_hide (knight);
    gtk_widget_hide (rook);
    GtkWidget* old = getWidget(bxx*100, byy*100);
    gtk_widget_destroy(old);
    GdkPixbuf* fou;
    if(board[bxx+byy*8]->color == WHITE)
    {
        fou = gdk_pixbuf_new_from_file_at_scale ("chess/white/fou.png", 100, 100, TRUE, NULL);
        
    }
    else
    {
        fou = gdk_pixbuf_new_from_file_at_scale ("chess/black/fou.png", 100, 100, TRUE, NULL);
    }
    GtkWidget *foub = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(foub), fou);
    gtk_widget_show(foub);
    gtk_fixed_put(GTK_FIXED(fixed), foub, bxx*100, byy*100);
}

void promote_queen()
{
    promotion(board[bxx+byy*8], QUEEN);
    gtk_widget_set_sensitive (GTK_WIDGET(bishop), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(queen), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(knight), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(rook), FALSE);
    gtk_widget_hide (bishop);
    gtk_widget_hide (queen);
    gtk_widget_hide (knight);
    gtk_widget_hide (rook);

    GtkWidget* old = getWidget(bxx*100, byy*100);
    gtk_widget_destroy(old);
    GdkPixbuf* reine;
    if(board[bxx+byy*8]->color == WHITE)
    {
        reine = gdk_pixbuf_new_from_file_at_scale ("chess/white/reine.png", 100, 100, TRUE, NULL);
        
    }
    else
    {
        reine = gdk_pixbuf_new_from_file_at_scale ("chess/black/reine.png", 100, 100, TRUE, NULL);
    }
    GtkWidget *reineb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(reineb), reine);
    gtk_widget_show(reineb);
    gtk_fixed_put(GTK_FIXED(fixed), reineb, bxx*100, byy*100);
}

void promote_knight()
{
    promotion(board[bxx+byy*8], KNIGHT);
    gtk_widget_set_sensitive (GTK_WIDGET(bishop), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(queen), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(knight), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(rook), FALSE);
    gtk_widget_hide (bishop);
    gtk_widget_hide (queen);
    gtk_widget_hide (knight);
    gtk_widget_hide (rook);

    GtkWidget* old = getWidget(bxx*100, byy*100);
    gtk_widget_destroy(old);
    GdkPixbuf* cavalier;
    if(board[bxx+byy*8]->color == WHITE)
    {
        cavalier = gdk_pixbuf_new_from_file_at_scale ("chess/white/cavalier.png", 100, 100, TRUE, NULL);
        
    }
    else
    {
        cavalier = gdk_pixbuf_new_from_file_at_scale ("chess/black/cavalier.png", 100, 100, TRUE, NULL);
    }
    GtkWidget *cavalierb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(cavalierb), cavalier);
    gtk_widget_show(cavalierb);
    gtk_fixed_put(GTK_FIXED(fixed), cavalierb, bxx*100, byy*100);
}

void promote_rook()
{
    promotion(board[bxx+byy*8], ROOK);
    gtk_widget_set_sensitive (GTK_WIDGET(bishop), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(queen), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(knight), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(rook), FALSE);
    gtk_widget_hide (bishop);
    gtk_widget_hide (queen);
    gtk_widget_hide (knight);
    gtk_widget_hide (rook);

    GtkWidget* old = getWidget(bxx*100, byy*100);
    gtk_widget_destroy(old);
    GdkPixbuf* tour;
    if(board[bxx+byy*8]->color == WHITE)
    {
        tour = gdk_pixbuf_new_from_file_at_scale ("chess/white/tour.png", 100, 100, TRUE, NULL);
        
    }
    else
    {
        tour = gdk_pixbuf_new_from_file_at_scale ("chess/black/tour.png", 100, 100, TRUE, NULL);
    }
    GtkWidget *tourb = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(tourb), tour);
    gtk_widget_show(tourb);
    gtk_fixed_put(GTK_FIXED(fixed), tourb, bxx*100, byy*100);
}
void stopG()
{
    removeWidget();
    gtk_widget_show(welcome);
    gtk_widget_show(playLabel);
    gtk_widget_show(launchGame);
    gtk_widget_hide(stop);
    gtk_widget_hide(stopLabel);
    gtk_widget_hide(wturn);
    gtk_widget_hide(checkMateLabel);
    gtk_widget_hide(checkLabel);
    turn = 0;
}
void launch()
{
    set_image();
    gtk_widget_hide(welcome);
    gtk_widget_hide(playLabel);
    gtk_widget_hide(launchGame);
    board = malloc(64*sizeof(struct piece));
    checkMatevalue = 0;
    check = 0;
    turn = 0;
    hasmoved = 0;
    initParty(board, WHITE);
    gtk_widget_show(wturn);
    gtk_widget_show(stop);
    gtk_widget_show(stopLabel);
}

int main(int argc, char *argv[] )
{
	gtk_init (&argc, &argv);

    // window
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_window_set_default_size (GTK_WINDOW(window), 1250, 900);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "StockMeat");
    gtk_widget_show (window);

    // window fixed
    general = gtk_fixed_new();
    gtk_widget_show(general);
    gtk_container_add(GTK_CONTAINER(window), general);

    // eventbox
    GtkWidget* eventbox = gtk_event_box_new();
    gtk_widget_set_size_request(eventbox, 800, 800);
    gtk_widget_show(eventbox);
    gtk_fixed_put(GTK_FIXED(general), eventbox, 50, 50);

    // chessfixed
	fixed = gtk_fixed_new();
	gtk_widget_show (fixed);
    gtk_container_add(GTK_CONTAINER(eventbox), fixed);
    
    // chessplate's image
    GdkPixbuf* ch = gdk_pixbuf_new_from_file_at_scale ("chess/chessplate.jpg", 800, 800, TRUE, NULL);
    GtkWidget *chess = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(chess), ch);
    gtk_widget_show(chess);
    gtk_fixed_put(GTK_FIXED(fixed), chess, 0, 0);
    
    // promote buttons
    bishop = gtk_button_new();
    queen = gtk_button_new();
    knight = gtk_button_new();
    rook = gtk_button_new();

    gtk_button_set_label(GTK_BUTTON(bishop), "Bishop");
    gtk_button_set_label(GTK_BUTTON(queen), "Queen");
    gtk_button_set_label(GTK_BUTTON(knight), "Knight");
    gtk_button_set_label(GTK_BUTTON(rook), "Rook");

    gtk_widget_set_sensitive (GTK_WIDGET(bishop), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(queen), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(knight), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(rook), FALSE);

    gtk_widget_set_size_request(bishop, 100, 50);
    gtk_widget_set_size_request(queen, 100, 50);
    gtk_widget_set_size_request(knight, 100, 50);
    gtk_widget_set_size_request(rook, 100, 50);

    // load css file
    GdkDisplay *display;
    GdkScreen *screen;
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    GtkCssProvider* provider;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);

    // buttons play / stop

    launchGame = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(launchGame), "New Game");
    gtk_widget_set_size_request(launchGame, 200, 50);
    gtk_widget_set_name(launchGame, "button-30");
    gtk_widget_show (launchGame);

    stop = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(stop), "Stop Game");
    gtk_widget_set_name(stop, "button-30");
    gtk_widget_set_size_request(stop, 200, 50);    

    // labels

    title = gtk_label_new("STOCKMEAT");
    gtk_widget_set_size_request(title, 300, 50);
    gtk_widget_set_name(title, "h1");
    gtk_widget_show (title);

    checkLabel = gtk_label_new("CHECK");
    gtk_widget_set_size_request(checkLabel, 400, 50);
    gtk_widget_set_name(checkLabel, "check");

    checkMateLabel = gtk_label_new("CHECKMATE");
    gtk_widget_set_size_request(checkMateLabel, 400, 50);
    gtk_widget_set_name(checkMateLabel, "check");

    welcome = gtk_label_new("Welcome in");
    gtk_widget_set_size_request(welcome, 400, 50);
    gtk_widget_set_name(welcome, "welcome");
    gtk_widget_show (welcome);

    playLabel = gtk_label_new("Do you want to play?");
    gtk_widget_set_size_request(playLabel, 400, 50);
    gtk_widget_set_name(playLabel, "welcome");
    gtk_widget_show (playLabel);

    stopLabel = gtk_label_new("Do you want to stop?");
    gtk_widget_set_size_request(stopLabel, 400, 50);
    gtk_widget_set_name(stopLabel, "welcome");
    
    winnerLabel = gtk_label_new("");
    gtk_widget_set_size_request(winnerLabel, 300, 50);
    gtk_widget_set_name(winnerLabel, "h1");
    gtk_widget_show (winnerLabel);

    wturn = gtk_label_new("Turn to White");
    gtk_widget_set_name(wturn, "texte");
    gtk_widget_set_size_request(wturn, 400, 50);

    // met tous les éléments au bon endroit
    int borderx = 50;
    int bordery = 50;

    gtk_fixed_put(GTK_FIXED(general), bishop, 880 + borderx, 600 + bordery);
    gtk_fixed_put(GTK_FIXED(general), queen, 1020 + borderx, 600 + bordery);
    gtk_fixed_put(GTK_FIXED(general), knight, 880 + borderx, 700 + bordery);
    gtk_fixed_put(GTK_FIXED(general), rook, 1020 + borderx, 700 + bordery);
    gtk_fixed_put(GTK_FIXED(general), title, 850 + borderx, 65+bordery);
    gtk_fixed_put(GTK_FIXED(general), welcome, 800 + borderx, 10 + bordery);
    gtk_fixed_put(GTK_FIXED(general), playLabel, 800 + borderx, 130 + bordery);
    gtk_fixed_put(GTK_FIXED(general), wturn, 800 + borderx, 260 + bordery);
    gtk_fixed_put(GTK_FIXED(general), launchGame, 900 + borderx, 195 + bordery);
    gtk_fixed_put(GTK_FIXED(general), stopLabel, 800 + borderx, 130 + bordery);
    gtk_fixed_put(GTK_FIXED(general), stop, 900 + borderx, 195 + bordery);
    gtk_fixed_put(GTK_FIXED(general), checkLabel, 800 + borderx, 325 + bordery);
    gtk_fixed_put(GTK_FIXED(general), checkMateLabel, 800 + borderx, 325 + bordery);	

    // connect events

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (eventbox), "button_press_event", G_CALLBACK (button_press_callback), NULL);
    g_signal_connect(bishop, "clicked", G_CALLBACK(promote_bishop), NULL);
    g_signal_connect(queen, "clicked", G_CALLBACK(promote_queen), NULL);
    g_signal_connect(rook, "clicked", G_CALLBACK(promote_rook), NULL);
    g_signal_connect(knight, "clicked", G_CALLBACK(promote_knight), NULL);
    g_signal_connect(launchGame, "clicked", G_CALLBACK(launch), NULL);
    g_signal_connect(stop, "clicked", G_CALLBACK(stopG), NULL);

	gtk_main ();
	return 0;
}