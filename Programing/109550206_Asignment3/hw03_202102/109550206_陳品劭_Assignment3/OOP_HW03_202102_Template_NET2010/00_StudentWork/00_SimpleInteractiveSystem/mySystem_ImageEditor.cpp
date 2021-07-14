//
// Prof. Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
//
#include <iostream>
#include "mySystem_ImageEditor.h"

#define IMAGE_FILE_NAME "3d-flower-desktop.jpg"

#define IMAGE_MAX_HIERARCHY_DEPTH 8

IMAGE_SYSTEM::IMAGE_SYSTEM()
{
    m_ImageHierarchy = 0;
    m_Image = new ns_opengl::Image;
    m_Image->readFile(IMAGE_FILE_NAME);

    int wImage, hImage;
        m_Image->getInfo(wImage, hImage);

    int cur_depth = 0;
        int start_x = 0;
    int start_y = 0;

        int w = wImage;
        int h = hImage;
        float sx = 2; 
        float sy = 2;

        float radius = wImage/2.0*(sx+sy)*0.5;

    m_ImageHierarchy = new IMAGE_NODE(
        cur_depth, 
        start_x,
        start_y,
        w,
        h,
        sx,
        sy,
        radius
        ); 
    float r, g, b;
    computeAverageColor(start_x, start_y, w, h, r, g, b);

    m_ImageHierarchy->setColor(r,g,b);
    m_ImageHierarchy->computeDrawPosition(
        wImage, hImage
        );
    //

	m_CurrentNode_Replay = 0;
    m_Replay_Head = 0;
    m_Replay_Tail = 0;
}

//dfs to reset
void IMAGE_SYSTEM::reset(IMAGE_NODE *node)
{
    node->flg_explored = false;
    for (int i = 0; i < 4; ++i ) {
        if (node->children[i]) {
            reset(node->children[i]);
        }
    }
}
//
void IMAGE_SYSTEM::reset()
{
	//for <, >
	m_CurrentNode_Replay = 0;
    m_Replay_Head = 0;
    m_Replay_Tail = 0;
	//reset all node
    reset(m_ImageHierarchy);
}

void IMAGE_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    switch(key) {
    case ' ':
		m_CurrentNode_Replay = 0;
        break;
    case '.':
    case '<':
		replay_forward();
        break;
    case ',':
    case '>': 
		replay_backward();
        break;
    case 'r':
        reset();
        break;
    
    case 'k':
    case 'K':
        break;
    case 'l':
    case 'L':
        break;
    }
}

//
// Compute the node color.
// That is compute the average color of the block of the node
//
void IMAGE_SYSTEM::computeNodeColor(IMAGE_NODE *node)
{
    float r, g, b;
    computeAverageColor(node->start_x, node->start_y, node->w, node->h, r, g, b);
    node->setColor(r,g,b);
}

