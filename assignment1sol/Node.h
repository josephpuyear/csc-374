/*--------------------------------------------------------------------------*
 *----									----*
 *----		Node.h							----*
 *----									----*
 *----	    This file declares the struct that stores an integer and	----*
 *----	a next-pointer to implement a node in a singly-linked list.	----*
 *----									----*
 *----	----	----	----	----	----	----	----	----	----*
 *----									----*
 *----	Version 1a					Joseph Phillips	----*
 *----									----*
 *--------------------------------------------------------------------------*/

struct	Node
{
  int		value_;
  struct Node*	nextPtr_;
};