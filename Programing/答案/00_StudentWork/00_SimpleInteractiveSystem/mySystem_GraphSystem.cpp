//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/04/09
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 10000;
int Param::GRAPH_MAX_NUM_EDGES = 10000;

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    mFlgAutoNodeDeletion = false;

    initMemoryPool();
    createDefaultGraph();
}

void GRAPH_SYSTEM::initMemoryPool( )
{
    mMaxNumNodes = Param::GRAPH_MAX_NUM_NODES;
    mMaxNumEdges = Param::GRAPH_MAX_NUM_EDGES;

    mNodeArr_Pool = new GRAPH_NODE[mMaxNumNodes];
    mEdgeArr_Pool = new GRAPH_EDGE[mMaxNumEdges];

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;
    mActiveNodeArr = new int[mMaxNumNodes];
    mActiveEdgeArr = new int[mMaxNumEdges];

    mFreeNodeArr = new int[mMaxNumNodes];
    mFreeEdgeArr = new int[mMaxNumEdges];
    //
    for ( int i = 0; i < mMaxNumNodes; ++i ) {
        mNodeArr_Pool[ i ].id = i;
    }
    for ( int i = 0; i < mMaxNumEdges; ++i ) {
        mEdgeArr_Pool[ i ].id = i;
    }
    //
    reset( );
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();

    //mNumPoints_DoubleCircles = 0;

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;

    mCurNumOfFreeNodes = mMaxNumNodes;
    mCurNumOfFreeEdges = mMaxNumEdges;

    for ( int i = 0; i < mCurNumOfFreeNodes; ++i ) {
        mFreeNodeArr[ i ] = i;
    }
    for ( int i = 0; i < mCurNumOfFreeEdges; ++i ) {
        mFreeEdgeArr[ i ] = i;
    }

    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
}

GRAPH_NODE *GRAPH_SYSTEM::getFreeNode( ) 
{
    if ( mCurNumOfFreeNodes == 0 ) return 0;
    --mCurNumOfFreeNodes;
    int id = mFreeNodeArr[ mCurNumOfFreeNodes ];
    GRAPH_NODE *n = &mNodeArr_Pool[ id ];
    mActiveNodeArr[ mCurNumOfActiveNodes ] = id;
    n->dynamicID = mCurNumOfActiveNodes;
    ++mCurNumOfActiveNodes;
    return n;
}

GRAPH_EDGE *GRAPH_SYSTEM::getFreeEdge( )
{
    if ( mCurNumOfFreeEdges == 0 ) return 0;
    --mCurNumOfFreeEdges;
    int id = mFreeEdgeArr[ mCurNumOfFreeEdges ];
    GRAPH_EDGE *e = &mEdgeArr_Pool[ id ];
    mActiveEdgeArr[ mCurNumOfActiveEdges ] = id;
    e->dynamicID = mCurNumOfActiveEdges;

    ++mCurNumOfActiveEdges;
    return e;
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    cout << "here"<< endl;
    reset( );

    int n_0 = addNode( 0.0, 0.0, 0.0 );
    cout << "n_0:"<< n_0 << endl;

    int n_1 = addNode( 5.0, 0.0, 0.0 );
    cout << "n_1:"<< n_1 << endl;

    int n_2 = addNode( 0.0, 0.0, 5.0 );
    cout << "n_2:"<< n_2 << endl;

    addEdge( n_0, n_1 );
    addEdge( n_1, n_2 );

}

void GRAPH_SYSTEM::createNet_Horizontal( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    vector<int> id;
    id.resize( nx );
    for ( int j = 0; j < ny; ++j ) {
        for ( int i = 0; i < nx; ++i ) {
            id[ i ] = addNode( i*dx, 0.0, j*dz );
        }
        for ( int i = 0; i < nx-1; ++i ) {
            addEdge( id[i], id[i+1] );
        }
    }


}

