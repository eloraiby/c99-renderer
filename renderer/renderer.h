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

typedef enum {

	RM_FLUSH,		// flush the message queue to the screen
	RM_CLEAR_BUFFER,	// clear the screen buffer

	// 2d related messages
	RM_SET_2D_TEXTURE,
	RM_BATCH_2D,		// render 2d rectangle batch
	RM_PUSH_2D_REGION,	// push clip region
	RM_POP_2D_REGION,	// pop clip region

} RENDER_MESSAGE;

typedef struct render_message_s {
	RENDER_MESSAGE		type;
} render_message_t;

#endif // RENDERER_H
