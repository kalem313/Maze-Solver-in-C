 ///////////////////////////////////////////////////////////
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
//$							$//
//$ 	Μάης Σπυρίδων:2022201400112	        	$//									 
//$                                           		$//									 
//$ 	Καλεμκερίδης Ευάγγελος Ραφαήλ:2022201600058	$//
//$					         	$//
//$							$//
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
///////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>



//This is our maze double linked list
typedef struct list{
	
	//list variables
	int visited;
	char block;
	
	//list node connections
	struct list* up;
	struct list* down;	
	struct list* left;
	struct list* right;
		
}maze;

//recursion algorithm function
maze* Pathfinding_Algorithm(maze* node, maze* previous, maze* exit);


int main(){
	
	
	
	//list pointers
	maze* node = NULL;
	maze* head = NULL;
	maze* row_ptr = NULL;
	maze* row_start_ptr = NULL;
	maze* entrance = NULL;
	maze* exit = NULL;
	maze* previous = NULL;

	
	
	char c[10];
	int columns=0,rows=0, i, j;
	char ch;
	
	
	
	//create and open file
	FILE* file = NULL;
	file = fopen("maze.txt", "r+");
	
	
	
	
	
	
	//check if file is created
	if(file == NULL){
		printf("The file maze.txt has not been found\n\n");
		return 0;
	}
	
	
	
	
	
	
	
	
	
	//Find the columns number
	fgets(c,10,file);
	columns = strlen(c) - 1;
	
	
	
	
	
	
	
	
	//Find the rows number
		
		//return file pointer to start of file
	fseek(file, 0, SEEK_SET);
	
		
		//count number of rows
	do{
      ch = fgetc(file);
      if ( ch == '\n'){
         rows++;
	  }
        
   	} while (ch != EOF);
   	rows++;
   	
   	
   	
   	
   	
   	//start of list
   	node = (maze*)malloc(sizeof(maze));
   	if(node == NULL){
   		printf("Memory Allocation Failed. Program Terminated.\n");
   		return 0;
	}
   	head = node;
   	row_ptr = node;
   	row_start_ptr = node;
	
	
	//list node initialization of connection points   
   	node->up = NULL;
   	node->down = NULL;
   	node->left = NULL;
   	node->right = NULL;
   	   	
   	
   	//create and double-link first nodes of each row
   	for(i=1;i<rows;i++){
   		
		node->down  = (maze*)malloc(sizeof(maze));
		
		if(node == NULL){
   			printf("Memory Allocation Failed. Program Terminated.\n");
   			return 0;
		}
		
		node->down->up = node;
	
		
		//point to next node;
		node = node->down;    	  	
		node->left = NULL;
		node->right= NULL;
		node->down = NULL;
	}
	
	node = head;
   	
	printf("Rows = %d \n",rows);
	printf("Columns = %d \n",columns);
   	
	   
	   
	//create maze
   	//double-link maze horizontally
   	for(i=0;i<rows;i++){
   		
   		//create a row of list nodes
		for(j=1;j<columns;j++){
			
			//create next node and link to current node
			node->right = (maze*)malloc(sizeof(maze));
			//double-link the list nodes
			node->right->left = node;	
			//point to next node
			node = node->right;   		
			node->up = NULL;
			node->down = NULL;
			node->right = NULL;   		
		}	
		row_ptr = row_ptr->down ;
		node = row_ptr;
		
   		
	}
	


	//double-link maze vertically
	row_ptr = head;
	node = head->down;
	
	for(i=1; i<rows;i++){
		
		for(j=0;j<columns;j++){
			
			node->up = row_ptr;
			
		
		
			node->up->down = node;
	
			node = node->right;
	
			row_ptr= row_ptr->right;
	
			 
		}

	
			
		if(i == (rows - 1) ){
		
			break;
		}
		
		row_ptr = row_start_ptr->down;
		row_start_ptr= row_start_ptr->down;
		node = row_ptr->down;
			
	}
	
	
	//reset pointers position to start of list
	row_ptr = head;
	row_start_ptr = head;
	node = head;
	
	
	
	
	
	
	//return file pointer to start of file
	fseek(file, 0, SEEK_SET);
	
	
	
	
	//pass information about maze to list node variables

	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			node->block = fgetc(file);
			node->visited = 0;
			node = node-> right;
		}
		fgetc(file);
		node = row_ptr -> down;
		row_ptr = node; 
	}
	
	
	
	
	//reset pointers position to start of list
	row_ptr = head;
	row_start_ptr = head;
	node = head;
	
	
	
	

	

	
	while(node != NULL){
		
		
		if(node->block == '-'){
	
			
			if(entrance == NULL){
				
				entrance = node;
			}
			else{	
			
				exit = node;
		
			}
		}
	
		
		node = node->down;
	}
	

	node = head;  
	row_ptr = head;
	
	if(exit == NULL){
		
		
		//upper line check for exit
		for(i=1;i<columns;i++){
	
			node= node->right;
			if(node->block == '-'){
			
				exit = node;
				while(node->right != NULL){
					node = node->right;
				}
				break;
			}
		}

		
			
		//rightest column check for exit
		if(exit == NULL){
		
			for(i=1;i<rows;i++){
				node=node->down;
			
				if(node->block == '-'){
				
					exit = node;
				while(node->down != NULL){
					node = node->down;
				}
				break;
			}
			}
		}
		
		
		//bottom line check for exit
		if(exit == NULL){
	
			for(i=2;i<columns;i++){
				node= node->left;

			
				if(node->block == '-'){
					exit = node;
					break;
				}
			}
		}
	}
		
		
	node = head;
	row_ptr = head;	

	
	//print Maze
	printf("\n\n");
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			printf("%c",node->block);
			node = node-> right;
		}
		printf("\n");
		
		node = row_ptr -> down;
		row_ptr = node; 
	}
	printf("\n\n\n");
		
		
		//Anadromi
		node = entrance;
		row_ptr = head;
		previous = entrance;
	
		
		//Find the way through darkness
		if(exit == NULL){
			entrance->block = '-';
			printf("You shall not Pass the exit has been destroyed by Minotaur\n");
			free(row_ptr);
			free(node);
			free(entrance);
			free(exit);
			free(previous);
			free(row_start_ptr);
			free(head);
			return 0;
		}
		
		node =	Pathfinding_Algorithm(entrance,previous,exit);
		printf("\n\n\n");
	
		if(node == exit){
			printf("The path through the dark maze has been revealed and marked with 'O'\n");
			printf("Proceed with caution...beware beware the Minotaur Comes\n");	
		}			
		
	
	
		
		node = head;
		row_ptr = head;
	
	

	
	//print Maze

	printf("\n\n\n");
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			printf("%c",node->block);
			node = node-> right;
		}
		printf("\n");
		
		node = row_ptr -> down;
		row_ptr = node; 
	}
	
	row_ptr = head;
	node = head;
	
	
		
		//free list memory
		free(row_ptr);
		free(node);
		free(entrance);
		free(exit);
		free(previous);
		free(row_start_ptr);
		free(head);
	
		
		
		
	
	
	
   	
   	
   	
   	
   	
	
	
	

}







