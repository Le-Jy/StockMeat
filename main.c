#include <gtk/gtk.h>
#include "Game/game.h"
#include <math.h>

GtkWidget *fixed;
GtkWidget *fixed2;
GtkWidget* window;
size_t win = 0;

struct piece** board = malloc(64*sizeof(struct piece));
int checkMatevalue = 0;
int check = 0;
unsigned long turn = 0;
initParty(board, WHITE);
int bx,by,bxx,byy;

gint x = -1;
gint y = -1;

gint dest_x = -1;
gint dest_y = -1;

static gboolean button_press_callback (GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
    
    GtkWidget* toMove;

    if(x == -1 && y == -1)
    {
        x = event->x;
        y = event->y;
        // g_print ("first click %i,%i\n", x, y);

        return TRUE;
    }
    if(x != -1 && y != -1 && dest_x == -1 && dest_y == -1)
    {
        dest_x = event->x;
        dest_y = event->y;
        // g_print ("second click %i,%i\n", dest_x, dest_y);
    }

    if(dest_x != -1 && x!=-1 && dest_y != -1 && y!=-1)
    {
        if(GTK_IS_CONTAINER(fixed)) {
            GList *children = gtk_container_get_children(GTK_CONTAINER(fixed));
            size_t found = 0;
            for (guint i = 0; i < g_list_length(children); ++i) {
                GtkWidget* widget = (GtkWidget*)g_list_nth_data(children, i);
                gint wx, wy;
                gtk_widget_translate_coordinates(widget, gtk_widget_get_toplevel(widget), 0, 0, &wx, &wy);
                if(wx <= x && x <= wx + 100 && wy <= y && y <= wy + 100)
                {
                    
                    if(gtk_widget_get_allocated_width(widget) > 200 && x < 100 && y < 100)
                    {
                        size_t find = 0;
                        guint j = 0;
                        while(j < g_list_length(children) && find == 0)
                        {
                            GtkWidget* compare = (GtkWidget*)g_list_nth_data(children, j);
                            gint cx, cy;
                            gtk_widget_translate_coordinates(compare, gtk_widget_get_toplevel(compare), 0, 0, &cx, &cy);
                            if(cx <= x && x <= cx + 100 && cy <= y && y <= cy + 100)
                            {
                                if(gtk_widget_get_allocated_width(compare) < 105)
                                {
                                    printf("oui");
                                    find = 1;
                                }
                                
                            }
                            j++;
                        }
                        // SI il n'y a rien en case (0,0) mais qu'il a cliqué dessus
                        if(find == 0)
                        {
                            x = -1;
                            y = -1;
                            dest_x = -1;
                            dest_y = -1;
                        }
                        
                    }
                    else{
                        // WIDGET qui est sélectionné est correct, la destination peut être tout type de case 

                        // checker si le move est possible pour pouvoir faire la suite
                        
                        bx = floor(x/100);
                        by = floor(y/100);
                        bxx = floor(dest_x/100);
                        byy = floor(dest_y/100);

                        printf("x: %i, y: %i \n", bx, by);
                        printf("dx: %i, dy: %i \n", bxx, byy);

                        found = 1;

                        // SI c'est bon tu fais ça 
                        toMove = widget;
                        printf("%f\n", floor(dest_x));
                        gtk_fixed_move(GTK_FIXED(fixed), toMove, floor(dest_x/100)*100, floor(dest_y/100)*100);

                        // checker si y a etc


                        x = -1;
                        y = -1;
                        dest_x = -1;
                        dest_y = -1;
                    }
                    
                }
            
            }
            // Si CASE VIDE
            if(found == 0)
            {
                win = 1;
                x = -1;
                y = -1;
                dest_x = -1;
                dest_y = -1;
            }
        }
        
    }
    
    return TRUE;
}

void set_image()
{
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

int main(int argc, char *argv[] )
{
	gtk_init (&argc, &argv);

    



	// WINDOW
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_window_set_default_size (GTK_WINDOW(window), 800, 800);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "StockMeat");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show (window);

    // EVENT BOX
    GtkWidget* eventbox = gtk_event_box_new();
    gtk_widget_set_size_request(eventbox, 800, 800);
    
    gtk_container_add(GTK_CONTAINER(window), eventbox);
    gtk_widget_show(eventbox);

	// FIXED
	fixed = gtk_fixed_new();
	gtk_widget_show (fixed);
    gtk_container_add(GTK_CONTAINER(eventbox), GTK_WIDGET(fixed));
    
    GdkPixbuf* ch = gdk_pixbuf_new_from_file_at_scale ("chess/chessplate.jpg", 800, 800, TRUE, NULL);
    GtkWidget *chess = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(chess), ch);
    gtk_widget_show(chess);
    gtk_fixed_put(GTK_FIXED(fixed), chess, 0, 0);

    // MET LES IMAGES
    set_image();

    g_signal_connect (G_OBJECT (eventbox), "button_press_event", G_CALLBACK (button_press_callback), NULL);
    
	gtk_main ();
	return 0;
}