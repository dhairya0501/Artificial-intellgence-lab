#include<cstdlib>
#include<iostream>
#include<vector>

using namespace std;
int b,m,count1=0,count2=0;
struct node
{
	int val;
	int alpha;
	int beta;
	int x;
	int next;
	struct node **children;
};

struct node* build_GameTree(int b,int m) //b is the branching factor and m is the depth
{
	int i;
	struct node *root=(struct node*)malloc(sizeof(struct node));
	count1++;
	if(m!=1)
	{
		root->children=(struct node**)malloc(b*sizeof(struct node*));
		root->val=-99;
		for(i=0;i<b;i++)
		{
			root->children[i]=(struct node*)malloc(sizeof(struct node));
			root->children[i]=build_GameTree(b,m-1);
		}
	}
	else
	{
		root->val=(rand()%100);
		root->children=NULL;
		printf(" %d" ,root->val);
	}
	printf("\n");
	return root;
}

int minimax(struct node *GameTree)
{
	int i;
	if(GameTree->children==NULL)
		return GameTree->val;
	else
	{
		for(i=0;i<b;i++)
		{
			if(GameTree->val==-99)
				GameTree->val=minimax(GameTree->children[i]);
			if(GameTree->children[i]->val==-99)
				GameTree->children[i]->val=minimax(GameTree->children[i]);
			if(GameTree->x==1 && GameTree->val<=GameTree->children[i]->val)
			{
				GameTree->val=GameTree->children[i]->val;
				GameTree->next=i;
			}
			if(GameTree->x!=1 && GameTree->val>=GameTree->children[i]->val)
			{
				GameTree->val=GameTree->children[i]->val;
				GameTree->next=i;
			}
		}
	return GameTree->val;
	}
}

int AlphaBetaprune(struct node *GameTree)
{
	count2++;
	if(GameTree->children==NULL)
		return GameTree->val;	
	else
	{
		int i=0;
		while (i<b && GameTree->beta>=GameTree->alpha)
		{
			if(GameTree->val=-99)
			{
				GameTree->children[i]->alpha=GameTree->alpha;
				GameTree->children[i]->beta=GameTree->beta;
				GameTree->children[i]->val=AlphaBetaprune(GameTree->children[i]);
			}
			if(GameTree->children[i]->val==-99)
			{
				GameTree->children[i]->alpha=GameTree->alpha;
				GameTree->children[i]->beta=GameTree->beta;
				GameTree->children[i]->val=AlphaBetaprune(GameTree->children[i]);
			}
			if(GameTree->x==1 && GameTree->val<=GameTree->children[i]->val)
			{
				GameTree->val=GameTree->children[i]->val;
				GameTree->next=i;
				GameTree->alpha=GameTree->val;
			}
			if(GameTree->x!=1 && GameTree->val>=GameTree->children[i]->val)
			{
				GameTree->next=GameTree->children[i]->val;
				GameTree->beta=GameTree->val;
				GameTree->next=i;
			}
			i++;
		}
	}
	return GameTree->val;
}

void depth(struct node* GameTree)
{
	int i;
	if(GameTree->children!=NULL)
	for(i=0;i<b;i++)
	{
		GameTree->children[i]->x=1-GameTree->x;
		depth(GameTree->children[i]);
	}
}

void OptimalPlay(struct node *GameTree)
{
	if(GameTree->x==1)
		printf("MAX: %d\n",GameTree->val);
	else
		printf("MIN: %d\n",GameTree->next);
	if (GameTree->children!=NULL)
		OptimalPlay(GameTree->children[GameTree->next]);
}

int main()
{
	printf("Enter the branching factor and depth of the tree\n");
	scanf("%d %d",&b,&m);
	struct node *root=build_GameTree(b,m);
	//printf("PP");
	root->x=1; //set root as MAX player
	root->alpha=-1000;
	root->beta=1000;
	depth(root);
	//printf(" PP ");
	printf(" %d \n",AlphaBetaprune(root));
	//printf(" PP ");
	printf(" %d \n",minimax(root));
	//printf(" PP ");
	OptimalPlay(root);
	//printf(" PP ");
	printf("NODES PRUNED %d \n", count2-count1);
	return 0;
	
}
