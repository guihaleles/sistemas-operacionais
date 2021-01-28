#include "Person.c"

typedef struct Position_t
{
  int position;
  int score;
  int personId;
} Position_t;

int position = 0;
Position_t list_t[num_persons];

int prioritiesq[num_persons][num_persons] = {
    {1, 1, 0, 1, 1, 1, 1, 1}, //Sheldon    7
    {0, 1, 1, 1, 1, 1, 1, 1}, //Howard     7
    {1, 0, 1, 1, 1, 1, 1, 1}, //Leonard    7
    {0, 0, 0, 1, 1, 1, 1, 1}, //Stuart     5
    {0, 0, 0, 0, 1, 0, 0, 1}, //Amy        2
    {0, 0, 0, 0, 0, 1, 0, 1}, //Bernadette 2
    {0, 0, 0, 0, 0, 0, 1, 1}, //Penny      2
    {0, 0, 0, 0, 0, 0, 0, 1}  //Kripke     1
};

void queue(int personId){
    Position_t p;
    p.personId = personId;
    p.position = position;
    list_t[position] = p;
    position++;    
}

void deQueue(int personId){
    bool find = false;

    for(int i = 0; i< position ; i++){
        if(list_t[i].personId == personId)
            find = true;
        
        if(find){
            list_t[i] = list_t[i+1];
            list_t[i].position = i;
        }

    }

    if(find){
        position--;
    }
}

void printList(){
    for(int i =0; i < position; i++){
        printf("Person Id: %d ", list_t[i].personId);
        printf("Position Id: %d \n", list_t[i].position);
    }
}

int nextToUse(){
    bool priority;
    int nextId = -1;
    for(int i =0; i<position; i++)
    {   
        priority = true;    
        for(int j =0; j<position; j++)
        { 
           priority =  priority & (bool)prioritiesq[list_t[i].personId][list_t[j].personId];
           printf("Person ID:%d ",list_t[i].personId);
           printf("Person2 ID:%d ",list_t[j].personId);
           printf("Precedence:%d ",prioritiesq[list_t[i].personId][list_t[j].personId]);
           printf("Priority:%d\n", priority);
        }

        if(priority){
            if(nextId == -1)
                nextId = list_t[i].personId;
            else
                nextId = -1;    
        }
            
    }
    return nextId;
}

void main(int argc, char *argv[]){
    queue(7);
    queue(1);
    printList();
    printf("NextId: %d\n", nextToUse());

}