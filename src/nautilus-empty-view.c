/* fm-empty-view.c - implementation of empty view of directory.
 *
 *  Copyright (C) 2006 Free Software Foundation, Inc.
 *
 *  The Gnome Library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public License as
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  The Gnome Library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with the Gnome Library; see the file COPYING.LIB.  If not,
 *  see <http://www.gnu.org/licenses/>.
 *
 *  Authors: Christian Neumair <chris@gnome-de.org>
 */

#include <config.h>

#include "nautilus-empty-view.h"

#include "nautilus-files-view.h"

#include <string.h>
#include "nautilus-file-utilities.h"
#include <eel/eel-vfs-extensions.h>

struct _NautilusEmptyView
{
	NautilusFilesView parent_instance;
	int number_of_files;
};

static GList *nautilus_empty_view_get_selection (NautilusFilesView *view);
static GList *nautilus_empty_view_get_selection_for_file_transfer (NautilusFilesView *view);
static void   nautilus_empty_view_scroll_to_file (NautilusFilesView *view,
                                                  const char        *uri);

G_DEFINE_TYPE (NautilusEmptyView, nautilus_empty_view, NAUTILUS_TYPE_FILES_VIEW)

static void
nautilus_empty_view_add_file (NautilusFilesView *view,
                              NautilusFile      *file,
                              NautilusDirectory *directory)
{
    static GTimer *timer = NULL;
    static gdouble cumu = 0, elaps;
    NAUTILUS_EMPTY_VIEW (view)->number_of_files++;
    GdkPixbuf *icon;

    if (!timer)
    {
        timer = g_timer_new ();
    }

    g_timer_start (timer);
    icon = nautilus_file_get_icon_pixbuf (file, nautilus_get_icon_size_for_zoom_level (NAUTILUS_CANVAS_ZOOM_LEVEL_STANDARD), TRUE, 0);

    elaps = g_timer_elapsed (timer, NULL);
    g_timer_stop (timer);

    g_object_unref (icon);

    cumu += elaps;
    g_message ("entire loading: %.3f, cumulative %.3f", elaps, cumu);
}


static void
nautilus_empty_view_begin_loading (NautilusFilesView *view)
{
}

static void
nautilus_empty_view_clear (NautilusFilesView *view)
{
}


static void
nautilus_empty_view_file_changed (NautilusFilesView *view,
                                  NautilusFile      *file,
                                  NautilusDirectory *directory)
{
}

static GList *
nautilus_empty_view_get_selection (NautilusFilesView *view)
{
    return NULL;
}


static GList *
nautilus_empty_view_get_selection_for_file_transfer (NautilusFilesView *view)
{
    return NULL;
}

static gboolean
nautilus_empty_view_is_empty (NautilusFilesView *view)
{
    return NAUTILUS_EMPTY_VIEW (view)->number_of_files == 0;
}

static void
nautilus_empty_view_end_file_changes (NautilusFilesView *view)
{
}

static void
nautilus_empty_view_remove_file (NautilusFilesView *view,
                                 NautilusFile      *file,
                                 NautilusDirectory *directory)
{
    NAUTILUS_EMPTY_VIEW (view)->number_of_files--;
    g_assert (NAUTILUS_EMPTY_VIEW (view)->number_of_files >= 0);
}

static void
nautilus_empty_view_set_selection (NautilusFilesView *view,
                                   GList             *selection)
{
    nautilus_files_view_notify_selection_changed (view);
}

static void
nautilus_empty_view_select_all (NautilusFilesView *view)
{
}

static void
nautilus_empty_view_reveal_selection (NautilusFilesView *view)
{
}

static void
nautilus_empty_view_update_menus (NautilusFilesView *view)
{
    NAUTILUS_FILES_VIEW_CLASS (nautilus_empty_view_parent_class)->update_menus (view);
}

static void
nautilus_empty_view_bump_zoom_level (NautilusFilesView *view,
                                     int                zoom_increment)
{
}

static NautilusCanvasZoomLevel
nautilus_empty_view_get_zoom_level (NautilusFilesView *view)
{
    return NAUTILUS_CANVAS_ZOOM_LEVEL_STANDARD;
}

static void
nautilus_empty_view_zoom_to_level (NautilusFilesView       *view,
                                   NautilusCanvasZoomLevel  zoom_level)
{
}

static void
nautilus_empty_view_restore_standard_zoom_level (NautilusFilesView *view)
{
}

static gboolean
nautilus_empty_view_can_zoom_in (NautilusFilesView *view)
{
    return FALSE;
}

static gboolean
nautilus_empty_view_can_zoom_out (NautilusFilesView *view)
{
    return FALSE;
}

