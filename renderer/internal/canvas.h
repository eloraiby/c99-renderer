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
#ifndef CANVAS_H
#define CANVAS_H

#include <mathlib.h>
#include <assert.h>

#include <GLFW/glfw3.h>

#include "../renderer.h"

#define MAX_TITLE_SIZE		128
#define MAX_MSG_QUEUE_SIZE	4096

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

#define MAKE_QUEUE(NAME, FNAME, TYPE, MAX_QUEUE_SIZE)	typedef struct { \
							TYPE			data[MAX_QUEUE_SIZE]; \
							uint32			start; \
							uint32			count; \
						} NAME; \
	static inline void \
	FNAME ## _push(NAME* queue, const TYPE* t) { \
		if( MAX_QUEUE_SIZE < queue->count ) { \
			fprintf(stderr, "queue_push: queue exceeded the maximum allows of %d elements: DROPPING OLD elements\n", MAX_QUEUE_SIZE); \
			++queue->start; \
			--queue->count; \
		} \
		queue->data[queue->count]	= *t; \
		++queue->count; \
	} \
	 \
	static inline TYPE \
	FNAME ## _pop(NAME* queue) { \
		assert(queue->count != 0); \
		TYPE out	= queue->data[queue->start]; \
		 \
		++queue->start; \
		--queue->count; \
		 \
		if( 0 == queue->count ) { /* move the head to 0 */ \
			queue->start	= 0; \
		} \
		 \
		return out; \
	}

MAKE_QUEUE(canvas_message_queue_t, cmqueue, canvas_message_t, MAX_MSG_QUEUE_SIZE)

struct canvas_s {
	char			title[MAX_TITLE_SIZE];
	GLFWwindow*		window;
	texture2d_t		ui_tex;
	GLuint			gl_ui_tex;
	canvas_message_queue_t	message_queue;
};

#endif // CANVAS_H
