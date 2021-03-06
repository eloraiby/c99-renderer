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

#include "renderer.h"
#include "gl_core_2_1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>

#include "internal/canvas.h"



DLL_RENDERING_PUBLIC rserver_t*
renderer_init() {
	static rserver_t	rserver;
	static bool		initialized	= false;
	if( !initialized ) {
		memset(&rserver, 0, sizeof(rserver));
		for( size_t i = 0; i < MAX_CANVAS; ++i ) {
			rserver.canvas[i].id	= -1;	// set as free
		}

		if( GL_FALSE == glfwInit() ) {
			return NULL;
		}

		initialized	= true;
	}

	printf("renderer reserved memory: %fkb\n", sizeof(rserver) / 1024.0f);

	return &rserver;
}

