#include <stdio.h>
#include <STDLIB.H>
#include <STRING.H>
#include <MEMORY.H>
#include "WINDOWS.H"

typedef struct stTest
{
	int NodeNo;
	char *NodeName;
	struct stTest *pTail;
}stTest;

stTest *Root;

stTest *pfCreatNode()
{
	stTest *pstNodeForCreat;
	pstNodeForCreat = (stTest *)malloc(sizeof(stTest));
	pstNodeForCreat->NodeName = (char *)malloc(10 * sizeof(char));

	pstNodeForCreat->NodeNo = 0x00;
	memset(pstNodeForCreat->NodeName, 0x00, 10);
	pstNodeForCreat->pTail = NULL;

	return pstNodeForCreat;
}

void ReleaseNodeMemory(stTest *pstNodeForCreat)
{
	free(pstNodeForCreat->NodeName);
	pstNodeForCreat->NodeName = NULL;

	free(pstNodeForCreat);
	pstNodeForCreat = NULL;
}

stTest *InfoInputProc(int *NodeCnt)
{
	stTest *pstNode;

	pstNode = pfCreatNode();

	pstNode->NodeNo = ++(*NodeCnt);
	printf("Input Node Name(MAX = 10):");
	scanf("%s",pstNode->NodeName);
	printf("\n");

	return pstNode;
}

void DisplayInfoProc()
{
	stTest *pstNode;

	pstNode = Root;

	while(pstNode != NULL)
	{
		printf("\nThe Name of %dst Node is [%s]\n",pstNode->NodeNo, pstNode->NodeName);
		pstNode = pstNode->pTail;
	};

	if (NULL == Root)
	{
		printf("\nNothing can be displayed!!\n");
	}
}

void DeleteAllInfoProc()
{
	stTest *pstNode,*pstNextNode;

	pstNode = Root;
	pstNextNode = Root->pTail;

	while(NULL != pstNode)
	{
		ReleaseNodeMemory(pstNode);
		pstNode = pstNextNode;
		pstNextNode = pstNode->pTail;
	}
	
	Root = NULL;
}

void SeekInfoProc()
{
	stTest *pstNodeTmp;
	int i;
	
	printf("\nplease input which one you want to seek: ");
	scanf("%d", &i);

	pstNodeTmp = Root;

	while (NULL != pstNodeTmp)
	{
		if (i == pstNodeTmp->NodeNo)
		{
			printf("\nNode No is : %d\nNode Name is : %s\n", pstNodeTmp->NodeNo, pstNodeTmp->NodeName);
			break;
		}
		else
		{
			pstNodeTmp = pstNodeTmp->pTail;
			if (NULL == pstNodeTmp)
			{
				printf("\nNode NO %d is no exist!\n", i);
				break;
			}
		}
	}
}

void DeleteSglInfoProc(int *NodeCnt)
{
	stTest *pstNodeTmp,*pstLastNode;
	int i;
	
	printf("\nplease input which one you want to delete: ");
	scanf("%d", &i);
	
	pstNodeTmp = Root;
	pstLastNode = Root;
	
	while (NULL != pstNodeTmp)
	{
		if (i == pstNodeTmp->NodeNo)
		{
			printf("\nNode [%d] Node Name [%s] was deleted!!\n", pstNodeTmp->NodeNo, pstNodeTmp->NodeName);
			pstLastNode->pTail = pstNodeTmp->pTail;
			ReleaseNodeMemory(pstNodeTmp);
			pstNodeTmp = NULL;
		}
		else
		{
			pstLastNode = pstNodeTmp;
			pstNodeTmp = pstNodeTmp->pTail;
			if (NULL == pstNodeTmp)
			{
				printf("\nNode NO %d is no exist!\n", i);
			}
		}
	}
}

int main()
{
	stTest *CurrentNode,*LastNode;
	int LoopSwitch = TRUE;
	int NodeCnt = 0;
	char a = 0x00;

	Root = NULL;

	while(LoopSwitch)
	{
		fflush(stdin);
		printf("\nplease choose which operate to execute\n(1 = continue, 2 = stop, 3 = display, 4 = delete all, 5 = seek, 6 = delete single):  ");
		a = getchar();
		printf("\n");
		switch(a)
		{
			case '1':
				CurrentNode = InfoInputProc(&NodeCnt);
				if (1 == NodeCnt)
				{
					Root = CurrentNode;
				}
				else
				{
					LastNode->pTail = CurrentNode;
				}
				LastNode = CurrentNode;
				break;
			case '2':
				LoopSwitch = FALSE;
				printf("\nprogram will quit for 2s!!\n");
				if (NULL != Root)
				{
					DeleteAllInfoProc();
				}
				Sleep(2000);
				exit(0);
				break;
			case '3':
				DisplayInfoProc();
				break;
			case '4':
				if (NULL != Root)
				{
					DeleteAllInfoProc();
				}
				else
				{
					printf("\nNothing can be deleted!!\n");
				}
				break;
			case '5':
				if (NULL != Root)
				{
					SeekInfoProc(NodeCnt);
				}
				else
				{
					printf("\nNothing had been saved!!\n");
				}
				break;
			case '6':
				if (NULL != Root)
				{
					DeleteSglInfoProc(&NodeCnt);
				}
				else
				{
					printf("\nNothing had been deleted!!\n");
				}
				break;			
			default:
				break;
		}
	}
	
	return 0;
}