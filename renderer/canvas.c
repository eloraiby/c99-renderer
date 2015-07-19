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
#include <stdio.h>

#include <renderer.h>

#include "gl_core_2_1.h"
#include "internal/canvas.h"

/*******************************************************************************
** message handling
*******************************************************************************/
static void
push_message(canvas_t* canvas, canvas_message_t msg) {
	if( MAX_MSG_QUEUE_SIZE < canvas->message_count ) {
		fprintf(stderr, "push_message: unhandled messages in queue exceeded the maximum allows of %d messages: DROPPING OLD MESSAGE\n", MAX_MSG_QUEUE_SIZE);
		++canvas->message_start;
		--canvas->message_count;
	}

	canvas->message_queue[canvas->message_count]	= msg;

	++canvas->message_count;
}

static canvas_message_t
pop_message(canvas_t* canvas) {
	canvas_message_t out	= canvas->message_queue[canvas->message_start];

	++canvas->message_start;
	--canvas->message_count;

	if( 0 == canvas->message_count ) { // move the head to 0
		canvas->message_start	= 0;
	}

	return out;
}

/*******************************************************************************
** transforming events to messages
*******************************************************************************/
static void
key_callback(GLFWwindow* window, int key, int scan, int action, int modifiers) {
	canvas_t*		canvas	= (canvas_t*)glfwGetWindowUserPointer(window);
	MODIFIER		mods	= 0;
	canvas_message_t	msg;

	if( modifiers && GLFW_MOD_ALT )		mods	|= CM_MOD_ALT;
	if( modifiers && GLFW_MOD_CONTROL )	mods	|= CM_MOD_CONTROL;
	if( modifiers && GLFW_MOD_SHIFT )	mods	|= CM_MOD_SHIFT;
	if( modifiers && GLFW_MOD_SUPER )	mods	|= CM_MOD_SUPER;

	msg.type	= action == GLFW_PRESS ? CM_KEY_PRESS : CM_KEY_RELEASE;
	msg.key_press_release.key	= key;
	msg.key_press_release.mods	= mods;
	msg.key_press_release.scan	= scan;

	push_message(canvas, msg);
}

static void
character_callback(GLFWwindow* window, unsigned int codepoint) {
	canvas_t*		canvas	= (canvas_t*)glfwGetWindowUserPointer(window);

}

static void
cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	canvas_t*		canvas	= (canvas_t*)glfwGetWindowUserPointer(window);

}

static void
cursor_enter_callback(GLFWwindow* window, int entered) {
	canvas_t*		canvas	= (canvas_t*)glfwGetWindowUserPointer(window);
	if( entered ) {
		// The cursor entered the client area of the window
	} else {
		// The cursor left the client area of the window
	}
}

static void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	canvas_t*		canvas	= (canvas_t*)glfwGetWindowUserPointer(window);

//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//	popup_menu();
}

static void
scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	canvas_t*		canvas	= (canvas_t*)glfwGetWindowUserPointer(window);

}

/*******************************************************************************
** public API
*******************************************************************************/
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
			memset(canvas, 0, sizeof(canvas_t));
			canvas->window	= win;
			memcpy(canvas->title, title, tlen > MAX_TITLE_SIZE - 1 ? MAX_TITLE_SIZE - 1 : tlen);

			glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			printf("OpenGL version: %d.%d\n", major, minor);

			glfwSetWindowUserPointer(win, canvas);

			glfwSetKeyCallback(win, key_callback);
			glfwSetCharCallback(win, character_callback);
			glfwSetCursorPosCallback(win, cursor_position_callback);
			glfwSetCursorEnterCallback(win, cursor_enter_callback);
			glfwSetMouseButtonCallback(win, mouse_button_callback);
			glfwSetScrollCallback(win, scroll_callback);

			return canvas;
		} else	return NULL;
	} else	return NULL;
}

