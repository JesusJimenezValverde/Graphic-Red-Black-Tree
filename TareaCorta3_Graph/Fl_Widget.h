#pragma once
//
 // "$Id$"
 //
 // Widget header file for the Fast Light Tool Kit (FLTK).
 //
 // Copyright 1998-2015 by Bill Spitzak and others.
 //
 // This library is free software. Distribution and use rights are outlined in
 // the file "COPYING" which should have been included with this file.  If this
 // file is missing or damaged, see the license at:
 //
 //     http://www.fltk.org/COPYING.php
 //
 // Please report all bugs and problems on the following page:
 //
 //     http://www.fltk.org/str.php
 //

#ifndef Fl_Widget_H
#define Fl_Widget_H

#include "Enumerations.H"

#ifdef _WIN64
#if defined(__GNUC__) || defined(__clang__)
#include <stdint.h>
#else
#include <stddef.h>  // M$VC
#endif
typedef intptr_t fl_intptr_t;
typedef uintptr_t fl_uintptr_t;
#else
typedef long fl_intptr_t;
typedef unsigned long fl_uintptr_t;
#endif

class Fl_Widget;
class Fl_Window;
class Fl_Group;
class Fl_Image;

typedef void (Fl_Callback0)(Fl_Widget*, void*);
typedef Fl_Callback* Fl_Callback_p; // needed for BORLAND
typedef void (Fl_Ca3llback0)(Fl_Widget*);
typedef void (Fl_Callback1)(Fl_Widget*, long);
typedef void (Fl_Callback)(Fl_Widget*, void*);

struct FL_EXPORT Fl_Label {
	const char* value;
	Fl_Image* image;
	Fl_Image* deimage;
	Fl_Font font;
	Fl_Fontsize size;
	Fl_Color color;
	Fl_Align align_;
	uchar type;

	void draw(int, int, int, int, Fl_Align) const;
	void measure(int &w, int &h) const;
};


class FL_EXPORT Fl_Widget {
	friend class Fl_Group;

	Fl_Group* parent_;
	Fl_Callback* callback_;
	void* user_data_;
	int x_, y_, w_, h_;
	Fl_Label label_;
	unsigned int flags_;
	Fl_Color color_;
	Fl_Color color2_;
	uchar type_;
	uchar damage_;
	uchar box_;
	uchar when_;
	//Simple_window* wind_;

	const char *tooltip_;

	Fl_Widget(const Fl_Widget &);
	Fl_Widget& operator=(const Fl_Widget &);

protected:

	Fl_Widget(int x, int y, int w, int h, const char *label = 0L);

	void x(int v) { x_ = v; }
	void y(int v) { y_ = v; }
	void w(int v) { w_ = v; }
	void h(int v) { h_ = v; }
	unsigned int flags() const { return flags_; }
	void set_flag(unsigned int c) { flags_ |= c; }
	void clear_flag(unsigned int c) { flags_ &= ~c; }
	enum {
		INACTIVE = 1 << 0,
		INVISIBLE = 1 << 1,
		OUTPUT = 1 << 2,
		NOBORDER = 1 << 3,
		FORCE_POSITION = 1 << 4,
		NON_MODAL = 1 << 5,
		SHORTCUT_LABEL = 1 << 6,
		CHANGED = 1 << 7,
		OVERRIDE = 1 << 8,
		VISIBLE_FOCUS = 1 << 9,
		COPIED_LABEL = 1 << 10,
		CLIP_CHILDREN = 1 << 11,
		MENU_WINDOW = 1 << 12,
		TOOLTIP_WINDOW = 1 << 13,
		MODAL = 1 << 14,
		NO_OVERLAY = 1 << 15,
		GROUP_RELATIVE = 1 << 16,
		COPIED_TOOLTIP = 1 << 17,
		FULLSCREEN = 1 << 18,
		MAC_USE_ACCENTS_MENU = 1 << 19,
		// (space for more flags)
		USERFLAG3 = 1 << 29,
		USERFLAG2 = 1 << 30,
		USERFLAG1 = 1 << 31
	};
	void draw_box() const;
	void draw_box(Fl_Boxtype t, Fl_Color c) const;
	void draw_box(Fl_Boxtype t, int x, int y, int w, int h, Fl_Color c) const;
	void draw_backdrop() const;
	void draw_focus() { draw_focus(box(), x(), y(), w(), h()); }
	void draw_focus(Fl_Boxtype t, int x, int y, int w, int h) const;
	void draw_label() const;
	void draw_label(int, int, int, int) const;

public:

