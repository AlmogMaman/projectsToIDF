#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

#define MIN_FRAME_NODE_INDEX 1

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

typedef struct gif
{
	FrameNode* firstNode;
	FrameNode* lastNode;
	int framesNodesSum;
}gif;


//gif's Functions:
void freeGif(gif* pGif);
void freeFrameNode(FrameNode* frameNode);
void addFrameNodeToGif(gif* pGif);
void mainAddFrameNodeToGif(gif* pGif, FrameNode* newNode);
FrameNode* createFrameNode();
void initFrameNodeByUser(FrameNode* newNode);
void removalFrameNodeFromGif(gif* pGif);
int mainRemovalFrameFromGif(gif* pGif, char* frameName);
void changeFramePosition(gif* pGif);
void mainChangingFramePosition(gif* pGif, FrameNode* preNode, FrameNode* movedNode, char* movedNodeName, unsigned int futureIndex);
FrameNode* findPreNodeByName(gif* pGif, char* frameName);
void findPreNodeByIndex(gif* pGif, unsigned int index, FrameNode** pPPreNode);
void tearNode(gif* pGif, FrameNode* preNode, char* frameName);
void printFramesList(gif* pGif);
FrameNode* findNodeByPreNode(FrameNode* preNode, char* frameName);
int isSuitable(gif* pGif, FrameNode* frameNode, unsigned int index);
void changeFrameDuration(gif* pGif);
void changeAllFramesDuration(gif* pGif);
void resetGif(gif* pGif);

#endif
