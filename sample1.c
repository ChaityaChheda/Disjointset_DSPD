#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
typedef enum {FAILURE,SUCCESS} statuscode;


typedef struct disjoint_tag
{
	int data;
	int rank;
	struct disjoint_tag *parent;
}disjoint_set;

//Array node ; It is the array where every node has the number and pointer to the disjoint_set node containing that number;
typedef struct arraynode_tag
{
    int data;
    disjoint_set *node;
}arraynode;

// Creating a node and initialising it 
disjoint_set * makeset(int data)
{
	disjoint_set *ptr;
	ptr=(disjoint_set*)malloc(sizeof(disjoint_set));
	ptr->data=data;
	ptr->rank=0;
	ptr->parent=NULL;
return ptr;
}

disjoint_set * FindParent(disjoint_set *node)
{
	
	if(node->parent == NULL)
	return node;
	else
	{
		FindParent(node->parent);
	}
}
		
	

statuscode UnionOfSet(int val1,int val2,arraynode array[])
{
	statuscode sc=SUCCESS;
	int i,flag1=0,flag2=0;
	disjoint_set *node1,*node2;
	
	for(i=0;i<SIZE && (flag1==0 || flag2==0) ;i++)
	{
		if(array[i].data==val1)
		{
			node1 = array[i].node;
			flag1=1;
		}
		if(array[i].data==val2)
		{
			node2 = array[i].node;
			flag2=1;
		}
	}
	

	disjoint_set *parent1,*parent2;
	parent1=FindParent(node1);
	parent2=FindParent(node2);
	
	
	if(parent1->data==parent2->data)
	{
		sc=FAILURE;
	}
	
	if(parent1->rank >= parent2->rank)
	{
		if(parent1->rank == parent2->rank)
		{
			parent1->rank = (parent1->rank)+1;
			
		}
		parent2->parent = parent1;
	}
	else
	{
		parent1->parent = parent2;
	}

return sc;
}
		
			
// Heap sort Algo follows:

void InsertHeap(arraynode array[],int low,int high,arraynode key)
{
    int large;
    large=2*low+1;done=0;
    while((large<high)&&(done==0))
    {
        if((large<high)&&(array[large].data<array[large+1].data))
        {
            large++;
        }
        if (array[large].data < key.data)
        {
            done =1;
        }
        else
        {
            array[low]=array[large];
            low=large;
            large =2*low+1;
        }
        array[low]=key;
    }
    
    
}
void BuildHeap (arraynode array[],int n)
{
    int low;
    for(low= (n/2)-1;low>=0; low--)
    {
        InsertHeap(array,low,n-1,array[low]);
    }
}
void Sort(arraynode array[],int n)
   {
       int pos; 
       arraynode current;
       BuildHeap(array,n);
       for(pos =n-1;pos>=1;pos--)
       {
           current=array[pos];
           array[pos]=array[0];
           InsertHeap(array,0,pos-1,current);
           
       }
   }


disjoint_set * BinSearch(arraynode array[], int n , int x)
{
    int low,high,mid,found;
    disjoint_set *retval;
    low=0;high=n-1;found=0;
    while(low <= high && found == 0)
    {
        mid =(low+high)/2;
        if (x==array[mid].data)
        {
            found =1;
            retval = array[mid].node ;
        }
        else if (x<array[mid].data)
        {
            high=mid-1;    
        }
        else
        {
            low = mid+1;
        }
    }
    return retval;
}

void listunion(arraynode array[],int n,arraynode array1[],int m)
{
	int i=0,j=0,k=0;
	arraynode result[m+n];
	while(i<n && j<m)
	{
		if(array[i].data < array1[j].data)
		{
			result[k]=array[i];
			k++;i++;
		}
		else if (array[i].data > array1[j].data)
		{
			result[k]=array1[j];
			k++;j++;
		}
		else
		{
			result[k]=array1[j];
			k++;j++;i++;
		}
	}
	while(i<=n)
	{
		result[k]=array[i];
			k++;i++;	
	}
	while(j<=m)
	{
		result[k]=array1[j];
			k++;j++;
	}
	//print result
	
}