	virtual ~Fl_Widget();

	virtual void draw() = 0;

	virtual int handle(int event);

	int is_label_copied() const { return ((flags_ & COPIED_LABEL) ? 1 : 0); }

	Fl_Group* parent() const { return parent_; }

	void parent(Fl_Group* p) { parent_ = p; } // for hacks only, use Fl_Group::add()

	uchar type() const { return type_; }

	void type(uchar t) { type_ = t; }

	int x() const { return x_; }

	int y() const { return y_; }

	int w() const { return w_; }

	int h() const { return h_; }

	virtual void resize(int x, int y, int w, int h);

	int damage_resize(int, int, int, int);

	void position(int X, int Y) { resize(X, Y, w_, h_); }

	void size(int W, int H) { resize(x_, y_, W, H); }

	Fl_Align align() const { return label_.align_; }

	void align(Fl_Align alignment) { label_.align_ = alignment; }

	Fl_Boxtype box() const { return (Fl_Boxtype)box_; }

	void box(Fl_Boxtype new_box) { box_ = new_box; }

	Fl_Color color() const { return color_; }

	void color(Fl_Color bg) { color_ = bg; }

	Fl_Color selection_color() const { return color2_; }

	void selection_color(Fl_Color a) { color2_ = a; }

	void color(Fl_Color bg, Fl_Color sel) { color_ = bg; color2_ = sel; }

	const char* label() const { return label_.value; }

	void label(const char* text);

	void copy_label(const char *new_label);

	void label(Fl_Labeltype a, const char* b) { label_.type = a; label_.value = b; }

	Fl_Labeltype labeltype() const { return (Fl_Labeltype)label_.type; }

	void labeltype(Fl_Labeltype a) { label_.type = a; }

	Fl_Color labelcolor() const { return label_.color; }

	void labelcolor(Fl_Color c) { label_.color = c; }

	Fl_Font labelfont() const { return label_.font; }

	void labelfont(Fl_Font f) { label_.font = f; }

	Fl_Fontsize labelsize() const { return label_.size; }

	void labelsize(Fl_Fontsize pix) { label_.size = pix; }

	Fl_Image* image() { return label_.image; }
	const Fl_Image* image() const { return label_.image; }

	void image(Fl_Image* img) { label_.image = img; }

	void image(Fl_Image& img) { label_.image = &img; }

	Fl_Image* deimage() { return label_.deimage; }
	const Fl_Image* deimage() const { return label_.deimage; }

	void deimage(Fl_Image* img) { label_.deimage = img; }

	void deimage(Fl_Image& img) { label_.deimage = &img; }

	const char *tooltip() const { return tooltip_; }

	void tooltip(const char *text);               // see Fl_Tooltip
	void copy_tooltip(const char *text);          // see Fl_Tooltip

	void callback(Fl_Callback* cb, void* p) { callback_ = cb; user_data_ = p; }

	Fl_Callback_p callback() const { return callback_; }

	//void callback(Fl_Callback* cb, void* p) { callback_ = cb; user_data_ = p; }

	void callback(Fl_Callback* cb) { callback_ = cb; }

	void callback(Fl_Callback0*cb) { callback_ = (Fl_Callback*)cb; }

