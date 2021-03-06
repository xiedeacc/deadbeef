
/*  Gtk+ User Interface Builder
 *  Copyright (C) 1998  Damon Chaplin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtkcolorseldialog.h>
#include "../gb.h"

/* Include the 21x21 icon pixmap for this widget, to be used in the palette */
#include "../graphics/colorseldialog.xpm"

/*
 * This is the GbWidget struct for this widget (see ../gbwidget.h).
 * It is initialized in the init() function at the end of this file
 */
static GbWidget gbwidget;

static gchar *Title = "ColorSelDialog|GtkWindow::title";
static gchar *Type = "ColorSelDialog|GtkWindow::type";
static gchar *Position = "ColorSelDialog|GtkWindow::window_position";
static gchar *Modal = "ColorSelDialog|GtkWindow::modal";
static gchar *DefaultWidth = "ColorSel|GtkWindow::default_width";
static gchar *DefaultHeight = "ColorSel|GtkWindow::default_height";
static gchar *Shrink = "ColorSelDialog|GtkWindow::allow_shrink";
static gchar *Grow = "ColorSelDialog|GtkWindow::allow_grow";
static gchar *AutoShrink = "ColorSelDialog|GtkWindow::auto_shrink";
static gchar *IconName = "ColorSelDialog|GtkWindow::icon_name";
static gchar *FocusOnMap = "ColorSelDialog|GtkWindow::focus_on_map";

static gchar *Resizable = "ColorSelDialog|GtkWindow::resizable";
static gchar *DestroyWithParent = "ColorSelDialog|GtkWindow::destroy_with_parent";
static gchar *Icon = "ColorSelDialog|GtkWindow::icon";

static gchar *Role = "ColorSelDialog|GtkWindow::role";
static gchar *TypeHint = "ColorSelDialog|GtkWindow::type_hint";
static gchar *SkipTaskbar = "ColorSelDialog|GtkWindow::skip_taskbar_hint";
static gchar *SkipPager = "ColorSelDialog|GtkWindow::skip_pager_hint";
static gchar *Decorated = "ColorSelDialog|GtkWindow::decorated";
static gchar *Gravity = "ColorSelDialog|GtkWindow::gravity";
static gchar *Urgency = "ColorSelDialog|GtkWindow::urgency_hint";

/******
 * NOTE: To use these functions you need to uncomment them AND add a pointer
 * to the function in the GbWidget struct at the end of this file.
 ******/

/*
 * Creates a new GtkWidget of class GtkColorSelectionDialog, performing any specialized
 * initialization needed for the widget to work correctly in this environment.
 * If a dialog box is used to initialize the widget, return NULL from this
 * function, and call data->callback with your new widget when it is done.
 * If the widget needs a special destroy handler, add a signal here.
 */
GtkWidget *
gb_color_selection_dialog_new (GbWidgetNewData * data)
{
  GtkWidget *new_widget = gtk_color_selection_dialog_new (_("Select Color"));

  GtkColorSelectionDialog *colorsel = GTK_COLOR_SELECTION_DIALOG (new_widget);

  /* We want it to be treated as a normal window. */
  gtk_window_set_type_hint (GTK_WINDOW (new_widget),
			    GDK_WINDOW_TYPE_HINT_NORMAL);

  gtk_signal_connect (GTK_OBJECT (new_widget), "delete_event",
		      GTK_SIGNAL_FUNC (editor_close_window), NULL);

  gb_widget_create_from (colorsel->ok_button,
			 data->action == GB_CREATING ? "ok_button" : NULL);
  gb_widget_set_child_name (colorsel->ok_button, GladeChildOKButton);

  gb_widget_create_from (colorsel->cancel_button,
			 data->action == GB_CREATING ? "cancel_button" : NULL);
  gb_widget_set_child_name (colorsel->cancel_button, GladeChildCancelButton);

  gb_widget_create_from (colorsel->help_button,
			 data->action == GB_CREATING ? "help_button" : NULL);
  gb_widget_set_child_name (colorsel->help_button, GladeChildHelpButton);

  gb_widget_create_from (colorsel->colorsel,
			 data->action == GB_CREATING ? "color_selection" : NULL);
  gb_widget_set_child_name (colorsel->colorsel, GladeChildColorSelection);

  gtk_object_set_data (GTK_OBJECT (new_widget), TypeHint,
		       GINT_TO_POINTER (GLADE_TYPE_HINT_DIALOG_INDEX));

  return new_widget;
}



