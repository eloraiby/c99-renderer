/*
** Renderer library Copyright 2015(c) Wael El Oraiby. All Rights Reserved
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** Under Section 7 of GPL version 3, you are granted additional
** permissions described in the GCC Runtime Library Exception, version
** 3.1, as published by the Free Software Foundation.
**
** You should have received a copy of the GNU General Public License and
** a copy of the GCC Runtime Library Exception along with this program;
** see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
** <http://www.gnu.org/licenses/>.
**
*/
#ifndef RENDERER_H
#define RENDERER_H

#include <mathlib.h>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_RENDERING_DLL
    #ifdef __GNUC__
      #define DLL_RENDERING_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_RENDERING_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_RENDERING_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_RENDERING_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_RENDERING_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_RENDERING_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_RENDERING_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_RENDERING_PUBLIC
    #define DLL_RENDERING_LOCAL
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

// texture
typedef enum {
	TEXF_R8G8B8	= 0x00000888,
	TEXF_A8R8G8B8	= 0x00008888,
} TEXTURE_FORMAT;

#define TILE_WIDTH	64
#define TILE_HEIGHT	64




struct canvas_s;
typedef struct canvas_s canvas_t;

typedef enum {
	CM_NONE,
	CM_POINTER_MOVE,	// move inside the canvas
	CM_POINTER_PRESS,	// press inside the canvas
	CM_POINTER_RELEASE,	// release inside the canvas
	CM_SCROLL,		// scroll canvas
	CM_ENTER,		// enter canvas
	CM_LEAVE,		// leave canvas
	CM_KEY_PRESS,
	CM_KEY_RELEASE,
	CM_CHAR,
} CANVAS_MESSAGE;

typedef enum {
	CM_PBUTTON_0		= 0x0001,
	CM_PBUTTON_1		= 0x0002,
	CM_PBUTTON_2		= 0x0004,
	CM_PBUTTON_3		= 0x0008,

	CM_PBUTTON_LEFT		= 0x0001,
	CM_PBUTTON_MIDDLE	= 0x0002,
	CM_PBUTTON_RIGHT	= 0x0004,
} POINTER_BUTTON;

typedef enum {
	CM_MOD_SHIFT		= 0x0001,
	CM_MOD_CONTROL		= 0x0002,
	CM_MOD_ALT		= 0x0004,
	CM_MOD_SUPER		= 0x0008,
} MODIFIER;

typedef enum {
	KEY_SPACE              = 32,
	KEY_APOSTROPHE         = 39,  /* ' */
	KEY_COMMA              = 44,  /* , */
	KEY_MINUS              = 45,  /* - */
	KEY_PERIOD             = 46,  /* . */
	KEY_SLASH              = 47,  /* / */
	KEY_0                  = 48,
	KEY_1                  = 49,
	KEY_2                  = 50,
	KEY_3                  = 51,
	KEY_4                  = 52,
	KEY_5                  = 53,
	KEY_6                  = 54,
	KEY_7                  = 55,
	KEY_8                  = 56,
	KEY_9                  = 57,
	KEY_SEMICOLON          = 59,  /* ; */
	KEY_EQUAL              = 61,  /* = */
	KEY_A                  = 65,
	KEY_B                  = 66,
	KEY_C                  = 67,
	KEY_D                  = 68,
	KEY_E                  = 69,
	KEY_F                  = 70,
	KEY_G                  = 71,
	KEY_H                  = 72,
	KEY_I                  = 73,
	KEY_J                  = 74,
	KEY_K                  = 75,
	KEY_L                  = 76,
	KEY_M                  = 77,
	KEY_N                  = 78,
	KEY_O                  = 79,
	KEY_P                  = 80,
	KEY_Q                  = 81,
	KEY_R                  = 82,
	KEY_S                  = 83,
	KEY_T                  = 84,
	KEY_U                  = 85,
	KEY_V                  = 86,
	KEY_W                  = 87,
	KEY_X                  = 88,
	KEY_Y                  = 89,
	KEY_Z                  = 90,
	KEY_LEFT_BRACKET       = 91,  /* [ */
	KEY_BACKSLASH          = 92,  /* \ */
	KEY_RIGHT_BRACKET      = 93,  /* ] */
	KEY_GRAVE_ACCENT       = 96,  /* ` */
	KEY_WORLD_1            = 161, /* non-US #1 */
	KEY_WORLD_2            = 162, /* non-US #2 */

	/* Function keys */
	KEY_ESCAPE             = 256,
	KEY_ENTER              = 257,
	KEY_TAB                = 258,
	KEY_BACKSPACE          = 259,
	KEY_INSERT             = 260,
	KEY_DELETE             = 261,
	KEY_RIGHT              = 262,
	KEY_LEFT               = 263,
	KEY_DOWN               = 264,
	KEY_UP                 = 265,
	KEY_PAGE_UP            = 266,
	KEY_PAGE_DOWN          = 267,
	KEY_HOME               = 268,
	KEY_END                = 269,
	KEY_CAPS_LOCK          = 280,
	KEY_SCROLL_LOCK        = 281,
	KEY_NUM_LOCK           = 282,
	KEY_PRINT_SCREEN       = 283,
	KEY_PAUSE              = 284,
	KEY_F1                 = 290,
	KEY_F2                 = 291,
	KEY_F3                 = 292,
	KEY_F4                 = 293,
	KEY_F5                 = 294,
	KEY_F6                 = 295,
	KEY_F7                 = 296,
	KEY_F8                 = 297,
	KEY_F9                 = 298,
	KEY_F10                = 299,
	KEY_F11                = 300,
	KEY_F12                = 301,
	KEY_F13                = 302,
	KEY_F14                = 303,
	KEY_F15                = 304,
	KEY_F16                = 305,
	KEY_F17                = 306,
	KEY_F18                = 307,
	KEY_F19                = 308,
	KEY_F20                = 309,
	KEY_F21                = 310,
	KEY_F22                = 311,
	KEY_F23                = 312,
	KEY_F24                = 313,
	KEY_F25                = 314,
	KEY_KP_0               = 320,
	KEY_KP_1               = 321,
	KEY_KP_2               = 322,
	KEY_KP_3               = 323,
	KEY_KP_4               = 324,
	KEY_KP_5               = 325,
	KEY_KP_6               = 326,
	KEY_KP_7               = 327,
	KEY_KP_8               = 328,
	KEY_KP_9               = 329,
	KEY_KP_DECIMAL         = 330,
	KEY_KP_DIVIDE          = 331,
	KEY_KP_MULTIPLY        = 332,
	KEY_KP_SUBTRACT        = 333,
	KEY_KP_ADD             = 334,
	KEY_KP_ENTER           = 335,
	KEY_KP_EQUAL           = 336,
	KEY_LEFT_SHIFT         = 340,
	KEY_LEFT_CONTROL       = 341,
	KEY_LEFT_ALT           = 342,
	KEY_LEFT_SUPER         = 343,
	KEY_RIGHT_SHIFT        = 344,
	KEY_RIGHT_CONTROL      = 345,
	KEY_RIGHT_ALT          = 346,
	KEY_RIGHT_SUPER        = 347,
	KEY_MENU               = 348,
} KEY;