	void callback(Fl_Callback1*cb, long p = 0) { callback_ = (Fl_Callback*)cb; user_data_ = (void*)(fl_intptr_t)p; }

	void* user_data() const { return user_data_; }

	void user_data(void* v) { user_data_ = v; }

	long argument() const { return (long)(fl_intptr_t)user_data_; }

	void argument(long v) { user_data_ = (void*)(fl_intptr_t)v; }

	Fl_When when() const { return (Fl_When)when_; }

	void when(uchar i) { when_ = i; }

	unsigned int visible() const { return !(flags_&INVISIBLE); }

	int visible_r() const;

	virtual void show();

	virtual void hide();

	void set_visible() { flags_ &= ~INVISIBLE; }

	void clear_visible() { flags_ |= INVISIBLE; }

	unsigned int active() const { return !(flags_&INACTIVE); }

	int active_r() const;

	void activate();

	void deactivate();

	unsigned int output() const { return (flags_&OUTPUT); }

	void set_output() { flags_ |= OUTPUT; }

	void clear_output() { flags_ &= ~OUTPUT; }

	unsigned int takesevents() const { return !(flags_&(INACTIVE | INVISIBLE | OUTPUT)); }

	unsigned int changed() const { return flags_ & CHANGED; }

	void set_changed() { flags_ |= CHANGED; }

	void clear_changed() { flags_ &= ~CHANGED; }

	void clear_active() { flags_ |= INACTIVE; }

	void set_active() { flags_ &= ~INACTIVE; }

	int take_focus();

	void set_visible_focus() { flags_ |= VISIBLE_FOCUS; }

	void clear_visible_focus() { flags_ &= ~VISIBLE_FOCUS; }

	void visible_focus(int v) { if (v) set_visible_focus(); else clear_visible_focus(); }

	unsigned int  visible_focus() { return flags_ & VISIBLE_FOCUS; }

	static void default_callback(Fl_Widget *cb, void *d);

	void do_callback() { do_callback(this, user_data_); }

	void do_callback(Fl_Widget* o, long arg) { do_callback(o, (void*)(fl_intptr_t)arg); }

	// Causes a widget to invoke its callback function with arbitrary arguments.
	// Documentation and implementation in Fl_Widget.cxx
	void do_callback(Fl_Widget* o, void* arg = 0);

	/* Internal use only. */
	int test_shortcut();
	/* Internal use only. */
	static unsigned int label_shortcut(const char *t);
	/* Internal use only. */
	static int test_shortcut(const char*, const bool require_alt = false);
	/* Internal use only. */
	void _set_fullscreen() { flags_ |= FULLSCREEN; }
	void _clear_fullscreen() { flags_ &= ~FULLSCREEN; }

	int contains(const Fl_Widget *w) const;

	int inside(const Fl_Widget* wgt) const { return wgt ? wgt->contains(this) : 0; }

	void redraw();

	void redraw_label();

	uchar damage() const { return damage_; }

	void clear_damage(uchar c = 0) { damage_ = c; }

	void damage(uchar c);

	void damage(uchar c, int x, int y, int w, int h);

	void draw_label(int, int, int, int, Fl_Align) const;

	void measure_label(int& ww, int& hh) const { label_.measure(ww, hh); }

	Fl_Window* window() const;
	Fl_Window* top_window() const;
	Fl_Window* top_window_offset(int& xoff, int& yoff) const;

	virtual Fl_Group* as_group() { return 0; }

	virtual Fl_Window* as_window() { return 0; }

	virtual class Fl_Gl_Window* as_gl_window() { return 0; }

	int use_accents_menu() { return flags() & MAC_USE_ACCENTS_MENU; }

	Fl_Color color2() const { return (Fl_Color)color2_; }

	void color2(unsigned a) { color2_ = a; }
};

#define FL_RESERVED_TYPE 100

#endif

//
// End of "$Id$".
//