//
// Explore a node if it is not explored.
// Go down the children if the node is explored.
//
void IMAGE_SYSTEM::exploreImageNode(IMAGE_NODE *node, double x, double y)
{
	//check 
    if (node->flg_explored) {
        // If the node has been explored, 
        // go to check its children
		for (int i = 0; i < 4; ++i) {//dfs
            exploreImageNode(node->children[i], x, y);
        }
    } else {
        // The node is not explored yet.
        // Now, explored it.
        // Do the following steps:
        // Can we explore it? If the dimension is less than 1x1, return.
        // If the dimension is at least 2x2
        //
        // Divide the image block into four children
        // Compute the draw positions of each child.
        //
		
		if (node->w / 2 == 0 || node->h / 2 == 0) return;
        float dx = x - node->draw_x;
        float dy = y - node->draw_y;
        float d2 = dx*dx + dy*dy;
        float r2 = node->radius * node->radius;
        if (d2 > r2) return;
        //
        if (m_Replay_Head) {
            m_Replay_Tail->next = node;
            node->prev = m_Replay_Tail;
            m_Replay_Tail = node;
        } else {
            m_Replay_Head = m_Replay_Tail = node;
        }
        //
        node->flg_explored = true;
        if (node->children[0]) return;
		//
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
		//create four little disk
        IMAGE_NODE *children[4];
        float radius = node->w/2.0;
        children[0] = new IMAGE_NODE( node->cur_depth+1, node->start_x, node->start_y, node->w/2, node->h/2, node->sx, node->sy, radius);
        children[1] = new IMAGE_NODE( node->cur_depth+1, node->start_x+node->w/2, node->start_y, node->w/2, node->h/2, node->sx, node->sy, radius );
        children[2] = new IMAGE_NODE( node->cur_depth+1, node->start_x, node->start_y+node->h/2, node->w/2, node->h/2, node->sx, node->sy, radius );
        children[3] = new IMAGE_NODE( node->cur_depth+1, node->start_x +node->w/2, node->start_y+node->h/2, node->w/2, node->h/2, node->sx, node->sy, radius );
		//call and let four disk color
        for (int i = 0; i < 4; ++i) {
            computeNodeColor(children[i]);
            children[i]->computeDrawPosition(wImage, hImage);
            node->children[i] = children[i];
        }
    }
}

//
// call exploreImageNode(root, mouse_x, mouse_y)
//
void IMAGE_SYSTEM::handlePassiveMouseEvent( double x, double y )
{
    //std::cout << "IMAGE_SYSTEM Mouse:" << x << "\t" << y << std::endl;
	exploreImageNode(m_ImageHierarchy,x, y);
}

///////////////////////////////////////////////////
void IMAGE_SYSTEM::collapseImageNode(IMAGE_NODE *node)
{
	//explore or fix from some node
    if (node ==0) return;
    node->flg_explored = false;
    for (int i =0; i <4; ++i) {
        if (node->children[i]) {
            collapseImageNode(node->children[i]);
        }
    }
}

//
void IMAGE_SYSTEM::collapseImageNode(IMAGE_NODE* parent_node, IMAGE_NODE* node, double x, double y)
{
    if (node->flg_explored) {
        bool flg_collapsed = false;
        for (int i =0; i <4; ++i) {
            if (node->children[i] == 0) {
                flg_collapsed = true;
                break;
            } else {
                collapseImageNode(node, node->children[i], x, y);
            }
        }
        if ( flg_collapsed ) {
              collapseImageNode(parent_node);
        }
    } else {
        if (parent_node) {
			float dx = x - parent_node->draw_x;
			float dy = y - parent_node->draw_y;
			float d2 = dx*dx + dy*dy;
			float r2 = parent_node->radius*parent_node->radius;
			if (d2 > r2) return;
			collapseImageNode(parent_node);
        }
    }
}
//下一步
void IMAGE_SYSTEM::replay_backward()
{
    if ( m_Replay_Head == 0) return;

    if (  m_CurrentNode_Replay == 0) {
        collapseImageNode(m_Replay_Head);
        m_CurrentNode_Replay = m_Replay_Tail;
    } else {
        m_CurrentNode_Replay->flg_explored = false;
        m_CurrentNode_Replay = m_CurrentNode_Replay->prev;
        if ( m_CurrentNode_Replay == 0) {
            m_CurrentNode_Replay = m_Replay_Head;
        }
    }
}
//上一步
void IMAGE_SYSTEM::replay_forward()
{
    if ( m_Replay_Head == 0) return;

    if (  m_CurrentNode_Replay == 0) {
        collapseImageNode(m_Replay_Head);
        m_CurrentNode_Replay = m_Replay_Head;
    } else {
        m_CurrentNode_Replay->flg_explored = true;
        m_CurrentNode_Replay = m_CurrentNode_Replay->next;
        if (m_CurrentNode_Replay==0) {
            m_CurrentNode_Replay = m_Replay_Tail;
        }
    }
}