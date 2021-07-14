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
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
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
    //
    // Implement your own stuff
    //
	mMaxNumNode = Param::GRAPH_MAX_NUM_NODES;
    mMaxNumEdge = Param::GRAPH_MAX_NUM_EDGES;

    mNodeArr = new GRAPH_NODE[mMaxNumNode];
    mEdgeArr = new GRAPH_EDGE[mMaxNumEdge];

    mActiveNodeArr = new int[mMaxNumNode];
    mActiveEdgeArr = new int[mMaxNumEdge];

    mFreeNodeArr = new int[mMaxNumNode];
    mFreeEdgeArr = new int[mMaxNumEdge];
    //
    for ( int i = 0; i < mMaxNumNode; ++i ) {
        mNodeArr[i].id = i;
    }
    for ( int i = 0; i < mMaxNumEdge; ++i ) {
        mEdgeArr[i].id = i;
    }
    //
    reset( );
	//
	createDefaultGraph();
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
	mNumOfNode = 0;
    mNumOfEdge = 0;

    mFreeNode = mMaxNumNode;
    mFreeEdge = mMaxNumEdge;

    for ( int i = 0; i < mFreeNode; ++i ) {
        mFreeNodeArr[ i ] = i;
    }
    for ( int i = 0; i < mFreeEdge; ++i ) {
        mFreeEdgeArr[ i ] = i;
    }
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
	reset( );
    //
    // Implement your own stuff
    //
	cout << "here"<< endl;

    int n_0 = addNode( 0.0, 0.0, 0.0 );
    cout << "n_0:"<< n_0 << endl;

    int n_1 = addNode( 5.0, 0.0, 0.0 );
    cout << "n_1:"<< n_1 << endl;

    int n_2 = addNode( 0.0, 0.0, 5.0 );
    cout << "n_2:"<< n_2 << endl;

    addEdge( n_0, n_1 );
    addEdge( n_1, n_2 );
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
	vector<int> id;
    id.resize( 2 * n );
    for ( int j = 0; j < 2; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            float cr = r + d * j;
            float a = i / (float) n * 2.0 * 3.14;
            float x = cr * cos(a);
            float z = cr * sin(a);
            int index = i + j * n;
            id[ index ] = addNode( offset_x+x, 0.0, offset_z+z );
        }
    }
	//rand edge
    for (int i = 0; i < n;++i ) {
        int k0 = i;
        int tmp_k1 = (k0 + (rand() % 3) * (2 * (rand() % 2) - 1) ) % n;
        if (tmp_k1 < 0) tmp_k1 = (n-1) + tmp_k1;
        int k1 = tmp_k1 + n;
        addEdge(id[k0], id[k1]);
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
	vector<int> id;
    id.resize( n * (num_layers + 1 ) );
    for ( int j = 0; j < num_layers+1; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            float cr = r + d * j;
            float a = (float) i /  n * 2.0 * 3.14;
            float x = cr * cos(a);
            float z = cr * sin(a);
            int index = i + j * n;
            id[ index ] = addNode( offset_x + x, 0.0, offset_z + z );
        }
		//circle edge
        if ( j < num_layers){
            for ( int i = 0; i < n; ++i ) {
                int k0 = i + j * n;
                int k1 = (i + 1) % n + j * n;
                addEdge( id[k0], id[k1] );
            }
		}
    }
	//layer edge
    for ( int j = 0; j < num_layers; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            int k0 = i + n * j;
            int k1 = i + n * (j+1);
            addEdge( id[k0], id[k1] );
        }
    }
}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float offset_x = 5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
	vector<int> id;
    int total = num_layers * num_layers;
    id.resize( total );
	//create num * num nodes
    for ( int j = 0; j < num_layers; ++j ) {
        for ( int i = 0; i < num_layers; ++i ) {
            float x, z;
            x = i*dx;
            z = j*dz;
            int index = i + j * num_layers;
            id[ index ] = addNode( offset_x+x, 0.0, offset_z+z );
        }
    }
	//add ¥­¦æ edge
    for ( int j = 0; j < num_layers; ++j ) {
        for ( int i = 0; i < num_layers - 1; ++i ) {
            int k0, k1;
            k0 = i + num_layers * j;
            k1 = k0 + 1;
            addEdge( id[k0], id[k1] );
        }
    }
	//add ¹]ª½ edge
    for ( int j = 0; j < num_layers-1; ++j ) {
        for ( int i = 0; i < num_layers; ++i ) {
            int k0, k1;
            k0 = i + num_layers * j;
            k1 = k0 + num_layers;
            addEdge( id[k0], id[k1] );
        }
    }
	//delete center n * n nodes
    int half = num_layers / 2 - n / 2;
    for ( int j = 0; j < n; ++j ) {
        for ( int i = 0; i < n; ++i ) {
            int layer = num_layers / 2;
            int k = half * num_layers + j * num_layers + half+i;
            deleteNode(id[k]);
            deleteEdge(id[k]);
        }
    }
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //    
	vector<int> id;
    id.resize( n + 1);
	//center node
    id[ 0 ] = addNode( offset_x, 0.0, offset_z);
	//circle node
    for ( int i = 0; i < n; ++i ) {
        float x, z;
        float a = i / (float) n * 2.0 * 3.14;
        x = r * cos(a);
        z = r * sin(a);
        int index = i+1;
        id[ index ] = addNode( offset_x + x, 0.0, offset_z + z );
    }
	//add edge with center
    for ( int i = 0; i < n; ++i ) {
        int k = i + 1;
        addEdge( id[0], id[k] );
    }
}

// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    //
    // Implement your own stuff
    //  
	//check max num of node
	if(this->mFreeNode == 0) return -1;
	//load ID
	int id = mFreeNodeArr[--mFreeNode];
	GRAPH_NODE* new_node = &mNodeArr[id];
	mActiveNodeArr[mNumOfNode] = id;
	new_node->dynamicID = mNumOfNode++;
	//init new node
    new_node->p = vector3( x, y, z );
    new_node->r = r;
    new_node->edgeID.clear( );
	//
    return new_node->id;
}

// return edge id
int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    //
    // Implement your own stuff
    //  
	//check max num of edge
	if ( mFreeEdge == 0 ) return -1;
	//loaf ID
    int id = mFreeEdgeArr[--mFreeEdge];
    GRAPH_EDGE* new_edge = &mEdgeArr[ id ];
	mActiveEdgeArr[ mNumOfEdge ] = id;
    new_edge->dynamicID = mNumOfEdge++;
    //init new edge
    new_edge->nodeID[ 0 ] = nodeID_0;
    new_edge->nodeID[ 1 ] = nodeID_1;
    mNodeArr[ nodeID_0 ].edgeID.push_back( new_edge->id );
    mNodeArr[ nodeID_1 ].edgeID.push_back( new_edge->id );
	//
    return new_edge->id;
}

