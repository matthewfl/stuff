#include <stdlib.h>
#include <stdio.h>

int lll=0;

void compute(int height, int width) {
  for(int at=0; at < height*width; at++) {
    // check if it already did this element, move along diagonal
    if(at % width < at / height) continue;
    int next = at;
    // current x = at % width, y = at / height
    while(at < height*width) {
      next = (next / height) + (next % width) * height;
      if(next == at) break; // do compute this value
      if(next < at) { next = ++at; } // not a good value
      printf("%d, %d, %d \n", next, (next / height) , (next % width));
      //if(lll++ > 1000) exit(0);
    }
    if(at >= height*width) return;

    int from = at;
    int target;
    printf("%d ", from);
    while(1) {
      target = (from / height) + (from % width) * height;
      if(target <= at) break;
      printf("%d ", target);
      from = target;
    }
    printf("\n");
  }
}

int main () {
  compute(40,41);

}
