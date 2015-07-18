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
#include <stdlib.h>
#include <string.h>
#include <renderer.h>

#include "gl_core_2_1.h"
#include "internal/canvas.h"

DLL_RENDERING_PUBLIC canvas_t*
canvas_create(const char* title, sint32 width, sint32 height) {

	GLFWwindow* win	= glfwCreateWindow(width, height, title, NULL, NULL);
	if( NULL != win ) {
		glfwMakeContextCurrent(win);
		if( ogl_LOAD_SUCCEEDED == ogl_LoadFunctions() ) {
			int	major	= ogl_GetMajorVersion();
			int	minor	= ogl_GetMinorVersion();
			size_t tlen	= strlen(title);
			canvas_t*	canvas	= (canvas_t*)malloc(sizeof(canvas_t));
			canvas->window	= win;
			memcpy(canvas->title, title, tlen > MAX_TITLE_SIZE ? MAX_TITLE_SIZE - 1 : tlen);
			canvas->title[MAX_TITLE_SIZE - 1] = '\0';

			printf("OGL: %d.%d", major, minor);
			return canvas;
		} else	return NULL;
	} else	return NULL;
}

DLL_RENDERING_PUBLIC void
canvas_release(canvas_t* canvas) {
	glfwDestroyWindow(canvas->window);
}

DLL_RENDERING_PUBLIC rect_t
canvas_get_screen_rect(canvas_t* canvas) {
	int pos_x	= 0;
	int pos_y	= 0;
	int width	= 0;
	int height	= 0;

	rect_t		r;

	glfwGetWindowSize(canvas->window, &width, &height);
	glfwGetWindowPos(canvas->window, &pos_x, &pos_y);

	r.x		= pos_x;
	r.y		= pos_y;
	r.width		= width;
	r.height	= height;

	return r;
}

DLL_RENDERING_PUBLIC void
canvas_set_screen_rect(canvas_t* canvas, rect_t r) {
	glfwSetWindowPos(canvas->window, r.x, r.y);
	glfwSetWindowSize(canvas->window, r.width, r.height);
}

DLL_RENDERING_PUBLIC const char*
canvas_get_title(canvas_t* canvas) {
	return canvas->title;
}

DLL_RENDERING_PUBLIC void
canvas_set_title(canvas_t* canvas, const char* title) {
	size_t tlen	= strlen(title);
	memcpy(canvas->title, title, tlen > MAX_TITLE_SIZE ? MAX_TITLE_SIZE - 1 : tlen);
	canvas->title[MAX_TITLE_SIZE - 1] = '\0';

	glfwSetWindowTitle(canvas->window, title);
}

//DLL_RENDERING_PUBLIC void			canvas_ui_set_texture(canvas_t* canvas, texture2d_t tex);
//DLL_RENDERING_PUBLIC void			canvas_ui_set_texture_tile(canvas_t* canvas, sint32 row, sint32 column, const vec4_t* pixels);
//DLL_RENDERING_PUBLIC void			canvas_ui_render_batch(canvas_t* canvas, sint32 count, rm_batch2d_rect_t* rects);
//DLL_RENDERING_PUBLIC void			canvas_ui_push_region(canvas_t* canvas, rect_t r);
//DLL_RENDERING_PUBLIC rect_t			canvas_ui_pop_region(canvas_t* canvas);
//DLL_RENDERING_PUBLIC rect_t			canvas_ui_relative_top_region(canvas_t* canvas);
//DLL_RENDERING_PUBLIC rect_t			canvas_ui_absolute_top_region(canvas_t* canvas);

//DLL_RENDERING_PUBLIC void			canvas_clear(canvas_t* canvas);
//DLL_RENDERING_PUBLIC void			canvas_flush(canvas_t* canvas);

//DLL_RENDERING_PUBLIC canvas_message_t		canvas_poll_message();
//DLL_RENDERING_PUBLIC canvas_message_t		canvas_wait_message();
