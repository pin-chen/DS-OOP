//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
//
// Add your own functions if necessary
//
#ifndef __MY_GRAPH_SYSTEM_H_
#define __MY_GRAPH_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;

class Param {
public: 
    static int GRAPH_MAX_NUM_NODES;
    static int GRAPH_MAX_NUM_EDGES;
};



class GRAPH_SYSTEM : public BASE_SYSTEM {

protected:
    void drawNodes( ) const;
    void drawEdges( ) const;
    void drawSelectedNode( ) const;
    //
    void drawNodes_Indirect( ) const;
    void drawEdges_Indirect( ) const;
    void drawSelectedNode_Indirect( ) const;
    //
    void initMemoryPool( );
    GRAPH_NODE *getFreeNode( );
    GRAPH_EDGE *getFreeEdge( );
    GRAPH_NODE *findNearestNode( double x, double y, double &cur_distance2 ) const;
    void deleteNode( int nodeID );
    void deleteSelectedNode(  );
    void deleteEdge( int edgeID );
    void deleteEdgesOfNode( int nodeID );
    void removeEdgeFromNode( const GRAPH_EDGE *e, int nodeID );

    void createNet_Horizontal( int nx, int ny );
    void createNet_Vertical( int nx, int ny );
    void createRandomGraph( int nx, int ny );
    void createRadialGraph( int nx, int ny );
    //
    void createNet_Circular( int n, int num_layers );
    void createNet_Square( int n, int num_layers );
    void createNet_RadialCircular( int n );
    void createRandomGraph_DoubleCircles(int n);
public:
    GRAPH_SYSTEM( );
    void update( );
    void stopAutoNodeDeletion();
    void reset( );
    void askForInput( );
    void clickAt(double x, double z);
    void moveTo(double x, double y );
    void handleKeyPressedEvent( unsigned char key );
    void handlePassiveMouseEvent( double x, double y );
    void draw( ) const;
    void createDefaultGraph( );
    int addNode( float x, float y, float z, float r = 1.0 );
    int addEdge( int nodeID_0, int nodeID_1 );
    bool isSelectedNode( ) const;
    void getInfoOfSelectedPoint( double &r, vector3 &p ) const;
    //
    int getNumOfEdges( ) const;
    vector3 getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const;

    int getNumOfNodes( ) const;
    void getNodeInfo( int nodeIndex, double &r, vector3 &p ) const;
protected:
    int mMaxNumNodes;
    int mMaxNumEdges;
    GRAPH_NODE *mNodeArr_Pool; 
    GRAPH_EDGE *mEdgeArr_Pool;
    //
    int *mActiveNodeArr;
    int mCurNumOfActiveNodes;
    int *mActiveEdgeArr;
    int mCurNumOfActiveEdges;
    //
    int *mFreeNodeArr;
    int *mFreeEdgeArr;
    int mCurNumOfFreeNodes;
    int mCurNumOfFreeEdges;
    //
    GRAPH_NODE *mSelectedNode;
    GRAPH_NODE *mPassiveSelectedNode;
    //
    bool mFlgAutoNodeDeletion;

    int mNumPoints_DoubleCircles;
};

#endif