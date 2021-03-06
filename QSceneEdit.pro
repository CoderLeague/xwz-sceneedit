#-------------------------------------------------
#
# Project created by QtCreator 2012-10-13T21:34:29
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSceneEdit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trimesh/TriMesh_tstrips.cc \
    trimesh/TriMesh_stats.cc \
    trimesh/TriMesh_pointareas.cc \
    trimesh/TriMesh_normals.cc \
    trimesh/TriMesh_io.cc \
    trimesh/TriMesh_grid.cc \
    trimesh/TriMesh_curvature.cc \
    trimesh/TriMesh_connectivity.cc \
    trimesh/TriMesh_bounding.cc \
    trimesh/subdiv.cc \
    trimesh/shared.cc \
    trimesh/reorder_verts.cc \
    trimesh/remove.cc \
    trimesh/overlap.cc \
    trimesh/lmsmooth.cc \
    trimesh/KDtree.cc \
    trimesh/ICP.cc \
    trimesh/GLCamera.cc \
    trimesh/filter.cc \
    trimesh/faceflip.cc \
    trimesh/edgeflip.cc \
    trimesh/diffuse.cc \
    trimesh/conn_comps.cc \
    QSceneDisplay.cpp \
    Model.cpp \
    Material.cpp \
    Scene.cpp \
    mersenne-twister.cpp

HEADERS  += mainwindow.h \
    trimesh/XForm.h \
    trimesh/Vec.h \
    trimesh/TriMesh_algo.h \
    trimesh/TriMesh.h \
    trimesh/timestamp.h \
    trimesh/strutil.h \
    trimesh/noise3d.h \
    trimesh/mempool.h \
    trimesh/lineqn.h \
    trimesh/KDtree.h \
    trimesh/ICP.h \
    trimesh/GLCamera.h \
    trimesh/Color.h \
    trimesh/bsphere.h \
    trimesh/Box.h \
    Model.h \
    Material.h \
    BaseStruct.h \
    BaseFunction.h \
    Scene.h \
    QSceneDisplay.h \
    mersenne-twister.h

FORMS    += mainwindow.ui

RESOURCES += \
    QSceneEdit.qrc