typedef struct {
	CANVAS_MESSAGE	type;
	union {
		struct  {
			KEY		key;
			uint32		scan;
			MODIFIER	mods;
		} key_press_release;

		struct {
			vec2_t		position;
			POINTER_BUTTON	buttons;
		} pointer_move;

		struct {
			vec2_t		position;
			POINTER_BUTTON	button;
		} pointer_press_release;

		struct {
			vec2_t		pos;
		} scroll;

		uint32	code_point;
	};
} canvas_message_t;

DLL_RENDERING_PUBLIC bool			renderer_init();

DLL_RENDERING_PUBLIC canvas_t*			canvas_create(const char* title, sint32 width, sint32 height);
DLL_RENDERING_PUBLIC void			canvas_release(canvas_t* canvas);
DLL_RENDERING_PUBLIC rect_t			canvas_get_screen_rect(canvas_t* canvas);
DLL_RENDERING_PUBLIC void			canvas_set_screen_rect(canvas_t* canvas, rect_t r);
DLL_RENDERING_PUBLIC const char*		canvas_get_title(canvas_t* canvas);
DLL_RENDERING_PUBLIC void			canvas_set_title(canvas_t* canvas, const char* title);

DLL_RENDERING_PUBLIC bool			canvas_ui_set_texture(canvas_t* canvas, sint32 columns, sint32 rows);
DLL_RENDERING_PUBLIC bool			canvas_ui_set_texture_tile(canvas_t* canvas, sint32 row, sint32 column, const color4b_t* pixels);
DLL_RENDERING_PUBLIC bool			canvas_ui_render_rectangle(canvas_t* canvas, vec2_t p0, vec2_t t0, vec2_t p1, vec2_t t1, color4_t col);
DLL_RENDERING_PUBLIC void			canvas_ui_push_region(canvas_t* canvas, rect_t r);
DLL_RENDERING_PUBLIC rect_t			canvas_ui_pop_region(canvas_t* canvas);
DLL_RENDERING_PUBLIC rect_t			canvas_ui_relative_top_region(canvas_t* canvas);
DLL_RENDERING_PUBLIC rect_t			canvas_ui_absolute_top_region(canvas_t* canvas);

DLL_RENDERING_PUBLIC void			canvas_clear(canvas_t* canvas);
DLL_RENDERING_PUBLIC void			canvas_flush(canvas_t* canvas);

DLL_RENDERING_PUBLIC bool			canvas_poll_message(canvas_t* canvas, canvas_message_t* out);

// warning, this will block events on other threads using wait_message: DO NOT USE in Multi threaded applications
DLL_RENDERING_PUBLIC canvas_message_t		canvas_wait_message(canvas_t* canvas);

#ifdef __cplusplus
}
#endif

#endif // RENDERER_H