/*
 * Creates the components needed to edit the extra properties of this widget.
 */
static void
gb_color_selection_dialog_create_properties (GtkWidget * widget,
					     GbWidgetCreateArgData * data)
{
  gb_window_create_standard_properties (widget, data,
					Title, Type, Position, Modal,
					DefaultWidth, DefaultHeight,
					Shrink, Grow, AutoShrink,
					IconName, FocusOnMap,
					Resizable, DestroyWithParent, Icon,
					Role, TypeHint, SkipTaskbar,
					SkipPager, Decorated, Gravity, Urgency);
}



/*
 * Gets the properties of the widget. This is used for both displaying the
 * properties in the property editor, and also for saving the properties.
 */
static void
gb_color_selection_dialog_get_properties (GtkWidget * widget,
					  GbWidgetGetArgData * data)
{
  GtkColorSelectionDialog *colorseldlg;
  GtkColorSelection *colorsel;

  colorseldlg = GTK_COLOR_SELECTION_DIALOG (widget);
  colorsel = GTK_COLOR_SELECTION (colorseldlg->colorsel);

  gb_window_get_standard_properties (widget, data,
				     Title, Type, Position, Modal,
				     DefaultWidth, DefaultHeight,
				     Shrink, Grow, AutoShrink,
				     IconName, FocusOnMap,
				     Resizable, DestroyWithParent, Icon,
				     Role, TypeHint, SkipTaskbar,
				     SkipPager, Decorated, Gravity, Urgency);
}



/*
 * Sets the properties of the widget. This is used for both applying the
 * properties changed in the property editor, and also for loading.
 */
static void
gb_color_selection_dialog_set_properties (GtkWidget * widget,
					  GbWidgetSetArgData * data)
{
  GtkColorSelectionDialog *colorseldlg;
  GtkColorSelection *colorsel;

  colorseldlg = GTK_COLOR_SELECTION_DIALOG (widget);
  colorsel = GTK_COLOR_SELECTION (colorseldlg->colorsel);

  gb_window_set_standard_properties (widget, data,
				     Title, Type, Position, Modal,
				     DefaultWidth, DefaultHeight,
				     Shrink, Grow, AutoShrink,
				     IconName, FocusOnMap,
				     Resizable, DestroyWithParent, Icon,
				     Role, TypeHint, SkipTaskbar,
				     SkipPager, Decorated, Gravity, Urgency);
}



/*
 * Adds menu items to a context menu which is just about to appear!
 * Add commands to aid in editing a GtkColorSelectionDialog, with signals pointing to
 * other functions in this file.
 */
/*
   static void
   gb_color_selection_dialog_create_popup_menu(GtkWidget *widget, GbWidgetCreateMenuData *data)
   {

   }
 */



/*
 * Writes the source code needed to create this widget.
 * You have to output everything necessary to create the widget here, though
 * there are some convenience functions to help.
 */