static gfloat
nautilus_empty_view_get_zoom_level_percentage (NautilusFilesView *view)
{
    return 1.0;
}

static void
nautilus_empty_view_click_policy_changed (NautilusFilesView *directory_view)
{
}


static int
nautilus_empty_view_compare_files (NautilusFilesView *view,
                                   NautilusFile      *file1,
                                   NautilusFile      *file2)
{
    if (file1 < file2)
    {
        return -1;
    }

    if (file1 > file2)
    {
        return +1;
    }

    return 0;
}

static gboolean
nautilus_empty_view_using_manual_layout (NautilusFilesView *view)
{
    return FALSE;
}

static void
nautilus_empty_view_end_loading (NautilusFilesView *view,
                                 gboolean           all_files_seen)
{
}

static char *
nautilus_empty_view_get_first_visible_file (NautilusFilesView *view)
{
    return NULL;
}

static void
nautilus_empty_view_scroll_to_file (NautilusFilesView *view,
                                    const char        *uri)
{
}

static void
nautilus_empty_view_sort_directories_first_changed (NautilusFilesView *view)
{
}

static guint
nautilus_empty_view_get_id (NautilusFilesView *view)
{
    return NAUTILUS_VIEW_EMPTY_ID;
}

static GIcon *
nautilus_empty_view_get_icon (NautilusFilesView *view)
{
    return NULL;
}

static void
nautilus_empty_view_class_init (NautilusEmptyViewClass *class)
{
    NautilusFilesViewClass *nautilus_files_view_class;

    nautilus_files_view_class = NAUTILUS_FILES_VIEW_CLASS (class);

    nautilus_files_view_class->add_file = nautilus_empty_view_add_file;
    nautilus_files_view_class->begin_loading = nautilus_empty_view_begin_loading;
    nautilus_files_view_class->bump_zoom_level = nautilus_empty_view_bump_zoom_level;
    nautilus_files_view_class->can_zoom_in = nautilus_empty_view_can_zoom_in;
    nautilus_files_view_class->can_zoom_out = nautilus_empty_view_can_zoom_out;
    nautilus_files_view_class->get_zoom_level_percentage = nautilus_empty_view_get_zoom_level_percentage;
    nautilus_files_view_class->click_policy_changed = nautilus_empty_view_click_policy_changed;
    nautilus_files_view_class->clear = nautilus_empty_view_clear;
    nautilus_files_view_class->file_changed = nautilus_empty_view_file_changed;
    nautilus_files_view_class->get_selection = nautilus_empty_view_get_selection;
    nautilus_files_view_class->get_selection_for_file_transfer = nautilus_empty_view_get_selection_for_file_transfer;
    nautilus_files_view_class->is_empty = nautilus_empty_view_is_empty;
    nautilus_files_view_class->remove_file = nautilus_empty_view_remove_file;
    nautilus_files_view_class->update_menus = nautilus_empty_view_update_menus;
    nautilus_files_view_class->restore_standard_zoom_level = nautilus_empty_view_restore_standard_zoom_level;
    nautilus_files_view_class->reveal_selection = nautilus_empty_view_reveal_selection;
    nautilus_files_view_class->select_all = nautilus_empty_view_select_all;
    nautilus_files_view_class->set_selection = nautilus_empty_view_set_selection;
    nautilus_files_view_class->compare_files = nautilus_empty_view_compare_files;
    nautilus_files_view_class->sort_directories_first_changed = nautilus_empty_view_sort_directories_first_changed;
    nautilus_files_view_class->get_zoom_level = nautilus_empty_view_get_zoom_level;
    nautilus_files_view_class->zoom_to_level = nautilus_empty_view_zoom_to_level;
    nautilus_files_view_class->end_file_changes = nautilus_empty_view_end_file_changes;
    nautilus_files_view_class->using_manual_layout = nautilus_empty_view_using_manual_layout;
    nautilus_files_view_class->end_loading = nautilus_empty_view_end_loading;
    nautilus_files_view_class->get_view_id = nautilus_empty_view_get_id;
    nautilus_files_view_class->get_first_visible_file = nautilus_empty_view_get_first_visible_file;
    nautilus_files_view_class->scroll_to_file = nautilus_empty_view_scroll_to_file;
    nautilus_files_view_class->get_icon = nautilus_empty_view_get_icon;
}

static void
nautilus_empty_view_init (NautilusEmptyView *empty_view)
{
    empty_view->number_of_files = 0;
}

NautilusFilesView *
nautilus_empty_view_new (NautilusWindowSlot *slot)
{
    return g_object_new (NAUTILUS_TYPE_EMPTY_VIEW,
                         "window-slot", slot,
                         NULL);
}
