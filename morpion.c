#include <stdio.h>
#include <stdlib.h>

typedef struct _morpion* morpion;
typedef struct _morpion S_morpion;

struct _morpion{
  char data[9];
  int nb_free_spaces;// between 0-9
  char player; // 'O' 'X'
  char status;//'O' 'X' '.' '&'
};
//debeug the tableau char
void morpion_show_grid(morpion m){
  int i;
  for(i=0;i<9;i+=3){
    printf("%c %c %c         %d %d %d",m->data[i],m->data[i+1],m->data[i+2],i,i+1,i+2);
    if(i!=8)
      printf("\n");
  }
  // printf("The number of play is %d",m->nb_free_spaces);
  printf("\n");
}

//initialise the grid
void morpion_init_grid(morpion m){
  //initilise the morpion values
  m->nb_free_spaces=9;
  m->player='O';
  m->status='.';
  //initilise the data grid with '.'
  int i;
  for(i =0;i<9;i++){
    m->data[i]='.';
  }
  morpion_show_grid(m);
}

int morpion_get_input(morpion m){
  char cposition;
  int position;
  int ok=0;
  printf("The player %c , it is your turn to play.\n",m->player);
  while(ok==0){
    scanf(" %c",&cposition);
    position = cposition-'0';
    // printf("Position value %d",position);
    // if the position is not between 0 and 9
    if(position<0 || position>=9){
      printf("The position %c is not between 0-9. please enter a valid position.\n",cposition);
      continue;
    }
    // if the position you are in is used 
    if(m->data[position]!='.'){
      printf("The position %c is already used please enter an empty position.\n",cposition);
      continue;
    }
    ok=1;
  }
  return position;
  
}
void update_status(morpion m){
  if(m->nb_free_spaces==0){
    m->status='&';
    return;
  }
  if((m->player==m->data[0]&&m->player==m->data[4]&&m->player==m->data[8])
    ||(m->player==m->data[2]&&m->player==m->data[4]&&m->player==m->data[6])
    ||(m->player==m->data[0]&&m->player==m->data[1]&&m->player==m->data[2])
    ||(m->player==m->data[3]&&m->player==m->data[4]&&m->player==m->data[5])
    ||(m->player==m->data[6]&&m->player==m->data[7]&&m->player==m->data[8])
    ||(m->player==m->data[0]&&m->player==m->data[3]&&m->player==m->data[6])
    ||(m->player==m->data[1]&&m->player==m->data[4]&&m->player==m->data[7])
    ||(m->player==m->data[2]&&m->player==m->data[5]&&m->player==m->data[8])){
      m->status=m->player;
      return;
  }
}
void morpion_play(morpion m){

  while(m->status=='.'){
    //take the position
    int position = morpion_get_input(m);
    //put the choise of the player in the grid
    m->data[position]=m->player;
    //update the number of free places
    m->nb_free_spaces--;
    //show the grid
    morpion_show_grid(m);
    update_status(m);
    if(m->player=='O'){
      m->player='X';
    }else if(m->player=='X'){
      m->player='O';
    }
  }
  // printf("Status %c \n\n",m->status);
  if(m->status=='O'){
    printf("Congratulation!! The player O won.");
  }else if(m->status=='X'){
    printf("Congratulation!! The player X won.");
  }else if(m->status=='&'){
    printf("The game is draw.");
  }
  printf("\n");
  
}
int main(int argc, char* argv){
  S_morpion morpion;
  int pos;
  char input;
  printf("The Tic Tac Toe in c.\n");
  morpion_init_grid(&morpion);
  morpion_play(&morpion);
  return 0;
}