void GRAPH_SYSTEM::createNet_Vertical( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    vector<int> id;
    id.resize( nx );
    for ( int i = 0; i < nx; ++i ) {
        for ( int j = 0; j < ny; ++j ) {

            id[ j ] = addNode( i*dx, 0.0, j*dz );
        }
        for ( int i = 0; i < nx-1; ++i ) {
            addEdge( id[i], id[i+1] );
        }
    }


}

void GRAPH_SYSTEM::createRandomGraph( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;

    for ( int i = 0; i < nx; ++i ) {
        for ( int j = 0; j < ny; ++j ) {

            addNode( i*dx, 0.0, j*dz );
        }
    }
    int numEdges = 10;
    /*
    while ( true ) {
    cout << "Input the number of edges to be created [1, 20]:" << endl;
    cin >> numEdges;
    if ( numEdges > 0 && numEdges <= 20) break;
    }
    */

    for ( int i = 0; i < numEdges; ++i ) {
        int index0 = rand( )%mCurNumOfActiveNodes;
        int index1 = rand( )%mCurNumOfActiveNodes;
        addEdge( 
            mActiveNodeArr[ index0],
            mActiveNodeArr[ index1]
        );
    }
}

void GRAPH_SYSTEM::createRadialGraph( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;

    for ( int i = 0; i < nx; ++i ) {
        for ( int j = 0; j < ny; ++j ) {

            addNode( i*dx, 0.0, j*dz );
        }
    }
    int numEdges = 10;

    int index0 = rand( )%mCurNumOfActiveNodes;
    for ( int i = 0; i < numEdges; ++i ) {

        int index1 = rand( )%mCurNumOfActiveNodes;
        addEdge( 
            mActiveNodeArr[ index0],
            mActiveNodeArr[ index1]
        );
    }

}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );

    //n = 36;
    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;

    vector<int> id;
    int num_layers = 2;
    id.resize( n*(num_layers) );
    for ( int j = 0; j < num_layers; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            float x, z;
            float cr = r + d*j;
            float a = i/(float)n*2.0*3.14;
            x = cr*cos(a);
            z = cr*sin(a);
            int index = i + j*n;
            id[ index ] = addNode( offset_x+x, 0.0, offset_z+z );
        }
    }

    for (int i =0; i < n;++i ) {
        int k0 = i;
        int tmp_k1 = (k0 + (rand()%3)*(2*(rand()%2)-1))%n;
        if (tmp_k1<0) tmp_k1 = (n-1) + tmp_k1;
        int k1 = tmp_k1 + n;
        addEdge(id[k0], id[k1]);
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    vector<int> id;
    id.resize( n*(num_layers+1) );
    for ( int j = 0; j < num_layers+1; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            float x, z;
            float cr = r + d*j;
            float a = i/(float)n*2.0*3.14;
            x = cr*cos(a);
            z = cr*sin(a);
            int index = i + j*n;
            id[ index ] = addNode( offset_x+x, 0.0, offset_z+z );
        }
        if ( j<num_layers)
            for ( int i = 0; i < n; ++i ) {
                int k0, k1;
                k0 = i + j*n;
                k1 = (i+1)%n + j*n;

                addEdge( id[k0], id[k1] );
            }
    }
    for ( int j = 0; j < num_layers; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            int k0, k1;
            k0 = i + n*j;
            k1 = i + n*(j+1);
            addEdge( id[k0], id[k1] );
        }
    }

}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    vector<int> id;
    int num = n + (num_layers-1)*2;
    int total = num*num;
    id.resize( total );
    for ( int j = 0; j < num; ++j ) {
        for ( int i = 0; i < num; ++i ) {
            float x, z;
            x = i*dx;
            z = j*dz;
            int index = i + j*num;
            id[ index ] = addNode( offset_x+x, 0.0, offset_z+z );
        }
    }
    for ( int j = 0; j < num; ++j ) {
        for ( int i = 0; i < num-1; ++i ) {
            int k0, k1;
            k0 = i + num*j;
            k1 = k0+1;
            addEdge( id[k0], id[k1] );
        }
    }

    for ( int j = 0; j < num-1; ++j ) {
        for ( int i = 0; i < num; ++i ) {
            int k0, k1;
            k0 = i + num*j;
            k1 = k0 + num;
            addEdge( id[k0], id[k1] );
        }
    }
    int half = num/2-n/2+1;
    for ( int j = 0; j < n-2; ++j ) {
        for ( int i = 0; i < n-2; ++i ) {
            int layer = num/2;
            int k = half*num + j*num+half+i;
            deleteNode(id[k]);
            deleteEdgesOfNode(id[k]);
        }
    }
}
void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    vector<int> id;
    id.resize( n + 1);
    id[ 0 ] = addNode( offset_x, 0.0, offset_z);
    for ( int i = 0; i < n; ++i ) {
        float x, z;
        float a = i/(float)n*2.0*3.14;
        x = r*cos(a);
        z = r*sin(a);
        int index = i+1;
        id[ index ] = addNode( offset_x+x, 0.0, offset_z+z );
    }

    for ( int i = 0; i < n; ++i ) {
        int k0, k1;
        k0 = 0;
        k1 = i+1;
        addEdge( id[k0], id[k1] );
    }


}

