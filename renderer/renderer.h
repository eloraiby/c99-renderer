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
typedef enum {

	RM_FLUSH,		// flush the message queue to the screen
	RM_CLEAR_BUFFER,	// clear the screen buffer

	// 2d related messages
	RM_SET_2D_TEXTURE,
	RM_BATCH_2D,		// render 2d rectangle batch
	RM_PUSH_2D_REGION,	// push clip region
	RM_POP_2D_REGION,	// pop clip region

} RENDER_MESSAGE;

// texture
typedef enum {
	TEXF_R8G8B8,
	TEXF_A8R8G8B8,
} TEXTURE_FORMAT;

typedef struct {
	uint32			width;
	uint32			height;
	TEXTURE_FORMAT		fmt;
	void*			data;
} texture_2d_t;

// 2d/ui texture
typedef struct {
	texture_2d_t		tex;
} rm_2d_texture_t;

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

typedef struct {
	uint16			count;
	rm_batch2d_rect_t*	rects;
} rm_batch2d_t;

// the render message
typedef struct render_message_s {
	RENDER_MESSAGE		type;

	union {
		rm_batch2d_t	batch2d;
		rect_t		clip_region;
		rm_2d_texture_t	texture_2d;
	};
} render_message_t;

DLL_RENDERING_PUBLIC bool renderer_init();

#ifdef __cplusplus
}
#endif

#endif // RENDERER_H