void listintersection(arraynode array[],int n,arraynode array1[],int m)
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if(array[i].data < array1[j].data)
		{
			i++;
		}
		else if (array[i].data > array1[j].data)
		{
			j++;
		}
		else
		{
			result[k]=array1[j];
			k++;j++;i++;
		}
	}
	
	//print result
	
}

// array - array1
void listdifference(arraynode array[],int n,arraynode array1[],int m)
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if(array[i].data < array1[j].data)
		{
			result[k]=array[i];
			k++;i++;
		}
		else if (array[i].data > array1[j].data)
		{
			j++;
		}
		else
		{
			j++;i++;
		}
	}
	while(i<n)
	{
		result[k]=array[i];
		k++;i++;	
	}
	//print result ;
	
}

void listsymdiff(arraynode array[],int n,arraynode array1[],int m)
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if(array[i].data < array1[j].data)
		{
			result[k]=array[i];
			k++;i++;
		}
		else if (array[i].data > array1[j].data)
		{
			result[k]=array1[j];
			k++;j++;
		}
		else
		{
			j++;i++;
		}
	}
	while(i<=m)
	{
		list3[k]=list1[i];
			k++;i++;	
	}
	while(j<=n)
	{
		list3[k]=list2[j];
			k++;j++;
	}
	//print result
	
}


int main()
{

	statuscode sc;
	disjoint_set *ptr,*node,*ptr1,*ptr2;
	arraynode array[1000],array1[1000];	
	int n,option,option1,m,i,val1,val2,data;
	printf("enter the number of elements to be read\n");
	scanf("%d",&n);
	printf("enter elemnts in disjoint set");
	for(i=0;i<n;i++)
	{
		scanf("%d",&data);
		array[i].node=makeset(data);
	    array[i].data=data;
	}
	Sort(array,n);
	option = 0;
	while(option != -1)
	{
	    printf("1.Union\n2.Find Parent of Element\n3.Find if 2 Elements Present in same set\n4.Give 2nd list and implement set operations\n5.Exit\n");
    	scanf("%d",&option);
        switch(option)
    	{
    	    case 1:printf("Enter 2 numbers\n");
    	            scanf("%d %d",&val1,&val2);
    	            sc = UnionOfSet(val1,val2,array);
    	            if(sc==0)
    	                printf("Elements are already in same set\n");
    	            else
    	                printf("Union operation successful\n");
    	            break;
    	   case 2:printf("Enter a number\n");
    	            scanf("%d",&val1);
    	            node = BinSearch(array,n,val1);
    	            ptr=FindParent(node);
    	            printf("%d\n",ptr->data);
    	            break;
    	   case 3:printf("Enter 2 numbers\n");
    	          scanf("%d %d",&val1,&val2);
    	          node = BinSearch(array,n,val1);
    	          ptr1 = FindParent(node);
    	          node = BinSearch(array,n,val2);
    	          ptr2 = FindParent(node);
    	           if(ptr1->data == ptr2->data)
    	                printf("They are in same set \n");
    	           else
    	                printf("They are in different set\n");
    	           break;
    	   case 4:printf("enter the number of elements to be read\n");
				scanf("%d",&m);
				printf("enter elemnts in disjoint set");
				for(i=0;i<m;i++)
				{
					scanf("%d",&data);
					array1[i].node=makeset(data);
	    			array1[i].data=data;
				}
				Sort(array1,m);
				option1 = 0;
				while(option1 !=-1)
				{
					printf("1.list union\n2.list intersection\n3.list difference\n4.list symmetric difference\n");
					scanf("%d",&option1);
					switch(option1)
					{
						case 1: listunion(array,n,array1,m);
						break;
						case 2: listintersection(array,n,array1,m);
						break;
						case 3: listdifference(array,n,array1,m);
						break;
						case 4: listsymdiff(array,n,array1,m);
						break;
						default:option1=-1;
					}
				}
    	       break;
    	   default: option=-1;
    	}
	}

}
