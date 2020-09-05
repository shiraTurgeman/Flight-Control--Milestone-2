//
// Created by noa on 17/01/2020.
//

#ifndef EXGIT__BESTFIRSTSEARCH_H_
#define EXGIT__BESTFIRSTSEARCH_H_

#include "Searcher.h"
#include <unordered_set>
#include <queue>
#include "list"
#include <stack>
#include <algorithm>


#include <queue>
#include <bits/unordered_set.h>
#include <algorithm>
#include "AbstractSearcher.h"
#include "State.h"

using namespace std;

/**
* class for bestFirstSearch
**/
template<class S>

struct compareCost {
  bool operator()(State<S> *const &p1, State<S> *const &p2) {
    return p1->getPathCost() > p2->getPathCost();
  }
};

template<class T>

class BestFirstSearch : public AbstractSearcher<T>  {

 private:
//variable for the algorithm
  int numOfVisitVertex;
  double sumCost;
  typename std::vector<State<T> *>::iterator it;
  bool found;
  list<State<T>*>* closed = new list<State<T>*>();
  list<State<T>*>* sortList = new list<State<T>*>();
  vector<State<T> *> vecOpen;
  priority_queue<State<T> *, vector<State<T> *>, compareCost<T>> side;
  priority_queue<State<T> *,
      vector<State<T> *>, compareCost<T>> sort;
  stack<State<T> *> forSave;
  State<T> *current;
  State<T> *start;
  State<T> *now;
  State<T> *checkMe;
  State<T> *returnThis;
  vector<State<T> *> adj;

 public:
  //template<class P>
  AbstractSearcher<T>* cloneMe()  {
    return new BestFirstSearch();
  }

  priority_queue<State<T> *, vector<State<T> *>, compareCost<T>> open;

  //check if this element is in the closed list
  bool inClose(State<pair<int,int>>* s){
    for (auto itr = closed->begin(); itr!=closed->end(); itr++){
      now = *itr;
      if (now==s){
        return true;
      }
    }
    return false;
  }
  //check if this element is in the open list
  bool inOpen(State<pair<int,int>>* s){
    for (int i = 0; i < open.size(); i++) {
      side.push(open.top());
      if (side.top() == now) {
        return true;
      }
    }
    return false;
  }

  //check if this node is a neighbor of current
  bool isIndex(State<T> *n, State<T> *cur) {
    if ((n->getI()==cur->getI())&&((n->getJ()==cur->getJ()+1)||(n->getJ()==cur->getJ()-1))){
      return true;
    }else if ((n->getJ()==cur->getJ())&&((n->getI()==cur->getI()+1)||(n->getI()==cur->getI()-1))){
      return true;
    }else{
      return false;
    }
  }

  //searches for the first element in the open list that is a neighbor of this current node
  State<T> *getFirstOnThatIsNeighbor(State<T> *n, State<T> *current) {
    State<T> *ret;
    while (!open.empty()) {
      ret = open.top();
      //if its isnt a neighbor
      if (!isIndex(ret,current)) {//keep taking element until you find one that match
        forSave.push(ret);
        open.pop();
      } else {//we found one that is a neighbor
        break;
      }
    }
    //pop the element we found from the open list - (thats why we used flag)
    //open.pop();
    while (!forSave.empty()) {//return all the elemets we poped out to open back
      open.push(forSave.top());
      forSave.pop();
    }
    return ret;
  }

  State<T>* search(Searchable<T> *s) override {

    //cout<<"best"<<endl;
    vector<vector<State<pair<int, int>>*>>  mat = s->getstateMatrix();
    int i;
    int j;
    for (i = 0; i < mat.size(); i++) {
      for (j = 0; j < mat[i].size(); j++) {
        this->initialize(mat[i][j]);
      }
    }

    // initial open
    State<T>* first = s->getInitialState();
    first->setPathCost(first->getCost());
    this->open.push(first);


    while (!this->open.empty()) {
// untill the queue isn't empty
      // get the most lower path cost.
      State<T>* n = this->open.top();
      this->open.pop();
      numOfVisitVertex++;
      this->visited.at(n) = BLACK;
      this->numOfNodes++;

      // check if it is the goal.
      if (n==s->getGoalState()){
        cout<<"return: "<<s->getGoalState()->getPathCost()<<endl;
        cout<<"num vertex"<<numOfVisitVertex;

        return s->getGoalState();
      }

      // get all the neighbors.
      vector<State<pair<int, int>>*> succerssors = (s->getAdj(n));
      for (State<T>* it : succerssors) { // check state's children.
        if (it->getCost() == -1){
          continue;
        }
        double currentPathCost = n->getPathCost() + it->getCost();
        // if s is not in open and not in closed.
        if (this->visited.at(it) == WHITE) {
          this->visited.at(it) = GRAY;
          it->setFather(n);
          it->setPathCost(currentPathCost);
          this->open.push(it);

        } else if (currentPathCost < it->getPathCost()) {
          it->setFather(n);
          it->setPathCost(currentPathCost);
          if (this->visited.at(it) == BLACK) {
            this->visited.at(it) = GRAY;
            this->open.push(it);
          }
        }
      }
    }
    return nullptr;
  }

  //get the number on nodes
  int getNumberOfNodesEvaluated() {
    return this->numOfVisitVertex;
  }

  bool isOnOpenOrClosed(State<T> *now) {
    //check if its on closed
    if (std::find(std::begin(closed), std::end(closed), now) != std::end(closed)) {
      return false;
    } else if (isOnOpen(now)) {
      return false;
    } else {
      return true;
    }
  };
  bool isOnOpen(State<T> *now) {
    //check if its on open
    for (int i = 0; i < open.size(); i++) {
      side.push(open.top());

      if (side.top() == now) {
        return true;
      }
    }
    return false;
  };


  State<T> *getB() {
    State<T> *ret;
    while (!open.empty()) {
      ret = open.top();
      if (!isIndex(ret)) {
        forSave.push(ret);
        open.pop();
      } else {
        break;
      }
    }
    open.pop();
    while (!forSave.empty()) {
      open.push(forSave.top());
      forSave.pop();
    }
    return ret;
  }
  double getCost(Searchable<T> *searchable, State<T> *startSer) {
    State<T> *check = search(searchable, startSer);
    double costThis = sumCost;
    return costThis;
  }



};

#endif //EXGIT__BESTFIRSTSEARCH_H_