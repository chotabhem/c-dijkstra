#include <stdio.h>
#define MAX 50
#define LENGTH 50
#define INFINITE 999999

void getEdgeAndCost(char nodes[][LENGTH],int costs[][MAX],int count);
void findPath(char nodes[][LENGTH],int costs[][MAX],int count);
void printPath(char nodes[][LENGTH],int valueParent[][3],int startIndex);
void showTable(char nodes[][LENGTH],int valueParent[][3],int count);

int main(){
    int i,j,flag;
    int nodeCount;
    char nodes[MAX][LENGTH];
    int costs[MAX][MAX]={0};

    printf("Enter a node count : ");
    scanf("%d",&nodeCount);

    for(i=0;i<nodeCount;i++){
        printf("enter node name:");
        scanf(" %s",&nodes[i]);
    }
    
    getEdgeAndCost(nodes,costs,nodeCount);
    findPath(nodes,costs,nodeCount);

    return 1;
}

void getEdgeAndCost(char nodes[][LENGTH],int costs[][MAX],int count){
    int i,j,cost,n1,n2,flag=1;

    printf("Use node numbers instead of node names:\n");
    for(i=0;i<count;i++){
        printf("\t%s [%d]\n",nodes[i],i+1);
    }
    printf("\nEnter connected node pairs only once. like only (A,B) or only (B,A)\nEnter '0' for exit\n\n");

    while(n1 != 0 || n2 != 0 ){
        printf("Enter a number of first node :");
        scanf("%d",&n1);
        printf("Enter a number of second node :");
        scanf("%d",&n2);
        printf("Enter a cost :");
        scanf("%d",&cost);
        costs[n1-1][n2-1] = cost;
        costs[n2-1][n1-1] = cost;
    }
    
    // print connected nodes & cost table
    
    printf("\n      ");
    for(i=0;i<count;i++)
    printf(" {%s}  ",nodes[i]);
    printf("\n"); 
    for(i=0;i<count;i++){
        printf(" {%s} |",nodes[i]);
        for(j=0;j<count;j++){
            printf(" [%d] |",costs[i][j]);
        }
        printf("\n");    
    }
    printf("\n");
}

void findPath(char nodes[][LENGTH],int costs[][MAX],int count){
    int i,j,k,start,stop,minValue,index=1,newCost;
    
    // [x][0] -> node value
    // [x][1] -> node parent
    // [x][2] -> is node explored (0: False 1: True)
    int valueParent[MAX][3];
    
    for (i=0;i<count;i++){
        valueParent[i][0]= INFINITE;
        valueParent[i][1]= -1;
        valueParent[i][2]= 0;
    }

    printf("Choose starting node: ");
    scanf("%d",&start);
    printf("Choose finishing node: ");
    scanf("%d",&stop);
    valueParent[start-1][0]= 0;
    printf("\n");

    // process
    for(k=0;k<count;k++){

        // find min value and node index
        minValue = INFINITE;
        for(i=0;i<count;i++){
            if( valueParent[i][0] < minValue && valueParent[i][2] ==0){
                index = i;
                minValue = valueParent[i][0];
            }
        }
        
        // current Node's name printed
        printf("-----------------\nScanning for [%s]\n-----------------\n",nodes[index]);

        for(j=0;j<count;j++){
            //If node has a connection with other nodes cost has to be different from zero
            if(costs[index][j] != 0){
                printf("\t\t-> [%s]\n",nodes[j]);
                newCost = valueParent[index][0] + costs[index][j];

                if( newCost < valueParent[j][0] ){
                    printf("update value and parent\n");
                    valueParent[j][0]= newCost;
                    valueParent[j][1]= index; 
                    
                }
                else{
                    printf("skipped\n");
                }
            }
        }
        // update node status : <Explored>
        valueParent[index][2] = 1;

        // show value-parent table
        showTable(nodes,valueParent,count);
    }

    // We use (stop-1) because the finishing node number is "3" but its index "2"
    printPath(nodes,valueParent,stop-1);
}

void printPath(char nodes[][LENGTH],int valueParent[][3],int startIndex){
    int nextParent = valueParent[startIndex][1] ;

    if( nextParent == -1 ){
        printf("%s-",nodes[startIndex]);
        return;
    }
    
    printPath(nodes, valueParent, nextParent);
    printf("%s-", nodes[startIndex]);
}

void showTable(char nodes[][LENGTH],int valueParent[][3],int count){
    int i;
    
    printf("\n~~~~~~~~~~~~~~~~~\n");
    for (i=0; i<count; i++){
            printf("%s -> %d ",nodes[i],valueParent[i][0]);
            if(valueParent[i][2] ==1){
                printf("-> Explored\n");
            }
            else{
                printf("->   ----  \n");
            }
        }
    printf("~~~~~~~~~~~~~~~~~\n\n");    
}
