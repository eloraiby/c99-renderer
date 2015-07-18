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


// 2d/ui texture
typedef struct {
	sint32			rows;
	sint32			columns;
	TEXTURE_FORMAT		fmt;
} texture2d_t;

// 2d textured/colored rectangle batch
typedef struct {
	vec2_t			position;
	vec2_t			uv;
	vec4_t			color;
} rm_batch2d_vertex_t;

typedef struct {
	rm_batch2d_vertex_t	min;
	rm_batch2d_vertex_t	max;
} rm_batch2d_rect_t;

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
} CANVAS_MESSAGE;

typedef enum {
	CM_PBUTTON_0	= 0x0001,
	CM_PBUTTON_1	= 0x0002,
	CM_PBUTTON_2	= 0x0004,
	CM_PBUTTON_3	= 0x0008,
} POINTER_BUTTON;

typedef struct {
	CANVAS_MESSAGE	type;
	union {
		struct {
			vec2_t		position;
			sint32		buttons;
		} pointer_move;

		struct {
			vec2_t		position;
			POINTER_BUTTON	button;
		} pointer_press_release;

		struct {
			float		pos;
		} scroll;
	};
} canvas_message_t;

DLL_RENDERING_PUBLIC bool			renderer_init();

DLL_RENDERING_PUBLIC canvas_t*			canvas_create(const char* title, sint32 width, sint32 height);
DLL_RENDERING_PUBLIC void			canvas_release(canvas_t* canvas);
DLL_RENDERING_PUBLIC rect_t			canvas_get_screen_rect(canvas_t* canvas);
DLL_RENDERING_PUBLIC void			canvas_set_screen_rect(canvas_t* canvas, rect_t r);
DLL_RENDERING_PUBLIC const char*		canvas_get_title(canvas_t* canvas);
DLL_RENDERING_PUBLIC void			canvas_set_title(canvas_t* canvas, const char* title);

DLL_RENDERING_PUBLIC bool			canvas_ui_set_texture(canvas_t* canvas, texture2d_t tex);
DLL_RENDERING_PUBLIC bool			canvas_ui_set_texture_tile_3b(canvas_t* canvas, sint32 row, sint32 column, const color3b_t* pixels);
DLL_RENDERING_PUBLIC bool			canvas_ui_set_texture_tile_4b(canvas_t* canvas, sint32 row, sint32 column, const color4b_t* pixels);
DLL_RENDERING_PUBLIC bool			canvas_ui_render_batch(canvas_t* canvas, sint32 count, rm_batch2d_rect_t* rects);
DLL_RENDERING_PUBLIC void			canvas_ui_push_region(canvas_t* canvas, rect_t r);
DLL_RENDERING_PUBLIC rect_t			canvas_ui_pop_region(canvas_t* canvas);
DLL_RENDERING_PUBLIC rect_t			canvas_ui_relative_top_region(canvas_t* canvas);
DLL_RENDERING_PUBLIC rect_t			canvas_ui_absolute_top_region(canvas_t* canvas);

DLL_RENDERING_PUBLIC void			canvas_clear(canvas_t* canvas);
DLL_RENDERING_PUBLIC void			canvas_flush(canvas_t* canvas);

DLL_RENDERING_PUBLIC canvas_message_t		canvas_poll_message();
DLL_RENDERING_PUBLIC canvas_message_t		canvas_wait_message();

#ifdef __cplusplus
}
#endif

#endif // RENDERER_H
