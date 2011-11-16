/**
 *
 * This file is part of Tulip (www.tulip-software.org)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux 1 and Inria Bordeaux - Sud Ouest
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */
#include <tulip/ExtendedMetaNodeRenderer.h>

#include <tulip/OpenGlConfigManager.h>

#include <tulip/DrawingTools.h>
#include <tulip/BoundingBox.h>

#include <tulip/Camera.h>
#include <tulip/GlGraphInputData.h>
#include <tulip/GlCPULODCalculator.h>
#include <tulip/Glyph.h>
#include <tulip/GlNode.h>
#include <tulip/GlEdge.h>
#include <tulip/GlMetaNode.h>
#include <tulip/GlVertexArrayManager.h>
#include <tulip/GlMainWidget.h>
#include <tulip/NodeLinkDiagramComponent.h>

using namespace std;

namespace tlp {

ExtendedMetaNodeRenderer::ExtendedMetaNodeRenderer(GlGraphInputData *inputData):inputData(inputData) {
}

ExtendedMetaNodeRenderer::~ExtendedMetaNodeRenderer() {
  for(map<unsigned int,GlMainView *>::iterator it=idToViewMap.begin();it!=idToViewMap.end();++it){
    delete (*it).second;
  }
}

void ExtendedMetaNodeRenderer::render(node n,float lod,Camera* camera) {

  GlMainView *view;

  if(idToViewMap.count(n.id)!=0){
    view=idToViewMap[n.id];
  }else{
    view=new NodeLinkDiagramComponent;
    Graph *metaGraph = inputData->getGraph()->getNodeMetaInfo(n);
    view->setupUi();
    view->setGraph(metaGraph);
    view->setState(DataSet());
    view->getGlMainWidget()->getScene()->setCalculator(new GlCPULODCalculator());
    idToViewMap[n.id]=view;
  }

  GlScene *scene=view->getGlMainWidget()->getScene();

  GlNode glNode(n.id);

  BoundingBox bb=glNode.getBoundingBox(inputData);

  Coord eyeDirection=camera->getEyes()-camera->getCenter();
  eyeDirection = eyeDirection/eyeDirection.norm();

  Camera newCamera2=*camera;
  newCamera2.setEyes(newCamera2.getCenter()+Coord(0,0,1)*(newCamera2.getEyes()-newCamera2.getCenter()).norm());
  newCamera2.setUp(Coord(0,1,0));

  Coord first=newCamera2.worldTo2DScreen((Coord)(bb[0]));
  Coord second=newCamera2.worldTo2DScreen((Coord)(bb[1]));

  Coord center=camera->worldTo2DScreen((Coord)(bb[0]+bb[1])/2);
  Coord size=second-first;

  Vector<int,4> viewport;
  viewport[0]=center[0]-size[0]/2;
  viewport[1]=center[1]-size[1]/2;
  viewport[2]=size[0];
  viewport[3]=size[1];

  viewport[0]=camera->getViewport()[0]+viewport[0]-viewport[2]/2;
  viewport[1]=camera->getViewport()[1]+viewport[1]-viewport[3]/2;
  viewport[2]*=2;
  viewport[3]*=2;

  view->getGlMainWidget()->resizeGL(camera->getViewport()[2],camera->getViewport()[3]);
  scene->setViewport(viewport[0],viewport[1],viewport[2],viewport[3]);

  scene->setClearBufferAtDraw(false);
  view->getGlMainWidget()->centerScene();

  float baseNorm=(scene->getGraphLayer()->getCamera().getEyes()-scene->getGraphLayer()->getCamera().getCenter()).norm();
  Camera newCamera=scene->getGraphLayer()->getCamera();
  newCamera.setUp(camera->getUp());
  newCamera.setEyes(newCamera.getCenter()+(eyeDirection*baseNorm));
  newCamera.setZoomFactor(newCamera.getZoomFactor()*0.5);
  scene->getGraphLayer()->setCamera(newCamera);

  scene->draw();

  camera->getScene()->setClearBufferAtDraw(false);
  camera->getScene()->initGlParameters();
  camera->getScene()->setClearBufferAtDraw(true);
  camera->initGl();

}

}