//function code
maze* Pathfinding_Algorithm(maze* node, maze* previous, maze* exit){
	
	char block_memory = node->block;
	maze* guide = node;

	node->visited = 1;
	node->block = 'O';
	
		
	if(node->up != NULL){
		if(node->up->visited == 0 && node->up->block == '-'){
			
			printf("going up\n");
			guide = node;
			node = node->up;
			node = Pathfinding_Algorithm(node,guide,exit);
		}
	}
	
	if(node->right != NULL){
		if(node->right->visited == 0 && node->right->block == '-'){
			printf("going right\n");
			guide = node;
			node = node->right;
			node = Pathfinding_Algorithm(node,	guide,exit);
		}
	}
	
	
	
	if(node->down != NULL){
		
		if(node->down->visited == 0 && node->down->block == '-'){
			printf("going down\n");
			guide = node;
			node = node->down;
			node = Pathfinding_Algorithm(node,	guide,exit);
		}
	}
	
	if(node->left != NULL){
		
		if(node->left->visited == 0 && node->left->block == '-'){
			printf("going left\n");
			guide = node;
			node = node->left;
			node = Pathfinding_Algorithm(node,	guide,exit);
		}
	}
	


	if(node == exit){
		
		return node;
	}
	
	else{
		guide->block = block_memory;
		printf("back\n");
		return previous;
	}
	
	
}
