int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    GRAPH_NODE *g;
    g = getFreeNode( );
    if ( g == 0 ) return -1;
    g->p = vector3( x, y, z );
    g->r = r;
    g->edgeID.clear( );
    return g->id;
}

int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    GRAPH_EDGE *e;
    e = getFreeEdge( );
    if ( e == 0 ) return -1;
    e->nodeID[ 0 ] = nodeID_0;
    e->nodeID[ 1 ] = nodeID_1;
    mNodeArr_Pool[ nodeID_0 ].edgeID.push_back( e->id );
    mNodeArr_Pool[ nodeID_1 ].edgeID.push_back( e->id );

    return e->id;
}

void GRAPH_SYSTEM::askForInput( )
{
    cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
    cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
    cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
    cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << " " << endl;
    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << " " << endl;
    cout << "A selected node is highlighted as red." << endl;

}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE *n = 0;
    cur_distance2 = -1.0;
    for ( int i = 0; i < mCurNumOfActiveNodes; ++i ) {
        int id = mActiveNodeArr[ i ];
        const GRAPH_NODE *cn = &mNodeArr_Pool[ id ];
        double dx = cn->p.x - x;
        double dz = cn->p.z - z;
        double d2 = dx*dx + dz*dz;
        if ( cur_distance2 < 0.0 || d2 < cur_distance2 ) {
            cur_distance2 = d2;
            n = (GRAPH_NODE *)cn;
        }

    }
    return n;
}

void GRAPH_SYSTEM::moveTo(double x, double y )
{
    if (!mSelectedNode) return;
    mSelectedNode->p.x = x;
    mSelectedNode->p.z = y;
}

void GRAPH_SYSTEM::clickAt(double x, double z)
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) {
        mSelectedNode = 0;
        return;
    }
    if ( cur_d2 > n->r*n->r ) {
        mSelectedNode = 0;
        return;

    }
    if ( mSelectedNode == n ) {
        mSelectedNode = 0;
        return;
    }
    if ( mSelectedNode != 0 ) {
        addEdge( mSelectedNode->id, n->id );
        mSelectedNode = 0;
        return;
    }
    mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteEdge( int edgeID )
{
    GRAPH_EDGE *e = &mEdgeArr_Pool[ edgeID ];
    int dynamicID = e->dynamicID;
    if ( dynamicID + 1 == mCurNumOfActiveEdges ) {
        --mCurNumOfActiveEdges; // last edge
    } else {
        --mCurNumOfActiveEdges;
        int src_id = mActiveEdgeArr[ mCurNumOfActiveEdges ];
        mActiveEdgeArr[ e->dynamicID ] = src_id;
        mEdgeArr_Pool[ src_id ].dynamicID = e->dynamicID;
    }

    mFreeEdgeArr[ mCurNumOfFreeEdges ] = e->id;
    ++mCurNumOfFreeEdges;
    //

}

