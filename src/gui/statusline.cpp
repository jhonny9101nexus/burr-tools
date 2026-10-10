/* BurrTools
 *
 * BurrTools is the legal property of its developers, whose
 * names are listed in the COPYRIGHT file, which is included
 * within the source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include "statusline.h"

#include "buttongroup.h"
#include "configuration.h"

LStatusLine::LStatusLine(int x, int y, int w, int h) : layouter_c(x, y, w, h) {

  text = new LFl_Box(0, 0, 1, 1);
  text->box(FL_UP_BOX);
  text->color(FL_BACKGROUND_COLOR);
  text->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  text->weight(1, 0);

  Fl_Button * b;

  mode = new ButtonGroup_c(1, 0, 1, 1);

  b = mode->addButton();
  b->image(pm.get(ViewModeNormal_xpm));
  b->tooltip("Mostrar normalmente con el color de la forma");

  b = mode->addButton();
  b->image(pm.get(ViewModeColor_xpm));
  b->tooltip("Mostrar con los colores de las restricciones de color");

  b = mode->addButton();
  b->image(pm.get(ViewMode3D_xpm));
  b->tooltip("Mostrar en modo anaglifo");

  b = mode->addButton();
  b->image(pm.get(ViewMode3DL_xpm));
  b->tooltip("Mostrar en modo anaglifo con las gafas invertidas");

  rstyle = new ButtonGroup_c(2, 0, 1, 1);

  b = rstyle->addButton();
  b->image(pm.get(RenderModeVoxel_xpm));
  b->tooltip("Dibujar cada vóxel por separado");

  b = rstyle->addButton();
  b->image(pm.get(RenderModeEdges_xpm));
  b->tooltip("Dibujar caras planas con líneas en las aristas reales");

  b = rstyle->addButton();
  b->image(pm.get(RenderModeSTL_xpm));
  b->tooltip("Dibujar las piezas como las produce la exportación STL");

  rstyle->select(config.renderStyle());

#ifdef __APPLE__
  (new LFl_Box(0, 3, 0, 1, 1))->setMinimumSize(20, 0);
#endif

  clear_visible_focus();

  end();
}

void LStatusLine::setText(const char * t) {

  text->copy_label(t);
}

voxelFrame_c::colorMode LStatusLine::getColorMode(void) const {

  switch (mode->getSelected()) {
    case 0: return voxelFrame_c::pieceColor;
    case 1: return voxelFrame_c::paletteColor;
    case 2: return voxelFrame_c::anaglyphColor;
    case 3: return voxelFrame_c::anaglyphColorL;
    default: return voxelFrame_c::pieceColor;
  }
}

voxelFrame_c::renderStyle LStatusLine::getRenderStyle(void) const {

  switch (rstyle->getSelected()) {
    case 0: return voxelFrame_c::styleVoxel;
    case 1: return voxelFrame_c::styleEdges;
    case 2: return voxelFrame_c::styleSTL;
    default: return voxelFrame_c::styleVoxel;
  }
}

// cppcheck-suppress duplInheritedMember
void LStatusLine::callback(Fl_Callback* fkt, void * dat) {
  mode->callback(fkt, dat);
  rstyle->callback(fkt, dat);
}