void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    // 
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
	//
}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE *n = 0;
    //
    // Implement your own stuff
    // 
	//First node distance
	int id = mActiveNodeArr[0];
	GRAPH_NODE* near_node = &mNodeArr[id];
    double dx = near_node->p.x - x;
    double dz = near_node->p.z - z;
    double d2 = dx*dx + dz*dz;
	cur_distance2 = d2;
	n = near_node;
	//Find shortest distance
    for ( int i = 1; i < mNumOfNode; ++i ) {
        int id = mActiveNodeArr[i];
        near_node = &mNodeArr[id];
        dx = near_node->p.x - x;
        dz = near_node->p.z - z;
        d2 = dx*dx + dz*dz;
        if ( d2 < cur_distance2 ) {
            cur_distance2 = d2;
            n = near_node;
        }
    }
	//
    return n;
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
    //
    // Implement your own stuff
    // 
	double cur_distance2;
    GRAPH_NODE* n = findNearestNode(x, z, cur_distance2);
    if ( n == 0 || n == mSelectedNode || cur_distance2 > n->r * n->r){
        mSelectedNode = 0;
        return;
    }
    if ( mSelectedNode != 0 ) {
        addEdge( mSelectedNode->id, n->id );
        mSelectedNode = 0;
        return;
    }
    mSelectedNode = n;
	return;
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    // 
	//check Alive now of node
	if ( mNumOfNode <= 0 ) return;
	//take node which will be deleted
    GRAPH_NODE* delete_node = &mNodeArr[ nodeID ];
    int dynamicID = delete_node->dynamicID;
	//if node is not last one node, change last and this node's ID
    if ( dynamicID + 1 !=  mNumOfNode ) {
        int src_id = mActiveNodeArr[ mNumOfNode - 1 ];
        mActiveNodeArr[ delete_node->dynamicID ] = src_id;
        mNodeArr[ src_id ].dynamicID = delete_node->dynamicID;
    }
	--mNumOfNode;
    mFreeNodeArr[ mFreeNode ] = delete_node->id;
    ++mFreeNode;
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    //
    // Implement your own stuff
    // 
	if ( mSelectedNode == 0 ) return;
    deleteNode( mSelectedNode->id );
    deleteEdge( mSelectedNode->id );
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    //
    // mSelectedNode != 0;
    //
    // Implement your own stuff
    // 
   
    return mSelectedNode != 0;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
	if ( isSelectedNode() ){
		r = mSelectedNode->r;
		p = mSelectedNode->p;
	}
    //
    // Implement your own stuff
    // 
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
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;
        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;
        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(24);
        mSelectedNode = 0;
		mNumPoints = 24;
        break;
	case '<':
        mFlgAutoNodeDeletion = false;
		--mNumPoints;
        if (mNumPoints<3) mNumPoints = 3;
        createRandomGraph_DoubleCircles(mNumPoints);
        mSelectedNode = 0;
        break;
    case '>':
        mFlgAutoNodeDeletion = false;
		++mNumPoints;
        if (mNumPoints> 36) mNumPoints = 36;
        createRandomGraph_DoubleCircles(mNumPoints);
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

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 
    return  mNumOfNode;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    // 
	int id = mActiveNodeArr[ nodeIndex ];
    GRAPH_NODE* node = &mNodeArr[ id ];
    r = node->r;
    p = node->p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mNumOfEdge;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    vector3 p;
    //
    // Implement your own stuff
    // 
	int id = mActiveEdgeArr[ edgeIndex ];
    GRAPH_EDGE* edge = &mEdgeArr[ id ];
    p = mNodeArr[ edge->nodeID[ nodeIndex ] ].p;
    return p;
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
	//
	if (mNumOfNode <= 0) {
		mFlgAutoNodeDeletion = false;
        return;
    }
	//
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
	//
    Sleep(250);
    //
    // Implement your own stuff
    // 
	int nodeID = mActiveNodeArr[0];
	//
    deleteNode(nodeID);
    deleteEdge(nodeID);
}

//delete all edges with this node
void GRAPH_SYSTEM::deleteEdge( int nodeID )
{
	GRAPH_NODE* node  = &mNodeArr[ nodeID ];
	GRAPH_EDGE* now_edge;
    for ( int i = 0; i < node->edgeID.size( ); ++i ) {
		//load
		int id =  node->edgeID[i];
        now_edge = &mEdgeArr[id];
		int dynamicID = now_edge->dynamicID;
		//if edge is not last one node, change last and this edge's ID
		if ( dynamicID + 1 != mNumOfEdge ) {
			int src_id = mActiveEdgeArr[ mNumOfEdge - 1 ];
			mActiveEdgeArr[ now_edge->dynamicID ] = src_id;
			mEdgeArr[ src_id ].dynamicID = now_edge->dynamicID;
		}
		//update data
		--mNumOfEdge;
		mFreeEdgeArr[ mFreeEdge ] = now_edge->id;
		++mFreeEdge;
		//load connect node
        int connect_nodeID = now_edge->nodeID[0] == nodeID ? now_edge->nodeID[1] : now_edge->nodeID[0];
		GRAPH_NODE* connect_node = &mNodeArr[ connect_nodeID ];
		//move last edge id to this and clear last one
		for ( int i = 0; i < connect_node->edgeID.size(); ++i) {
			if ( connect_node->edgeID[i] == now_edge->id ) {
				int size = connect_node->edgeID.size() - 1;
				connect_node->edgeID[i] = connect_node->edgeID[ size ];
				connect_node->edgeID.resize( size );
				break;
			}
		}
		//
    }
}