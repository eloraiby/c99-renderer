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
#include <renderer.h>

#include <stdio.h>

int
main(int argc, char *argv[]) {
	if( !renderer_init() ) {
		printf("failed to initialize renderer\n");
		return 1;
	}

	canvas_t*		canvas	= canvas_create("canvas", 800, 480);
	canvas_clear(canvas);
	canvas_flush(canvas);
	canvas_flush(canvas);

	canvas_message_t	msg;
	do {
		canvas_flush(canvas);
		msg	= canvas_wait_message(canvas);

		if( CM_CHAR == msg.type ) {
			fprintf(stderr, "%c", msg.code_point);
		}
	} while( !(CM_KEY_PRESS == msg.type && KEY_ESCAPE == msg.key_press_release.key) );

	canvas_release(canvas);
	return 0;
}
