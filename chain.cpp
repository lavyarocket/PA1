#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the curr Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
 clear();   
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
   
   if(p == NULL) {
     head_ = new Node(ndata);
     length_++;
     return head_;
   }
   else if(p->next == NULL) {
    Node *tmp = new Node(ndata);
     p->next = tmp;
     tmp->prev = p;
     tmp->next = NULL;
     length_++;
     return tmp;
   }
   else {
     Node* tmp = new Node(ndata);
     tmp->next = p->next;
     p->next = tmp;
     tmp->prev = p;
     tmp->next->prev =tmp;
     length_++;
     return tmp;    
   }  
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {

  if (p == NULL || q == NULL || p == q) {
    return;
  }
  if (p == head_) {
    head_ = q;
  } 
  else if (q == head_) {
    head_ = p;
  }
  Node *prev_node_q = q->prev;
  Node *next_node_q = q->next;
  Node *prev_node_p = p->prev;
  Node *next_node_p = p->next;
  if (next_node_p != NULL && next_node_p != q) {
    next_node_p->prev = q;
  }
  if (prev_node_p != NULL && prev_node_p != q) {
    prev_node_p->next = q;
  }
  if (next_node_q != NULL && next_node_q != p) {
    next_node_q->prev = p;
  }
  if (prev_node_q != NULL && prev_node_q != p) {
    prev_node_q->next = p;
  }
  if (q->next == p) {
    q->next = next_node_p;
    p->prev = prev_node_q;
    p->next = q;
    q->prev = p;
  } else if (p->next == q) {
    p->next = next_node_q;
    q->prev = prev_node_p;
    p->prev = q;
    q->next = p;
  } 
  else {
    p->next = next_node_q;
    p->prev = prev_node_q;
    q->next = next_node_p;
    q->prev = prev_node_p;
  }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * curr Chain class.
 */

void Chain::clear() {
Node *curr = head_;
  Node *elem = curr;
  while (curr != NULL) {
    elem = curr->next;
    delete curr;
    curr = elem;
  }
  length_ = 0;
}

/**
 * Makes the curr object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  head_ = new Node(other.head_->data);
  Node *curr = head_;
  Node *elem = other.head_->next;
  while (elem != NULL) {
    curr->next = new Node(elem->data);
    curr = curr->next;
    elem = elem->next;
  }
  length_ = other.length_;
}

/* Modifies the curr chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the max_distimum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */

void Chain::unscramble() {
  /* your code here */
  if (head_ == NULL || head_->next == NULL) {
    return;
  }
    int s  =0;
  int dist = 0;
  int indices = 0;
  Node *n5 = head_;
  while (n5 != NULL) {
    n5 = n5->next;
    s++;
  }
   double values[length_;
  Node *xD = head_;
  double distances[length_];
  n5 = head_;
  int counter1 = 0;
  int counter2 = 0;
  while(counter1<s) {
    while(counter2<s) {
      distances[counter2] = xD->data.distanceTo(n5->data);
      if (distances[dist] > distances[counter2] && n5 != xD) {
        dist = counter2;
      }
      xD = xD->next;
      counter2++;
    }
    values[counter1] = distances[dist];
    dist = 0;
    if (values[indices] < values[counter1]) {
      indices = counter1;
    }
    n5 = n5->next;
    xD = head_;
    counter1++;
  }
  for (int i = 0; i < indices; i++) {
    xD = xD->next;
  }
  swap(head_, xD);
  if (s == 2) {
    return;
  }
  dist = 1;
  n5 = head_;
  xD = head_->next;
  Node *correct = head_;
  for (int i = 0; i < s-1; i++) {
    dist = i+1;
    for (int j = i+1; j < s; j++) {
      distances[j] = n5->data.distanceTo(xD->data);
        if (distances[dist] >= distances[j]) {
          dist = j;
          correct = xD;
        }
      xD = xD->next;
    }
    swap(n5->next, correct);
    n5 = n5->next;
    xD = n5->next;
  }
}