void GRAPH_SYSTEM::removeEdgeFromNode( const GRAPH_EDGE *e, int nodeID )
{
    GRAPH_NODE *n = &mNodeArr_Pool[ nodeID ];
    int j = 0;
    for ( int i = 0; i < n->edgeID.size( ); ++i) {
        if ( n->edgeID[i] == e->id ) {
        } else {
            n->edgeID[j++] = n->edgeID[i];
        }
    }
    n->edgeID.resize( j );
}
void GRAPH_SYSTEM::deleteEdgesOfNode( int nodeID )
{
    GRAPH_NODE *n  = &mNodeArr_Pool[ nodeID ];
    for ( int i = 0; i < n->edgeID.size( ); ++i ) {
        deleteEdge( n->edgeID[ i ] );
        GRAPH_EDGE *e = &mEdgeArr_Pool[ n->edgeID[ i ] ];
        int src_nodeID = e->nodeID[ 0 ];
        if ( e->nodeID[ 0 ] == nodeID ) {
            src_nodeID = e->nodeID[ 1 ];
        }
        removeEdgeFromNode( e, src_nodeID );
    }
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    if ( mCurNumOfActiveNodes <= 0 ) return;
    GRAPH_NODE *n = &mNodeArr_Pool[ nodeID ];
    int dynamicID = n->dynamicID;
    if ( dynamicID + 1 == mCurNumOfActiveNodes ) {
        --mCurNumOfActiveNodes;
    } else {
        --mCurNumOfActiveNodes;
        int src_id = mActiveNodeArr[ mCurNumOfActiveNodes ];
        mActiveNodeArr[ n->dynamicID ] = src_id;
        mNodeArr_Pool[ src_id ].dynamicID = n->dynamicID;
    }

    mFreeNodeArr[ mCurNumOfFreeNodes ] = n->id;
    ++mCurNumOfFreeNodes;
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    if ( mSelectedNode == 0 ) return;
    deleteNode( mSelectedNode->id );
    deleteEdgesOfNode( mSelectedNode->id );
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    return mSelectedNode != 0;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    if ( isSelectedNode( ) == false ) return;
    r = mSelectedNode->r;
    p = mSelectedNode->p;

}



void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(15, 4);
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mNumPoints_DoubleCircles = 24;
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        mSelectedNode = 0;
        break;
    case '<':
        mNumPoints_DoubleCircles--;
        if (mNumPoints_DoubleCircles<3) 
            mNumPoints_DoubleCircles = 3;
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        mSelectedNode = 0;
        break;
    case '>':
        mNumPoints_DoubleCircles++;
        if (mNumPoints_DoubleCircles> 36) 
            mNumPoints_DoubleCircles = 36;
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        mSelectedNode = 0;
        break;

    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'd':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    return mCurNumOfActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    int nodeID = mActiveNodeArr[ nodeIndex ];
    GRAPH_NODE *n = &mNodeArr_Pool[ nodeID ];
    r = n->r;
    p = n->p;
}

int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    return mCurNumOfActiveEdges;
}

vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    int edgeID = mActiveEdgeArr[ edgeIndex ];
    GRAPH_EDGE *e = &mEdgeArr_Pool[ edgeID ];
    return mNodeArr_Pool[ e->nodeID[ nodeIndex ] ].p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
//
// 
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    if (mCurNumOfActiveNodes<=0) {
     mFlgAutoNodeDeletion = false;
        return;
    }
    Sleep(250);

    int nodeID = mActiveNodeArr[0];
    deleteNode(nodeID);

    deleteEdgesOfNode(nodeID);

    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
}