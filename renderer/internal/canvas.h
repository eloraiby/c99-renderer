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
#include <GLFW/glfw3.h>

#include "../renderer.h"

#define MAX_TITLE_SIZE		128
#define MAX_MSG_QUEUE_SIZE	4096

struct canvas_s {
	char			title[MAX_TITLE_SIZE];
	GLFWwindow*		window;
	texture2d_t		ui_tex;
	GLuint			gl_ui_tex;
	canvas_message_t	message_queue[MAX_MSG_QUEUE_SIZE];
	uint32			message_start;
	uint32			message_count;
};

#endif // CANVAS_H