DLL_RENDERING_PUBLIC void
canvas_release(canvas_t* canvas) {
	if( 0 != canvas->gl_ui_tex ) {
		glDeleteTextures(1, &canvas->gl_ui_tex);
	}
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

DLL_RENDERING_PUBLIC bool
canvas_ui_set_texture(canvas_t* canvas, sint32 columns, sint32 rows) {
	glfwMakeContextCurrent(canvas->window);

	if( 0 == canvas->gl_ui_tex ) {
		glGenTextures(1, &canvas->gl_ui_tex);
	}

	glBindTexture(GL_TEXTURE_2D, canvas->gl_ui_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, columns * TILE_WIDTH, rows * TILE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	canvas->ui_tex.fmt	= TEXF_A8R8G8B8;
	canvas->ui_tex.columns	= columns;
	canvas->ui_tex.rows	= rows;

	return true;
}

DLL_RENDERING_PUBLIC bool
canvas_ui_set_texture_tile(canvas_t* canvas, sint32 row, sint32 column, const color4b_t* pixels) {
	glfwMakeContextCurrent(canvas->window);

	if( 0 == canvas->gl_ui_tex ) {
		fprintf(stderr, "ERROR: canvas_ui_set_texture_tile: no call canvas_ui_set_texture has been made before this call...\n");
		return false;
	}

	if( row >= canvas->ui_tex.rows ) {
		fprintf(stderr, "ERROR: canvas_ui_set_texture_tile: given row %d, max is %d...\n", row, canvas->ui_tex.rows - 1);
		return false;
	}

	if( column >= canvas->ui_tex.columns ) {
		fprintf(stderr, "ERROR: canvas_ui_set_texture_tile: given column %d, max is %d...\n", column, canvas->ui_tex.columns - 1);
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, canvas->gl_ui_tex);
	glTexSubImage2D(GL_TEXTURE_2D,
			0,
			column * TILE_WIDTH,
			row * TILE_HEIGHT,
			canvas->ui_tex.columns * TILE_WIDTH,
			canvas->ui_tex.rows * TILE_HEIGHT,
			canvas->ui_tex.fmt,
			GL_UNSIGNED_BYTE,
			pixels);

	return true;
}

DLL_RENDERING_PUBLIC bool
canvas_ui_render_batch(canvas_t* canvas, sint32 count, rm_batch2d_rect_t* rects) {

	glfwMakeContextCurrent(canvas->window);
	if( 0 == canvas->gl_ui_tex ) {
		fprintf(stderr, "ERROR: canvas_ui_render_batch: no call canvas_ui_set_texture has been made before this call...\n");
		return false;
	}


	return true;
}

//DLL_RENDERING_PUBLIC void			canvas_ui_push_region(canvas_t* canvas, rect_t r);
//DLL_RENDERING_PUBLIC rect_t			canvas_ui_pop_region(canvas_t* canvas);
//DLL_RENDERING_PUBLIC rect_t			canvas_ui_relative_top_region(canvas_t* canvas);
//DLL_RENDERING_PUBLIC rect_t			canvas_ui_absolute_top_region(canvas_t* canvas);

DLL_RENDERING_PUBLIC void
canvas_clear(canvas_t* canvas) {
	glfwMakeContextCurrent(canvas->window);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

DLL_RENDERING_PUBLIC void
canvas_flush(canvas_t* canvas) {
	glfwMakeContextCurrent(canvas->window);
	glfwSwapBuffers(canvas->window);
}

DLL_RENDERING_PUBLIC bool
canvas_poll_message(canvas_t* canvas, canvas_message_t* out) {
	glfwPollEvents();
	if( 0 < canvas->message_count ) {
		*out	= pop_message(canvas);
		return true;
	} else return false;
}

DLL_RENDERING_PUBLIC canvas_message_t
canvas_wait_message(canvas_t* canvas) {

	// warning, this will block events on other threads using wait_message: better not to use
	while( 0 == canvas->message_count ) {
		glfwWaitEvents();
	}

	return pop_message(canvas);
}
