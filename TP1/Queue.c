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
    printList();    
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
    else{
        printf("Erro ao remover da fila");
    }
    printf("Dequeue %d \n",personId);
    printList();
}

void printList(){
    for(int i =0; i < position; i++){
        printf("Person Id: %d ", list_t[i].personId);
        printf("Position Id: %d \n", list_t[i].position);
    }
}

bool checkPartnerOnTheList(int id){
    int partnerId = partners[id];
    bool partnerExist = false;

    for(int i =0; i<position; i++){
        if(list_t[i].personId == partnerId)
            partnerExist = true;
    }
    return partnerExist;
}

void setScore(){
    int score = 0;
    int biggest = 0;
    int nextId = -1;

    for(int i =0; i<position; i++)
    {   
        score = 0;

        bool partnerI = checkPartnerOnTheList(list_t[i].personId);

        if(partnerI)
            score = score + 10;    

        for(int j =0; j<position; j++)
        {
            bool partnerJ = checkPartnerOnTheList(list_t[j].personId);

            if(partnerI && partnerJ) 
                score =  score + prioritiesq[list_t[i].personId][list_t[j].personId];
            else if(!partnerI && !partnerJ)
                score =  score + prioritiesq[list_t[i].personId][list_t[j].personId];
        }

        list_t[i].score = score;
        // printf("Score: %d\n",list_t[i].score);            
    }
}

int getHighestScoreId(){
    setScore();
    int highestScore = 0;
    int highestScoreId = -1;

    for(int i =0; i<position; i++){
        // printf("Score: %d\n",list_t[i].score);
        if(list_t[i].score > highestScore){
            highestScore = list_t[i].score;
            highestScoreId = list_t[i].personId;
        }
        else if(list_t[i].score == highestScore){
            highestScoreId = -1;
            // printf("Queue:")
            // printList();
            // printf("end\n")
        }
    }

    return highestScoreId;
}

getRandon(){
    int personId = list_t[(int)(position*drand48())].personId;
    return personId;
}


// void main(int argc, char *argv[]){
//     queue(2);
//     queue(1);
//     queue(0);

//     setScore();
//     printf("Highest Score Id: %d\n",getHighestScoreId());

// }