static void
gb_color_selection_dialog_write_source (GtkWidget * widget,
					GbWidgetWriteSourceData * data)
{
  gchar *wname, *child_name;
  const gchar *child_widget_name;
  gboolean translatable, context;
  gchar *comments;

  if (data->create_widget)
    {
      glade_util_get_translation_properties (widget, Title, &translatable,
					     &comments, &context);
      source_add_translator_comments (data, translatable, comments);

      source_add (data, "  %s = gtk_color_selection_dialog_new (%s);\n",
		  data->wname,
		  source_make_string_full (GTK_WINDOW (widget)->title,
					   data->use_gettext && translatable,
					   context));
    }

  gb_widget_write_standard_source (widget, data);

  /* The title is already set above, so we pass NULL to skip it. */
  gb_window_write_standard_source (widget, data,
				   NULL, Type, Position, Modal,
				   DefaultWidth, DefaultHeight,
				   Shrink, Grow, AutoShrink,
				   IconName, FocusOnMap,
				   Resizable, DestroyWithParent, Icon,
				   Role, TypeHint, SkipTaskbar,
				   SkipPager, Decorated, Gravity, Urgency);


  /* We output the source code for the buttons here, but we don't want them
     to be created. We need to remember the dialog's name since data->wname
     will be overwritten. */
  wname = g_strdup (data->wname);

  source_add (data, "\n");

  child_widget_name = gtk_widget_get_name (GTK_COLOR_SELECTION_DIALOG (widget)->ok_button);
  child_name = source_create_valid_identifier (child_widget_name);
  source_add (data, "  %s = GTK_COLOR_SELECTION_DIALOG (%s)->ok_button;\n",
	      child_name, wname);
  g_free (child_name);
  data->create_widget = FALSE;
  gb_widget_write_source (GTK_COLOR_SELECTION_DIALOG (widget)->ok_button,
			  data);

  child_widget_name = gtk_widget_get_name (GTK_COLOR_SELECTION_DIALOG (widget)->cancel_button);
  child_name = source_create_valid_identifier (child_widget_name);
  source_add (data, "  %s = GTK_COLOR_SELECTION_DIALOG (%s)->cancel_button;\n",
	      child_name, wname);
  g_free (child_name);
  data->create_widget = FALSE;
  gb_widget_write_source (GTK_COLOR_SELECTION_DIALOG (widget)->cancel_button,
			  data);

  child_widget_name = gtk_widget_get_name (GTK_COLOR_SELECTION_DIALOG (widget)->help_button);
  child_name = source_create_valid_identifier (child_widget_name);
  source_add (data, "  %s = GTK_COLOR_SELECTION_DIALOG (%s)->help_button;\n",
	      child_name, wname);
  g_free (child_name);
  data->create_widget = FALSE;
  gb_widget_write_source (GTK_COLOR_SELECTION_DIALOG (widget)->help_button,
			  data);

  child_widget_name = gtk_widget_get_name (GTK_COLOR_SELECTION_DIALOG (widget)->colorsel);
  child_name = source_create_valid_identifier (child_widget_name);
  source_add (data, "  %s = GTK_COLOR_SELECTION_DIALOG (%s)->colorsel;\n",
	      child_name, wname);
  g_free (child_name);
  data->create_widget = FALSE;
  gb_widget_write_source (GTK_COLOR_SELECTION_DIALOG (widget)->colorsel,
			  data);

  g_free (wname);

  data->write_children = FALSE;
}



static GtkWidget *
gb_color_selection_dialog_get_child (GtkWidget * widget,
				     const gchar * child_name)
{
  if (!strcmp (child_name, GladeChildOKButton))
    return GTK_COLOR_SELECTION_DIALOG (widget)->ok_button;
  else if (!strcmp (child_name, GladeChildCancelButton))
    return GTK_COLOR_SELECTION_DIALOG (widget)->cancel_button;
  else if (!strcmp (child_name, GladeChildHelpButton))
    return GTK_COLOR_SELECTION_DIALOG (widget)->help_button;
  else if (!strcmp (child_name, GladeChildColorSelection))
    return GTK_COLOR_SELECTION_DIALOG (widget)->colorsel;
  else
    return NULL;
}


/*
 * Initializes the GbWidget structure.
 * I've placed this at the end of the file so we don't have to include
 * declarations of all the functions.
 */
GbWidget *
gb_color_selection_dialog_init ()
{
  /* Initialise the GTK type */
  volatile GtkType type;
  type = gtk_color_selection_dialog_get_type ();

  /* Initialize the GbWidget structure */
  gb_widget_init_struct (&gbwidget);

  /* Fill in the pixmap struct & tooltip */
  gbwidget.pixmap_struct = colorseldialog_xpm;
  gbwidget.tooltip = _("Color Selection Dialog");

  /* Fill in any functions that this GbWidget has */
  gbwidget.gb_widget_new = gb_color_selection_dialog_new;
  gbwidget.gb_widget_create_properties = gb_color_selection_dialog_create_properties;
  gbwidget.gb_widget_get_properties = gb_color_selection_dialog_get_properties;
  gbwidget.gb_widget_set_properties = gb_color_selection_dialog_set_properties;
  gbwidget.gb_widget_get_child = gb_color_selection_dialog_get_child;
  gbwidget.gb_widget_write_source = gb_color_selection_dialog_write_source;
  gbwidget.gb_widget_destroy = gb_window_destroy;
/*
   gbwidget.gb_widget_create_popup_menu = gb_color_selection_dialog_create_popup_menu;
 */

  return &gbwidget;
}
