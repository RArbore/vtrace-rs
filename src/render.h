/*
 * This file is part of vtrace-rs.
 * vtrace-rs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * vtrace-rs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with vtrace-rs. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

typedef struct renderer {
    uint32_t window_width;
    uint32_t window_height;
    GLFWwindow* window;
} renderer;

void init(void);

void cleanup(void);

int32_t render_tick(void);
