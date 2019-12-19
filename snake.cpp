#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;


class snake{
  private:
  bool alive=true, passThrough;
  short length = 1;
  short L,B;
  pair<short, short> head;
  vector<pair<short, short> > tail;

  public:
    snake(pair<short, short> H,short L,short B,bool psst){
      this->head = H;
      this->L = L;
      this->B = B;
      passThrough = psst;
    }

  void move(char D){
    short i=head.first, j=head.second;
    pair<short,short> newhead;
    if(passThrough){
      if(D =='W' || D =='w' ){
        i=(L+i-1)%L;
      }
      else if(D =='S' || D =='s' ){
        i=(++i)%L;
      }
      else if(D =='A' || D =='a' ){
        j=(B+j-1)%B;
      }
      else if(D =='d' || D =='D' ){
        j=(++j)%B;
      }
      else{
        printf("invalid move");
        return;
      }
    }
    else{
      if(D =='W' || D =='w' ){
        i--;
      }
      else if(D =='S' || D =='s' ){
        i++;
      }
      else if(D =='A' || D =='a' ){
        j--;
      }
      else if(D =='d' || D =='D' ){
        j++;
      }
      else{
        printf("invalid move");
        return;
      }
    }
    tail.insert(tail.begin(),head);
    tail.pop_back();
    head.first=i; head.second=j;

    alive = find(tail.begin(), tail.end(), head) == tail.end();
  }

  void grow(pair<short,short> fruit){
  (this->tail).push_back(fruit);
  length++;
  }

  pair<short,short> getHead(){
    return head;
  }

  short getLength(){
    return length;
  }

  bool isTail(short i, short j){
    return find(tail.begin(), tail.end(), make_pair(i,j)) != tail.end();
  }

  bool isAlive(){
    return alive;
  }

};

class board{
  private:
    short R,C;
    char tp,bt,ver;
    bool **G;
    snake *python;
    bool automatic;

  public:
    board(short rows,short cols,bool mode,bool psst){
      R = rows;
      C = cols;
      if(psst){
        tp = '=';
        bt = '=';
        ver = '|';
      }else{
        tp = 220;
        bt = 223;
        ver = 219;
      }
      automatic = mode;
      G = new bool* [rows];
      for(short i=0;i<rows;i++){
        G[i] = new bool[cols];
        for (short j = 0; j < cols;j++){
          G[i][j] = false;
        }
      }
      short i = rand() % rows;
      short j = rand() % cols;
      pair<short,short> head(R-1, j);
      python=new snake(head,rows,cols,psst);

      i = rand() % rows;
      j = rand() % cols;
      G[i][j] = true;
    }
    
    void display(){
      auto border = [](short cols,char hor) {
        printf("@");
        for (short i = 0; i < cols;i++){
          printf("%c%c%c",hor,hor,hor);
        }
        printf("\b@\n");
        return;
      };
      system("cls");
       cout<<endl;
      border(C,tp);
      short x = python->getHead().first, y = python->getHead().second;
      for (short i = 0; i < R;i++){
        printf("%c",ver);
        for (short j = 0; j < C;j++){
          if (x==i && y==j){
            printf(" 0 ");
          }
          else if (G[i][j]){
            printf(" * ");
          }
          else{
             if(python->isTail(i,j)){
               printf(" o ");
               }
             else{
               printf("   ");
             }
          }
        }
        printf("\b%c\n",ver);
      }
      border(C,bt);
    }

    void pause(){
      display();
      printf("use 'W' 'S' 'A' 'D' to start\n");
      char cmd = getch();
      play(cmd);
    }

    void play(char cmd){
      while (1)
      {
        if(automatic){
          if(kbhit()){
            cmd = getch();
            if(cmd==' '){
              pause();
            }
          } 
        }
        else{
          cmd = getch();
        }
        python->move(cmd);
        pair<short, short> head = python->getHead();
        short i = head.first, j = head.second;

        if (! ( python->isAlive() && 0<=i && i<R && 0<=j && j<C )  ){
          printf("LOLOLOLOL..LOOSER\nGAMEOVER!\n");
          break;
        }
        if(G[i][j]){
          G[i][j] = false;
          pair<short, short> fruit(i,j);
          python->grow(fruit);
          do{
            i = rand() % R;
            j = rand() % C;
            head = make_pair(i, j);
          } while (head==python->getHead() || python->isTail(i,j));
          G[i][j] = true;
        }
        if(R*C==python->getLength()){
          printf("congrats!! you won!\n");
          break;
        }
        display();
      }
    }
};


int main(){
  char choice='r';
  do{
  short h, w;
  printf("scale:\n");
  printf("  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25\n");
  printf("Enter width of the board(minimum:7)\n");
  scanf("%d", &w);
  w = max((short)7, w);

  for (short i = 1; i < 9;i++){
    printf(" %d\n", i);
  }
  for (short i = 10; i < 26;i++){
    printf("%d\n", i);
  }
  printf("Enter height(minimum:7): ");
  scanf("%d", &h);
  h = max((short)7, h);
  printf("Pass through walls? 'Y':Yes, 'N':No  (default:Yes)\n");
  char PT = getch();
  bool psst=(PT!='N' && PT!='n');
  printf("Press A for auto forwarding snake, any other key for manual forwarding");
  char mode =getch();
  bool autom = (mode=='A' || mode=='a');
  board game(h,w,autom,psst);
  game.pause();
  printf("R: Restart, Q: Quit (default is Quit)\n");
  choice = getch();
  } while (choice=='r' || choice=='R');
  
  printf("Quitting... Have a nice day!");
  Sleep(1500);
  return 0;
}